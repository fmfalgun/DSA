# Stack Data Structure

A stack is a linear data structure that follows the Last-In-First-Out (LIFO) principle. It works like a stack of plates where you can only add or remove items from the top.

## Basic Operations

- **push**: Add element to top of stack
- **pop**: Remove element from top of stack
- **peek/top**: View top element without removing
- **isEmpty**: Check if stack is empty

## Implementation Approaches

### Array-based Stack (C)
```c
#define MAX_SIZE 100

struct Stack {
    int items[MAX_SIZE];
    int top;
};

void initStack(struct Stack* s) { s->top = -1; }
void push(struct Stack* s, int x) { s->items[++(s->top)] = x; }
int pop(struct Stack* s) { return s->items[(s->top)--]; }
int peek(struct Stack* s) { return s->items[s->top]; }
int isEmpty(struct Stack* s) { return s->top == -1; }
```

### Linked List-based Stack (JavaScript)
```javascript
class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class Stack {
    constructor() {
        this.top = null;
    }
    
    push(data) {
        const newNode = new Node(data);
        newNode.next = this.top;
        this.top = newNode;
    }
    
    pop() {
        if (!this.top) return null;
        const data = this.top.data;
        this.top = this.top.next;
        return data;
    }
}
```

## Practice Problems

### Easy: Valid Parentheses

**Problem**: Determine if a string of parentheses is valid.
```
Input: "({[]})"
Output: true

Input: "([)]"
Output: false
```

**Solution**:
```python
def isValid(s):
    stack = []
    mapping = {')': '(', '}': '{', ']': '['}
    
    for char in s:
        if char in mapping:  # closing bracket
            top_element = stack.pop() if stack else '#'
            if mapping[char] != top_element:
                return False
        else:  # opening bracket
            stack.append(char)
            
    return not stack  # stack should be empty
```

### Medium: Next Greater Element

**Problem**: For each element in the array, find the first greater element to its right.
```
Input: [4, 5, 2, 10, 8]
Output: [5, 10, 10, -1, -1]
```

**Solution**:
```java
public int[] nextGreaterElement(int[] nums) {
    int n = nums.length;
    int[] result = new int[n];
    Stack<Integer> stack = new Stack<>();
    
    // Fill with default value
    Arrays.fill(result, -1);
    
    for (int i = 0; i < n; i++) {
        // Pop elements smaller than current
        while (!stack.isEmpty() && nums[stack.peek()] < nums[i]) {
            result[stack.pop()] = nums[i];
        }
        stack.push(i);
    }
    
    return result;
}
```

### Hard: Largest Rectangle in Histogram

**Problem**: Find the area of the largest rectangle in a histogram.
```
Input: [2, 1, 5, 6, 2, 3]
Output: 10 (The largest rectangle has height 5 and width 2)
```

**Solution**:
```cpp
int largestRectangleArea(vector<int>& heights) {
    stack<int> s;
    int maxArea = 0;
    int i = 0;
    
    while (i < heights.size()) {
        // If stack is empty or current height is >= stack top height
        if (s.empty() || heights[s.top()] <= heights[i]) {
            s.push(i++);
        } else {
            // Current height is less than stack top
            int top = s.top();
            s.pop();
            
            // Calculate area with the popped height as smallest
            int area = heights[top] * (s.empty() ? i : i - s.top() - 1);
            maxArea = max(maxArea, area);
        }
    }
    
    // Process remaining elements in stack
    while (!s.empty()) {
        int top = s.top();
        s.pop();
        int area = heights[top] * (s.empty() ? i : i - s.top() - 1);
        maxArea = max(maxArea, area);
    }
    
    return maxArea;
}
```

### Advanced: Min Stack

**Problem**: Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

