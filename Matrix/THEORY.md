# Matrix

A 2D array treated as its own topic because matrix problems have their own recurring tricks (in-place rotation, layer-by-layer traversal, exploiting row/column sort order) distinct from flat-array techniques.

## Canonical DSA-450 Problems

From Love Babbar's sheet:

| Problem | Difficulty | LeetCode |
|---|---|---|
| Spiral traversal on a Matrix | Medium | #54 |
| Search an element in a sorted matrix | Easy | #74 |
| Find median in a row wise sorted matrix | Hard | — |
| Find row with maximum no. of 1s | Easy | — |
| Print elements in sorted order using row-column wise sorted matrix | Medium | — |
| Maximum size rectangle | Medium | #85 |

## Common Techniques

- **Boundary/layer traversal** — spiral order, rotate by layers instead of full transpose+reverse when rotation must be in-place.
- **Binary search on 2D structure** — when rows and columns are both sorted, search can often be reduced to O(m+n) or O(log(m*n)) instead of O(m*n).
- **Row/column prefix tricks** — histogram-style reduction (e.g. "maximum size rectangle" reduces to largest-rectangle-in-histogram run per row).
