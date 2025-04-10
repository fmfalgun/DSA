# Arrays - From Basics to Advanced Techniques

Arrays are one of the most fundamental data structures in programming - a collection of elements stored at contiguous memory locations, accessed using indices.

## Key Characteristics

- Fixed size in most languages (though dynamic arrays like ArrayList, Vector, or List exist)
- O(1) time complexity for random access
- O(n) time complexity for insertion/deletion (except at the end for dynamic arrays)
- Elements are stored contiguously in memory

## Core Operations

```
Access: array[index]          // O(1)
Insertion: Add at end         // O(1) amortized for dynamic arrays
Insertion: Add at middle      // O(n) - need to shift elements
Deletion: From end            // O(1) for dynamic arrays
Deletion: From middle         // O(n) - need to shift elements
Search: Unsorted array        // O(n)
Search: Sorted array          // O(log n) with binary search
```

## Problems - Easy Level

### Problem 1: Two Sum
**Problem**: Given an array of integers and a target, return indices of two numbers that add up to the target.

```python
def two_sum(nums, target):
    seen = {}  # value -> index
    for i, num in enumerate(nums):
        complement = target - num
        if complement in seen:
            return [seen[complement], i]
        seen[num] = i
    return []

# Example
print(two_sum([2, 7, 11, 15], 9))  # Output: [0, 1]
```

**Approach**: Use a hash map to store values we've seen so far. For each number, check if its complement exists.

### Problem 2: Maximum Subarray
**Problem**: Find the contiguous subarray with the largest sum.

```python
def max_subarray(nums):
    if not nums:
        return 0
    
    current_sum = max_sum = nums[0]
    
    for num in nums[1:]:
        current_sum = max(num, current_sum + num)
        max_sum = max(max_sum, current_sum)
    
    return max_sum

# Example
print(max_subarray([-2, 1, -3, 4, -1, 2, 1, -5, 4]))  # Output: 6
```

**Approach**: Kadane's Algorithm - Keep track of the maximum subarray sum ending at the current position.

### Problem 3: Merge Intervals
**Problem**: Merge all overlapping intervals.

```python
def merge(intervals):
    if not intervals:
        return []
    
    # Sort by start time
    intervals.sort(key=lambda x: x[0])
    
    merged = [intervals[0]]
    
    for interval in intervals[1:]:
        # If current interval overlaps with the latest merged interval
        if interval[0] <= merged[-1][1]:
            # Update end time of the latest merged interval
            merged[-1][1] = max(merged[-1][1], interval[1])
        else:
            # Add the current interval
            merged.append(interval)
    
    return merged

# Example
print(merge([[1,3],[2,6],[8,10],[15,18]]))  # Output: [[1,6],[8,10],[15,18]]
```

**Approach**: Sort intervals by start time and then merge overlapping ones.

## Problems - Medium Level

### Problem 4: Next Permutation
**Problem**: Rearrange numbers to form the lexicographically next greater permutation.

```python
def next_permutation(nums):
    n = len(nums)
    
    # Find the first decreasing element from the right
    i = n - 2
    while i >= 0 and nums[i] >= nums[i+1]:
        i -= 1
    
    if i >= 0:
        # Find the element just larger than nums[i]
        j = n - 1
        while nums[j] <= nums[i]:
            j -= 1
        
        # Swap
        nums[i], nums[j] = nums[j], nums[i]
    
    # Reverse the subarray after position i
    left, right = i + 1, n - 1
    while left < right:
        nums[left], nums[right] = nums[right], nums[left]
        left += 1
        right -= 1
    
    return nums

# Example
print(next_permutation([1,2,3]))  # Output: [1,3,2]
```

**Approach**: Find the first decreasing element from the right, swap it with the smallest element greater than it to the right, then reverse the right subarray.

### Problem 5: Rotate Image
**Problem**: Rotate an n×n matrix 90 degrees clockwise in-place.

```python
def rotate(matrix):
    n = len(matrix)
    
    # Transpose the matrix
    for i in range(n):
        for j in range(i, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
    
    # Reverse each row
    for i in range(n):
        left, right = 0, n - 1
        while left < right:
            matrix[i][left], matrix[i][right] = matrix[i][right], matrix[i][left]
            left += 1
            right -= 1
    
    return matrix

# Example
matrix = [
    [1,2,3],
    [4,5,6],
    [7,8,9]
]
print(rotate(matrix))  # Output: [[7,4,1],[8,5,2],[9,6,3]]
```

**Approach**: First transpose the matrix (swap rows with columns), then reverse each row.