**Solution**:
```python
class MinStack:
    def __init__(self):
        self.stack = []
        self.min_stack = []
        
    def push(self, val):
        self.stack.append(val)
        if not self.min_stack or val <= self.min_stack[-1]:
            self.min_stack.append(val)
            
    def pop(self):
        if self.stack.pop() == self.min_stack[-1]:
            self.min_stack.pop()
            
    def top(self):
        return self.stack[-1]
        
    def getMin(self):
        return self.min_stack[-1]
```

## Applications of Stacks

1. Function call management (call stack)
2. Expression evaluation and conversion
3. Backtracking algorithms
4. Undo/Redo operations
5. Browser history
6. Syntax parsing

# More Advanced Stack Problems

Let's continue with more stack applications and challenging problems to enhance your understanding.

## Expression Evaluation

### Problem: Evaluate Postfix Expression
**Problem**: Evaluate a postfix (Reverse Polish Notation) expression.
```
Input: ["2", "1", "+", "3", "*"]
Output: 9 ((2+1)*3 = 9)
```

**Solution**:
```python
def evaluatePostfix(tokens):
    stack = []
    operators = {
        '+': lambda a, b: a + b,
        '-': lambda a, b: a - b,
        '*': lambda a, b: a * b,
        '/': lambda a, b: int(a / b)  # Integer division
    }
    
    for token in tokens:
        if token in operators:
            b = stack.pop()
            a = stack.pop()
            stack.append(operators[token](a, b))
        else:
            stack.append(int(token))
            
    return stack[0]
```

### Problem: Infix to Postfix Conversion
**Problem**: Convert an infix expression to postfix.
```
Input: "a+b*(c-d)/e"
Output: "abcd-*e/+"
```

**Solution**:
```java
public String infixToPostfix(String infix) {
    StringBuilder result = new StringBuilder();
    Stack<Character> stack = new Stack<>();
    Map<Character, Integer> precedence = Map.of(
        '+', 1, '-', 1,
        '*', 2, '/', 2,
        '^', 3
    );
    
    for (char c : infix.toCharArray()) {
        // If operand, add to output
        if (Character.isLetterOrDigit(c)) {
            result.append(c);
        }
        // If left parenthesis, push to stack
        else if (c == '(') {
            stack.push(c);
        }
        // If right parenthesis, pop until matching left parenthesis
        else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                result.append(stack.pop());
            }
            stack.pop();  // Remove '('
        }
        // If operator
        else {
            while (!stack.isEmpty() && stack.peek() != '(' && 
                   precedence.getOrDefault(stack.peek(), 0) >= 
                   precedence.getOrDefault(c, 0)) {
                result.append(stack.pop());
            }
            stack.push(c);
        }
    }
    
    // Pop remaining operators
    while (!stack.isEmpty()) {
        result.append(stack.pop());
    }
    
    return result.toString();
}
```

## Stack for Complex Problems

### Problem: Daily Temperatures
**Problem**: For each day, find how many days you need to wait until a warmer temperature.
```
Input: [73, 74, 75, 71, 69, 72, 76, 73]
Output: [1, 1, 4, 2, 1, 1, 0, 0]
```

**Solution**:
```cpp
vector<int> dailyTemperatures(vector<int>& T) {
    int n = T.size();
    vector<int> result(n, 0);
    stack<int> s;
    
    for (int i = 0; i < n; i++) {
        while (!s.empty() && T[s.top()] < T[i]) {
            int prevDay = s.top();
            s.pop();
            result[prevDay] = i - prevDay;
        }
        s.push(i);
    }
    
    return result;
}
```

### Problem: Trapping Rain Water
**Problem**: Given n non-negative integers representing an elevation map, compute how much water can be trapped after raining.
```
Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
```

**Solution Using Stack**:
```python
def trap(height):
    stack = []
    water = 0
    
    for i in range(len(height)):
        while stack and height[i] > height[stack[-1]]:
            top = stack.pop()
            
            if not stack:
                break
                
            # Calculate width between current position and stack top
            width = i - stack[-1] - 1
            
            # Calculate bounded height
            bounded_height = min(height[i], height[stack[-1]]) - height[top]
            
            # Add water trapped in this section
            water += width * bounded_height
            
        stack.append(i)
        
    return water
```

