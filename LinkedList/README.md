# LinkedList - A Comprehensive Guide

This guide covers linked list data structures from fundamentals to advanced topics, with implementation examples and practice problems in increasing order of complexity.

## Table of Contents

1. [Introduction to Linked Lists](#introduction-to-linked-lists)
2. [Types of Linked Lists](#types-of-linked-lists)
3. [Basic Implementation](#basic-implementation)
4. [Core Operations](#core-operations)
5. [Two-Pointer Techniques](#two-pointer-techniques)
6. [Common LinkedList Problems](#common-linkedlist-problems)
7. [Advanced LinkedList Problems](#advanced-linkedlist-problems)
8. [LinkedList Variations](#linkedlist-variations)
9. [Optimization Techniques](#optimization-techniques)
10. [Common Pitfalls](#common-pitfalls)
11. [Real-World Applications](#real-world-applications)

## Introduction to Linked Lists

A linked list is a linear data structure where elements (nodes) are stored in non-contiguous memory locations. Each node contains:
- Data (the value stored)
- Reference(s) to other node(s)

**Key Characteristics:**
- Dynamic size (can grow or shrink during execution)
- No random access (must traverse from beginning)
- Efficient insertions and deletions
- Extra memory required for pointers
- Better for frequent insertions/deletions than arrays

## Types of Linked Lists

### 1. Singly Linked List
- Each node points to the next node
- Last node points to NULL
- Only forward traversal is possible

### 2. Doubly Linked List
- Each node has pointers to both next and previous nodes
- Allows bidirectional traversal
- Requires more memory for the extra pointer

### 3. Circular Linked List
- Last node points back to the first node instead of NULL
- Can be singly or doubly circular
- Useful for applications that need to cycle through elements

## Basic Implementation

Here's a basic implementation of a singly linked list in Python:

```python
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None
    
    # Add a node at the beginning
    def push(self, new_data):
        new_node = Node(new_data)
        new_node.next = self.head
        self.head = new_node
    
    # Add a node at the end
    def append(self, new_data):
        new_node = Node(new_data)
        
        # If the list is empty
        if self.head is None:
            self.head = new_node
            return
        
        # Traverse to the last node
        last = self.head
        while last.next:
            last = last.next
        
        # Change the next of last node
        last.next = new_node
    
    # Insert after a given node
    def insertAfter(self, prev_node, new_data):
        if prev_node is None:
            print("The given previous node must be in LinkedList")
            return
        
        new_node = Node(new_data)
        new_node.next = prev_node.next
        prev_node.next = new_node
    
    # Delete a node by key
    def deleteNode(self, key):
        temp = self.head
        
        # If head node itself holds the key to be deleted
        if temp and temp.data == key:
            self.head = temp.next
            return
        
        # Search for the key to be deleted
        while temp and temp.next and temp.next.data != key:
            temp = temp.next
        
        # If key was not found
        if not temp or not temp.next:
            return
        
        # Unlink the node from linked list
        temp.next = temp.next.next
    
    # Print the linked list
    def printList(self):
        temp = self.head
        while temp:
            print(temp.data, end=" -> ")
            temp = temp.next
        print("None")
```

## Core Operations

### Time Complexity

Operation | Singly Linked List | Doubly Linked List
--------- | ----------------- | -----------------
Access | O(n) | O(n)
Search | O(n) | O(n)
Insertion at beginning | O(1) | O(1)
Insertion at end | O(n) or O(1)* | O(1)
Insertion at middle | O(n) | O(n)
Deletion at beginning | O(1) | O(1)
Deletion at end | O(n) or O(1)* | O(1)
Deletion at middle | O(n) | O(n)

*O(1) if we maintain a tail pointer

### Key Operations

1. **Traversal** - Visit each node in the list
2. **Insertion** - Add a new node
   - At beginning
   - At end
   - After a specific node
3. **Deletion** - Remove a node
   - From beginning
   - From end
   - By key/value
4. **Search** - Find a node with a specific value
5. **Reversal** - Reverse the linked list

## Two-Pointer Techniques

Two-pointer technique is a powerful approach for solving many linked list problems efficiently.

### Common Two-Pointer Patterns:

1. **Fast and Slow Pointers** (Hare and Tortoise)
   - Used for finding cycles, middle elements, etc.
   - One pointer moves faster than the other

```python
def find_middle(head):
    slow = fast = head
    
    while fast and fast.next:
        slow = slow.next         # Move one step
        fast = fast.next.next    # Move two steps
    
    return slow  # When fast reaches the end, slow is at the middle
```

2. **Left and Right Pointers**
   - Often used for operations involving both ends of a list

```python
def isPalindrome(head):
    # Find middle of the linked list
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    
    # Reverse second half
    prev = None
    curr = slow
    while curr:
        next_temp = curr.next
        curr.next = prev
        prev = curr
        curr = next_temp
    
    # Compare first and second half
    first = head
    second = prev
    while second:
        if first.val != second.val:
            return False
        first = first.next
        second = second.next
    
    return True
```

3. **Multiple Pointers**
   - Used for more complex operations

## Common LinkedList Problems

Here are some fundamental linked list problems in increasing order of difficulty:

### 1. Reverse a Linked List
**Problem**: Given the head of a singly linked list, reverse it and return the new head.

```python
def reverseList(head):
    prev = None
    current = head
    
    while current:
        next_temp = current.next  # Store next
        current.next = prev       # Reverse current node's pointer
        prev = current            # Move prev to current
        current = next_temp       # Move current to next
    
    return prev  # prev is the new head
```

### 2. Detect a Cycle in a Linked List
**Problem**: Given the head of a linked list, determine if it has a cycle.

```python
def hasCycle(head):
    if not head or not head.next:
        return False
    
    slow = head
    fast = head.next
    
    while slow != fast:
        if not fast or not fast.next:
            return False
        slow = slow.next
        fast = fast.next.next
    
    return True
```

### 3. Find the Middle of a Linked List
**Problem**: Given the head of a singly linked list, return the middle node.

```python
def middleNode(head):
    slow = head
    fast = head
    
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    
    return slow
```

### 4. Merge Two Sorted Lists
**Problem**: Merge two sorted linked lists and return it as a new sorted list.

```python
def mergeTwoLists(l1, l2):
    dummy = Node(0)
    tail = dummy
    
    while l1 and l2:
        if l1.data <= l2.data:
            tail.next = l1
            l1 = l1.next
        else:
            tail.next = l2
            l2 = l2.next
        tail = tail.next
    
    # Add remaining nodes
    if l1:
        tail.next = l1
    if l2:
        tail.next = l2
    
    return dummy.next
```

### 5. Remove Nth Node From End
**Problem**: Given the head of a linked list, remove the nth node from the end and return its head.

```python
def removeNthFromEnd(head, n):
    dummy = Node(0)
    dummy.next = head
    
    # Find length
    length = 0
    current = head
    while current:
        length += 1
        current = current.next
    
    # Find the (length - n)th node
    current = dummy
    for i in range(length - n):
        current = current.next
    
    # Delete the next node (nth from end)
    current.next = current.next.next
    
    return dummy.next
```

### 6. Intersection of Two Linked Lists
**Problem**: Find the node at which two linked lists intersect.

```python
def getIntersectionNode(headA, headB):
    if not headA or not headB:
        return None
    
    ptrA, ptrB = headA, headB
    
    while ptrA != ptrB:
        # When we reach the end of a list, redirect to the beginning of the other list
        ptrA = headB if ptrA is None else ptrA.next
        ptrB = headA if ptrB is None else ptrB.next
    
    # Either we found the intersection point or both are None
    return ptrA
```

### 7. Palindrome Linked List
**Problem**: Given a singly linked list, determine if it's a palindrome.

```python
def isPalindrome(head):
    if not head or not head.next:
        return True
    
    # Find the middle of the linked list
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    
    # Reverse the second half
    prev = None
    curr = slow
    while curr:
        next_temp = curr.next
        curr.next = prev
        prev = curr
        curr = next_temp
    
    # Compare the first and second half
    first_half = head
    second_half = prev
    while second_half:
        if first_half.val != second_half.val:
            return False
        first_half = first_half.next
        second_half = second_half.next
    
    return True
```

### 8. Delete Node in a Linked List
**Problem**: Delete a node in a linked list given only access to that node.

```python
def deleteNode(node):
    # Copy the next node's value to the current node
    node.val = node.next.val
    
    # Delete the next node
    node.next = node.next.next
```

## Advanced LinkedList Problems

### 1. LRU Cache
**Problem**: Implement an LRU (Least Recently Used) cache with get and put operations.

```python
class DNode:
    def __init__(self, key=0, value=0):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.cache = {}  # key -> node
        
        # Initialize doubly linked list
        self.head = DNode()  # dummy head
        self.tail = DNode()  # dummy tail
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def _add_node(self, node):
        # Always add node right after head
        node.prev = self.head
        node.next = self.head.next
        
        self.head.next.prev = node
        self.head.next = node
    
    def _remove_node(self, node):
        # Remove an existing node
        prev = node.prev
        next = node.next
        
        prev.next = next
        next.prev = prev
    
    def _move_to_head(self, node):
        # Move to head (recently used)
        self._remove_node(node)
        self._add_node(node)
    
    def _pop_tail(self):
        # Remove and return the tail (least recently used)
        res = self.tail.prev
        self._remove_node(res)
        return res
    
    def get(self, key):
        if key not in self.cache:
            return -1
        
        # Update to recently used
        node = self.cache[key]
        self._move_to_head(node)
        
        return node.value
    
    def put(self, key, value):
        if key in self.cache:
            # Update value
            node = self.cache[key]
            node.value = value
            self._move_to_head(node)
        else:
            # Add new node
            newNode = DNode(key, value)
            self.cache[key] = newNode
            self._add_node(newNode)
            
            # Check capacity
            if len(self.cache) > self.capacity:
                # Remove least recently used
                tail = self._pop_tail()
                del self.cache[tail.key]
```

### 2. Reverse Nodes in k-Group
**Problem**: Given a linked list, reverse the nodes of a linked list k at a time and return the modified list.

```python
def reverseKGroup(head, k):
    dummy = Node(0)
    dummy.next = head
    
    prev_group_end = dummy
    
    while True:
        # Find the end of the k-group
        group_end = prev_group_end
        for i in range(k):
            group_end = group_end.next
            if not group_end:
                return dummy.next  # Less than k nodes left
        
        # Reverse the k-group
        next_group_start = group_end.next
        
        # Reverse
        prev = next_group_start
        current = prev_group_end.next
        
        while current != next_group_start:
            next_temp = current.next
            current.next = prev
            prev = current
            current = next_temp
        
        # Connect with the previous and next groups
        temp = prev_group_end.next
        prev_group_end.next = group_end
        prev_group_end = temp
    
    return dummy.next
```

### 3. Copy List with Random Pointer
**Problem**: A linked list is given with a random pointer that could point to any node or null. Return a deep copy.

```python
class Node:
    def __init__(self, val):
        self.val = val
        self.next = None
        self.random = None

def copyRandomList(head):
    if not head:
        return None
    
    # Step 1: Create copies alongside original nodes
    current = head
    while current:
        # Create a copy
        copy = Node(current.val)
        copy.next = current.next
        current.next = copy
        
        # Move to the next original node
        current = copy.next
    
    # Step 2: Connect random pointers for copies
    current = head
    while current:
        if current.random:
            # random pointer of copy points to the copy of original's random
            current.next.random = current.random.next
        current = current.next.next
    
    # Step 3: Separate the two lists
    current = head
    copy_head = head.next
    copy_current = copy_head
    
    while copy_current.next:
        current.next = current.next.next
        copy_current.next = copy_current.next.next
        
        current = current.next
        copy_current = copy_current.next
    
    # Final node
    current.next = None
    
    return copy_head
```

### 4. Merge k Sorted Lists
**Problem**: Merge k sorted linked lists and return it as one sorted list.

```python
import heapq

def mergeKLists(lists):
    # Initialize a min-heap
    h = []
    
    # Add the first node from each list to the heap
    for i, lst in enumerate(lists):
        if lst:
            # (value, list index, node)
            heapq.heappush(h, (lst.val, i, lst))
    
    dummy = Node(0)
    current = dummy
    
    while h:
        val, i, node = heapq.heappop(h)
        
        # Add to result list
        current.next = node
        current = current.next
        
        # Add next node from the same list
        if node.next:
            heapq.heappush(h, (node.next.val, i, node.next))
    
    return dummy.next
```

### 5. Flatten a Multilevel Doubly Linked List
**Problem**: Given a doubly linked list where nodes can have a 'child' pointer to another doubly linked list, flatten it.

```python
class Node:
    def __init__(self, val):
        self.val = val
        self.prev = None
        self.next = None
        self.child = None

def flatten(head):
    if not head:
        return None
    
    # Create a dummy node to simplify processing
    dummy = Node(0)
    dummy.next = head
    head.prev = dummy
    
    # Stack to keep track of next nodes when processing child lists
    stack = []
    current = head
    
    while current:
        if current.child:
            # If current has a child, save the next node for later
            if current.next:
                stack.append(current.next)
                current.next.prev = None  # Break the next connection
            
            # Connect current with its child
            current.next = current.child
            current.child.prev = current
            current.child = None  # Remove child reference
        
        # If no next node, but stack is not empty, connect to the next node in stack
        elif not current.next and stack:
            next_node = stack.pop()
            current.next = next_node
            next_node.prev = current
        
        # Move to the next node
        current = current.next
    
    # Fix the head
    head = dummy.next
    head.prev = None
    
    return head
```

### 6. Sort List
**Problem**: Sort a linked list using merge sort in O(n log n) time and O(1) space.

```python
def sortList(head):
    if not head or not head.next:
        return head
    
    # Split the list into two halves
    mid = findMiddle(head)
    left = head
    right = mid.next
    mid.next = None  # Break the list
    
    # Recursively sort both halves
    left = sortList(left)
    right = sortList(right)
    
    # Merge the sorted halves
    return merge(left, right)

def findMiddle(head):
    if not head:
        return head
    
    slow = head
    fast = head
    
    # When fast reaches the end, slow will be at the middle
    while fast.next and fast.next.next:
        slow = slow.next
        fast = fast.next.next
    
    return slow

def merge(l1, l2):
    dummy = Node(0)
    tail = dummy
    
    while l1 and l2:
        if l1.val <= l2.val:
            tail.next = l1
            l1 = l1.next
        else:
            tail.next = l2
            l2 = l2.next
        tail = tail.next
    
    # Attach the remaining nodes
    if l1:
        tail.next = l1
    if l2:
        tail.next = l2
    
    return dummy.next
```

## LinkedList Variations

### 1. Skip List
A skip list is a probabilistic data structure that allows O(log n) search complexity on average.

```python
import random

class SkipNode:
    def __init__(self, value, level):
        self.value = value
        self.forward = [None] * (level + 1)  # Array of pointers

class SkipList:
    def __init__(self, max_level=16, p=0.5):
        self.max_level = max_level
        self.p = p
        self.header = SkipNode(-1, max_level)
        self.level = 0
    
    def random_level(self):
        lvl = 0
        while random.random() < self.p and lvl < self.max_level:
            lvl += 1
        return lvl
    
    def insert(self, value):
        update = [None] * (self.max_level + 1)
        current = self.header
        
        # Find position to insert
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
            update[i] = current
        
        # Generate random level
        level = self.random_level()
        
        # Update maximum level
        if level > self.level:
            for i in range(self.level + 1, level + 1):
                update[i] = self.header
            self.level = level
        
        # Create new node and update pointers
        new_node = SkipNode(value, level)
        for i in range(level + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node
```

### 2. XOR Linked List
A memory-efficient doubly linked list that uses the bitwise XOR operation to store both next and previous pointers in a single field.

```c
// Only possible in languages with pointer arithmetic like C/C++
typedef struct Node {
    int data;
    struct Node* npx;  // XOR of next and previous node addresses
} Node;

// Helper functions
Node* XOR(Node* a, Node* b) {
    return (Node*) ((uintptr_t)a ^ (uintptr_t)b);
}

void insert(Node** head, int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    
    // New node's npx = XOR of NULL and current head
    new_node->npx = XOR(NULL, *head);
    
    if (*head != NULL) {
        // Update old head's npx to include new node
        Node* next = XOR((*head)->npx, NULL);
        (*head)->npx = XOR(new_node, next);
    }
    
    *head = new_node;
}
```

### 3. Unrolled Linked List
A hybrid data structure combining arrays and linked lists for better cache performance.

```python
class UnrolledLinkedList:
    class Node:
        def __init__(self, capacity=16):
            self.elements = [None] * capacity
            self.count = 0
            self.capacity = capacity
            self.next = None
    
    def __init__(self, node_capacity=16):
        self.head = None
        self.size = 0
        self.node_capacity = node_capacity
```

### 4. Self-Organizing List
A list that reorders elements based on access frequency.

```python
class SelfOrganizingList:
    class Node:
        def __init__(self, key, value):
            self.key = key
            self.value = value
            self.next = None
    
    def __init__(self):
        self.head = None
    
    def find(self, key):
        # Keep track of current and previous nodes
        prev = None
        curr = self.head
        
        # Search for the node
        while curr and curr.key != key:
            prev = curr
            curr = curr.next
        
        # If found, move to front (Move-to-Front strategy)
        if curr and prev:  # Found and not already at front
            # Remove from current position
            prev.next = curr.next
            
            # Move to front
            curr.next = self.head
            self.head = curr
            
            return curr.value
        elif curr:  # Found at front
            return curr.value
        
        return None  # Not found
```

## Optimization Techniques

### 1. Dummy Node Technique
Using a dummy/sentinel node to simplify edge cases, especially when the head might change.

```python
def remove_elements_with_value(head, val):
    dummy = Node(0)
    dummy.next = head
    current = dummy
    
    while current.next:
        if current.next.val == val:
            current.next = current.next.next  # Skip the node
        else:
            current = current.next
    
    return dummy.next  # New head
```

### 2. Two-Step Deletion
For deleting a node when you need to maintain a reference to the previous node.

```python
def delete_node(head, key):
    if not head:
        return None
    
    if head.val == key:
        return head.next
    
    current = head
    
    # Find the node to delete and keep track of previous node
    while current.next and current.next.val != key:
        current = current.next
    
    # If found, delete it
    if current.next:
        current.next = current.next.next
    
    return head
```

### 3. In-place Reversal
Reversing a linked list without using extra space.

```python
def reverse_in_place(head):
    prev = None
    current = head
    
    while current:
        next_temp = current.next
        current.next = prev      # Reverse the pointer
        prev = current           # Move prev forward
        current = next_temp      # Move current forward
    
    return prev  # New head
```

### 4. Runner Technique (Fast/Slow Pointers)
Also known as the hare and tortoise algorithm.

```python
def has_cycle(head):
    if not head or not head.next:
        return False
    
    slow = head
    fast = head.next
    
    while slow != fast:
        if not fast or not fast.next:
            return False
        slow = slow.next
        fast = fast.next.next
    
    return True
```

## Common Pitfalls

### 1. Null Pointer Exceptions
Always check for null pointers before dereferencing.

```python
# Incorrect
def get_length(head):
    count = 0
    while head.next:  # Will crash if head is None
        head = head.next
        count += 1
    return count

# Correct
def get_length(head):
    count = 0
    while head:
        head = head.next
        count += 1
    return count
```

### 2. Off-by-One Errors
Common when traversing to a specific position or when counting nodes.

### 3. Not Updating Pointers Correctly During Insertions/Deletions
When modifying the list, ensure all pointers are updated in the correct order.

### 4. Memory Leaks in Languages Without Garbage Collection
In languages like C and C++, not properly freeing nodes can cause memory leaks.

## Real-World Applications

1. **Implementation of other data structures**:
   - Stacks, queues, and hash tables can use linked lists as their underlying storage.

2. **Memory Management**:
   - Operating systems use linked lists to track memory blocks.

3. **LRU Cache**:
   - Efficient implementation of LRU cache using a doubly linked list and hash map.

4. **Polynomial Manipulation**:
   - Each term can be a node with coefficient and exponent.

5. **Image Viewers**:
   - Previous and next images in a slideshow.

6. **Undo Functionality**:
   - Implementing undo/redo operations in applications.

7. **Database Systems**:
   - Index structures and transaction logs.

8. **Blockchain**:
   - Each block in a blockchain can be represented as a node in a linked list.

9. **Graph Algorithms**:
   - Adjacency list representation of graphs.

10. **File Systems**:
    - Directory structures and file allocation tables.

By understanding linked lists thoroughly, from basic operations to advanced patterns and optimizations, you'll be well-equipped to solve a wide range of problems efficiently and implement complex data structures.
