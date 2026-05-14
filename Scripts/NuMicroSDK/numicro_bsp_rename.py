from __future__ import annotations

import argparse
import fnmatch
import io
import os
import sys
from pathlib import Path
from shutil import copy2

from numicro_bsp_clone import NUMICRO_BSPS, fetch_numicro_bsps


INCLUDES = ["*.c", "*.h"]
EXCLUDES = [
    "\\CMSIS\\",
    "\\FWUpdate\\",
    "\\SmartcardLib\\",
    "\\UsbHostLib\\",
    "\\SampleCode\\",
    "\\ThirdParty\\",
]
RENAME_PREFIX = "nu_"
OUTPUT_FOLDER_PREFIX = "RTT"
TEXT_FILE_EXTENSIONS = {".c", ".h", ".cpp", ".hpp"}
REPLACEMENT_MAP = {
    "\u2018": "'",
    "\u2019": "'",
    "\u201c": '"',
    "\u201d": '"',
    "\u3000": " ",
    "\uff0c": ",",
    "\uff1b": ";",
    "\uff08": "(",
    "\uff09": ")",
}


if sys.stdout.encoding != "utf-8":
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding="utf-8", errors="replace")


def normalize_for_match(path: Path) -> str:
    return "\\{}\\".format(str(path).replace("/", "\\").strip("\\"))


def should_include_file(path: Path) -> bool:
    path_str = normalize_for_match(path)
    if any(excluded in path_str for excluded in EXCLUDES):
        return False
    return any(fnmatch.fnmatch(path.name, pattern) for pattern in INCLUDES)


def rename_csource(path: Path) -> Path:
    new_path = path.with_name(RENAME_PREFIX + path.name)
    print("Rename {} -> {}".format(path, new_path))
    os.replace(path, new_path)
    return new_path


def rename_cheader(path: Path) -> Path:
    new_path = path.with_name(RENAME_PREFIX + path.name)
    old_header_guard = "__{}__".format(path.name.replace(".", "_").upper()).encode("ascii")
    new_header_guard = "__{}__".format(new_path.name.replace(".", "_").upper()).encode("ascii")
    content = path.read_bytes()
    content = content.replace(path.name.encode("ascii"), new_path.name.encode("ascii"))
    content = content.replace(old_header_guard, new_header_guard)
    new_path.write_bytes(content)
    path.unlink()
    print("Rename {} -> {}".format(path, new_path))
    return new_path


def rename_cheader_in_header_head(header_head: Path, original_name: str, renamed_name: str) -> Path:
    pattern = '"{}"'.format(original_name).encode("ascii")
    new_pattern = '"{}"'.format(renamed_name).encode("ascii")
    content = header_head.read_bytes().replace(pattern, new_pattern)
    header_head.write_bytes(content)
    print("Update include {} -> {} in {}".format(original_name, renamed_name, header_head))
    return header_head


def mirror_file(source: Path, relative_path: Path, output_root: Path) -> Path:
    destination = output_root / relative_path
    destination.parent.mkdir(parents=True, exist_ok=True)
    copy2(source, destination)
    return destination


def fix_file_content(file_path: Path) -> list[str]:
    try:
        original_content = file_path.read_text(encoding="utf-8", errors="replace")
    except OSError as exc:
        print("[ERR] Could not process {}: {}".format(file_path, exc))
        return []

    new_content = original_content
    changes_made: list[str] = []

    for char, replacement in REPLACEMENT_MAP.items():
        if char in new_content:
            count = new_content.count(char)
            new_content = new_content.replace(char, replacement)
            changes_made.append("Fixed {} instances of {!r}".format(count, char))

    if new_content != original_content:
        file_path.write_text(new_content, encoding="utf-8")

    return changes_made


def fix_output_tree(output_root: Path) -> int:
    if not output_root.exists():
        return 0

    fixed_count = 0
    for file_path in output_root.rglob("*"):
        if not file_path.is_file() or file_path.suffix.lower() not in TEXT_FILE_EXTENSIONS:
            continue

        changes = fix_file_content(file_path)
        if not changes:
            continue

        fixed_count += 1
        print("[FIXED] {}".format(file_path))
        for change in changes:
            print("        -> {}".format(change))

    return fixed_count


