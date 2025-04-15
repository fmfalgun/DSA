# Understanding Queues

A queue is a linear data structure that follows the First In, First Out (FIFO) principle - the first element added is the first one to be removed.

## Basic Operations
- **Enqueue**: Add element to the end (rear)
- **Dequeue**: Remove element from the front
- **Peek/Front**: View the first element without removing
- **IsEmpty**: Check if queue is empty

## Implementation Approaches

### 1. Array-based Queue
```python
class Queue:
    def __init__(self):
        self.items = []
    
    def enqueue(self, item):
        self.items.append(item)
    
    def dequeue(self):
        if not self.is_empty():
            return self.items.pop(0)  # O(n) operation
        return None
    
    def peek(self):
        if not self.is_empty():
            return self.items[0]
        return None
    
    def is_empty(self):
        return len(self.items) == 0
```

### 2. Linked List-based Queue
```python
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Queue:
    def __init__(self):
        self.front = None
        self.rear = None
    
    def enqueue(self, item):
        new_node = Node(item)
        if self.rear is None:
            self.front = self.rear = new_node
            return
        self.rear.next = new_node
        self.rear = new_node
    
    def dequeue(self):
        if self.is_empty():
            return None
        temp = self.front
        self.front = temp.next
        if self.front is None:
            self.rear = None
        return temp.data
    
    def peek(self):
        if self.is_empty():
            return None
        return self.front.data
    
    def is_empty(self):
        return self.front is None
```

### 3. Circular Queue
```python
class CircularQueue:
    def __init__(self, capacity):
        self.capacity = capacity
        self.items = [None] * capacity
        self.front = self.rear = -1
    
    def enqueue(self, item):
        # Check if queue is full
        if (self.rear + 1) % self.capacity == self.front:
            return False
        
        # If queue is empty
        if self.front == -1:
            self.front = self.rear = 0
        else:
            self.rear = (self.rear + 1) % self.capacity
            
        self.items[self.rear] = item
        return True
    
    def dequeue(self):
        if self.front == -1:  # Empty queue
            return None
        
        item = self.items[self.front]
        
        # If only one element
        if self.front == self.rear:
            self.front = self.rear = -1
        else:
            self.front = (self.front + 1) % self.capacity
            
        return item
```

## Practice Problems (Easy to Complex)

### Problem 1: Implement a Queue using Stacks
```
Design a queue that supports push and pop operations using only stacks.
```

**Solution:**
```python
class QueueUsingStacks:
    def __init__(self):
        self.stack1 = []  # for enqueue
        self.stack2 = []  # for dequeue
    
    def enqueue(self, x):
        self.stack1.append(x)
    
    def dequeue(self):
        if not self.stack2:
            while self.stack1:
                self.stack2.append(self.stack1.pop())
        
        if not self.stack2:
            return None
            
        return self.stack2.pop()
    
    def peek(self):
        if not self.stack2:
            while self.stack1:
                self.stack2.append(self.stack1.pop())
        
        if not self.stack2:
            return None
            
        return self.stack2[-1]
    
    def empty(self):
        return not self.stack1 and not self.stack2
```

### Problem 2: Sliding Window Maximum
```
Given an array and a window size k, find the maximum element in each sliding window of size k.
Input: [1,3,-1,-3,5,3,6,7], k=3
Output: [3,3,5,5,6,7]
```

**Solution with Deque:**
```python
from collections import deque

def max_sliding_window(nums, k):
    result = []
    dq = deque()  # will store indices
    
    for i in range(len(nums)):
        # Remove elements outside the window
        while dq and dq[0] < i - k + 1:
            dq.popleft()
        
        # Remove smaller elements
        while dq and nums[dq[-1]] < nums[i]:
            dq.pop()
            
        dq.append(i)
        
        # Add to result when first window is complete
        if i >= k - 1:
            result.append(nums[dq[0]])
            
    return result
```

### Problem 3: Task Scheduler
```
Given a list of tasks (represented by letters A-Z) and a cooling time n, 
find the minimum time to complete all tasks. Same tasks must be n units apart.

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B
```