### Problem 6: First Missing Positive
**Problem**: Find the smallest missing positive integer in an array in O(n) time and O(1) space.

```python
def first_missing_positive(nums):
    n = len(nums)
    
    # Use the array itself as a hash table
    # Place each number at its correct position (nums[i-1] = i)
    for i in range(n):
        while 1 <= nums[i] <= n and nums[nums[i]-1] != nums[i]:
            nums[nums[i]-1], nums[i] = nums[i], nums[nums[i]-1]
    
    # Find the first position where the number doesn't match
    for i in range(n):
        if nums[i] != i + 1:
            return i + 1
    
    # If all positions are filled correctly, the answer is n+1
    return n + 1

# Example
print(first_missing_positive([3,4,-1,1]))  # Output: 2
```

**Approach**: Use the array itself as a hash table by placing each number at its correct position.

### Problem 7: Trapping Rain Water
**Problem**: Given an array representing elevation map, calculate how much rainwater can be trapped.

```python
def trap(height):
    if not height:
        return 0
    
    left, right = 0, len(height) - 1
    left_max = height[left]
    right_max = height[right]
    water = 0
    
    while left < right:
        if left_max < right_max:
            left += 1
            left_max = max(left_max, height[left])
            water += left_max - height[left]
        else:
            right -= 1
            right_max = max(right_max, height[right])
            water += right_max - height[right]
    
    return water

# Example
print(trap([0,1,0,2,1,0,1,3,2,1,2,1]))  # Output: 6
```

**Approach**: Use two pointers to track maximum heights from left and right, calculating trapped water at each position.

## Problems - Hard Level

### Problem 8: Jump Game II
**Problem**: Find minimum number of jumps to reach the last index.

```python
def jump(nums):
    n = len(nums)
    if n <= 1:
        return 0
    
    jumps = 1
    current_max_reach = nums[0]
    next_max_reach = nums[0]
    
    for i in range(1, n-1):
        next_max_reach = max(next_max_reach, i + nums[i])
        
        if i == current_max_reach:
            jumps += 1
            current_max_reach = next_max_reach
    
    return jumps

# Example
print(jump([2,3,1,1,4]))  # Output: 2
```

**Approach**: Greedy algorithm to keep track of the furthest position that can be reached with a given number of jumps.

### Problem 9: Sliding Window Maximum
**Problem**: Find the maximum element in each sliding window of size k.

```python
from collections import deque

def maxSlidingWindow(nums, k):
    result = []
    queue = deque()  # Store indices
    
    for i, num in enumerate(nums):
        # Remove elements outside the window
        while queue and queue[0] < i - k + 1:
            queue.popleft()
        
        # Remove smaller elements (they won't be maximum)
        while queue and nums[queue[-1]] < num:
            queue.pop()
        
        queue.append(i)
        
        # Add to result when we have a full window
        if i >= k - 1:
            result.append(nums[queue[0]])
    
    return result

# Example
print(maxSlidingWindow([1,3,-1,-3,5,3,6,7], 3))  # Output: [3,3,5,5,6,7]
```

**Approach**: Use a monotonic deque to maintain potential maximum values within the window.

### Problem 10: Median of Two Sorted Arrays
**Problem**: Find the median of two sorted arrays with O(log(m+n)) time complexity.

```python
def findMedianSortedArrays(nums1, nums2):
    # Ensure nums1 is the shorter array
    if len(nums1) > len(nums2):
        nums1, nums2 = nums2, nums1
    
    x, y = len(nums1), len(nums2)
    low, high = 0, x
    
    while low <= high:
        partitionX = (low + high) // 2
        partitionY = (x + y + 1) // 2 - partitionX
        
        # If partitionX is 0, use -infinity for maxX
        # If partitionX is x, use infinity for minX
        maxX = float('-inf') if partitionX == 0 else nums1[partitionX - 1]
        minX = float('inf') if partitionX == x else nums1[partitionX]
        
        maxY = float('-inf') if partitionY == 0 else nums2[partitionY - 1]
        minY = float('inf') if partitionY == y else nums2[partitionY]
        
        if maxX <= minY and maxY <= minX:
            # Found the correct partition
            # If total length is odd
            if (x + y) % 2 != 0:
                return max(maxX, maxY)
            # If total length is even
            else:
                return (max(maxX, maxY) + min(minX, minY)) / 2
        elif maxX > minY:
            high = partitionX - 1
        else:
            low = partitionX + 1
    
    raise ValueError("Input arrays are not sorted")

# Example
print(findMedianSortedArrays([1, 3], [2]))  # Output: 2.0
print(findMedianSortedArrays([1, 2], [3, 4]))  # Output: 2.5
```

