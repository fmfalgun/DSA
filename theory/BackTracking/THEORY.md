# Backtracking - Complete Guide

**Backtracking** is a refinement of recursion used to solve constraint satisfaction problems — try all possibilities, undo (backtrack) when a constraint is violated. See [Recursion](../../non-450/Recursion/THEORY.md) for the base technique this builds on.

## Concept

Try all possibilities, backtrack when constraint violated.

**Template:**
```
Function backtrack(state):
    if isValid(state) and isGoal(state):
        add state to results
        return

    for each choice in possibleChoices:
        if isValid(choice):
            makeChoice(choice)
            backtrack(newState)
            undoChoice(choice)  // Backtrack
```

## Classic Backtracking Problems

1. **N-Queens:** Place N queens on N×N board
2. **Sudoku Solver:** Fill 9×9 grid with constraints
3. **Permutations:** Generate all permutations
4. **Combinations:** Generate all combinations
5. **Subset Sum:** Find subsets with target sum
6. **Word Search:** Find word in 2D grid
7. **Maze Problems:** Find path through maze

## Problem Statements

### Medium: Generate Parentheses
**Problem:** Generate all valid n pairs of parentheses.
**Hints:** Backtrack with count of open and close parens
**Platform:** LeetCode #22

### Medium: Permutations
**Problem:** Generate all permutations of array.
**Hints:** Swap elements, recurse, backtrack
**Platform:** LeetCode #46

### Medium: Subsets
**Problem:** Generate all possible subsets.
**Hints:** Include or exclude each element
**Platform:** LeetCode #78

### Medium: Letter Combinations of Phone Number
**Problem:** Generate letter combinations from phone digits.
**Hints:** Backtrack through digits, build combination
**Platform:** LeetCode #17

### Hard: N-Queens
**Problem:** Place N queens on N×N board (no attacks).
**Hints:** Try placing queen in each row, check validity
**Platform:** LeetCode #51

### Hard: Sudoku Solver
**Problem:** Solve Sudoku puzzle.
**Hints:** Try digits 1-9, backtrack if invalid
**Platform:** LeetCode #37

### Expert: Word Search II
**Problem:** Find all words from dictionary in board.
**Hints:** Build trie, DFS with backtracking
**Platform:** LeetCode #212

## Common Mistakes

- **Not Backtracking:** forgetting to undo a choice leads to wrong results in later branches.

## Real-World Applications

1. **Game AI:** Minimax algorithm
2. **Puzzle Solvers:** Sudoku, chess

## Tips

1. Identify the choice, constraint, and goal explicitly before coding.
2. Always undo the choice after the recursive call returns — that's the "back" in backtracking.
3. Prune early: check validity before recursing, not after.
