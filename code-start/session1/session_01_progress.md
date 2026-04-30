# DSA / Systems Programming — Session 01 Progress Report

> **Goal:** Re-activate coding flow after extended AI-assisted coding period.
> **Language:** C
> **Approach:** Write from scratch, no AI code generation, debug independently.

---

## Step 1 — Character Frequency Counter (`step1.c`)

**Task:** Read a string from user, print each unique character and its frequency, sorted highest first.

**Concepts Practiced:**
- Dynamic memory allocation (`malloc`, `realloc`)
- ASCII-based hash table using `freq[256]` array
- Bubble sort with index swapping

**Issues Faced & Resolutions:**

- **Missing null terminator** — `str[length]` never set to `'\0'`, loop behavior was undefined (got lucky with garbage `0x00`). Fixed by adding `str[length] = '\0'` after input loop.
- **Off-by-one in freq loop** — `i <= 256` caused out-of-bounds read at `freq[256]`. Fixed to `i < 256`.
- **Wrong swap in sort** — was swapping loop counters `i` and `j` instead of values inside `non_zero_index[]`. Fixed by swapping `non_zero_index[i]` and `non_zero_index[j]`.
- **Sort condition always false** — `!((i != -1) || (j != -1))` simplified via De Morgan's law to `(i == -1) && (j == -1)`, which is never true. Removed the condition entirely.
- **`int freq[256] = {-1}`** — only sets first element to `-1`, rest become `0`. Understood that `{value}` initializer only sets the first element in C.
- **Loop bounds** — replaced `256` with `counter` in sort and print loops for correctness and efficiency.

---

## Step 2 — File Word/Line/Character Counter (`step2.c`)

**Task:** Read a text file line by line, count total lines, words, and characters. Match output of `wc`.

**Concepts Practiced:**
- File I/O (`fopen`, `fgets`, `fclose`)
- Buffer-based line reading
- Word detection using state flag (`in_word`)
- Buffer overflow edge case handling

**Issues Faced & Resolutions:**

- **Word counting via spaces was fragile** — counting spaces broke on multiple consecutive spaces, leading spaces, and single-word lines. Replaced with `in_word` flag: increment word count on transition from non-word to word character.
- **`\n` not counted as character** — `wc` counts newline as a character. Fixed by moving `char_counter++` before the `break` on `\n`.
- **Buffer overflow on long lines** — `fgets` with buffer size 100 splits long lines into multiple reads, causing incorrect `line_counter` increments. Fixed using `buff_limit_reached` flag: only increment `line_counter` when previous read ended at `\n`, not at buffer limit.
- **Extra characters counted in overflow case** — was counting `'\0'` or null bytes in overflow chunks. Fixed by only counting characters when `!buff_limit_reached` at position 99.
- **Spaces-only line counted as 1 word** — `in_word` flag correctly handled this once implemented; no word transition occurs on a space-only line.

**Validation:** Final output matched `wc` exactly on all test cases including empty file, spaces-only, no-newline-at-EOF, and lines exceeding buffer size.

---

## Step 3 — Stack via Linked List (`step3.c`)

**Task:** Implement a stack using a linked list with `push`, `pop`, `peek`, `is_empty`. Each node `malloc`'d individually.

**Concepts Practiced:**
- Structs (`Node`, `Stack`)
- Pointer manipulation and `malloc`/`free`
- Stack LIFO behavior
- C vs C++ syntax differences

**Issues Faced & Resolutions:**

- **C++ syntax used in C** — `nullptr`, inline struct member initialization (`int *next = NULL` inside struct body), and no `struct` keyword prefix. All replaced with C equivalents: `NULL`, separate initialization, `struct Node` / `struct Stack`.
- **Stack pointer uninitialized** — declared `struct Stack *stack` without `malloc`. Pointed to garbage memory causing SIGSEGV. Fixed by `malloc(sizeof(struct Stack))`.
- **`stack->top` uninitialized after malloc** — `malloc` does not zero memory. `stack->top` contained garbage. Got lucky (happened to be 0x00). Fixed by explicitly setting `stack->top = NULL` after malloc.
- **Push added to bottom, not top** — used a `while` loop to traverse to end of list before inserting. Replaced with O(1) top-insert: `temp->next = stack->top; stack->top = temp`.
- **Unnecessary special case in push** — `if (ptr == NULL)` branch was redundant once top-insert logic was correct. Removed.
- **Unused variable** — `ptr` left in `push` after refactor. Removed.