**Solution:**
```python
from collections import Counter

def least_interval(tasks, n):
    task_counts = Counter(tasks)
    max_freq = max(task_counts.values())
    
    # Count how many tasks have the maximum frequency
    max_count = sum(1 for count in task_counts.values() if count == max_freq)
    
    # Formula explanation:
    # (max_freq - 1) * (n + 1) + max_count
    # (max_freq - 1) -> number of cooling intervals needed
    # (n + 1) -> length of each cycle (task + cooling)
    # max_count -> number of tasks to append at the end
    
    result = (max_freq - 1) * (n + 1) + max_count
    return max(len(tasks), result)  # Can't be less than the number of tasks
```

### Problem 4: Circular Tour / Gas Station
```
There are N gas stations along a circular route, where gas[i] is the amount of gas and cost[i] is the 
cost to travel to the next station. Find the starting gas station's index to complete the circuit.
Return -1 if it's not possible.

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
```

**Solution:**
```python
def can_complete_circuit(gas, cost):
    total_gas = 0
    total_cost = 0
    start_position = 0
    current_gas = 0
    
    for i in range(len(gas)):
        total_gas += gas[i]
        total_cost += cost[i]
        
        current_gas += gas[i] - cost[i]
        
        # If we can't reach the next station from current position
        if current_gas < 0:
            # Try starting from the next station
            start_position = i + 1
            current_gas = 0
    
    # If total gas is less than total cost, it's impossible to complete the circuit
    if total_gas < total_cost:
        return -1
    
    return start_position
```

### Problem 5: Design a Priority Queue (Heap-based)
```
Implement a priority queue with operations: insert, extract_max, and get_max.
```

**Solution:**
```python
class PriorityQueue:
    def __init__(self):
        self.heap = []
    
    def parent(self, i):
        return (i - 1) // 2
    
    def left_child(self, i):
        return 2 * i + 1
    
    def right_child(self, i):
        return 2 * i + 2
    
    def get_max(self):
        if not self.heap:
            return None
        return self.heap[0]
    
    def insert(self, key):
        self.heap.append(key)
        i = len(self.heap) - 1
        
        # Heapify up
        while i > 0 and self.heap[self.parent(i)] < self.heap[i]:
            # Swap with parent
            self.heap[i], self.heap[self.parent(i)] = self.heap[self.parent(i)], self.heap[i]
            i = self.parent(i)
    
    def heapify_down(self, i):
        max_index = i
        left = self.left_child(i)
        right = self.right_child(i)
        
        if left < len(self.heap) and self.heap[left] > self.heap[max_index]:
            max_index = left
            
        if right < len(self.heap) and self.heap[right] > self.heap[max_index]:
            max_index = right
            
        if i != max_index:
            # Swap with largest child
            self.heap[i], self.heap[max_index] = self.heap[max_index], self.heap[i]
            self.heapify_down(max_index)
    
    def extract_max(self):
        if not self.heap:
            return None
        
        max_item = self.heap[0]
        
        # Replace root with last element and remove last
        self.heap[0] = self.heap[-1]
        self.heap.pop()
        
        if self.heap:
            self.heapify_down(0)
            
        return max_item
```

# More Advanced Queue Problems

## Problem 6: Reconstruct Queue by Height

```
You have a number of people standing in a queue, where each person is described by [height, number of people in front with equal or greater height].
Reconstruct the queue.

Input: [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
```

**Solution:**
```python
def reconstructQueue(people):
    # Sort by height (descending) and then by k (ascending)
    people.sort(key=lambda x: (-x[0], x[1]))
    
    result = []
    for person in people:
        # Insert each person at their k position
        result.insert(person[1], person)
    
    return result
```

This approach works by:
1. First sorting people by height in descending order (and by k value when heights are equal)
2. Then inserting each person at position k in the result array
3. Since we process taller people first, inserting at position k works because k refers to number of people with equal or greater height

