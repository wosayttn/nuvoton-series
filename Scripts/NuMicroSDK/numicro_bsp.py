from __future__ import annotations

import argparse
from pathlib import Path

import numicro_bsp_clone
import numicro_bsp_rename


fetch_numicro_bsps = numicro_bsp_clone.fetch_numicro_bsps
fix_output_tree = numicro_bsp_rename.fix_output_tree
iter_repo_paths = numicro_bsp_rename.iter_repo_paths
process_repo = numicro_bsp_rename.process_repo


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Clone/update NuMicro BSP repositories and then mirror/rename driver sources.",
    )
    parser.add_argument(
        "destination",
        nargs="?",
        default=".",
        help="Workspace root that contains or will contain the bsp folder.",
    )
    parser.add_argument(
        "--skip-fetch",
        action="store_true",
        help="Do not clone/pull repositories before processing them.",
    )
    parser.add_argument(
        "--bsp-root",
        default="bsp",
        help="Relative BSP folder under the destination root.",
    )
    parser.add_argument(
        "--output-prefix",
        default=numicro_bsp_rename.OUTPUT_FOLDER_PREFIX,
        help="Base output folder used for generated BSP folders, for example RTT/M460.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    workspace_root = Path(args.destination).resolve()
    bsp_root = workspace_root / args.bsp_root
    output_root = workspace_root / args.output_prefix

    if not args.skip_fetch:
        fetch_numicro_bsps(workspace_root)

    for repo_path in iter_repo_paths(bsp_root):
        process_repo(repo_path, output_root)

    fixed_count = fix_output_tree(output_root)
    if fixed_count:
        print("Processed {} files in output tree {}".format(fixed_count, output_root))
    else:
        print("No full-width character fixes needed in {}".format(output_root))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
