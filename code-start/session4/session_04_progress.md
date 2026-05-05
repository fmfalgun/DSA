# DSA / Systems Programming — Session 04 Progress Report

> **Goal:** Implement a Binary Max-Heap in C — array representation, push (sift-up), pop (sift-down).
> **Language:** C
> **Approach:** Write independently, debug with minimal hints, understand *why* bugs are wrong.

---

## Step 1 — Index Formulas & Array Representation (`step1.c`)

**Task:** Given a 1-indexed max-heap array, derive parent/left-child/right-child index formulas. Draw the array as a tree.

### Conceptual Framework

- **Heap stored as array** — a tree that lives in a flat array; no pointers needed
- **1-indexed convention** — index 0 unused (sentinel `-1`); elements start at index 1; makes math clean
- **Index formulas** for node at index `i`:

| Relation | Formula |
|---|---|
| Parent | `i / 2` |
| Left child | `2 * i` |
| Right child | `2 * i + 1` |

- **Heap invariant** — every parent >= its children (max-heap); no left/right ordering like BST

### Array `[_, 90, 70, 80, 40, 60, 10, 50]` as a tree

```
        90
      /    \
    70      80
   /  \    /  \
  40  60  10  50
```

### Issues Faced & Resolutions

**Bug 1 — `parent_index(1)` returned 0 instead of -1**
- Root has no parent; returning 0 is misleading because index 0 is the unused sentinel slot
- Fix: added `value == 1` to the guard — return `-1` for both 0 and 1
- Root cause: forgot the root is a special case with no parent

---

## Step 2 — Push / Sift-Up (`step2.c`)

**Task:** Insert a value into the heap. Append at end, sift up until invariant holds.

### Conceptual Framework

- **Why append at end?** — heap must be a complete binary tree (filled level by level, left to right); appending to the end preserves that shape
- **Sift-up** — new value bubbles toward the root by swapping with parent while it's larger than parent
- **Static array trick** — declare `arr[100]`, track active elements with `last_value`; write into next unused slot

### Issues Faced & Resolutions

**Bug 1 — `arr[-1]` read when pushing the largest value ever seen**
- While condition was `ptr != -1 && arr[parent_index(ptr)] < value`
- When `ptr == 1` (root), `parent_index(1)` returns `-1`; condition checked `ptr != -1` but `ptr` was `1`, not `-1`
- So `arr[-1]` was accessed — garbage memory before the array
- Happened to work with 95 (garbage < 95 was false), broke with 999 (garbage was 100, which is < 999, so loop fired and corrupted the value)
- Fix: change condition to `ptr > 1` — loop stops cleanly when node reaches root
- Root cause: confused "ptr will become -1" with "ptr is currently -1"; the check fires one iteration too late

---

## Step 3 — Pop / Sift-Down (`step3.c`)

**Task:** Remove and return the max. Swap root with last element, shrink size, sift the displaced element down.

### Conceptual Framework