## Stack Implementation Variations

### Monotonic Stack
A monotonic stack maintains elements in either increasing or decreasing order.

**Problem: Remove K Digits**
**Problem**: Remove k digits from a number to get the smallest possible number.
```
Input: num = "1432219", k = 3
Output: "1219"
```

**Solution**:
```javascript
function removeKdigits(num, k) {
    const stack = [];
    
    // Build monotonic increasing stack
    for (const digit of num) {
        while (k > 0 && stack.length > 0 && stack[stack.length - 1] > digit) {
            stack.pop();
            k--;
        }
        stack.push(digit);
    }
    
    // Remove remaining digits if needed
    while (k > 0) {
        stack.pop();
        k--;
    }
    
    // Build result
    let result = stack.join('').replace(/^0+/, '');
    return result === '' ? '0' : result;
}
```

### Problem: Car Fleet
**Problem**: Find the number of car fleets that will arrive at the destination.
```
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
```

**Solution**:
```python
def carFleet(target, position, speed):
    # Pair positions with speeds and sort by position
    cars = sorted(zip(position, speed), reverse=True)
    stack = []
    
    for pos, spd in cars:
        # Time to reach target
        time = (target - pos) / spd
        
        # If this car is slower than the lead car of the previous fleet
        if not stack or time > stack[-1]:
            stack.append(time)
    
    return len(stack)
```

## Real-World Applications and Extensions

### Backtracking with Stack
**Problem: Iterative DFS for Graph Traversal**
```python
def iterativeDFS(graph, start):
    result = []
    stack = [start]
    visited = set()
    
    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            result.append(node)
            
            # Add neighbors in reverse order to maintain DFS property
            for neighbor in reversed(graph[node]):
                if neighbor not in visited:
                    stack.append(neighbor)
                    
    return result
```

### Undo/Redo Functionality
```javascript
class TextEditor {
    constructor() {
        this.text = "";
        this.undoStack = [];
        this.redoStack = [];
    }
    
    applyAction(action) {
        this.undoStack.push(this.text);
        this.text = action(this.text);
        this.redoStack = []; // Clear redo stack
    }
    
    undo() {
        if (this.undoStack.length > 0) {
            this.redoStack.push(this.text);
            this.text = this.undoStack.pop();
        }
    }
    
    redo() {
        if (this.redoStack.length > 0) {
            this.undoStack.push(this.text);
            this.text = this.redoStack.pop();
        }
    }
}
```

## Advanced Problem: Maximum Area Rectangle (using multiple stacks)

This is a variation of the histogram problem that works on a 2D grid.

**Problem**: Find the largest rectangle containing only 1's in a binary matrix.
```
Input: 
[
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
Output: 6
```

**Solution**:
```java
public int maximalRectangle(char[][] matrix) {
    if (matrix.length == 0) return 0;
    
    int rows = matrix.length;
    int cols = matrix[0].length;
    int[] heights = new int[cols];
    int maxArea = 0;
    
    for (int i = 0; i < rows; i++) {
        // Update heights for each row
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == '1') {
                heights[j]++;
            } else {
                heights[j] = 0;
            }
        }
        
        // Apply histogram algorithm on heights
        maxArea = Math.max(maxArea, largestRectangleArea(heights));
    }
    
    return maxArea;
}

// Use the histogram solution from earlier
private int largestRectangleArea(int[] heights) {
    Stack<Integer> stack = new Stack<>();
    int maxArea = 0;
    int i = 0;
    
    while (i < heights.length) {
        if (stack.isEmpty() || heights[stack.peek()] <= heights[i]) {
            stack.push(i++);
        } else {
            int top = stack.pop();
            int area = heights[top] * (stack.isEmpty() ? i : i - stack.peek() - 1);
            maxArea = Math.max(maxArea, area);
        }
    }
    
    while (!stack.isEmpty()) {
        int top = stack.pop();
        int area = heights[top] * (stack.isEmpty() ? i : i - stack.peek() - 1);
        maxArea = Math.max(maxArea, area);
    }
    
    return maxArea;
}
```

