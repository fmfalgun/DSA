#!/usr/bin/env python3
"""Generates per-topic README.md files from prepClash's DSA-450 data.

Source of truth for problem names/topics: prepClash/prepclash/src/data/dsa450.ts
(the canonical 15-topic, 370-problem Love Babbar list). Real LeetCode URLs are
filled in only when a normalized-name match is found in prepClash's
data/lovebabbar/*.json arena files (a smaller curated subset with real URLs) -
no URL is ever guessed or constructed from a bare LeetCode number, since a
numeric ID alone doesn't reliably resolve to LeetCode's slug-based URLs.

Usage: python3 scripts/generate_topic_readmes.py /path/to/prepClash/prepclash
"""
import json
import re
import sys
from pathlib import Path

# dsa450.ts topic id -> our repo folder(s). Two folders means the sheet
# combines them (Stack & Queue, Searching & Sorting) but our repo splits them;
# both get the identical full list rather than guessing which half each
# problem belongs to.
TOPIC_TO_FOLDERS = {
    "array": ["Arrays"],
    "matrix": ["Matrix"],
    "string": ["StringAlgorithms"],
    "search": ["Sorting", "Searching"],
    "list": ["LinkedList"],
    "tree": ["Trees"],
    "bst": ["Trees"],
    "greedy": ["Greedy"],
    "backtrack": ["BackTracking"],
    "stack": ["Stack", "Queue"],
    "heap": ["Heaps"],
    "graph": ["Graphs"],
    "trie": ["Tries"],
    "dp": ["DynamicProgramming"],
    "bits": ["BitManipulation"],
}


def normalize(name: str) -> str:
    name = name.lower()
    name = re.sub(r"[^a-z0-9 ]", " ", name)
    return re.sub(r"\s+", " ", name).strip()


def parse_dsa450(ts_path: Path):
    text = ts_path.read_text()
    # name is single-quoted normally, but double-quoted when it contains an
    # apostrophe (e.g. "Kadane's Algo") - handle both.
    pattern = re.compile(
        r"\{\s*id:\s*'([^']+)',\s*topic:\s*'([^']+)',\s*name:\s*"
        r"(?:'((?:[^'\\]|\\.)*)'|\"((?:[^\"\\]|\\.)*)\"),\s*"
        r"diff:\s*'([^']+)'(?:,\s*lc:\s*(\d+))?\s*\}"
    )
    problems = []
    for m in pattern.finditer(text):
        pid, topic, name_sq, name_dq, diff, lc = m.groups()
        name = (name_sq if name_sq is not None else name_dq).replace("\\'", "'").replace('\\"', '"')
        problems.append(
            {"id": pid, "topic": topic, "name": name, "diff": diff, "lc": int(lc) if lc else None}
        )
    return problems


def parse_arena_urls(lovebabbar_dir: Path):
    lookup = {}
    for f in lovebabbar_dir.glob("*.json"):
        data = json.loads(f.read_text())
        for q in data.get("questions", []):
            lookup[normalize(q["name"])] = q["url"]
    return lookup


def render_problem(p, url_lookup):
    url = url_lookup.get(normalize(p["name"]))
    if url:
        return f"- [{p['name']}]({url}) — {p['diff']}"
    if p["lc"]:
        return f"- {p['name']} — {p['diff']} (LeetCode #{p['lc']}, link not verified)"
    return f"- {p['name']} — {p['diff']}"


MENTAL_MODEL_INTRO = """## Mental Model

A running checklist of patterns recognized across solved problems in this
topic, grouped by category. One section per pattern — append to the matching
section when a new problem reinforces it, add a new section when a genuinely
new pattern shows up. Scan this *before* coding a new problem: check whether
it matches a category below before reaching for a default approach.

Each entry links back to its full write-up in `notes/` for the deeper
reasoning.

---

*(empty — will fill in as problems in this topic are solved)*
"""


def render_readme(topic_display_name: str, problems: list, url_lookup: dict) -> str:
    lines = [f"# {topic_display_name}", "", "## Problems (Love Babbar DSA-450)", ""]
    lines += [render_problem(p, url_lookup) for p in problems]
    lines += ["", MENTAL_MODEL_INTRO]
    return "\n".join(lines)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(1)

    prepclash_root = Path(sys.argv[1])
    ts_path = prepclash_root / "src" / "data" / "dsa450.ts"
    lovebabbar_dir = prepclash_root / "data" / "lovebabbar"
    repo_root = Path(__file__).resolve().parent.parent / "lovebabbar-450dsa"

    all_problems = parse_dsa450(ts_path)
    url_lookup = parse_arena_urls(lovebabbar_dir)
    topic_names = {}
    text = ts_path.read_text()
    for m in re.finditer(r"\{\s*id:\s*'([^']+)',\s*name:\s*'([^']+)'\s*\}", text):
        topic_names[m.group(1)] = m.group(2)

    by_topic = {}
    for p in all_problems:
        by_topic.setdefault(p["topic"], []).append(p)

    matched = sum(1 for p in all_problems if normalize(p["name"]) in url_lookup)
    print(f"Parsed {len(all_problems)} problems, {matched} with a verified URL match.")

    # Accumulate by destination folder first - multiple dsa450 topic ids can
    # map to the same folder (tree+bst -> Trees) and must be merged into one
    # list instead of the later topic overwriting the earlier one.
    folder_problems = {}
    folder_topic_names = {}
    for topic_id, folders in TOPIC_TO_FOLDERS.items():
        problems = by_topic.get(topic_id, [])
        if not problems:
            continue
        display_name = topic_names.get(topic_id, topic_id)
        for folder in folders:
            folder_problems.setdefault(folder, []).extend(problems)
            folder_topic_names.setdefault(folder, []).append(display_name)

    written = []
    for folder, problems in folder_problems.items():
        display_name = " + ".join(dict.fromkeys(folder_topic_names[folder]))
        content = render_readme(display_name, problems, url_lookup)
        out_path = repo_root / folder / "README.md"
        out_path.parent.mkdir(parents=True, exist_ok=True)
        out_path.write_text(content)
        written.append(str(out_path.relative_to(repo_root)))

    print(f"Wrote {len(written)} README.md files:")
    for w in written:
        print(f"  {w}")