- **Why not just delete the root?** — would leave a hole and break the complete binary tree shape
- **Why swap with the last element?** — the last element is the only node that can be freely removed without breaking shape (it's a leaf at the end of the array)
- **Sift-down** — displaced element (likely small) bubbles toward the leaves by swapping with the *larger* child while it's smaller than that child
- **Why swap with the larger child?** — swapping with the smaller child would leave the larger child as a sibling of a node smaller than it, still violating the invariant

### Issues Faced & Resolutions

**Bug 1 — `ptr` never updated after swap (Approach 1)**
- Computed `lci` and `rci` before the loop, then forgot to move `ptr` down after each swap
- Result: always sifted from root, never progressed — wrong positions, duplicate values in output
- Fix: update `ptr = lci` or `ptr = rci` after each swap, then recompute `lci` and `rci`

**Bug 2 — bounds check required both children to exist**
- Condition `lci <= last_value && rci <= last_value` exits loop when only left child exists
- A node can have a left child but no right child (last level, odd number of elements)
- That left child was never checked — silently skipped a needed swap
- Fix: restructured to `while(lci <= last_value)` and handle right-child absence inside

**Bug 3 — while condition read `arr[lci]` and `arr[rci]` before bounds check**
- Original: `while(arr[ptr] < arr[lci] || arr[ptr] < arr[rci])` with bounds check inside body
- When `ptr` is at a leaf, `lci` and `rci` are beyond `last_value` — reads garbage memory before the break fires
- Worked by accident (unused array slots are zero, always less than heap values)
- Concrete failure case: single-element heap — `last_value = 0`, `lci = 2`, `arr[2]` is out of bounds
- Fix: move bounds check to while condition: `while(lci <= last_value)`

**Bug 4 — always swapped even when invariant already held**
- Loop swapped unconditionally after finding `largest_child`
- Result: sifted element kept going past its correct position, corrupting the heap
- Fix: add `if (arr[ptr] >= arr[largest_child]) break;` before the swap

### Final Working Sift-Down Logic

```c
while(lci <= *last_value){
    if (rci > *last_value) largest_child = lci;
    else if (arr[lci] > arr[rci]) largest_child = lci;
    else largest_child = rci;

    if (arr[ptr] >= arr[largest_child]) break;

    int temp = arr[largest_child];
    arr[largest_child] = arr[ptr];
    arr[ptr] = temp;
    ptr = largest_child;

    lci = left_child_index(ptr);
    rci = right_child_index(ptr);
}
```

---

## Step 4 — Full Test (`step4.c`)

**Task:** Push `[3, 10, 1, 7, 4, 8]` one by one, print after each push. Pop three times, print popped value and array each time.

### Push sequence

| After pushing | Heap array | Tree root |
|---|---|---|
| 3 | `[3]` | 3 |
| 10 | `[10, 3]` | 10 |
| 1 | `[10, 3, 1]` | 10 |
| 7 | `[10, 7, 1, 3]` | 10 |
| 4 | `[10, 7, 1, 3, 4]` | 10 |
| 8 | `[10, 7, 8, 3, 4, 1]` | 10 |

Final tree:
```
        10
      /    \
     7      8
    / \    /
   3   4  1
```

### Pop sequence

| Pop # | Value returned | Remaining heap |
|---|---|---|
| 1 | 10 | `[8, 7, 1, 3, 4]` |
| 2 | 8 | `[7, 4, 1, 3]` |
| 3 | 7 | `[4, 3, 1]` |

All valid max-heaps at each step ✅

---

## Step 5 — Conceptual Wrap-Up

**Q: Why sift-up for push, sift-down for pop?**
- Push appends at the end (bottom of tree) — new value needs to rise to its correct level → sift-up
- Pop places the last element at the root (top of tree) — that value is likely small and needs to fall to its correct level → sift-down

**Q: Why swap root with last element rather than just removing the root?**
- Direct removal leaves a hole at the root — tree shape breaks
- The last element is the only node that can be freely removed without breaking the complete binary tree shape (it's always a leaf at the end)
- After moving it to the root, sift-down restores the invariant

**Key distinction clarified:** "last element" in pop = last in the heap array by position, not the last one inserted. The reason we pick it is shape preservation, not insertion order.

---

## Overall Session Summary

| Step | Operation | Core Concept | Bugs Resolved |
|---|---|---|---|
| 1 | Index formulas | Array-as-tree, 1-indexed | Parent of root returning 0 instead of -1 |
| 2 | Push / sift-up | Complete tree shape, bubble up | `arr[-1]` read; fixed with `ptr > 1` guard |
| 3 | Pop / sift-down | Largest-child strategy, bounds | 4 bugs: stale ptr, missing one-child case, out-of-bounds read, unconditional swap |
| 4 | Full test | End-to-end verification | All correct |
| 5 | Conceptual wrap-up | Why sift direction, why last element | Clarified "last element" = positional, not insertion order |

**Key Lessons:**
- Heap invariant is simpler than BST — only parent >= children; no left/right ordering
- Array index math (`i/2`, `2i`, `2i+1`) completely encodes the tree structure — no pointers needed
- Bounds check must happen *before* array access, not inside the loop body after
- Always swap with the *larger* child in sift-down — swapping with smaller leaves invariant violated
- `ptr > 1` is the correct sift-up termination; `lci <= last_value` is the correct sift-down termination
- A heap must always be a complete binary tree — this constraint drives both why we append on push and why we grab the last element on pop

---

## Session 05 — What's Next

Per `algorithms_masterclass.md` §12, remaining heap topics:
- **Heap sort** — build heap in O(n), repeatedly extract max → sorted array in-place
- **Build heap from unsorted array in O(n)** — heapify from bottom up (sift-down from `n/2` to 1)

> Push and pop are solid. Heap sort is the natural next step — it uses both operations and closes the loop on why heaps matter for sorting.