## Problem 7: Design a Double-ended Queue (Deque)

```
Implement a deque supporting: add_front, add_rear, remove_front, remove_rear operations.
```

**Solution:**
```python
class Deque:
    def __init__(self):
        self.items = []
    
    def add_front(self, item):
        self.items.insert(0, item)
    
    def add_rear(self, item):
        self.items.append(item)
    
    def remove_front(self):
        if not self.is_empty():
            return self.items.pop(0)
        return None
    
    def remove_rear(self):
        if not self.is_empty():
            return self.items.pop()
        return None
    
    def peek_front(self):
        if not self.is_empty():
            return self.items[0]
        return None
    
    def peek_rear(self):
        if not self.is_empty():
            return self.items[-1]
        return None
    
    def is_empty(self):
        return len(self.items) == 0
    
    def size(self):
        return len(self.items)
```

## Problem 8: First Unique Character in a String

```
Given a string, find the first non-repeating character and return its index. If it doesn't exist, return -1.

Input: "leetcode"
Output: 0

Input: "loveleetcode"
Output: 2
```

**Solution using Queue:**
```python
from collections import Counter, deque

def firstUniqChar(s):
    # Count character frequencies
    count = Counter(s)
    
    # Use queue to track characters in order
    queue = deque()
    for i, char in enumerate(s):
        queue.append((char, i))
    
    # Process the queue
    while queue and count[queue[0][0]] > 1:
        queue.popleft()
    
    return queue[0][1] if queue else -1
```

## Problem 9: LRU Cache

```
Design and implement a data structure for Least Recently Used (LRU) cache. 
It should support operations: get and put with O(1) time complexity.

Input: 
LRUCache cache = new LRUCache(2);
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
```

**Solution using Queue and Hash Map:**
```python
from collections import OrderedDict

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = OrderedDict()
    
    def get(self, key):
        if key not in self.cache:
            return -1
        
        # Move this key to the end (most recently used)
        value = self.cache.pop(key)
        self.cache[key] = value
        return value
    
    def put(self, key, value):
        # If key exists, remove it first
        if key in self.cache:
            self.cache.pop(key)
        # If cache is full, remove the least recently used item (first item)
        elif len(self.cache) >= self.capacity:
            self.cache.popitem(last=False)
        
        # Add new key-value pair
        self.cache[key] = value
```

## Problem 10: Maximum Frequency Stack

```
Implement FreqStack, a stack-like data structure that pops the most frequent element. 
If there are multiple elements with the same frequency, pop the most recent one.

Input:
["FreqStack","push","push","push","push","push","push","pop","pop","pop","pop"]
[[],[5],[7],[5],[7],[4],[5],[],[],[],[]]
Output: [null,null,null,null,null,null,null,5,7,5,4]
```

**Solution:**
```python
class FreqStack:
    def __init__(self):
        self.freq = {}  # Map elements to their frequency
        self.group = {}  # Map frequency to a stack of elements
        self.maxfreq = 0
    
    def push(self, x):
        # Update frequency counter
        self.freq[x] = self.freq.get(x, 0) + 1
        f = self.freq[x]
        
        # Update maximum frequency
        if f > self.maxfreq:
            self.maxfreq = f
        
        # Add to the frequency group
        if f not in self.group:
            self.group[f] = []
        self.group[f].append(x)
    
    def pop(self):
        # Get the most frequent element
        x = self.group[self.maxfreq].pop()
        
        # Update frequency counter
        self.freq[x] -= 1
        
        # Update maxfreq if the group becomes empty
        if not self.group[self.maxfreq]:
            self.maxfreq -= 1
            
        return x
```

## Problem 11: Rotten Oranges

```
You are given a grid where each cell contains:
0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.

Every minute, any fresh orange that is adjacent to a rotten orange becomes rotten.
Return the minimum number of minutes needed for all oranges to be rotten or -1 if impossible.

Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
```

