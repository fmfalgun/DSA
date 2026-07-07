**Finding the k-th Largest Element Using a Min-Heap (C++)**

---

### Problem Statement

> Given an unsorted array of integers and an integer _k_, find the _k_-th largest element in the array.

---

### Key Idea: Min-Heap of Size _k_

1. **Maintain a min-heap** (smallest at top) of the _k_ largest elements seen so far.
2. **Process elements** one by one:
   - **Push** the current element into the heap.
   - If the heap size exceeds _k_, **pop** the smallest (heap top).
3. After processing all elements, the heap top is the _k_-th largest element.

**Why a min-heap?**
- Keeps the _k_ largest elements in the heap.
- The smallest among these _k_ elements (the _k_-th largest overall) is always at the top, enabling O(1) retrieval.

---

### C++ `priority_queue` Configuration

```cpp
std::priority_queue<int,
    std::vector<int>,
    std::greater<int>> minHeap;
```

- **`int`**: Type of elements.
- **`vector<int>`**: Underlying container.
- **`greater<int>`**: Comparator that makes the queue a **min-heap** (default is `less<int>` for max-heap).

---

### Step-by-Step Example

```cpp
nums = {3, 2, 1, 5, 6, 4}, k = 2
```  

| Step | Action                       | Heap Contents | Explanation                                   |
|------|------------------------------|---------------|-----------------------------------------------|
| 1    | Insert 3                     | [3]           |                                        |
| 2    | Insert 2                     | [2, 3]        |                                        |
| 3    | Insert 1 → size > 2 → pop    | [2, 3]        | After pushing 1 → [1,3,2], pop 1 → [2,3]     |
| 4    | Insert 5 → size > 2 → pop    | [3, 5]        | After pushing 5 → [2,3,5], pop 2 → [3,5]     |
| 5    | Insert 6 → size > 2 → pop    | [5, 6]        | After pushing 6 → [3,5,6], pop 3 → [5,6]     |
| 6    | Insert 4 → size > 2 → pop    | [5, 6]        | After pushing 4 → [4,6,5], pop 4 → [5,6]     |

**Result:** `minHeap.top()` = 5 → the 2nd largest element.

---

### C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <queue>

int findKthLargest(const std::vector<int>& nums, int k) {
    std::priority_queue<int,
        std::vector<int>,
        std::greater<int>> minHeap;

    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k)
            minHeap.pop();
    }

    return minHeap.top();
}

int main() {
    std::vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;
    std::cout << "The " << k << "-th largest element is "
              << findKthLargest(nums, k) << std::endl;
    return 0;
}
```

**Complexities:**
- **Time:** O(n log k)
- **Space:** O(k)

---

### Tips for Visualization

- Draw the heap as a binary tree or array after each insertion.
- Verify the heap property (parent ≤ children) but expect children out of sorted order.
- Focus on the top element as the current candidate for the _k_-th largest.

---

*Store this note and revisit when preparing for interviews or coding practice!*


