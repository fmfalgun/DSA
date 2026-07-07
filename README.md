# DSA

- Learning + revision reference while working through Love Babbar's DSA-450 sheet, one problem (or one improvement) per branch and PR, even solo. See [data-structures/README.md](./data-structures/README.md) for the topic index and current scope.
- Layout (per topic, under `data-structures/`): `<Topic>/codes/<name>.cpp` (source), `<Topic>/binary/<name>` (compiled output), `<Topic>/input/<name>.in` (sample input), `<Topic>/output/<name>.out` (expected output), `<Topic>/notes/<name>.md` (optional per-problem deep-dive — the topic's own `README.md` already serves as its theory/mental-model reference).
- One-time local setup after cloning: `git config core.hooksPath .githooks`.

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
- Scoped to `data-structures/**/*.cpp` — `code-start/` (C, not C++) and `algorithms/` aren't gated by this setup.
- Only files changed in the diff are checked, so pre-existing solutions are never retroactively blocked.

---

## Code-quality checklist (self-review at PR time — not machine-checkable)

- **Single responsibility** — once a solution is more than ~20 lines, split input parsing, the algorithm, and output formatting into separate functions instead of one long `main()`.
- **Comments explain *why*, not *what*** — a note on the approach ("two-pointer since array is sorted") beats restating the code in English; the automated check only confirms a comment exists, not that it's a good one.
- **State your assumptions correctly** — if the algorithm assumes sorted input, non-negative values, no duplicates, etc., say so; the automated check can't judge whether the stated assumption is actually true.
- **DRY** — if you paste the same helper (fast I/O template, GCD, tree node struct, etc.) into a third file, promote it to a shared header instead of a fourth copy.
- **Consistent naming** — pick one convention (`snake_case` or `camelCase`) and stick to it across the file.

---

## Notes convention (per problem, optional)

- **`<Topic>/notes/<name>.md`** — one file per problem, matching the `<name>` used in `codes/`/`input/`/`output/`.
  - The full-depth write-up: what made the problem hard, the reasoning step by step, where the thinking initially stalled, a reusable checklist for that problem family.
  - Not machine-checked and not required for every problem — write one when the problem taught something worth remembering, skip it for routine ones.
  - This is where AI-discussion/search content and in-depth reasoning gets logged for later reference, so it doesn't need to be re-derived from scratch next time a similar problem shows up.
- Not linted or gated by CI — reviewed the same informal way as any other markdown.

---

## Never do this

- Never commit compiled binaries by hand outside `binary/` — extension-less build artifacts or `.o` files sitting next to a `.cpp` elsewhere are a sign the layout convention was skipped.
- Never force-push over shared history on `master`.
