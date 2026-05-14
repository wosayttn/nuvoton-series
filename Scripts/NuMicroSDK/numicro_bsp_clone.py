from __future__ import annotations

import argparse
import subprocess
from pathlib import Path
from typing import Iterable


NUMICRO_BSPS = [
    {
        "name": "BSP/M460",
        "path": "BSP/M460",
        "url": "https://github.com/OpenNuvoton/m460bsp",
        "branch": "master",
    },
    {
        "name": "BSP/M2354",
        "path": "BSP/M2354",
        "url": "https://github.com/OpenNuvoton/M2354BSP",
        "branch": "master",
    },
    {
        "name": "BSP/M480",
        "path": "BSP/M480",
        "url": "https://github.com/OpenNuvoton/M480BSP",
        "branch": "master",
    },
    {
        "name": "BSP/M2L31",
        "path": "BSP/M2L31",
        "url": "https://github.com/OpenNuvoton/M2L31BSP",
    },
    {
        "name": "BSP/M5531",
        "path": "BSP/M5531",
        "url": "https://github.com/OpenNuvoton/M5531BSP",
    },
    {
        "name": "BSP/M3331",
        "path": "BSP/M3331",
        "url": "https://github.com/OpenNuvoton/m3331bsp",
    },
    {
        "name": "BSP/M3351",
        "path": "BSP/M3351",
        "url": "https://github.com/OpenNuvoton/M3351BSP",
    },
]


def run_git(args: list[str], cwd: Path | None = None) -> None:
    command = ["git"] + args
    print("[git]", " ".join(command))
    subprocess.run(command, cwd=str(cwd) if cwd else None, check=True)


def clone_or_update_repo(repo: dict[str, str], destination_root: Path) -> Path:
    destination = destination_root / repo["path"]
    branch = repo.get("branch")

    if destination.exists():
        print("Updating {} -> {}".format(repo["name"], destination))
        run_git(["fetch", "--all", "--tags", "--prune"], cwd=destination)
        if branch:
            run_git(["checkout", branch], cwd=destination)
            run_git(["pull", "origin", branch], cwd=destination)
        else:
            run_git(["pull"], cwd=destination)
        return destination

    destination.parent.mkdir(parents=True, exist_ok=True)
    print("Cloning {} -> {}".format(repo["name"], destination))

    clone_args = ["clone"]
    if branch:
        clone_args.extend(["--branch", branch, "--single-branch"])
    clone_args.extend([repo["url"], str(destination)])
    run_git(clone_args)
    return destination


def fetch_numicro_bsps(
    destination_root: str | Path = ".",
    repositories: Iterable[dict[str, str]] | None = None,
) -> list[Path]:
    destination_root = Path(destination_root).resolve()
    repositories = list(repositories or NUMICRO_BSPS)
    results = []

    for repo in repositories:
        results.append(clone_or_update_repo(repo, destination_root))

    return results


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Clone or update NuMicro BSP repositories from GitHub.",
    )
    parser.add_argument(
        "destination",
        nargs="?",
        default=".",
        help="Destination root folder. Repository paths are created under this folder.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    fetched_paths = fetch_numicro_bsps(args.destination)
    print("Fetched {} repositories.".format(len(fetched_paths)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