## Summary of Stack Applications

1. **Expression Evaluation and Conversion**
   - Infix to Postfix
   - Postfix evaluation
   - Calculator implementations

2. **Parentheses Matching**
   - Valid expressions
   - Minimum additions to make valid

3. **Monotonic Stack Problems**
   - Next greater/smaller element
   - Largest rectangle
   - Remove digits to create smallest number

4. **Memory Management**
   - Function call stack
   - Recursion to iteration conversion

5. **History Tracking**
   - Undo/Redo operations
   - Browser navigation

# Advanced Stack Applications and Problems

Let's explore more complex applications of stacks and solve challenging problems that require sophisticated understanding of the data structure.

## Pattern Matching with Stacks

### Problem: Basic Calculator
**Problem**: Implement a basic calculator to evaluate a string expression consisting of non-negative integers, +, -, *, /, and parentheses.

```
Input: "2*(5+5*2)/3+(6/2+8)"
Output: 21
```

**Solution**:
```python
def calculate(s):
    def eval_expr():
        stack = []
        sign = '+'
        num = 0
        
        while len(tokens) > 0 and tokens[0] != ')':
            token = tokens.pop(0)
            
            if token.isdigit():
                num = int(token)
            elif token == '(':
                num = eval_expr()
            
            if token in '+-*/' or len(tokens) == 0 or tokens[0] == ')':
                if sign == '+':
                    stack.append(num)
                elif sign == '-':
                    stack.append(-num)
                elif sign == '*':
                    stack[-1] *= num
                elif sign == '/':
                    # Integer division with truncation toward zero
                    stack[-1] = int(stack[-1] / num)
                
                sign = token
                num = 0
        
        if len(tokens) > 0:
            tokens.pop(0)  # Remove the closing parenthesis
            
        return sum(stack)
    
    # Tokenize the input
    tokens = []
    num = ''
    for char in s:
        if char.isdigit():
            num += char
        else:
            if num:
                tokens.append(num)
                num = ''
            if char != ' ':  # Ignore spaces
                tokens.append(char)
    if num:
        tokens.append(num)
        
    return eval_expr()
```

## Nested Data Structures

### Problem: Flatten Nested List Iterator
**Problem**: Design an iterator to flatten a nested list of integers.

```
Input: [[1,1],2,[1,1]]
Operations: 
next() -> 1
next() -> 1
next() -> 2
next() -> 1
next() -> 1
hasNext() -> false
```

**Solution**:
```java
public class NestedIterator implements Iterator<Integer> {
    private Stack<ListIterator<NestedInteger>> stack;
    private Integer nextInteger;
    
    public NestedIterator(List<NestedInteger> nestedList) {
        stack = new Stack<>();
        stack.push(nestedList.listIterator());
        findNext();
    }

    @Override
    public Integer next() {
        Integer result = nextInteger;
        findNext();
        return result;
    }

    @Override
    public boolean hasNext() {
        return nextInteger != null;
    }
    
    private void findNext() {
        nextInteger = null;
        while (!stack.isEmpty()) {
            if (!stack.peek().hasNext()) {
                stack.pop();
                continue;
            }
            
            NestedInteger ni = stack.peek().next();
            if (ni.isInteger()) {
                nextInteger = ni.getInteger();
                break;
            } else {
                List<NestedInteger> list = ni.getList();
                stack.push(list.listIterator());
            }
        }
    }
}
```

## Stack for Optimizing Recursive Solutions

### Problem: Decode String
**Problem**: Decode a string encoded as `k[encoded_string]` where encoded_string can contain more patterns.