---

## Step 4 — Queue via Two Stacks (`step4.c`, `queue.h`, `queue.c`, `stack.h`, `stack.c`)

**Task:** Implement a queue using two stacks with `enqueue`, `dequeue`, `q_peek`, `q_is_empty`.

**Concepts Practiced:**
- Multi-file C project structure
- Header files, header guards (`#ifndef / #define / #endif`)
- `typedef` vs `struct` keyword
- Linker vs compiler errors
- Amortized O(1) queue via lazy shift

**Architecture:**
- `S1` — input stack (enqueue here)
- `S2` — output stack (dequeue/peek from here)
- `shift()` — moves all of S1 to S2, only when S2 is empty

**Key Insight — Lazy Shift:**
- Moving S1→S2 only when S2 is empty avoids O(n) cost on every operation.
- Each element is moved at most once, giving amortized O(1) per operation.

**Issues Faced & Resolutions:**

- **Missing semicolon after struct in header** — `struct Queue { ... }` missing `;`. C requires semicolon after struct definition.
- **Function name conflict** — `peek` and `is_empty` defined in both `stack.h` and `queue.h`. C has no namespaces/overloading. Fixed by prefixing queue functions: `q_peek`, `q_is_empty`.
- **Linker error** — compiling only `step4.c` caused "undefined reference" errors. Fixed by compiling all `.c` files together: `gcc step4.c queue.c stack.c -o step4`.
- **Missing `#include <stdlib.h>`** in `queue.c` and `stack.c` — each `.c` file needs its own includes. Including a header does not chain standard library includes.
- **`S1` and `S2` uninitialized** — `malloc(Queue)` allocates the shell but `S1` and `S2` pointers inside are garbage. Fixed by separately `malloc`-ing each stack and setting their `top = NULL`.
- **Memory leak in `shift()`** — `malloc`'d a new Node then immediately overwrote the pointer with an existing address. That allocated memory was lost. Fixed by removing the `malloc` — `temp` only needs to hold an existing pointer, no allocation required.

---

## Step 5 — Binary Search + First Occurrence (`step5.c`)

**Task:** Implement binary search on sorted array. Then find first occurrence of a duplicate target.

**Concepts Practiced:**
- Divide and conquer
- Left/right boundary approach
- Off-by-one in boundary updates
- Recursion (emerged naturally)

**Issues Faced & Resolutions:**

- **Size-halving approach broke on edge elements** — original approach of halving `size` and adding/subtracting from index failed because integer division loses the remainder, making it impossible to reach certain indices (e.g., index 1 in a 10-element array). Replaced with `left`/`right` boundary approach.
- **`mid` uninitialized in while condition** — `while (left <= right && mid)` used garbage `mid` value on first iteration, causing unpredictable loop entry. Removed `&& mid` from condition.
- **Wrong `mid` calculation** — `mid = (right - left) / 2` gives a distance, not an index. Fixed to `mid = left + (right - left) / 2`.
- **Wrong boundary updates** — `left += mid` and `right -= mid` caused infinite loops because mid is an index, not a step size. Fixed to `left = mid + 1` and `right = mid - 1` (excluding already-checked mid from next window).
- **First occurrence via recursion** — when target found at `mid`, recursively call `first_occurrence(arr, mid, target)` on left subarray. Naturally discovered recursion without being prompted.

**Note:** Iterative alternative exists — save result when target found, set `right = mid - 1`, continue searching left. Both approaches valid.

---

## Overall Session Notes

| Step | File | Core Concept |
|------|------|-------------|
| 1 | `step1.c` | Hash table, sorting |
| 2 | `step2.c` | File I/O, buffer handling |
| 3 | `step3.c` | Linked list, pointers, malloc/free |
| 4 | `step4.c` | Multi-file project, header guards, amortized complexity |
| 5 | `step5.c` | Binary search, recursion |

**Key C Lessons Reinforced:**
- `malloc` does not zero memory — always initialize explicitly
- Every `.c` file needs its own `#include` statements
- C has no namespaces — use prefixes for related functions
- Pointer vs value: changing a local pointer copy does not affect the original
- Compiler errors = syntax/type problems; Linker errors = missing definitions
- `{value}` initializer only sets first element of array; rest become `0`

---

*Session 01 — Flow re-activated. Next: sorting algorithms or pointer-based trees.*
