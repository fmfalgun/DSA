# DSA / Systems Programming — Session 03 Progress Report

> **Goal:** Implement a full Binary Search Tree (BST) in C — insert, search, delete, traversal.
> **Language:** C
> **Approach:** Write independently, debug with minimal hints, understand *why* bugs are wrong.

---

## Step 1 — BST Implementation (`step1.c`)

**Task:** Implement a BST with `create_node`, `insert`, `search`, `delete`, and `inorder` traversal.

### Conceptual Framework

- **BST property** — left child < node, right child >= node
- **Insert** — recurse left/right until NULL; return new node; wire it in on the way back up
- **Search** — recurse left/right based on comparison; return true on match, false on NULL
- **Delete** — three cases: leaf (free & return NULL), one child (return the child), two children (find inorder successor, copy value, delete successor)
- **Inorder** — left → node → right; gives sorted output; proof that BST is structurally correct

### Pointer Clarification (pre-coding)

| Expression | Meaning |
|---|---|
| `struct Node* node = malloc(...)` | pointer to a heap-allocated node ✅ |
| `struct Node node = malloc(...)` | value type — cannot hold a pointer, compile error ❌ |
| `node->field` | dereference pointer and access field ✅ |
| `node.field` | only valid if `node` is a value, not a pointer ❌ |

---

### Issues Faced & Resolutions

**Bug 1 — `create_node`: wrong malloc size**
- Wrote `malloc(sizeof(struct Node*))` — allocates only pointer size (~8 bytes), not the full struct
- Fix: `malloc(sizeof(struct Node))` — allocates memory for the entire struct
- Root cause: confused pointer type with the thing it points to

**Bug 2 — `create_node`: missing type in parameter**
- Wrote `create_node(value)` instead of `create_node(int value)`
- C requires explicit types; old-style implicit `int` is an error in modern GCC
- Fix: add `int` before `value`

**Bug 3 — `insert`: both `if` conditions fired on equal value**
- Wrote two separate `if` statements: `if (value < node->value)` and `if (value >= node->value)`
- When `value == node->value`, both conditions were true → recursed into both subtrees
- Fix: use `else if` so only one branch runs

**Bug 4 — `insert`: iterative approach fundamentally flawed**
- First attempt used a `while` loop to walk to a NULL child and attach the new node
- Root problem: loop condition `while(temp->left_node != NULL || temp->right_node != NULL)` stops at *any* node with a NULL child — not necessarily the correct insertion point
- Guided discovery: traced through inserting 5 into a tree with 10→left=3; loop stops at 10 immediately, never reaches 3
- Fix: rewrote as recursive insert returning the updated subtree root; each call wires its result back via `node->left_node = insert(node->left_node, value)`

**Why recursive insert works — key insight:**
```
insert(NULL, 5)       → create and return new node(5)
insert(node=10, 5):
    5 < 10 → node->left = insert(node->left, 5)
                         → returns node(5)
    node(10)->left = node(5) ✅
    return node(10)
```
Each level returns the same root it received (unchanged), except the bottom which returns a new node. The assignment wires it in.

**Bug 5 — `search`: never checked current node**
- Went straight to recursing left/right without checking `if (node->value == value) return true`
- Result: always returned false even when value was present
- Fix: add the equality check at the top, before recursing

**Bug 6 — `search`: both `if` conditions could fire**
- Same problem as insert — two separate `if` statements instead of `else if`
- Fix: restructured to `if (==) return true; else if (<) recurse left; else recurse right`

**Bug 7 — `delete` two-children case: lost left subtree (Approach 1)**
- Moved `node` pointer to `node->right_node` to find the successor
- This discarded the reference to the original node's left subtree entirely — memory leak + structural corruption
- Fix: abandoned this approach

**Bug 8 — `delete` two-children case: successor loop went too far (Approach 2)**
- Wrote `while(successor != NULL) successor = successor->left_node`
- This goes until `successor` IS NULL — then `successor->value` on the next line dereferences NULL → crash
- Same off-by-one as the `left_most_node` helper written earlier
- Fix: `while(successor->left_node != NULL)` — stop when the *child* is NULL, not the node itself

### Final Working Delete (two-children case)
```c
struct Node *successor = node->right_node;
while(successor->left_node != NULL) successor = successor->left_node;
node->value = successor->value;          // copy value in place
node->right_node = delete(node->right_node, successor->value);  // delete successor
```

---

### Traversal

```c
void inorder(struct Node* node){
    if (node == NULL) return;
    inorder(node->left_node);
    printf("%i\t", node->value);
    inorder(node->right_node);
}
```

- Inorder output was sorted → confirmed BST structure correct
- Deleting leaf (17): output dropped 17 ✅
- Deleting node with two children (10): replaced by 13 (inorder successor), BST valid ✅

---

## Overall Session Notes

| Step | Operation | Approach | Core Bug Resolved |
|---|---|---|---|
| 1a | `insert` | Iterative → abandoned | Loop condition stopped at wrong node |
| 1b | `insert` | Recursive (return root) | Understood wire-back-up pattern |
| 1c | `search` | Recursive | Missing equality check, fixed else-if |
| 1d | `delete` (leaf) | Direct free + return NULL | Worked first try |
| 1e | `delete` (one child) | Return surviving child | Worked first try |
| 1f | `delete` (two children) | Successor copy + recurse | Two attempts; loop off-by-one fixed |

**Key Lessons:**
- Recursive BST operations return the updated subtree root — this is what wires new nodes and deletions in on the way back up
- `malloc(sizeof(struct Node*))` vs `malloc(sizeof(struct Node))` — always malloc the struct, not the pointer type
- Stop condition `while(ptr->child != NULL)` vs `while(ptr != NULL)` — the former stops *at* the node before NULL, the latter goes *past* it
- Two separate `if` conditions on complementary ranges is a bug waiting to happen — always use `else if`
- Inorder traversal producing sorted output is the gold-standard sanity check for a BST

---

## Session 04 — What's Next

Per `data_structures_complete.md` progress, next candidates:
- **Heaps & Priority Queues** — binary heap, heapify, heap sort
- **AVL Trees** — self-balancing BST, rotation logic

> BST is complete. Heaps are the natural next step — they share the tree mental model but with different invariants and array-based implementation.