```
Input: "3[a]2[bc]"
Output: "aaabcbc"

Input: "3[a2[c]]"
Output: "accaccacc"
```

**Solution**:
```cpp
string decodeString(string s) {
    stack<string> stringStack;
    stack<int> countStack;
    string currentString = "";
    int num = 0;
    
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '[') {
            // Save the current state
            countStack.push(num);
            stringStack.push(currentString);
            num = 0;
            currentString = "";
        } else if (c == ']') {
            // Get the previously saved string and repeat it
            string prevString = stringStack.top(); stringStack.pop();
            int repeatCount = countStack.top(); countStack.pop();
            
            string repeated = "";
            for (int i = 0; i < repeatCount; i++) {
                repeated += currentString;
            }
            
            currentString = prevString + repeated;
        } else {
            currentString += c;
        }
    }
    
    return currentString;
}
```

## Stack for Complex Traversals

### Problem: Binary Tree Zigzag Level Order Traversal
**Problem**: Return the zigzag level order traversal of a binary tree.

```
Input: 
    3
   / \
  9  20
    /  \
   15   7
Output: [[3], [20, 9], [15, 7]]
```

**Solution**:
```python
def zigzagLevelOrder(root):
    if not root:
        return []
    
    result = []
    current_level = [root]
    left_to_right = True
    
    while current_level:
        level_vals = []
        next_level = []
        
        for node in current_level:
            level_vals.append(node.val)
            
            if node.left:
                next_level.append(node.left)
            if node.right:
                next_level.append(node.right)
        
        # Add values in zigzag order
        if not left_to_right:
            level_vals.reverse()
            
        result.append(level_vals)
        current_level = next_level
        left_to_right = not left_to_right
        
    return result
```

## Implementing Advanced Data Structures with Stacks

### Problem: LRU Cache
**Problem**: Design a data structure that follows the Least Recently Used (LRU) cache pattern.

```
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

**Implementation using stacks**:
```javascript
class LRUCache {
    constructor(capacity) {
        this.capacity = capacity;
        this.cache = new Map();
        this.stack = [];
    }
    
    get(key) {
        if (!this.cache.has(key)) {
            return -1;
        }
        
        // Update recency by removing and adding to top of stack
        this.stack = this.stack.filter(k => k !== key);
        this.stack.push(key);
        
        return this.cache.get(key);
    }
    
    put(key, value) {
        // If key exists, update and move to most recent
        if (this.cache.has(key)) {
            this.cache.set(key, value);
            this.get(key); // Use get to update recency
            return;
        }
        
        // Check capacity
        if (this.stack.length === this.capacity) {
            const leastRecent = this.stack.shift();
            this.cache.delete(leastRecent);
        }
        
        // Add new key
        this.cache.set(key, value);
        this.stack.push(key);
    }
}
```

## Stack for Parsing and Syntax Analysis

### Problem: Mini Parser
**Problem**: Parse a nested list string into a NestedInteger class.

```
Input: "324"
Output: 324

Input: "[123,[456,[789]]]"
Output: [123,[456,[789]]]
```

**Solution**:
```java
public NestedInteger deserialize(String s) {
    if (s.charAt(0) != '[') {
        return new NestedInteger(Integer.parseInt(s));
    }
    
    Stack<NestedInteger> stack = new Stack<>();
    NestedInteger current = null;
    int start = 0; // Start of a number
    
    for (int i = 0; i < s.length(); i++) {
        char c = s.charAt(i);
        
        if (c == '[') {
            if (current != null) {
                stack.push(current);
            }
            current = new NestedInteger();
            start = i + 1;
        } else if (c == ',' || c == ']') {
            if (i > start) {
                String numStr = s.substring(start, i);
                if (!numStr.isEmpty()) {
                    current.add(new NestedInteger(Integer.parseInt(numStr)));
                }
            }
            
            if (c == ']' && !stack.isEmpty()) {
                NestedInteger popped = stack.pop();
                popped.add(current);
                current = popped;
            }
            
            start = i + 1;
        }
    }
    
    return current;
}
```

## Stack for State Management

### Problem: Online Stock Span
**Problem**: Find the span of stock's price for each day (consecutive days for which the price is less than or equal to the price of that day).

```
Input: [100, 80, 60, 70, 60, 75, 85]
Output: [1, 1, 1, 2, 1, 4, 6]
```

**Solution**:
```python
class StockSpanner:
    def __init__(self):
        self.stack = [] # (price, span)
        
    def next(self, price):
        span = 1
        
        # Pop lower or equal prices and add their spans
        while self.stack and self.stack[-1][0] <= price:
            _, prev_span = self.stack.pop()
            span += prev_span
            
        self.stack.append((price, span))
        return span