def process_repo(
    repo_root: Path,
    output_base: Path | str | None = None,
    *,
    output_prefix: str | None = None,
) -> None:
    item = repo_root.name.upper()
    bsp_header = repo_root / "Library" / "Device" / "Nuvoton" / item / "Include" / "{}.h".format(item)
    if not bsp_header.is_file():
        print("Skip {}: missing {}".format(item, bsp_header))
        return

    if output_base is None:
        output_base = Path(output_prefix or OUTPUT_FOLDER_PREFIX)
    else:
        output_base = Path(output_base)

    output_root = output_base / item
    header_destination = output_root / bsp_header.relative_to(repo_root / "Library")
    renamed_headers: list[tuple[str, str]] = []

    for source in repo_root.rglob("*"):
        if not source.is_file() or not should_include_file(source):
            continue

        if "Library" not in source.parts:
            continue

        relative_path = source.relative_to(repo_root)
        if relative_path.parts[0] != "Library":
            continue

        if len(relative_path.parts) < 2 or relative_path.parts[1] not in {"Device", "StdDriver"}:
            continue

        relative_path = Path(*relative_path.parts[1:])
        print("Mirror {}".format(source))
        mirrored_path = mirror_file(source, relative_path, output_root)

        if "StdDriver" not in str(mirrored_path):
            continue

        if mirrored_path.suffix == ".c":
            rename_csource(mirrored_path)
        elif mirrored_path.suffix == ".h":
            original_name = mirrored_path.name
            renamed_header = rename_cheader(mirrored_path)
            renamed_headers.append((original_name, renamed_header.name))

    if header_destination.exists():
        for original_name, renamed_name in renamed_headers:
            rename_cheader_in_header_head(header_destination, original_name, renamed_name)
    elif renamed_headers:
        print("Skip include updates for {}: missing {}".format(item, header_destination))


def iter_repo_paths(bsp_root: Path) -> list[Path]:
    if not bsp_root.exists():
        print("BSP root not found: {}".format(bsp_root))
        return []

    repo_paths = []
    for repo in NUMICRO_BSPS:
        repo_path = bsp_root / Path(repo["path"]).name
        if repo_path.exists():
            repo_paths.append(repo_path)
        else:
            print("Skip missing repo path {}".format(repo_path))
    return repo_paths


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Mirror/rename driver sources from existing NuMicro BSP repositories.",
    )
    parser.add_argument(
        "destination",
        nargs="?",
        default=".",
        help="Workspace root that already contains the bsp folder.",
    )
    parser.add_argument(
        "--bsp-root",
        default="bsp",
        help="Relative BSP folder under the destination root.",
    )
    parser.add_argument(
        "--output-prefix",
        default=OUTPUT_FOLDER_PREFIX,
        help="Base output folder used for generated BSP folders, for example RTT/M460.",
    )
    parser.add_argument(
        "--auto-fetch",
        action="store_true",
        help="Automatically clone/update BSP repositories when the BSP folder is missing.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    workspace_root = Path(args.destination).resolve()
    bsp_root = workspace_root / args.bsp_root

    repo_paths = iter_repo_paths(bsp_root)
    if not repo_paths:
        if args.auto_fetch:
            print("Auto-fetch enabled. Cloning BSP repositories into {}".format(workspace_root))
            fetch_numicro_bsps(workspace_root)
            repo_paths = iter_repo_paths(bsp_root)

        if not repo_paths:
            print("No BSP repositories found to rename.")
            print("Run 'python numicro_bsp.py' first, or point --bsp-root to an existing BSP folder.")
            return 0

    output_root = workspace_root / args.output_prefix
    for repo_path in repo_paths:
        process_repo(repo_path, output_root)

    fixed_count = fix_output_tree(output_root)
    if fixed_count:
        print("Processed {} files in output tree {}".format(fixed_count, output_root))
    else:
        print("No full-width character fixes needed in {}".format(output_root))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