**Solution using BFS:**
```python
from collections import deque

def orangesRotting(grid):
    rows, cols = len(grid), len(grid[0])
    fresh_count = 0
    rotten = deque()
    
    # Count fresh oranges and collect position of rotten oranges
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == 1:
                fresh_count += 1
            elif grid[r][c] == 2:
                rotten.append((r, c))
    
    # If no fresh oranges, return 0
    if fresh_count == 0:
        return 0
    
    minutes = 0
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # Right, Down, Left, Up
    
    # BFS using queue
    while rotten and fresh_count > 0:
        minutes += 1
        size = len(rotten)
        
        for _ in range(size):
            r, c = rotten.popleft()
            
            # Check all four adjacent cells
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                
                # If in bounds and a fresh orange, make it rotten
                if (0 <= nr < rows and 0 <= nc < cols and 
                    grid[nr][nc] == 1):
                    grid[nr][nc] = 2
                    fresh_count -= 1
                    rotten.append((nr, nc))
    
    # If there are still fresh oranges, it's impossible to rot all
    return minutes if fresh_count == 0 else -1
```

## Problem 12: Implement a Queue with Max API

```
Implement a queue with an additional max() function that returns the maximum element in the queue in O(1) time.
```

**Solution using Deque:**
```python
from collections import deque

class MaxQueue:
    def __init__(self):
        self.queue = deque()  # Regular queue
        self.max_queue = deque()  # Deque to track maximum values
    
    def enqueue(self, x):
        self.queue.append(x)
        
        # Remove all smaller elements from max_queue
        while self.max_queue and self.max_queue[-1] < x:
            self.max_queue.pop()
        
        self.max_queue.append(x)
    
    def dequeue(self):
        if not self.queue:
            return None
        
        val = self.queue.popleft()
        
        # If the dequeued element is the current maximum, remove it from max_queue too
        if val == self.max_queue[0]:
            self.max_queue.popleft()
            
        return val
    
    def max_value(self):
        if not self.max_queue:
            return None
        
        return self.max_queue[0]
    
    def is_empty(self):
        return len(self.queue) == 0
```

# Advanced Queue Problems and Applications

## Problem 13: Minimum Number of K Consecutive Bit Flips

```
You are given a binary array nums and an integer k.
A k-bit flip is choosing a subarray of length k from nums and simultaneously flipping all the bits.
Return the minimum number of k-bit flips required to make all bits in nums equal to 1, or -1 if it's impossible.

Input: nums = [0,1,0], k = 1
Output: 2

Input: nums = [0,0,0,1,0,1,1,0], k = 3
Output: 3
```

**Solution with Queue:**
```python
from collections import deque

def minKBitFlips(nums, k):
    n = len(nums)
    flips = 0
    queue = deque()  # Queue to track flip operations
    
    for i in range(n):
        # If the current position was affected by a previous flip that ends
        if queue and queue[0] == i:
            queue.popleft()
        
        # Current status after all previous affecting flips
        current_status = nums[i]
        if len(queue) % 2 == 1:
            current_status = 1 - current_status
        
        # If current_status is 0, we need to flip
        if current_status == 0:
            # Cannot flip starting at position n-k+1 or later
            if i + k > n:
                return -1
            
            flips += 1
            queue.append(i + k)
    
    return flips
```

## Problem 14: Shortest Subarray with Sum at Least K

```
Return the length of the shortest, non-empty, contiguous subarray of an array with sum at least k.
If there is no such subarray, return -1.

Input: nums = [2,-1,2], k = 3
Output: 3

Input: nums = [1,2], k = 4
Output: -1
```

**Solution using Deque:**
```python
from collections import deque

def shortestSubarray(nums, k):
    n = len(nums)
    prefix_sum = [0] * (n + 1)
    
    # Calculate prefix sums
    for i in range(n):
        prefix_sum[i + 1] = prefix_sum[i] + nums[i]
    
    result = n + 1  # Initialize with length greater than possible
    dq = deque()
    
    for i in range(n + 1):
        # For each prefix sum, find the leftmost prefix sum that makes the subarray sum >= k
        while dq and prefix_sum[i] - prefix_sum[dq[0]] >= k:
            result = min(result, i - dq.popleft())
        
        # Remove larger prefix sums from the back
        # (they won't lead to a shorter result than the current position)
        while dq and prefix_sum[i] <= prefix_sum[dq[-1]]:
            dq.pop()
        
        dq.append(i)
    
    return result if result <= n else -1
```