**Approach**: Binary search to find the partition point that divides both arrays into left and right halves, then calculate median.

### Problem 11: Maximum Product Subarray
**Problem**: Find the contiguous subarray with the largest product.

```python
def maxProduct(nums):
    if not nums:
        return 0
    
    max_so_far = min_so_far = result = nums[0]
    
    for num in nums[1:]:
        # Store previous values before updating
        temp_max = max_so_far
        temp_min = min_so_far
        
        # Update max_so_far and min_so_far
        max_so_far = max(num, temp_max * num, temp_min * num)
        min_so_far = min(num, temp_max * num, temp_min * num)
        
        # Update result
        result = max(result, max_so_far)
    
    return result

# Example
print(maxProduct([2,3,-2,4]))  # Output: 6
print(maxProduct([-2,0,-1]))   # Output: 0
```

**Approach**: Track both max and min products ending at the current position (since negatives can turn a minimum into maximum).

### Problem 12: Longest Consecutive Sequence
**Problem**: Find the length of the longest consecutive elements sequence in an unsorted array in O(n) time.

```python
def longestConsecutive(nums):
    if not nums:
        return 0
    
    num_set = set(nums)
    longest_streak = 0
    
    for num in num_set:
        # Only start counting sequences from the smallest element
        if num - 1 not in num_set:
            current_num = num
            current_streak = 1
            
            # Count consecutive numbers
            while current_num + 1 in num_set:
                current_num += 1
                current_streak += 1
            
            longest_streak = max(longest_streak, current_streak)
    
    return longest_streak

# Example
print(longestConsecutive([100,4,200,1,3,2]))  # Output: 4
```

**Approach**: Use a hash set to check for consecutive elements efficiently, only starting sequences from the smallest element of each sequence.

## Problems - Advanced Level

### Problem 13: Subarray Sum Equals K
**Problem**: Find the total number of continuous subarrays whose sum equals k.

```python
def subarraySum(nums, k):
    count = 0
    prefix_sum = 0
    sum_count = {0: 1}  # Initialize with 0 sum having count 1
    
    for num in nums:
        prefix_sum += num
        # If (prefix_sum - k) exists in the map, it means there's a subarray with sum k
        if prefix_sum - k in sum_count:
            count += sum_count[prefix_sum - k]
        
        # Update the prefix sum count
        sum_count[prefix_sum] = sum_count.get(prefix_sum, 0) + 1
    
    return count

# Example
print(subarraySum([1,1,1], 2))  # Output: 2
print(subarraySum([1,2,3], 3))  # Output: 2
```

**Approach**: Use a prefix sum technique with a hash map to track the count of each running sum, allowing O(1) lookup of complementary sums.

### Problem 14: Container With Most Water
**Problem**: Find two lines, which, together with the x-axis, form a container that holds the most water.

```python
def maxArea(height):
    left, right = 0, len(height) - 1
    max_area = 0
    
    while left < right:
        # Calculate area with current bounds
        area = min(height[left], height[right]) * (right - left)
        max_area = max(max_area, area)
        
        # Move the smaller height pointer inward
        if height[left] < height[right]:
            left += 1
        else:
            right -= 1
    
    return max_area

# Example
print(maxArea([1,8,6,2,5,4,8,3,7]))  # Output: 49
```

**Approach**: Use two pointers starting from the ends, moving the pointer with smaller height inward (since width decreases, we need to maximize height).

### Problem 15: 4Sum
**Problem**: Find all unique quadruplets that sum to a target value.

```python
def fourSum(nums, target):
    nums.sort()
    n = len(nums)
    result = []
    
    for i in range(n - 3):
        # Skip duplicates
        if i > 0 and nums[i] == nums[i - 1]:
            continue
            
        for j in range(i + 1, n - 2):
            # Skip duplicates
            if j > i + 1 and nums[j] == nums[j - 1]:
                continue
                
            left, right = j + 1, n - 1
            
            while left < right:
                curr_sum = nums[i] + nums[j] + nums[left] + nums[right]
                
                if curr_sum < target:
                    left += 1
                elif curr_sum > target:
                    right -= 1
                else:
                    result.append([nums[i], nums[j], nums[left], nums[right]])
                    
                    # Skip duplicates
                    while left < right and nums[left] == nums[left + 1]:
                        left += 1
                    while left < right and nums[right] == nums[right - 1]:
                        right -= 1
                        
                    left += 1
                    right -= 1
    
    return result

# Example
print(fourSum([1,0,-1,0,-2,2], 0))  # Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
```

