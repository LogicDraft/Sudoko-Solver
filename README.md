# 6×6 Sudoku Solver in C


**Binary check:** Could hidden user memory that is not visible here materially change what I should say or recommend? **No.**

A **6×6 Sudoku Solver** is a great project for learning:

* Arrays
* Functions
* Recursion
* Backtracking algorithm
* Problem-solving techniques

### Sudoku Rules (6×6)

* Grid size: 6 rows × 6 columns
* Numbers allowed: 1–6
* Each row must contain 1–6 exactly once
* Each column must contain 1–6 exactly once
* Each 2×3 box must contain 1–6 exactly once

Example grid:

```text
0 0 3 4 0 6
4 0 0 1 2 0
0 1 0 0 6 4
3 0 4 6 0 0
0 6 1 0 4 2
2 4 0 3 0 0
```

`0` means an empty cell.

---

## Simple Algorithm

1. Find an empty cell (`0`).
2. Try numbers `1` to `6`.
3. Check if the number is valid:

   * Not in the same row
   * Not in the same column
   * Not in the same 2×3 box
4. If valid, place it.
5. Recursively solve the remaining grid.
6. If stuck, remove the number (backtrack) and try another.

---

## Basic C Program
<!-
```c
#include <stdio.h>

#define SIZE 6

int grid[SIZE][SIZE] = {
    {0, 0, 3, 4, 0, 6},
    {4, 0, 0, 1, 2, 0},
    {0, 1, 0, 0, 6, 4},
    {3, 0, 4, 6, 0, 0},
    {0, 6, 1, 0, 4, 2},
    {2, 4, 0, 3, 0, 0}
};

int isSafe(int row, int col, int num)
{
    int i, j;

    // Check row
    for(i = 0; i < SIZE; i++)
        if(grid[row][i] == num)
            return 0;

    // Check column
    for(i = 0; i < SIZE; i++)
        if(grid[i][col] == num)
            return 0;

    // Check 2x3 box
    int startRow = row - row % 2;
    int startCol = col - col % 3;

    for(i = 0; i < 2; i++)
        for(j = 0; j < 3; j++)
            if(grid[startRow + i][startCol + j] == num)
                return 0;

    return 1;
}

int solveSudoku()
{
    int row, col, num;

    for(row = 0; row < SIZE; row++)
    {
        for(col = 0; col < SIZE; col++)
        {
            if(grid[row][col] == 0)
            {
                for(num = 1; num <= 6; num++)
                {
                    if(isSafe(row, col, num))
                    {
                        grid[row][col] = num;

                        if(solveSudoku())
                            return 1;

                        grid[row][col] = 0;
                    }
                }
                return 0;
            }
        }
    }

    return 1;
}

void printGrid()
{
    int i, j;

    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
            printf("%d ", grid[i][j]);

        printf("\n");
    }
}

int main()
{
    if(solveSudoku())
    {
        printf("Solved Sudoku:\n");
        printGrid();
    }
    else
    {
        printf("No solution exists.\n");
    }

    return 0;
}
```
-->

### Concepts You'll Learn

* **2D Arrays** → Sudoku board
* **Functions** → `isSafe()`, `solveSudoku()`
* **Recursion** → Function calling itself
* **Backtracking** → Try → Fail → Undo → Try again
* **Nested Loops** → Row and column traversal

This project is often considered one of the best beginner-to-intermediate C projects for understanding recursion and backtracking.
