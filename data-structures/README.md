# Data Structures & Algorithms

Currently working through **Love Babbar's DSA-450 sheet**, topic by topic. This repo is the reading/revision reference for that work — solved code and theory notes, not a progress tracker (that's managed elsewhere).

Once DSA-450 is done, the plan is to move on to other sheets (Striver's A2Z/SDE, NeetCode 150, etc.). Topics below that aren't part of DSA-450 are parked under `non-450/` until that phase starts.

## DSA-450 Topics

Each topic folder holds `THEORY.md` (reference theory + problem list), and — once problems are actually being solved there — `mental-model.md` (pattern checklist) and `notes/` (per-problem deep-dives). See [Naming Convention & Workflow](#naming-convention--workflow) below.

This list is cross-checked against the canonical 15-topic breakdown (Array, Matrix, String, Searching & Sorting, Linked List, Binary Trees, BST, Greedy, BackTracking, Stack & Queue, Heap & Priority Queue, Graph, Trie, Dynamic Programming, Bit Manipulation) — folders here are split finer in places (e.g. Stack/Queue, Searching/Sorting as separate dirs) but cover the same ground.

- [Arrays](./Arrays/THEORY.md)
- [Matrix](./Matrix/THEORY.md)
- [Linked Lists](./LinkedList/THEORY.md)
- [Stacks](./Stack/THEORY.md)
- [Queues](./Queue/THEORY.md)
- [Trees](./Trees/THEORY.md) (covers Binary Trees + BST)
- [Heaps](./Heaps/THEORY.md)
- [Graphs](./Graphs/THEORY.md) + Graph Algorithms ([Traversal](./GraphAlgorithms/Traversal/THEORY.md), [Shortest Path](./GraphAlgorithms/ShortestPath/THEORY.md), [MST](./GraphAlgorithms/MST/THEORY.md), [Topological Sort](./GraphAlgorithms/TopologicalSort/THEORY.md))
- [Tries](./Tries/THEORY.md)
- [Sorting](./Sorting/THEORY.md)
- [Searching](./Searching/THEORY.md)
- [BackTracking](./BackTracking/THEORY.md)
- [Dynamic Programming](./DynamicProgramming/THEORY.md)
- [Greedy](./Greedy/THEORY.md)
- [Bit Manipulation](./BitManipulation/THEORY.md)
- [String Algorithms](./StringAlgorithms/THEORY.md)

## Non-450 (Later Phases / Not in the Sheet)

Reference theory only for now, not active work (`THEORY.md` only — no `mental-model.md`/`notes/` yet):

- Later-sheet data structures: [Segment Trees](./non-450/SegmentTrees/THEORY.md), [Fenwick Trees](./non-450/FenwickTrees/THEORY.md), [Disjoint Set](./non-450/DisjointSet/THEORY.md), [Game Theory](./non-450/GameTheory/THEORY.md), [Advanced Data Structures](./non-450/AdvancedDataStructures/THEORY.md).
- Not a category in Love Babbar's DSA-450 at all, kept as general reference: [Recursion](./non-450/Recursion/THEORY.md) (backtracking split out into its own active topic above), [Hash Tables](./non-450/HashTables/THEORY.md), [Divide & Conquer](./non-450/DivideAndConquer/THEORY.md), [Mathematical Algorithms](./non-450/MathematicalAlgorithms/NumberTheory/THEORY.md).

## Naming Convention & Workflow

Layout for new solved problems going forward (existing flat files like `problem_1.cpp` are left as-is):

- `<Topic>/codes/<kebab-case-problem-name>.cpp`, with a matching `<Topic>/input/<name>.in` + `<Topic>/output/<name>.out` sample I/O pair and compiled output at `<Topic>/binary/<name>`.
- Name after the problem, not its number on the sheet (numbers shift across sheet versions/editions).
- One file per problem. If exploring multiple approaches, suffix them: `-brute.cpp`, `-optimal.cpp`.
- Example: `Arrays/codes/rotate-array-by-d.cpp`, `LinkedList/codes/detect-and-remove-loop.cpp`.
- If the problem taught you something worth keeping, capture it in `<Topic>/notes/<name>.md` and roll the reusable pattern into `<Topic>/mental-model.md` — optional, not every problem needs it.

Full git workflow, branch naming convention, and automated checks are documented in the [repo-root README](../README.md).

## Resources

See [Resources.md](./Resources.md) for books, courses, and practice platforms.