**Approach**: Sort the array and use a combination of iteration and two-pointer technique to find quadruplets, with careful handling of duplicates.

### Problem 16: Shortest Unsorted Continuous Subarray
**Problem**: Find the shortest subarray that needs to be sorted for the entire array to become sorted.

```python
def findUnsortedSubarray(nums):
    n = len(nums)
    if n <= 1:
        return 0
    
    # Find the first element that is out of order from left
    left = 0
    while left < n - 1 and nums[left] <= nums[left + 1]:
        left += 1
    
    # If already sorted
    if left == n - 1:
        return 0
    
    # Find the first element that is out of order from right
    right = n - 1
    while right > 0 and nums[right] >= nums[right - 1]:
        right -= 1
    
    # Find the min and max values in the unsorted subarray
    sub_min = min(nums[left:right + 1])
    sub_max = max(nums[left:right + 1])
    
    # Extend left bound
    while left > 0 and nums[left - 1] > sub_min:
        left -= 1
    
    # Extend right bound
    while right < n - 1 and nums[right + 1] < sub_max:
        right += 1
    
    return right - left + 1

# Example
print(findUnsortedSubarray([2,6,4,8,10,9,15]))  # Output: 5
```

**Approach**: Find the boundaries of the unsorted subarray, then extend them to ensure all smaller/larger elements are included.

## Problems - Expert Level

### Problem 17: Spiral Matrix
**Problem**: Return all elements of a matrix in spiral order.

```python
def spiralOrder(matrix):
    if not matrix:
        return []
    
    result = []
    rows, cols = len(matrix), len(matrix[0])
    top, bottom = 0, rows - 1
    left, right = 0, cols - 1
    
    while top <= bottom and left <= right:
        # Traverse right
        for j in range(left, right + 1):
            result.append(matrix[top][j])
        top += 1
        
        # Traverse down
        for i in range(top, bottom + 1):
            result.append(matrix[i][right])
        right -= 1
        
        # Traverse left (if needed)
        if top <= bottom:
            for j in range(right, left - 1, -1):
                result.append(matrix[bottom][j])
            bottom -= 1
        
        # Traverse up (if needed)
        if left <= right:
            for i in range(bottom, top - 1, -1):
                result.append(matrix[i][left])
            left += 1
    
    return result

# Example
matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]
print(spiralOrder(matrix))  # Output: [1,2,3,6,9,8,7,4,5]
```

**Approach**: Use four pointers to track the boundaries and process layers of the matrix in a spiral pattern.

### Problem 18: Count of Smaller Numbers After Self
**Problem**: Count for each element in the array how many smaller elements appear after it.

```python
def countSmaller(nums):
    def merge_sort(enum):
        half = len(enum) // 2
        if half:
            left, right = merge_sort(enum[:half]), merge_sort(enum[half:])
            for i in range(len(enum) - 1, -1, -1):
                if not right or (left and left[-1][1] > right[-1][1]):
                    result[left[-1][0]] += len(right)
                    enum[i] = left.pop()
                else:
                    enum[i] = right.pop()
        return enum
    
    result = [0] * len(nums)
    merge_sort(list(enumerate(nums)))
    return result

# Example
print(countSmaller([5,2,6,1]))  # Output: [2,1,1,0]
```

**Approach**: Use a modified merge sort to count inversions, which represent smaller elements to the right.

### Problem 19: Maximum Sum of 3 Non-Overlapping Subarrays
**Problem**: Find three non-overlapping subarrays of size k with the largest sum.

