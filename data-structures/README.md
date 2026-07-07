# Data Structures & Algorithms

Currently working through **Love Babbar's DSA-450 sheet**, topic by topic. This repo is the reading/revision reference for that work — solved code and theory notes, not a progress tracker (that's managed elsewhere).

Once DSA-450 is done, the plan is to move on to other sheets (Striver's A2Z/SDE, NeetCode 150, etc.). Topics below that aren't part of DSA-450 are parked under `non-450/` until that phase starts.

## DSA-450 Topics

- [Arrays](./Arrays/)
- [Linked Lists](./LinkedList/)
- [Stacks](./Stack/)
- [Queues](./Queue/)
- [Trees](./Trees/)
- [Heaps](./Heaps/)
- [Hash Tables](./HashTables/)
- [Graphs](./Graphs/) + [Graph Algorithms](./GraphAlgorithms/) (Traversal, Shortest Path, MST, Topological Sort)
- [Tries](./Tries/)
- [Sorting](./Sorting/)
- [Searching](./Searching/)
- [Recursion & Backtracking](./Recursion/)
- [Divide & Conquer](./DivideAndConquer/)
- [Dynamic Programming](./DynamicProgramming/)
- [Greedy](./Greedy/)
- [Bit Manipulation](./BitManipulation/)
- [String Algorithms](./StringAlgorithms/)
- [Mathematical Algorithms](./MathematicalAlgorithms/)

## Non-450 (Later Phases)

Reference theory only for now, not active work: [Segment Trees](./non-450/SegmentTrees/), [Fenwick Trees](./non-450/FenwickTrees/), [Disjoint Set](./non-450/DisjointSet/), [Game Theory](./non-450/GameTheory/), [Advanced Data Structures](./non-450/AdvancedDataStructures/).

## Company-Specific Practice

[companies/](./companies/) — real interview problems tied to a specific company (currently: Digivalet). Separate from the sheet work.

## Naming Convention & Workflow

Layout for new solved problems going forward (existing flat files like `problem_1.cpp` are left as-is):

- `<Topic>/codes/<kebab-case-problem-name>.cpp`, with a matching `<Topic>/input/<name>.in` + `<Topic>/output/<name>.out` sample I/O pair and compiled output at `<Topic>/binary/<name>`.
- Name after the problem, not its number on the sheet (numbers shift across sheet versions/editions).
- One file per problem. If exploring multiple approaches, suffix them: `-brute.cpp`, `-optimal.cpp`.
- Example: `Arrays/codes/rotate-array-by-d.cpp`, `LinkedList/codes/detect-and-remove-loop.cpp`.

Full git workflow, branch naming convention, and automated checks are documented in the [repo-root README](../README.md).

## Resources

See [Resources.md](./Resources.md) for books, courses, and practice platforms.