```

## Stack for Path Finding and Backtracking

### Problem: Minimum Cost Path in a Grid
**Problem**: Find the minimum cost path from top-left to bottom-right in a grid, moving only down or right.

```
Input: 
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Output: 7 (path: 1→3→1→1→1)
```

**Solution using stack for DFS with memoization**:
```java
public int minPathSum(int[][] grid) {
    int m = grid.length;
    int n = grid[0].length;
    int[][] memo = new int[m][n];
    
    // Initialize memo with -1 to indicate not calculated yet
    for (int[] row : memo) {
        Arrays.fill(row, -1);
    }
    
    Stack<int[]> stack = new Stack<>();
    stack.push(new int[]{0, 0}); // Start from the top-left
    
    while (!stack.isEmpty()) {
        int[] pos = stack.peek();
        int row = pos[0];
        int col = pos[1];
        
        // If we've reached the destination
        if (row == m - 1 && col == n - 1) {
            memo[row][col] = grid[row][col];
            stack.pop();
            continue;
        }
        
        // If we've already calculated this cell
        if (memo[row][col] != -1) {
            stack.pop();
            continue;
        }
        
        boolean canGoRight = col + 1 < n;
        boolean canGoDown = row + 1 < m;
        boolean allNeighborsCalculated = true;
        
        // Check right neighbor
        if (canGoRight && memo[row][col + 1] == -1) {
            stack.push(new int[]{row, col + 1});
            allNeighborsCalculated = false;
        }
        
        // Check down neighbor
        if (canGoDown && memo[row + 1][col] == -1) {
            stack.push(new int[]{row + 1, col});
            allNeighborsCalculated = false;
        }
        
        // Calculate current cell if all neighbors are calculated
        if (allNeighborsCalculated) {
            int rightCost = canGoRight ? memo[row][col + 1] : Integer.MAX_VALUE;
            int downCost = canGoDown ? memo[row + 1][col] : Integer.MAX_VALUE;
            
            memo[row][col] = grid[row][col] + 
                             (rightCost < downCost ? rightCost : downCost);
            
            // If destination, just use the cell value
            if (!canGoRight && !canGoDown) {
                memo[row][col] = grid[row][col];
            }
            
            stack.pop();
        }
    }
    
    return memo[0][0];
}
```

## Conclusion: Stack Implementation Techniques

When implementing complex stack-based solutions, consider these advanced techniques:

1. **Multiple Stacks**: Use multiple stacks to track different aspects of a problem
   
2. **Custom Stack Objects**: Store complex objects in stacks for state tracking
   
3. **Stack + Map/Set**: Combine stacks with hash tables for optimized lookups
   
4. **Monotonic Properties**: Enforce specific ordering to solve specialized problems
   
5. **Stack as Iteration Replacement**: Convert recursive algorithms to iterative using stacks

### Best Practices for Stack Usage:

1. **Always handle empty stack cases** to avoid runtime errors
   
2. **Consider space complexity** when working with large inputs
   
3. **Use clear variable names** to track what each stack represents
   
4. **Avoid unnecessary operations** by carefully designing your algorithm