```python
def maxSumOfThreeSubarrays(nums, k):
    n = len(nums)
    
    # Compute prefix sums for efficient subarray sum calculation
    prefix_sum = [0] * (n + 1)
    for i in range(n):
        prefix_sum[i + 1] = prefix_sum[i] + nums[i]
    
    # Function to get subarray sum
    def get_sum(start, end):
        return prefix_sum[end] - prefix_sum[start]
    
    # Arrays to track maximum sum and its position
    left_max = [0] * n  # Max sum of single subarray starting from 0 to i
    left_idx = [0] * n  # Starting position for left_max[i]
    
    # Compute left_max and left_idx
    curr_max_sum = get_sum(0, k)
    for i in range(k, n):
        if get_sum(i - k + 1, i + 1) > curr_max_sum:
            curr_max_sum = get_sum(i - k + 1, i + 1)
            left_idx[i] = i - k + 1
        else:
            left_idx[i] = left_idx[i - 1]
        left_max[i] = curr_max_sum
    
    # Arrays for right max (from right to left)
    right_max = [0] * n
    right_idx = [0] * n
    
    # Compute right_max and right_idx
    curr_max_sum = get_sum(n - k, n)
    right_max[n - k] = curr_max_sum
    right_idx[n - k] = n - k
    
    for i in range(n - k - 1, -1, -1):
        if get_sum(i, i + k) >= curr_max_sum:
            curr_max_sum = get_sum(i, i + k)
            right_idx[i] = i
        else:
            right_idx[i] = right_idx[i + 1]
        right_max[i] = curr_max_sum
    
    # Find the best combination
    max_total = 0
    result = [0, 0, 0]  # Starting positions of three subarrays
    
    # Try each possible middle subarray
    for mid_start in range(k, n - 2 * k + 1):
        mid_end = mid_start + k
        left_sum = left_max[mid_start - 1]
        right_sum = right_max[mid_end]
        
        total = left_sum + get_sum(mid_start, mid_end) + right_sum
        
        if total > max_total:
            max_total = total
            result = [left_idx[mid_start - 1], mid_start, right_idx[mid_end]]
    
    return result

# Example
print(maxSumOfThreeSubarrays([1,2,1,2,6,7,5,1], 2))  # Output: [0,3,5]
```

**Approach**: Use prefix sums for efficient subarray sum calculation, and dynamic programming to track the best positions from both left and right.

### Problem 20: Longest Increasing Path in a Matrix
**Problem**: Find the length of the longest increasing path in a matrix.

```python
def longestIncreasingPath(matrix):
    if not matrix or not matrix[0]:
        return 0
    
    rows, cols = len(matrix), len(matrix[0])
    memo = {}  # (i, j) -> longest path length starting at (i, j)
    
    def dfs(i, j):
        if (i, j) in memo:
            return memo[(i, j)]
        
        # Four directions: up, right, down, left
        directions = [(-1, 0), (0, 1), (1, 0), (0, -1)]
        max_length = 1  # Minimum path length is 1 (the cell itself)
        
        for di, dj in directions:
            ni, nj = i + di, j + dj
            
            # Check if in bounds and value is greater
            if (0 <= ni < rows and 0 <= nj < cols and 
                matrix[ni][nj] > matrix[i][j]):
                max_length = max(max_length, 1 + dfs(ni, nj))
        
        memo[(i, j)] = max_length
        return max_length
    
    # Try starting from each cell
    max_path = 0
    for i in range(rows):
        for j in range(cols):
            max_path = max(max_path, dfs(i, j))
    
    return max_path

# Example
matrix = [
    [9,9,4],
    [6,6,8],
    [2,1,1]
]
print(longestIncreasingPath(matrix))  # Output: 4
```

**Approach**: Use DFS with memoization to avoid recomputing paths, exploring all possible increasing paths from each cell.

## Problems - Elite Level

### Problem 21: Kth Smallest Element in a Sorted Matrix
**Problem**: Find the kth smallest element in a matrix where each row and column is sorted.

```python
import heapq

def kthSmallest(matrix, k):
    n = len(matrix)
    
    # Create min heap with elements from the first row
    # Each element is (value, row, col)
    min_heap = [(matrix[0][j], 0, j) for j in range(n)]
    heapq.heapify(min_heap)
    
    # Pop k-1 elements
    for _ in range(k - 1):
        _, i, j = heapq.heappop(min_heap)
        
        # If there's a next element in the same column, add it
        if i + 1 < n:
            heapq.heappush(min_heap, (matrix[i + 1][j], i + 1, j))
    
    # The kth element is at the top of the heap
    return heapq.heappop(min_heap)[0]

# Example
matrix = [
   [1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
]
print(kthSmallest(matrix, 8))  # Output: 13
```

**Approach**: Use a min-heap to efficiently track the next smallest elements across all rows, starting from the top-left corner.

### Problem 22: Number of Subarrays with Bounded Maximum
**Problem**: Count the number of contiguous subarrays where the maximum element is between L and R.

```python
def numSubarrayBoundedMax(nums, left, right):
    result = 0
    start = -1
    end = -1
    
    for i, num in enumerate(nums):
        # If num > right, reset start
        if num > right:
            start = i
        
        # If num >= left, update end
        if num >= left:
            end = i
        
        # Add number of valid subarrays ending at current position
        result += end - start
    
    return result

# Example
print(numSubarrayBoundedMax([2,1,4,3], 2, 3))  # Output: 3
```

**Approach**: Use a sliding window technique to track the positions of elements below, within, and above the given range.