## Problem 15: Design Snake Game

```
Design a Snake game that is played on a device with screen size = width x height.
The snake starts at position (0,0) with length 1 unit.
You are given a list of food positions. When snake eats the food, its length grows by 1 unit.
Each time the snake moves, it loses its tail. When a snake moves to a position, it adds that position to the head.
Return the score of the game (the length of the snake) after applying a sequence of moves.

Input: 
width = 3, height = 2, food = [[1,2],[0,1]]
Moves = "RRDL"
Output: 3
```

**Solution using Queue:**
```python
from collections import deque

class SnakeGame:
    def __init__(self, width, height, food):
        self.width = width
        self.height = height
        self.food = food
        self.food_index = 0
        self.score = 0
        
        # Initial position of snake
        self.snake = deque([(0, 0)])
        self.snake_set = {(0, 0)}  # For O(1) lookup
    
    def move(self, direction):
        # Get head position
        head_r, head_c = self.snake[0]
        
        # Update head position based on direction
        if direction == 'U':
            head_r -= 1
        elif direction == 'D':
            head_r += 1
        elif direction == 'L':
            head_c -= 1
        elif direction == 'R':
            head_c += 1
        
        # Check if snake hits border
        if head_r < 0 or head_r >= self.height or head_c < 0 or head_c >= self.width:
            return -1
        
        new_head = (head_r, head_c)
        
        # Check if snake eats food
        if (self.food_index < len(self.food) and 
            head_r == self.food[self.food_index][0] and 
            head_c == self.food[self.food_index][1]):
            # Snake grows, don't remove tail
            self.food_index += 1
            self.score += 1
        else:
            # Remove tail
            tail = self.snake.pop()
            self.snake_set.remove(tail)
        
        # Check if snake bites itself
        if new_head in self.snake_set:
            return -1
        
        # Add new head
        self.snake.appendleft(new_head)
        self.snake_set.add(new_head)
        
        return self.score
```

## Problem 16: Design a Stack with Increment Operation

```
Implement a stack with the following operations:
- push(x): Push element x onto stack
- pop(): Remove the element on top of the stack and return it
- increment(k, val): Increment the bottom k elements of the stack by val

Input:
["CustomStack","push","push","pop","push","push","push","increment","increment","pop","pop","pop","pop"]
[[3],[1],[2],[],[2],[3],[4],[5,100],[2,100],[],[],[],[]]
Output:
[null,null,null,2,null,null,null,null,null,4,3,2,-1]
```

**Solution using Array-based Stack:**
```python
class CustomStack:
    def __init__(self, maxSize):
        self.maxSize = maxSize
        self.stack = []
        self.inc = [0] * maxSize  # Track increments for each position
    
    def push(self, x):
        if len(self.stack) < self.maxSize:
            self.stack.append(x)
    
    def pop(self):
        if not self.stack:
            return -1
        
        i = len(self.stack) - 1
        if i > 0:
            self.inc[i-1] += self.inc[i]  # Pass increment to element below
        
        result = self.stack.pop() + self.inc[i]
        self.inc[i] = 0  # Reset increment for this position
        return result
    
    def increment(self, k, val):
        i = min(k, len(self.stack)) - 1
        if i >= 0:
            self.inc[i] += val
```

## Problem 17: Design a File System

```
Design a file system that simulates the following functions:
- createPath(path, value): Creates a new path and associates a value with it if possible
- get(path): Returns the value associated with a path or returns -1 if the path doesn't exist

Input:
["FileSystem","createPath","createPath","get","createPath","get"]
[[],["/a",1],["/a/b",2],["/a/b"],["/c/d",1],["/c"]]
Output:
[null,true,true,2,false,-1]
```

