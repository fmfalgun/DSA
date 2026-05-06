# DSA / Systems Programming — Session 05 Progress Report

> **Goal:** Implement build-heap (O(n) heapify) and heap sort in C.
> **Language:** C
> **Approach:** Write independently, debug with minimal hints, understand *why* bugs are wrong.

---

## Step 1 — Build-Heap Conceptually (`step1.c`)

**Task:** Given unsorted array `[4, 1, 9, 3, 7, 2, 6]`, identify which indices need sift-down and why build-heap starts at `n/2`.

### Conceptual Framework

Array as 1-indexed tree:

```
Index:  1    2    3    4    5    6    7
Value: [4,   1,   9,   3,   7,   2,   6]

          4(1)
         /    \
       1(2)   9(3)
       / \    / \
     3(4)7(5)2(6)6(7)
```

- **Leaves:** indices 4, 5, 6, 7 — no children (`2i > 7`), trivially valid, zero work needed
- **Non-leaves:** indices 1, 2, 3 — last non-leaf is `n/2 = 3`
- **Why start at n/2:** it's exactly the last non-leaf; everything after is a leaf
- **Why sift-down not sift-up:** subtrees below each node are already valid heaps (bottom-up order); only need to push current node down

### Q&A Summary

| Question | Answer |
|---|---|
| Which indices need sift-down? | 1 and 2 (values 4 and 1); index 3 (value 9) already satisfies invariant |
| Why start at n/2? | n/2 = 3 is the last non-leaf; indices 4–7 are leaves, trivially valid |
| Why sift-down not sift-up? | Processing bottom-up; subtrees below are already valid heaps |

### Issues Faced & Resolutions

**Bug 1 — confused index 3 (value 9) as not needing a visit**
- Initial answer: only indices 1 and 2 need sift-down
- Root cause: confused "value 9 won't move" with "index 3 doesn't need checking"
- Resolution: index 3 must still be visited; sift-down just happens to find the invariant already holds and does nothing

---

## Step 2 — Implement `heapify` / Build-Heap (`step1.c`)

**Task:** Implement `heapify(arr, size)` — single pass sift-down from `n/2` down to `1`.

### Final Working Implementation

```c
void heapify(int arr[], int size){
    int n = (size-1)/2;
    int lvi;
    for (int i = n; i > 0; i--){
        int lci = left_child_index(i);
        int rci = right_child_index(i);
        int ptr = i;
        while(lci <= size){
            if (rci > size) lvi = lci;
            else if (arr[lci] > arr[rci]) lvi = lci;
            else lvi = rci;
            if (arr[ptr] > arr[lvi]) break;
            int temp = arr[ptr];
            arr[ptr] = arr[lvi];
            arr[lvi] = temp;
            ptr = lvi;
            lci = left_child_index(ptr);
            rci = right_child_index(ptr);
        }
    }
}
```

### Issues Faced & Resolutions

**Bug 1 — single swap per node, no cascading (Approach 1)**
- First attempt: one swap per node, no inner while loop
- Result: a swapped-down value could violate invariant with its new children — heap not valid
- Root cause: missing the cascade; sift-down must follow the displaced value all the way down
- Resolution: added inner while loop that follows `ptr` until invariant holds or leaf reached

**Bug 2 — multiple outer passes to compensate (Approach 1)**
- Worked around missing cascade with `while(!completed)` outer loop — O(n²) behavior
- Resolution: replaced with proper cascading sift-down inner loop — single pass O(n)

**Bug 3 — outer `if` read `arr[rci]` before bounds check**
- `if((arr[i] < arr[lci]) || (arr[i] < arr[rci]))` before entering while loop
- When node has only left child, `arr[rci]` is out of bounds
- Works by accident here (unused slots are 0); latent bug for other datasets
- Resolution: removed outer `if` entirely — while loop handles all bounds checking correctly

---

## Step 3 — Implement `sift_down` and `heap_sort` (`step2.c`)

**Task:** Extract `sift_down(arr, size, root_index)` as a standalone function; implement `heap_sort` using it.

### Algorithm

```
heap_sort:
    repeat (size-1) times:
        swap arr[1] with arr[n]   // move max to sorted region
        n--                        // shrink heap boundary
        sift_down(arr, n, 1)      // restore heap from root
```

### Final Working `sift_down`

```c
void sift_down(int *arr, int size, int root_index){
    int ptr = root_index;
    int lci = left_child_index(ptr);
    int rci = right_child_index(ptr);
    while (lci <= size){
        int lvi;
        if (rci > size) lvi = lci;
        else if (arr[rci] < arr[lci]) lvi = lci;
        else lvi = rci;
        if (arr[ptr] < arr[lvi]){
            int temp = arr[lvi];
            arr[lvi] = arr[ptr];
            arr[ptr] = temp;
        }
        else break;
        ptr = lvi;
        lci = left_child_index(ptr);
        rci = right_child_index(ptr);
    }
}
```

### Final Working `heap_sort`

