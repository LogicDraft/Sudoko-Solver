# 🧩 Sudoku Solver in C

A console-based Sudoku Solver built in C that uses a **backtracking algorithm** to solve 6×6 and 9×9 Sudoku puzzles — with step-by-step input, visual grid display, and full input validation.

---

## ✨ Features

- 🔢 Supports **6×6** and **9×9** Sudoku grids
- 🧠 Solves puzzles using **recursive backtracking**
- 📊 Reports **backtracking step count** after solving
- 🖨️ Formatted grid display with proper **box separators**
- 🛡️ Robust **input validation** (invalid types, out-of-range values)
- 🔄 **Reset** the grid and start over without restarting the program
- 🧭 Clean **menu-driven interface**

---

## 📋 Menu Options

```
===== SUDOKU SOLVER =====
1. Enter Sudoku Puzzle
2. Display Sudoku
3. Solve Sudoku
4. Reset Grid
5. Exit
```

| Option | Description |
|--------|-------------|
| **1** | Input a new Sudoku puzzle (row by row, `0` for empty cells) |
| **2** | Display the current state of the grid |
| **3** | Solve the loaded puzzle using backtracking |
| **4** | Clear the grid and reset state |
| **5** | Exit the program |

---

## 🎮 Grid Display

### 9×9 Example
```
+-------+-------+-------+
| 5 3 . | . 7 . | . . . |
| 6 . . | 1 9 5 | . . . |
| . 9 8 | . . . | . 6 . |
+-------+-------+-------+
| 8 . . | . 6 . | . . 3 |
| 4 . . | 8 . 3 | . . 1 |
| 7 . . | . 2 . | . . 6 |
+-------+-------+-------+
| . 6 . | . . . | 2 8 . |
| . . . | 4 1 9 | . . 5 |
| . . . | . 8 . | . 7 9 |
+-------+-------+-------+
```

Dots (`.`) represent empty cells. Boxes are visually separated for readability.

---

## 🔬 Algorithm

The solver uses **recursive backtracking**:

1. Find the next empty cell.
2. Try placing digits `1` through `SIZE`.
3. For each digit, validate:
   - No duplicate in the **row**
   - No duplicate in the **column**
   - No duplicate in the **sub-box**
4. If valid, place the digit and recurse.
5. If no digit works, **backtrack** — clear the cell and try the next option.
6. Repeat until the board is complete or all possibilities are exhausted.

After solving, the number of **backtracking steps** taken is displayed.

---



## 📁 Project Structure

```
sudoku-solver/
│
|-- README.md              # Project overview and instructions
|-- main-101.c             # Main program with initialization build
└── Improve-Main.c        # Improvement of main-101.c 
```

---

## 🧩 Supported Grid Sizes

| Size | Box Dimensions | Valid Values |
|------|----------------|--------------|
| 9×9  | 3×3            | 1 – 9        |
| 6×6  | 2×3            | 1 – 6        |

---

## 📌 Input Format

- Enter values **row by row**, cell by cell.
- Use `0` to mark **empty cells**.
- Invalid characters or out-of-range values are **rejected with a prompt to re-enter**.

---

## 📈 Sample Output

```
Sudoku solved successfully:
Backtracking steps taken: 42

+-------+-------+-------+
| 5 3 4 | 6 7 8 | 9 1 2 |
| 6 7 2 | 1 9 5 | 3 4 8 |
| 1 9 8 | 3 4 2 | 5 6 7 |
+-------+-------+-------+
...
+-------+-------+-------+
```

---

## 👤 Authors

**Kruthik B T**  - USN: 1AY25AI053 <br>
**Akash B V** - USN: 1AY25AI005 <br>
**Rohith S J** - USN: 1AY25AI094 <br>
**Gowtham Gowda C B** - USN: 1AY25AI037 <br>
Acharya Institute of Technology, Bengaluru

---

> *"Build → Break → Learn → Repeat"*
