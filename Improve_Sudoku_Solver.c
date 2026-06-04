#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_SIZE 9
#define EMPTY 0

struct
{
    int row;
    int col;
    int SIZE;
    int box_row;
    int box_col;
    int Sudoku[MAX_SIZE][MAX_SIZE];
    bool puzzleLoaded;
    bool puzzleSolved;
    int backtrackingSteps;
} sudoku = {MAX_SIZE, MAX_SIZE, 0, 0, 0, {{0}}, false, false, 0};

void SizeofBox()                // Function to determine the size of the Sudoku grid and the corresponding box dimensions
{
    printf("\033[34m\nEnter the size of Sudoku (6 or 9): \033[0m");
    if (scanf("%d", &sudoku.SIZE) != 1) {
        printf("\033[31mInvalid input. Please enter a number.\033[0m\n");
        while(getchar() != '\n');
        SizeofBox();
    }
    if (sudoku.SIZE == 9)          // Standard 9x9 Sudoku
    {
        sudoku.box_col = 3;
        sudoku.box_row = 3;
    }
    else if (sudoku.SIZE == 6)       // 6x6 Sudoku with 2x3 boxes
    {
        sudoku.row = 6;
        sudoku.col = 6;
        sudoku.box_row = 2;
        sudoku.box_col = 3;
    }
    else {
        printf("\033[31mInvalid size. Please enter 6 or 9.\033[0m\n");
        SizeofBox();
    }
}

bool isValidValue(int value)                          // Function to check if the input value is valid
{
    return value >= 0 && value <= sudoku.SIZE;
}

int checkValidValue(int value)                     // Function to check if the input value is valid
{    
    if (!isValidValue(value)) {
        printf("\033[31mInvalid value. Use numbers from 0 to %d.\033[0m\n", sudoku.SIZE);
        printf("\n");
        return 0;
    }
    return 1;
}

bool validatePuzzle()
{
    for (int r = 0; r < sudoku.row; r++) {
        for (int c = 0; c < sudoku.col; c++) {
            int num = sudoku.Sudoku[r][c];
            if (num != EMPTY) {
                sudoku.Sudoku[r][c] = EMPTY; // Temporarily remove the number to check for validity
                if (!isSafe(r, c, num)) {
                    printf("\033[31mInvalid puzzle. The number %d at position (%d, %d) violates Sudoku rules.\033[0m\n", num, r + 1, c + 1);
                    resetGrid();
                    return false;
                }
                sudoku.Sudoku[r][c] = num; // Restore the number
            }
        }
    }
    return true;
}

void printline()                                // Function to print the separator line 
{
    if (sudoku.SIZE == 9)
        printf("+-------+-------+-------+\n");
    else if (sudoku.SIZE == 6)
        printf("+-------+-------+\n");
}

void printSeparator()                          // Function to print the Sudoku grid
{
    printline();
    for (int r = 0; r < sudoku.row; r++) 
    {
        printf("|");
        for (int c = 0; c < sudoku.col; c++) 
        {
            if (sudoku.Sudoku[r][c] == EMPTY) {
                printf(" .");
            } 
            else {
                printf(" %d", sudoku.Sudoku[r][c]);
            }
            if ((c + 1) % sudoku.box_col == 0)
                printf(" |");
        }
            printf("\n");

        if ((r + 1) % sudoku.box_row == 0)
            printline();
    }
} 