```c
void heap_sort(int *arr, int size){
    int n = size;
    while (n != 1){
        int temp = arr[n];
        arr[n] = arr[1];
        arr[1] = temp;
        n--;
        sift_down(arr, n, 1);
    }
}
```

### Issues Faced & Resolutions

**Bug 1 — calling full `heapify` instead of `sift_down` in heap_sort**
- Original: `heapify(arr, --n)` after each extraction — O(n) per step → O(n²) total
- Root cause: heap below root is already valid after swap; only root needs sifting
- Resolution: extracted `sift_down` and called that instead — O(log n) per step → O(n log n) total

**Bug 2 — missing `else break` in `sift_down`**
- `ptr = lvi` always executed even when no swap happened
- Result: node kept descending past its correct position, corrupting heap
- Root cause: no exit condition when invariant already holds
- Resolution: added `else break` after the swap block

**Bug 3 — undefined behavior: `sift_down(arr, n, --n)`**
- Modifying and reading `n` in the same function call — argument evaluation order is unspecified in C
- Root cause: trying to decrement and pass in one line
- Resolution: separated into two statements: `n--; sift_down(arr, n, 1);`

**Bug 4 — passing `size` instead of `n` to `sift_down`**
- `sift_down(arr, size, 1)` — heap boundary never shrank
- Result: sift-down could see already-sorted elements at the end, corrupting them
- Resolution: pass `n` (the shrinking boundary) not `size`

**Bug 5 — sifting from `n` instead of root `1`**
- `sift_down(arr, n, --n)` — passing `n` as root index
- After swap, the displaced element is always at index 1 (root), not at `n`
- Resolution: always pass `1` as root index

---

## Step 4 — Output Verification

Input: `[4, 1, 9, 3, 7, 2, 6]`

After `heapify`:
```
[9, 7, 6, 3, 1, 2, 4]
```
Valid max-heap ✅

After `heap_sort`:
```
[1, 2, 3, 4, 6, 7, 9]
```
Sorted ascending ✅

---

## Step 5 — Conceptual Wrap-Up

### Why is build-heap O(n) not O(n log n)?

Building block: most nodes are near the bottom of the tree and have very little room to fall.

| Level from bottom | Node count | Max swaps per node |
|---|---|---|
| 0 (leaves) | n/2 | 0 |
| 1 | n/4 | 1 |
| 2 | n/8 | 2 |
| k | n/2^(k+1) | k |

Total work = `n/2*0 + n/4*1 + n/8*2 + ...` = **2n** (geometric series). O(n) even worst case.

**Building analogy:** fixing employees floor by floor from ground up. Most are on the ground floor — nowhere to fall. Only the CEO travels all floors. Most workers travel 0–1 floors.

### Why is heap sort O(n log n)?

Every extraction starts sift-down from the **root** — always maximum room to fall (`log n` levels). The janitor placed at the CEO chair almost always needs the full trip back down. Repeated n times → O(n log n).

**Key distinction:** build-heap has most nodes starting near bottom; heap sort always starts from top.

| Phase | Complexity | Reason |
|---|---|---|
| `heapify` (build-heap) | O(n) | Most nodes near bottom, little room to fall |
| `heap_sort` extractions | O(n log n) | Every sift-down from root, full log n trip, n times |
| **Total** | **O(n log n)** | Build dominated by sort phase |

---

## Overall Session Summary

| Step | Operation | Core Concept | Bugs Resolved |
|---|---|---|---|
| 1 | Build-heap conceptually | Leaves vs non-leaves, why n/2 | Confused "won't move" with "don't visit" |
| 2 | `heapify` implementation | Bottom-up cascading sift-down | Missing cascade, redundant outer loop, latent bounds bug |
| 3 | `sift_down` + `heap_sort` | Shrinking boundary, always sift from root | 5 bugs: full heapify vs sift_down, missing break, UB on --, wrong boundary, wrong root |
| 4 | Output verification | End-to-end correctness | All correct |
| 5 | Complexity analysis | Why O(n) build, O(n log n) sort | Geometric series intuition, building analogy |

**Key Lessons:**
- Build-heap is O(n) because most nodes are leaves — geometric series of work per level converges to 2n
- Heap sort is O(n log n) because every sift-down starts from the root with full log n depth
- Always separate `n--` from function calls that use `n` — argument evaluation order is undefined in C
- Sift-down boundary must shrink with each extraction — passing original `size` corrupts sorted region
- After each heap-sort swap, sift-down always starts from index 1 (root), not from the last position

---

## Session 06 — What's Next

Per `algorithms_masterclass.md` §24, next topic: **Quick Sort (continued)**.

Lomuto partition + basic quicksort structure was covered in **Session 02**. Remaining topics:

- **Hoare partition** — two pointers from both ends; faster in practice than Lomuto
- **3-way partition (Dutch flag)** — partitions into `<`, `=`, `>`; O(n) when many duplicates
- **Pivot selection** — random pivot, median-of-three; how to avoid O(n²) worst case
- **Worst case analysis** — when does quicksort degrade, why, and concrete adversarial inputs