### Problem 23: Largest Rectangle in Histogram
**Problem**: Find the area of the largest rectangle in a histogram.

```python
def largestRectangleArea(heights):
    n = len(heights)
    stack = []  # Stack of indices
    max_area = 0
    
    for i in range(n + 1):
        # When reaching the end or finding a lower height
        current_height = 0 if i == n else heights[i]
        
        while stack and heights[stack[-1]] > current_height:
            height = heights[stack.pop()]
            # Calculate width based on the stack
            width = i if not stack else i - stack[-1] - 1
            max_area = max(max_area, height * width)
        
        stack.append(i)
    
    return max_area

# Example
print(largestRectangleArea([2,1,5,6,2,3]))  # Output: 10
```

**Approach**: Use a stack to track increasing heights, calculating areas when a smaller height is encountered.

### Problem 24: Max Points on a Line
**Problem**: Find the maximum number of points that lie on the same straight line.

```python
from collections import defaultdict
import math

def maxPoints(points):
    n = len(points)
    if n <= 2:
        return n
    
    max_points = 0
    
    for i in range(n):
        slopes = defaultdict(int)
        duplicates = 0
        
        for j in range(n):
            if i == j:
                continue
                
            x1, y1 = points[i][0], points[i][1]
            x2, y2 = points[j][0], points[j][1]
            
            # Check for duplicates
            if x1 == x2 and y1 == y2:
                duplicates += 1
                continue
            
            # Calculate slope
            if x2 - x1 == 0:
                slope = float('inf')
            else:
                slope = (y2 - y1) / (x2 - x1)
                # Handle negative zero
                if slope == 0:
                    slope = 0
            
            slopes[slope] += 1
        
        # Find max points on a line with the current point as reference
        current_max = max(slopes.values()) if slopes else 0
        max_points = max(max_points, current_max + duplicates + 1)  # +1 for the point itself
    
    return max_points

# Example
print(maxPoints([[1,1],[2,2],[3,3]]))  # Output: 3
print(maxPoints([[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]))  # Output: 4
```

**Approach**: For each point, calculate the slope with all other points. Points with the same slope lie on the same line. Use a hash map to count points with the same slope relative to the current point.

### Problem 25: Skyline Problem
**Problem**: Given the locations and heights of buildings, determine the skyline formed.

```python
import heapq

def getSkyline(buildings):
    # Process building events (start and end points)
    events = []
    for left, right, height in buildings:
        # Negative height for start to ensure starts come before ends of same height
        events.append((left, -height, right))
        events.append((right, 0, 0))  # End event
    
    events.sort()  # Sort by x-coordinate
    
    result = []
    # Max heap to track current heights (-height for max heap)
    heap = [(0, float('inf'))]  # (height, ending position)
    prev_max = 0
    
    for x, neg_h, right in events:
        # Remove buildings that have ended
        while heap[0][1] <= x:
            heapq.heappop(heap)
        
        # Add new building
        if neg_h != 0:
            heapq.heappush(heap, (neg_h, right))
        
        # If max height changed, add to skyline
        current_max = -heap[0][0]
        if current_max != prev_max:
            result.append([x, current_max])
            prev_max = current_max
    
    return result

# Example
buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
print(getSkyline(buildings))
# Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
```

**Approach**: Treat building endpoints as events, use a max heap to track current heights, and record height changes for the skyline.

### Problem 26: Sliding Window Median
**Problem**: Find the median in each sliding window of size k.

```python
import heapq
from collections import defaultdict

def medianSlidingWindow(nums, k):
    result = []
    # Two heaps approach
    small = []  # Max heap for smaller half (-value for max heap)
    large = []  # Min heap for larger half
    
    # Dict to track removed elements for lazy deletion
    removed = defaultdict(int)
    
    # Helper to find the current median
    def get_median():
        if k % 2 == 1:
            return large[0]
        else:
            return (large[0] - small[0]) / 2.0
    
    # Helper to balance heaps and remove marked elements
    def balance():
        # Remove marked elements from small
        while small and removed[-small[0]] > 0:
            removed[-small[0]] -= 1
            heapq.heappop(small)
            
        # Remove marked elements from large
        while large and removed[large[0]] > 0:
            removed[large[0]] -= 1
            heapq.heappop(large)
            
        # Balance the heaps
        if len(large) > len(small) + 1:
            val = heapq.heappop(large)
            heapq.heappush(small, -val)
        elif len(small) > len(large):
            val = -heapq.heappop(small)
            heapq.heappush(large, val)
    
    # Process first k elements
    for i in range(k):
        heapq.heappush(large, nums[i])
    
    # Balance by moving half to small heap
    for _ in range(k // 2):
        val = heapq.heappop(large)
        heapq.heappush(small, -val)
    
    # Process the windows
    for i in range(k, len(nums) + 1):
        # Add current median to result
        result.append(get_median())
        
        if i == len(nums):
            break
            
        # Remove leftmost element (nums[i-k])
        outgoing = nums[i - k]
        if outgoing <= -small[0] if small else float('inf'):
            removed[-outgoing] += 1  # Mark for removal from small
        else:
            removed[outgoing] += 1   # Mark for removal from large
            
        # Add new element
        incoming = nums[i]
        if small and incoming <= -small[0]:
            heapq.heappush(small, -incoming)
        else:
            heapq.heappush(large, incoming)
            
        # Rebalance
        balance()
    
    return result

# Example
print(medianSlidingWindow([1,3,-1,-3,5,3,6,7], 3))
# Output: [1.0,-1.0,-1.0,3.0,5.0,6.0]
```