void input_sudoku()                                    // Function to input the Sudoku puzzle from the user
{
    SizeofBox();
    printf("\033[34mEnter the Sudoku values directly into the grid below.\033[0m\n");
    printf("\033[34mUse 0 for empty cells.\033[0m\n");
    printSeparator();
    int temp;
    for (int r = 0; r < sudoku.row; r++) {
        printf("\033[34mRow : %d \033[0m\n", r + 1);
        for (int c = 0; c < sudoku.col; c++) {
            while (1) {
                printf("\033[34mEnter the value of sudoku[%d]: \033[0m", c + 1);
                if (scanf("%d", &temp) != 1) {
                    printf("\033[31mInvalid input. Please enter a number.\033[0m\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (!checkValidValue(temp)) {
                    continue;
                }
                sudoku.Sudoku[r][c] = temp;
                break;
            }
        }
        printf("\n");
    }
}



int isSafe(int row, int col, int num)               // Check if it's safe to place a number in the given cell
{
    // Row check
    for (int x = 0; x < sudoku.SIZE; x++)
        if (sudoku.Sudoku[row][x] == num)
            return false;
    
    // Column check
    for (int x = 0; x < sudoku.SIZE; x++)
        if (sudoku.Sudoku[x][col] == num)
            return false;

    // Box check
    int startRow = row - row % sudoku.box_row;
    int startCol = col - col % sudoku.box_col;
    for (int r = 0; r < sudoku.box_row; r++)
        for (int c = 0; c < sudoku.box_col; c++)
            if (sudoku.Sudoku[r + startRow][c + startCol] == num)
                return false;

    return true;
}

int SudokuSolver()                                   // Backtracking algorithm to solve the Sudoku puzzle
{
    int row, col;
    bool isEmpty = false;
    for (row = 0; row < sudoku.SIZE; row++) {
        for (col = 0; col < sudoku.SIZE; col++) {
            if (sudoku.Sudoku[row][col] == EMPTY) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // No empty space left, puzzle solved
    if (!isEmpty) {
        return true;
    }

    for (int num = 1; num <= sudoku.SIZE; num++) {
        if (isSafe(row, col, num)) {
            sudoku.Sudoku[row][col] = num;

            if (SudokuSolver()) {
                return true;
            }

            sudoku.Sudoku[row][col] = EMPTY; // Backtrack
            sudoku.backtrackingSteps++;
        }
    }

    return false; // Trigger backtracking
}


void resetGrid() {                                  // Reset the Sudoku grid to empty
    for (int r = 0; r < MAX_SIZE; r++) {
        for (int c = 0; c < MAX_SIZE; c++) {
            sudoku.Sudoku[r][c] = EMPTY;
        }
    }
}



void loadTestPuzzle(int num) 
{                           // Function to test the Sudoku solver with a predefined puzzle
    int temp = (sudoku.SIZE == 9) ? 0 : 1; // Determine which set of puzzles to use based on the grid size
    int testPuzzle[2][3][9][9] = {
        {
            {
                // Easy Sudoku Puzzle
                {5, 3, 0, 0, 7, 0, 0, 0, 0},
                {6, 0, 0, 1, 9, 5, 0, 0, 0},
                {0, 9, 8, 0, 0, 0, 0, 6, 0},
                {8 ,0 ,0 ,0 ,6 ,0 ,0 ,0 ,3},
                {4 ,0 ,0 ,8 ,0 ,3 ,0 ,0 ,1},
                {7 ,0 ,0 ,0 ,2 ,0 ,0 ,0 ,6},
                {0 ,6 ,0 ,0 ,0 ,0 ,2 ,8 ,0},
                {0 ,0 ,0 ,4 ,1 ,9 ,0 ,0 ,5},
                {0 ,0 ,0 ,0 ,8 ,0 ,0 ,7 ,9}
            },
            {
                // Medium Sudoku Puzzle
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 3, 0, 8, 5},
                {0, 0, 1, 0, 2, 0, 0, 0, 0},
                {0 ,0 ,0 ,5 ,0 ,7 ,0 ,0 ,0},
                {0 ,0 ,4 ,0 ,0 ,0 ,1 ,0 ,0},
                {0 ,9 ,0 ,6 ,0 ,8 ,0 ,4 ,0},
                {5 ,0 ,0 ,2 ,0 ,6 ,3 ,0 ,0},
                {6 ,7 ,2 ,8 ,0 ,4 ,0 ,0 ,0},
                {1 ,4 ,9 ,7 ,0 ,5 ,0 ,0 ,0}
            },
            {
                // Hard Sudoku Puzzle
                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 3, 0, 8, 5},
                {0, 0, 1, 0, 2, 0, 0, 0, 0},
                {0 ,0 ,0 ,5 ,0 ,7 ,0 ,0 ,0},
                {0 ,0 ,4 ,0 ,0 ,0 ,1 ,0 ,0},
                {0 ,9 ,0 ,6 ,0 ,8 ,0 ,4 ,0},
                {5 ,0 ,0 ,2 ,0 ,6 ,3 ,0 ,0},
                {6 ,7 ,2 ,8 ,0 ,4 ,0 ,0 ,1},
                {1 ,4 ,9 ,7 ,0 ,5 ,0 ,0 ,9}
            }
        },
        {
            {
                // Easy 6x6 Sudoku Puzzle
                {0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 3},
                {0, 0, 1, 0, 2, 0},
                {0 ,0 ,0 ,5 ,0 ,7},
                {0 ,0 ,4 ,0 ,0 ,0},
                {0 ,9 ,0 ,6 ,0 ,8}
            },
            {
                // Medium 6x6 Sudoku Puzzle
                {0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 3},
                {0, 0, 1, 0, 2, 0},
                {0 ,0 ,0 ,5 ,0 ,7},
                {0 ,0 ,4 ,0 ,0 ,0},
                {0 ,9 ,0 ,6 ,0 ,8}
            },
            {
                // Hard 6x6 Sudoku Puzzle
                {1, 0, 0, 4, 8, 9},
                {7, 3, 0, 0, 0, 0},
                {9, 5, 4, 6, 1, 2},
                {8 ,2 ,6 ,3 ,5 ,7},
                {3 ,9 ,1 ,7 ,2 ,8},
                {5 ,4 ,7 ,8 ,6 ,4}
            }
        }
    };
    // Copy the selected puzzle to the global sudoku grid
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            sudoku.Sudoku[r][c] = testPuzzle[temp][num][r][c];
        }
    }
}

