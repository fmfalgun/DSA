# DSA / Systems Programming — Session 02 Progress Report

> **Goal:** Implement merge sort and quick sort from scratch in C.
> **Language:** C
> **Approach:** Write independently, debug with minimal hints, understand *why* bugs are wrong.

---

## Step 1 — Merge Sort (`step1.c`)

**Task:** Write `merge_sort(arr, left, right)` and `merge(arr, left, mid, right)` to sort an integer array. Print sorted result in `main`.

### Conceptual Framework

- **Divide** — split array in half recursively until subarrays are size 1
- **Conquer** — size-1 array is trivially sorted
- **Merge** — combine two sorted halves into one sorted array using a temp array

Key insight: everything operates on the **same array** using index boundaries (`left`, `mid`, `right`) — no copying subarrays, no returning pointers. Same pattern as binary search from Session 01.

### Pointer Clarification (pre-coding)

| Expression | Meaning |
|------------|---------|
| `arr` | pointer to first element — what you pass ✅ |
| `arr[5]` | int value at index 5 |
| `*arr` | same as `arr[0]` |
| `*arr[5]` | compile error — can't dereference an int |

### Issues Faced & Resolutions

**Bug 1 — SIGSEGV: missing base case**
- `merge_sort` recursed infinitely with no stopping condition
- Fix: `if (left >= right) return;` at the top of `merge_sort`

**Bug 2 — Writing to `arr` instead of `temp` in merge**
- The while loop wrote `arr[k++] = arr[i++]` — destroying source data while reading it
- Fix: write to `temp[k++]` instead

**Bug 3 — Inverted comparison in merge**
- `if (arr[i] >= arr[j])` took the larger element first → descending order
- Fix: `<=` to take the smaller element first

**Bug 4 — Leftover elements not copied**
- The main while loop exits when *either* pointer exhausts its half
- Remaining elements in the other half were never copied to `temp`
- Fix: two cleanup loops after main while:
```c
while (i <= mid)   temp[k++] = arr[i++];
while (j <= right) temp[k++] = arr[j++];
```

**Why leftovers matter — example:**
```
left:  [1, 5, 9]
right: [2, 3]
→ after main loop: temp = [1, 2, 3, 5] — but 9 never copied
```

### Key Insight — Why In-Place Swap Doesn't Work for Merge

First attempt used swaps instead of a temp array. This corrupts the right half:
```
left: [1, 5, 9]   right: [2, 3, 4]
swap 5 and 2 →    left: [1, 2, 9]   right: [5, 3, 4]  ← right is now unsorted
```
Fixing this would require re-sorting the right half after every swap — exponentially worse complexity. Temp array is the right tool.

### Final Working Structure

```c
void merge(int *arr, int left, int mid, int right){
    int size = right - left + 1;
    int temp[size];
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];

    while (i <= mid)   temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int m = 0; m < size; m++) arr[left + m] = temp[m];
}

void merge_sort(int *arr, int left, int right){
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
```

---

## Step 2 — Quick Sort (`step2.c`)

**Task:** Write `quick_sort(arr, left, right)` and `partition(arr, left, right)` that places pivot in its correct position and returns its index.

### Conceptual Framework

- Pick last element as **pivot**
- Rearrange: everything smaller goes left, everything larger goes right
- Pivot is now in its **final correct position**
- Recursively sort left and right sides
- Sorts **in place** — no temp arrays needed (unlike merge sort)

### Attempt 1 — Temp Array Approach (failed)

First attempt used `left_arr[]` and `right_arr[]` temp arrays, copying elements in then writing back. Issues encountered:

- `pivot_index` stayed `-1` when all elements were smaller than pivot (loop boundary edge case)
- Pivot and right elements writing to same `k` index (overwrite)
- Off-by-one errors with `max_left` / `max_right` bounds (`<=` vs `<`)
- Right elements never written back when `left_filled` triggered `continue`
- Returning `-1` as `ptr` caused `quick_sort` to recurse with `ptr-1 = -2` → SIGSEGV

Despite many fixes, this approach was too tangled to patch cleanly. Root problem: reimplementing something complex that a simpler in-place approach handles naturally.

**Also fixed along the way:**
- Missing base case in `quick_sort`: `if (left >= right) return;`
- Wrong recursive call: `quick_sort(arr, left, ptr+1)` → `quick_sort(arr, ptr+1, right)`

### Attempt 2 — Lomuto Partition (working)

**The key insight — what `i` represents:**

At any point in the loop, the array is partitioned into three regions:
```
[left ... i-1]  [i ... j-1]  [j ... right-1]  [right]
  ≤ pivot          > pivot       unexplored       pivot
```

`j` scans forward. If `arr[j] <= pivot`, swap with `arr[i]` and advance `i` — growing the "small" region. At the end, swap pivot into position `i`.

```c
int partition(int *arr, int left, int right){
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++){
        if (arr[j] <= pivot){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }

    int temp = arr[i];
    arr[i] = arr[right];
    arr[right] = temp;

    return i;
}
```

No extra memory. One pass. Pivot ends up in its exact final position every time.

### Merge Sort vs Quick Sort

| | Merge Sort | Quick Sort |
|---|---|---|
| Strategy | Divide then merge | Partition then recurse |
| Extra memory | O(n) temp array | O(1) in place |
| Time complexity | O(n log n) always | O(n log n) avg, O(n²) worst |
| Stable | Yes | No (Lomuto) |

---

## Overall Session Notes

| Step | Algorithm | Core Concepts |
|------|-----------|---------------|
| 1 | Merge Sort | Recursion, temp array merge, leftover handling |
| 2 | Quick Sort | In-place partitioning, Lomuto scheme, pivot placement |

**Key Lessons:**
- Always add base case before recursive calls — missing it = guaranteed SIGSEGV
- In-place swap during merge corrupts source data — temp array is the right tool
- When a patching approach gets too tangled, the approach itself is wrong — rewrite clean
- `i < max` vs `i <= max` off-by-one errors are subtle — trace manually with a small example
- Lomuto partition is elegant because `i` has a clear invariant meaning throughout the loop

---

## Session 03 — What's Next

**Topic: Binary Search Trees (BST)**

Building on: pointers, malloc/free (Session 01), recursion (Session 02)

Tasks to implement:
- `insert(root, value)` — recursive insert maintaining BST property
- `search(root, value)` — recursive search
- `delete(root, value)` — three cases: leaf, one child, two children
- Traversals: `inorder`, `preorder`, `postorder`

**Stretch goal:** collect inorder traversal into an array — result is a sorted array (BST sort).

> BST delete is the hardest operation here — the two-children case requires finding the inorder successor. That's where the real thinking happens.