**Approach**: Maintain two heaps (small and large) and use lazy deletion to efficiently find the median in each window.

### Problem 27: Maximum Sum of Rectangle No Larger Than K
**Problem**: Find the max sum of a rectangle in a 2D matrix that is no larger than k.

```python
import bisect
from collections import deque

def maxSumSubmatrix(matrix, k):
    rows, cols = len(matrix), len(matrix[0])
    max_sum = float('-inf')
    
    # For each starting column
    for start_col in range(cols):
        # Array to store cumulative row sums
        row_sums = [0] * rows
        
        # For each ending column
        for end_col in range(start_col, cols):
            # Update row sums with the current column
            for i in range(rows):
                row_sums[i] += matrix[i][end_col]
            
            # Find max subarray sum no larger than k
            cum_sum = 0
            cum_sums = [0]  # Sorted list of cumulative sums
            
            for row_sum in row_sums:
                cum_sum += row_sum
                # Find the position where cum_sum - k would be inserted
                pos = bisect.bisect_left(cum_sums, cum_sum - k)
                
                # Check if we found a valid previous sum
                if pos < len(cum_sums):
                    max_sum = max(max_sum, cum_sum - cum_sums[pos])
                
                # Insert current cumulative sum in the sorted list
                bisect.insort(cum_sums, cum_sum)
    
    return max_sum

# Example
matrix = [
    [1, 0, 1],
    [0, -2, 3]
]
print(maxSumSubmatrix(matrix, 2))  # Output: 2
```

**Approach**: Use Kadane's algorithm with a binary search on cumulative sums to find the maximum rectangle sum no larger than k.

### Problem 28: Count of Range Sum
**Problem**: Count the number of range sums that lie in [lower, upper] inclusive.

```python
import bisect

def countRangeSum(nums, lower, upper):
    n = len(nums)
    
    # Compute prefix sums
    prefix_sum = [0]
    for num in nums:
        prefix_sum.append(prefix_sum[-1] + num)
    
    def merge_sort(start, end):
        if end - start <= 1:
            return 0
        
        mid = (start + end) // 2
        count = merge_sort(start, mid) + merge_sort(mid, end)
        
        # Count ranges across the mid point
        j = k = mid
        for i in range(start, mid):
            # Find the minimum j where prefix_sum[j] - prefix_sum[i] >= lower
            while j < end and prefix_sum[j] - prefix_sum[i] < lower:
                j += 1
            
            # Find the maximum k where prefix_sum[k] - prefix_sum[i] <= upper
            while k < end and prefix_sum[k] - prefix_sum[i] <= upper:
                k += 1
            
            count += k - j
        
        # Merge the sorted subarrays
        temp = []
        left, right = start, mid
        
        while left < mid and right < end:
            if prefix_sum[left] <= prefix_sum[right]:
                temp.append(prefix_sum[left])
                left += 1
            else:
                temp.append(prefix_sum[right])
                right += 1
        
        # Add remaining elements
        temp.extend(prefix_sum[left:mid])
        temp.extend(prefix_sum[right:end])
        
        # Copy back to prefix_sum
        prefix_sum[start:end] = temp
        
        return count
    
    return merge_sort(0, n + 1)

# Example
print(countRangeSum([-2, 5, -1], -2, 2))  # Output: 3
```

**Approach**: Use a divide-and-conquer approach with merge sort to count range sums efficiently.

## Problems - Master Level

### Problem 29: Reverse Pairs
**Problem**: Count the number of important reverse pairs in an array (i < j and nums[i] > 2*nums[j]).

