# DSA

- Learning + revision reference while working through Love Babbar's DSA-450 sheet, one problem (or one improvement) per branch and PR, even solo.
- Three top-level buckets, by what the content actually is:
  - [lovebabbar-450dsa/](./lovebabbar-450dsa/) — the active sheet. Once this is done, the plan is to move on to other sheets (Striver's A2Z/SDE, NeetCode 150, etc.), each getting its own sibling folder so they don't collide.
  - [non-450/](./non-450/) — topics that aren't part of Love Babbar's DSA-450 at all (theory reference only, not active work).
  - [theory/](./theory/) — generic concept/theory write-ups (not tied to any specific sheet — these predate the DSA-450 focus and were never actually the 450 list, so they're kept separate rather than mixed into either bucket above).
- [companies/](./companies/) holds real interview problems tied to a specific company — separate from all of the above, not gated by the checks below.
- Layout (per topic, under `lovebabbar-450dsa/`): `README.md` (curated DSA-450 problem list for that topic + growing mental-model section — see "Per-topic files" below), `codes/<name>.cpp` (source), `binary/<name>` (compiled output), `input/<name>.in` (sample input), `output/<name>.out` (expected output), `notes/<name>.md` (optional per-problem deep-dive).
- One-time local setup after cloning: `git config core.hooksPath .githooks`.

---

## DSA-450 Topics

Cross-checked against the canonical 15-topic breakdown (Array, Matrix, String, Searching & Sorting, Linked List, Binary Trees, BST, Greedy, BackTracking, Stack & Queue, Heap & Priority Queue, Graph, Trie, Dynamic Programming, Bit Manipulation) — folders here are split finer in places (e.g. Stack/Queue, Searching/Sorting as separate dirs) but cover the same ground. Each link goes to the topic's curated problem list; general theory for the same topic lives at the matching path under [theory/](./theory/).

- [Arrays](./lovebabbar-450dsa/Arrays/README.md)
- [Matrix](./lovebabbar-450dsa/Matrix/README.md)
- [Linked Lists](./lovebabbar-450dsa/LinkedList/README.md)
- [Stacks](./lovebabbar-450dsa/Stack/README.md)
- [Queues](./lovebabbar-450dsa/Queue/README.md)
- [Trees](./lovebabbar-450dsa/Trees/README.md) (covers Binary Trees + BST)
- [Heaps](./lovebabbar-450dsa/Heaps/README.md)
- [Graphs](./lovebabbar-450dsa/Graphs/README.md) + Graph Algorithms ([Traversal](./theory/GraphAlgorithms/Traversal/THEORY.md), [Shortest Path](./theory/GraphAlgorithms/ShortestPath/THEORY.md), [MST](./theory/GraphAlgorithms/MST/THEORY.md), [Topological Sort](./theory/GraphAlgorithms/TopologicalSort/THEORY.md) — theory only so far, no curated list yet)
- [Tries](./lovebabbar-450dsa/Tries/README.md)
- [Sorting](./lovebabbar-450dsa/Sorting/README.md)
- [Searching](./lovebabbar-450dsa/Searching/README.md)
- [BackTracking](./lovebabbar-450dsa/BackTracking/README.md)
- [Dynamic Programming](./lovebabbar-450dsa/DynamicProgramming/README.md)
- [Greedy](./lovebabbar-450dsa/Greedy/README.md)
- [Bit Manipulation](./lovebabbar-450dsa/BitManipulation/README.md)
- [String Algorithms](./lovebabbar-450dsa/StringAlgorithms/README.md)

Problem lists are generated from prepClash's `dsa450.ts` via `scripts/generate_topic_readmes.py` — rerun it if that source data changes. Links are only included where independently verified against prepClash's arena data; unverified entries list the name (and LeetCode number, if known) without a link rather than guessing one.

### Non-450 (Later Phases / Not in the Sheet)

Reference theory only for now, not active work (`THEORY.md` only — no `mental-model.md`/`notes/` yet):

- Later-sheet data structures: [Segment Trees](./non-450/SegmentTrees/THEORY.md), [Fenwick Trees](./non-450/FenwickTrees/THEORY.md), [Disjoint Set](./non-450/DisjointSet/THEORY.md), [Game Theory](./non-450/GameTheory/THEORY.md), [Advanced Data Structures](./non-450/AdvancedDataStructures/THEORY.md).
- Not a category in Love Babbar's DSA-450 at all, kept as general reference: [Recursion](./non-450/Recursion/THEORY.md) (backtracking split out into its own active topic above), [Hash Tables](./non-450/HashTables/THEORY.md), [Divide & Conquer](./non-450/DivideAndConquer/THEORY.md), [Mathematical Algorithms](./non-450/MathematicalAlgorithms/NumberTheory/THEORY.md).

See [Resources.md](./Resources.md) for books, courses, and practice platforms.

---

## Git workflow

- Start from an up-to-date master: `git checkout master && git pull`.
- Branch per unit of work, named per the convention below: `git checkout -b <type>/<slug>`.
- Write the solution in `<Topic>/codes/<name>.cpp`.
- Add a sample I/O pair for it: `<Topic>/input/<name>.in` and `output/<name>.out` — required even for structural problems (linked lists, trees, etc.); write a small driver that reads/builds/prints something testable.
- Add at least one comment stating your approach or any assumption the algorithm makes.
- If the problem taught you something worth keeping, capture it in `<Topic>/notes/<name>.md` — optional, not every problem needs it.
- Compile and self-test before staging: `g++ -O2 -std=c++17 <Topic>/codes/<name>.cpp -o <Topic>/binary/<name> && ./<Topic>/binary/<name> < <Topic>/input/<name>.in`.
- Review your own diff before staging: `git diff`.
- Stage only what you touched: `git add <files>`.
- Commit with a message naming the problem and the approach, not a date or "done".
  - Example: `git commit -m "Rotate array by d: reversal algorithm, O(n)"`.
  - The commit-msg hook (see below) will reject vague messages automatically.
- Push the branch: `git push -u origin <type>/<slug>`.
- Open a PR on GitHub — CI runs the checks below and must pass before merging.
- Merge once CI is green, then delete the branch from GitHub's merge screen.
  - Squash and merge — default choice; collapses messy in-progress commits (attempt/fix/final) into one clean commit.
  - Rebase and merge — use instead when the branch already has multiple separate, already-clean commits worth preserving individually.
  - Create a merge commit — skip this; it only adds merge-commit noise with no concurrent branches to reconcile.
- Sync back locally: `git checkout master && git pull && git branch -d <type>/<slug> && git fetch --prune`.

---

## Branch naming convention

Format: `<type>/<short-kebab-slug>`. Derived from [Conventional Commits](https://www.conventionalcommits.org)'s type vocabulary — this repo renames its one dominant type, `feat`, to `problem`, since every unit of real work here is solving one sheet problem.

| Type | Use for | Simple example |
|------|---------|-----------------|
| `problem` | Solving a new DSA-450 problem (this repo's `feat`) | `problem/rotate-array-by-d` |
| `fix` | Fixing a bug in an already-solved solution | `fix/linked-list-cycle-off-by-one` |
| `docs` | Documentation only, no code change | `docs/naming-convention-example` |
| `chore` | Maintenance/tooling/repo housekeeping | `chore/gitignore-compiled-binaries` |
| `refactor` | Restructuring a solution's code, same output | `refactor/split-bst-insert-into-functions` |
| `test` | Adding/improving a sample I/O pair only | `test/add-edge-case-for-empty-array` |
| `ci` | Changes to `.github/workflows/` or `scripts/` themselves | `ci/add-magic-number-check` |
| `perf` | Optimizing an existing solution, same output | `perf/optimize-sliding-window-loop` |
| `build` | Rarely needed here — no package manager/build system beyond `g++` directly | *(skip unless one actually comes up)* |

- One type per branch — a branch mixing `problem` work with unrelated `chore` cleanup should be two branches instead.
- If in doubt between `problem`/`fix`: `problem` solves something new, `fix` corrects a solution that already existed but was wrong.

---

## Automated checks (new/changed files only — old solutions are grandfathered)

- **Comment presence** — `scripts/check-comments.sh` fails if a file has zero comments.
- **Magic numbers** — `scripts/check-magic-numbers.sh` flags bare sentinel literals (`9999`, `1e9`, etc.) not backed by a named `const`/`#define`.
  - Silence a false positive by adding `// magic-ok` on that line.
- **Compile + sample test** — `scripts/run-tests.sh` compiles the file and diffs its output against `input/<name>.in`/`output/<name>.out`; fails if either is missing for a new file. Required for every file, including structural/no-natural-I/O problems — write a driver that makes the behavior observable.
- **Commit message** — `scripts/check-commit-msg.sh` rejects pure dates, `Auto-commit` placeholders, bare `problem N`, and anything under 12 characters.
- These run twice: locally via the `.githooks/pre-push` + `.githooks/commit-msg` hooks, and again in `.github/workflows/ci.yml` on every PR — the PR check is the one that actually blocks a bad merge.
- Scoped to any `*.cpp` file except `companies/**` — company-specific practice isn't gated by this setup.
- Rename-aware: pure file moves (e.g. shifting a legacy file into `codes/`) aren't treated as new files needing a test pair — only genuine additions/modifications are.
- Only files changed in the diff are checked, so pre-existing solutions are never retroactively blocked.

---

## Code-quality checklist (self-review at PR time — not machine-checkable)

- **Single responsibility** — once a solution is more than ~20 lines, split input parsing, the algorithm, and output formatting into separate functions instead of one long `main()`.
- **Comments explain *why*, not *what*** — a note on the approach ("two-pointer since array is sorted") beats restating the code in English; the automated check only confirms a comment exists, not that it's a good one.
- **State your assumptions correctly** — if the algorithm assumes sorted input, non-negative values, no duplicates, etc., say so; the automated check can't judge whether the stated assumption is actually true.
- **DRY** — if you paste the same helper (fast I/O template, GCD, tree node struct, etc.) into a third file, promote it to a shared header instead of a fourth copy.
- **Consistent naming** — pick one convention (`snake_case` or `camelCase`) and stick to it across the file.

---

## Per-topic files

- **`theory/<Topic>/THEORY.md`** — static concept reference (definitions, complexity). Predates the DSA-450 focus, not sheet-specific, kept separate from the active work below so it's never mistaken for the actual sheet's problem list.
- **`lovebabbar-450dsa/<Topic>/README.md`** — the topic's landing page: the curated DSA-450 problem list (generated — see `scripts/generate_topic_readmes.py`) on top, and a **Mental Model** section below it that grows organically as problems are solved — append to a matching category when a new problem reinforces it, add a new category when a genuinely new pattern shows up. Scan this *before* coding a new problem. Each entry links to its full write-up in `notes/`.
- **`lovebabbar-450dsa/<Topic>/notes/<name>.md`** — one file per problem, matching the `<name>` used in `codes/`/`input/`/`output/`.
  - The full-depth write-up: what made the problem hard, the reasoning step by step, where the thinking initially stalled, a reusable checklist for that problem family.
  - Not required for every problem — write one when the problem taught something worth remembering, skip it for routine ones.
  - This is where AI-discussion/search content and in-depth reasoning gets logged for later reference, so it doesn't need to be re-derived from scratch next time a similar problem shows up.
- None of these are linted or gated by CI — reviewed the same informal way as any other markdown.
- The 4 GraphAlgorithms subfolders (Traversal/ShortestPath/MST/TopologicalSort) don't have a generated README.md yet — dsa450.ts's "graph" topic doesn't distinguish which sub-area each problem belongs to, so they still use the older standalone `mental-model.md` + `notes/` pair until that's sorted out by hand.

---

## Never do this

- Never commit compiled binaries by hand outside `binary/` — extension-less build artifacts or `.o` files sitting next to a `.cpp` elsewhere are a sign the layout convention was skipped.
- Never force-push over shared history on `master`.