void printlines(int num)
{
    printf("\n");
    for (int j = 0; j < num; j++) {
        printf("-");
    }
    printf("\n");
}
enum MenuOption
{
    INPUT_SUDOKU = 1,
    DISPLAY_SUDOKU,
    SOLVE_SUDOKU,
    TEST_PUZZLES,
    RESET_GRID,
    EXIT
};


int main()                                        // Main function to run the Sudoku solver
{
    int choice;

    while (1) {
        printf("\033[33m\n===== SUDOKU SOLVER =====\n\n\033[0m");
        printf("\033[32m1. Enter Sudoku Puzzle\033[0m\n");
        printf("\033[32m2. Display Sudoku\033[0m\n");
        printf("\033[32m3. Solve Sudoku\033[0m\n");
        printf("\033[32m4. Test Puzzles\033[0m\n");
        printf("\033[32m5. Reset Grid\033[0m\n");
        printf("\033[32m6. Exit\033[0m\n");
        printf("\033[34m\nEnter Choice: \033[0m");

        if (scanf("%d",&choice) != 1) {
            printf("\033[31mInvalid input. Please enter a number.\033[0m\n\n");
            while(getchar() != '\n'); // Clear invalid input
            continue;
        }
        if (choice < 1 || choice > 6) {
            printf("\033[31mInvalid choice. Please enter a number between 1 and 6.\033[0m\n");
            continue;
        }

        switch (choice) 
        {
            case INPUT_SUDOKU:
                if (sudoku.puzzleLoaded == true) {
                    printf("\033[31mA puzzle is already loaded. Do you want to overwrite it? (y/n): \033[0m");
                    char confirm;
                    scanf(" %c", &confirm);
                    if (confirm != 'y' && confirm != 'Y') {
                        resetGrid();
                        sudoku.puzzleLoaded = false;
                        printf("\033[31mOverwriting cancelled.\033[0m\n");
                        break;
                    }
                }
                printf("\033[34m\n\nInput Sudoku Puzzle:\033[0m");
                input_sudoku();
                sudoku.puzzleLoaded = true;
                break;

            case DISPLAY_SUDOKU:
                if (sudoku.puzzleLoaded == false) {
                    printf("\033[31mThe Sudoku grid is empty. Please enter a puzzle first.\033[0m\n");
                }
                else {
                    printf("\nCurrent Sudoku Grid:\n");
                    printSeparator();
                }
                break;

            case SOLVE_SUDOKU:

                if(!validatePuzzle()) {
                    sudoku.puzzleLoaded = false;
                    sudoku.puzzleSolved = false;
                    break;
                }

                if (sudoku.puzzleLoaded == false) {
                    printf("\033[31mThe Sudoku grid is empty. Please enter a puzzle first.\033[0m\n");
                    break;
                }
                if (sudoku.puzzleSolved==true) {
                    printSeparator();
                    printf("\033[31mThe Sudoku puzzle is already solved.\033[0m\n");
                    break;
                }

                if (SudokuSolver() == true) {
                    printf("\nSudoku solved successfully:\n");
                    printf("Backtracking steps taken: %d\n", sudoku.backtrackingSteps);
                    printSeparator();
                    sudoku.puzzleSolved = true;
                } else {
                    printf("\033[31mNo solution exists for the given Sudoku.\033[0m\n");
                }
                break;

            case TEST_PUZZLES:
                if (sudoku.puzzleLoaded == true) {
                    printf("\033[31mAre you sure you want to load a test puzzle? This will overwrite the current grid. (y/n): \033[0m");
                    char confirm;
                    scanf(" %c", &confirm);
                    if (confirm != 'y' && confirm != 'Y') {
                        resetGrid();
                        sudoku.puzzleLoaded = false;
                        printf("\033[31mLoading test puzzle cancelled.\033[0m\n");
                        break;
                    }
                }

                if (sudoku.puzzleLoaded == true) {
                    printf("\033[31mResetting the current grid before loading a test puzzle...\033[0m\n");
                    resetGrid();
                    sudoku.puzzleLoaded = false;
                    sudoku.puzzleSolved = false;
                    sudoku.backtrackingSteps = 0;
                }
                SizeofBox();
                while (1)
                {
                    printlines(50);
                    printf("\033[32m\nSelect a test puzzle:\033[0m\n");
                    printf("\033[32m1. Easy Puzzle\033[0m\n");
                    printf("\033[32m2. Medium Puzzle\033[0m\n");
                    printf("\033[32m3. Hard Puzzle\033[0m\n");
                    printf("\033[34mEnter choice: \033[0m");
                    
                    int puzzleChoice;
                    if (scanf("%d", &puzzleChoice) != 1) {
                        printf("\033[31m\nInvalid input. Please enter a number.\033[0m\n");
                        while(getchar() != '\n'); // Clear invalid input
                        continue;
                    }
                    if (puzzleChoice < 1 || puzzleChoice > 3) {
                        printf("\033[31m\nInvalid choice. Please enter a number between 1 and 3.\033[0m\n");
                        continue;
                    }
                    loadTestPuzzle(puzzleChoice - 1);
                    printSeparator();
                    printf("\033[32mTest puzzle loaded successfully.\033[0m\n");
                    sudoku.puzzleLoaded = true;
                    break;
                }
                break;
            
            case RESET_GRID:
                if (sudoku.puzzleLoaded == false) {
                    printf("\033[31mThe Sudoku grid is already empty.\033[0m\n");
                    break;
                }
                else {
                    if (sudoku.puzzleLoaded == true) {
                         printf("\033[31mAre you sure you want to reset the grid? (y/n): \033[0m");
                         char confirm;
                         scanf(" %c", &confirm);
                         if (confirm != 'y' && confirm != 'Y') {
                             printf("\033[31mGrid reset cancelled.\033[0m\n");
                             break;
                         }
                    }
                    printf("\033[31mResetting the Sudoku grid...\033[0m\n");
                    resetGrid();
                    sudoku.puzzleLoaded = false;
                    sudoku.puzzleSolved = false;
                    sudoku.backtrackingSteps = 0;
                }
                break;
    
            case EXIT:
                exit(0);

            default:
                printf("\033[31mInvalid choice. Please try again.\033[0m\n");
                continue;
        }
        printlines(90);

    }
    getche();
}