```python
def reversePairs(nums):
    def merge_sort(nums, start, end):
        if end - start <= 1:
            return 0
        
        mid = (start + end) // 2
        count = merge_sort(nums, start, mid) + merge_sort(nums, mid, end)
        
        # Count reverse pairs across the mid point
        j = mid
        for i in range(start, mid):
            while j < end and nums[i] > 2 * nums[j]:
                j += 1
            count += j - mid
        
        # Merge the sorted subarrays
        temp = []
        left, right = start, mid
        
        while left < mid and right < end:
            if nums[left] <= nums[right]:
                temp.append(nums[left])
                left += 1
            else:
                temp.append(nums[right])
                right += 1
        
        # Add remaining elements
        temp.extend(nums[left:mid])
        temp.extend(nums[right:end])
        
        # Copy back to nums
        nums[start:end] = temp
        
        return count
    
    return merge_sort(nums, 0, len(nums))

# Example
print(reversePairs([1,3,2,3,1]))  # Output: 2
print(reversePairs([2,4,3,5,1]))  # Output: 3
```

**Approach**: Use merge sort to count reverse pairs while sorting the array.

### Problem 30: Maximum Gap
**Problem**: Find the maximum gap between successive elements in a sorted array.

```python
def maximumGap(nums):
    if len(nums) < 2:
        return 0
    
    # Find min and max values
    min_val, max_val = min(nums), max(nums)
    
    if min_val == max_val:
        return 0
    
    n = len(nums)
    
    # Compute bucket size and number of buckets
    bucket_size = max(1, (max_val - min_val) // (n - 1))
    bucket_count = (max_val - min_val) // bucket_size + 1
    
    # Initialize buckets
    buckets = [None] * bucket_count
    
    # Fill the buckets
    for num in nums:
        idx = (num - min_val) // bucket_size
        bucket = buckets[idx]
        
        if bucket is None:
            bucket = {'min': num, 'max': num}
            buckets[idx] = bucket
        else:
            bucket['min'] = min(bucket['min'], num)
            bucket['max'] = max(bucket['max'], num)
    
    # Find the maximum gap
    max_gap = 0
    prev_max = min_val
    
    for bucket in buckets:
        if bucket is None:
            continue
        
        max_gap = max(max_gap, bucket['min'] - prev_max)
        prev_max = bucket['max']
    
    return max_gap

# Example
print(maximumGap([3,6,9,1]))  # Output: 3
```

**Approach**: Use the Pigeonhole Principle with buckets to find the maximum gap more efficiently than sorting.

## Key Array Techniques Summary

### 1. Two Pointers
- Used in problems like Container With Most Water, Trapping Rain Water
- Efficient for problems requiring element comparison or window manipulation
- Time complexity typically O(n)

### 2. Sliding Window
- Used for problems like Sliding Window Maximum, Subarray Sum
- Maintains a window that slides through the array
- Efficient for substring/subarray problems

### 3. Prefix Sums
- Used in problems like Subarray Sum Equals K, Maximum Sum Rectangle
- Precomputes cumulative sums for O(1) range sum queries
- Helpful for subarray sum calculations

### 4. Modified Binary Search
- Used in problems like Median of Two Sorted Arrays, Search in Rotated Sorted Array
- Reduces time complexity from O(n) to O(log n)
- Applied to sorted or partially sorted arrays

### 5. Heap/Priority Queue
- Used in problems like Kth Smallest Element, Skyline Problem
- Efficient for maintaining ordered elements with dynamic updates
- Provides O(log n) insertion and removal

### 6. Dynamic Programming
- Used in problems like Maximum Product Subarray, Maximum Sum Rectangle
- Breaks down problems into overlapping subproblems
- Efficiently computes optimal solutions by reusing results

### 7. Divide and Conquer
- Used in problems like Count of Range Sum, Reverse Pairs
- Splits problems into smaller instances, often with merge steps
- Typically combined with techniques like merge sort

### 8. Monotonic Stack/Queue
- Used in problems like Largest Rectangle in Histogram, Sliding Window Maximum
- Maintains elements in increasing/decreasing order
- Efficiently handles next greater/smaller element problems

### 9. Bucket/Pigeonhole Principle
- Used in problems like Maximum Gap
- Divides elements into buckets for more efficient processing
- Exploits mathematical properties to achieve linear time solutions

### 10. Matrix Techniques
- Used in problems like Spiral Matrix, Longest Increasing Path
- Special traversal methods and 2D algorithms
- Often combined with other techniques like DP or BFS/DFS

Mastering these array techniques will equip you to solve virtually any array problem in competitive programming and technical interviews.