**Solution with Tree-like Structure:**
```python
class FileSystem:
    def __init__(self):
        self.paths = {"/": -1}  # Root path
    
    def createPath(self, path, value):
        # Check if path is valid and doesn't exist
        if not path or path == "/" or path in self.paths:
            return False
        
        # Get parent path
        parent = path[:path.rindex("/")]
        if not parent:
            parent = "/"
        
        # Check if parent exists
        if parent not in self.paths:
            return False
        
        # Create the path
        self.paths[path] = value
        return True
    
    def get(self, path):
        return self.paths.get(path, -1)
```

## Problem 18: Implement a Process Scheduler

```
Design a process scheduler with the following operations:
- addProcess(pid, priority): Add a process with given ID and priority
- getNextProcess(): Return the process ID of the highest priority process to execute next

If multiple processes have the same priority, the one added first should be executed first.
```

**Solution using Priority Queue:**
```python
import heapq

class ProcessScheduler:
    def __init__(self):
        self.pq = []  # Priority queue
        self.counter = 0  # To maintain FIFO order for same priority
        self.processes = {}  # Map to store processes by ID
    
    def addProcess(self, pid, priority):
        # Add process to the priority queue (negative priority for max heap)
        heapq.heappush(self.pq, (-priority, self.counter, pid))
        self.counter += 1
        self.processes[pid] = priority
    
    def getNextProcess(self):
        if not self.pq:
            return -1
        
        # Get the highest priority process
        _, _, pid = heapq.heappop(self.pq)
        del self.processes[pid]
        return pid
    
    def updatePriority(self, pid, new_priority):
        if pid not in self.processes:
            return False
        
        # Remove and re-add with new priority
        self.addProcess(pid, new_priority)
        return True
```

## Problem 19: Snakes and Ladders

```
You are given an n x n board where each square represents the number from 1 to n^2.
The board has some squares with snakes and ladders. Return the least number of rolls
needed to reach the last square or -1 if it's impossible.

Input: board = [[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
Output: 4
```

**Solution using BFS:**
```python
from collections import deque

def snakesAndLadders(board):
    n = len(board)
    
    # Convert board position to coordinates
    def get_coordinates(position):
        r = n - 1 - (position - 1) // n
        c = (position - 1) % n
        if ((n - 1 - r) % 2) == 1:  # odd row, reverse direction
            c = n - 1 - c
        return r, c
    
    # BFS
    queue = deque([(1, 0)])  # (position, moves)
    visited = {1}
    
    while queue:
        position, moves = queue.popleft()
        
        if position == n * n:
            return moves
        
        # Try all possible dice rolls
        for i in range(1, 7):
            next_pos = position + i
            if next_pos > n * n:
                continue
            
            r, c = get_coordinates(next_pos)
            
            # Check for snake or ladder
            if board[r][c] != -1:
                next_pos = board[r][c]
            
            if next_pos not in visited:
                visited.add(next_pos)
                queue.append((next_pos, moves + 1))
    
    return -1
```

## Problem 20: Design a Rate Limiter

```
Design a rate limiter that can limit the number of requests a user can make within a window of time.

Implement the following methods:
- allowRequest(userId, timestamp): Returns true if the request is allowed, false otherwise

Limit each user to 3 requests per minute.
```

**Solution using Sliding Window Queue:**
```python
from collections import defaultdict, deque

class RateLimiter:
    def __init__(self, limit=3, window=60):
        self.limit = limit  # Maximum requests allowed
        self.window = window  # Time window in seconds
        self.user_requests = defaultdict(deque)  # Map user to their requests
    
    def allowRequest(self, userId, timestamp):
        requests = self.user_requests[userId]
        
        # Remove expired requests
        while requests and requests[0] <= timestamp - self.window:
            requests.popleft()
        
        # Check if request can be allowed
        if len(requests) < self.limit:
            requests.append(timestamp)
            return True
        
        return False
```

