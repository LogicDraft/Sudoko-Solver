#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
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

int isSafe(int row, int col, int num);
void resetGrid(void);

void SizeofBox()        // Function to determine the size of the Sudoku grid and box dimensions based on user input
{
    while (1)
    {
        printf("\033[92m\nEnter Sudoku Size (6 or 9): \033[0m");

        if (scanf("%d", &sudoku.SIZE) != 1)
        {
            printf("\033[31mInvalid input. Please enter a number.\033[0m\n");
            while(getchar() != '\n');
            continue;
        }

        if (sudoku.SIZE == 9)
        {
            sudoku.row = 9;
            sudoku.col = 9;
            sudoku.box_row = 3;
            sudoku.box_col = 3;
            break;
        }
        else if (sudoku.SIZE == 6)
        {
            sudoku.row = 6;
            sudoku.col = 6;
            sudoku.box_row = 2;
            sudoku.box_col = 3;
            break;
        }
        printf("\033[31mInvalid size. Please enter 6 or 9.\033[0m\n");
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

bool validatePuzzle()       // Function to validate the initial Sudoku puzzle before attempting to solve it
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
        printf("\033[94m+-------+-------+-------+\033[0m\n");
    else if (sudoku.SIZE == 6)
        printf("\033[94m+-------+-------+\033[0m\n");
}

void printSeparator()                          // Function to print the Sudoku grid
{
    printline();
    for (int r = 0; r < sudoku.row; r++) 
    {
        printf("\033[94m");
        printf("\033[95m|\033[0m");
        for (int c = 0; c < sudoku.col; c++) 
        {
            if (sudoku.Sudoku[r][c] == EMPTY) {
                printf("\033[95m .\033[0m");
            } 
            else {
                printf("\033[95m %d\033[0m", sudoku.Sudoku[r][c]);
            }
            if ((c + 1) % sudoku.box_col == 0)
                printf(" \033[95m|\033[0m");
        }
            printf("\n");
        printf("\033[0m");

        if ((r + 1) % sudoku.box_row == 0)
            printline();
    }
} 



void input_sudoku()                                    // Function to input the Sudoku puzzle from the user
{
    SizeofBox();
    printf("\033[92mEnter the Sudoku values row by row (space-separated).\033[0m\n");
    printf("\033[92mUse 0 for empty cells.\033[0m\n");
    printSeparator();
    int temp;
    for (int r = 0; r < sudoku.row; r++) {
        while (1) {
            printf("\033[91mRow %d (Enter %d values): \033[0m", r + 1, sudoku.col);
            int valid = 1;
            int tempRow[MAX_SIZE];
            for (int c = 0; c < sudoku.col; c++) {
                if (scanf("%d", &temp) != 1) {
                    valid = 0;
                    break;
                }
                if (!checkValidValue(temp)) {
                    valid = 0;
                    break;
                }
                tempRow[c] = temp;
            }
            if (!valid) {
                printf("\033[31mInvalid input for row. Please re-enter the entire row.\033[0m\n\n");
                while (getchar() != '\n'); // Clear input buffer
                continue;
            }
            for (int c = 0; c < sudoku.col; c++) {
                sudoku.Sudoku[r][c] = tempRow[c];
            }
            break;
        }
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


void resetGrid(void) {                                  // Reset the Sudoku grid to empty
    memset(sudoku.Sudoku, 0, sizeof(sudoku.Sudoku));
}


void loadTestPuzzle(int num) 
{                           // Function to test the Sudoku solver with a predefined puzzle
    int temp = (sudoku.SIZE == 9) ? 0 : 1; // Determine which set of puzzles to use based on the grid size
    static const int testPuzzle[2][3][9][9] = {
        {
            {{5,3,0,0,7,0,0,0,0}, {6,0,0,1,9,5,0,0,0}, {0,9,8,0,0,0,0,6,0}, {8,0,0,0,6,0,0,0,3}, {4,0,0,8,0,3,0,0,1}, {7,0,0,0,2,0,0,0,6}, {0,6,0,0,0,0,2,8,0}, {0,0,0,4,1,9,0,0,5}, {0,0,0,0,8,0,0,7,9}},
            {{0,0,0,2,6,0,7,0,1}, {6,8,0,0,7,0,0,9,0}, {1,9,0,0,0,4,5,0,0}, {8,2,0,1,0,0,0,4,0}, {0,0,4,6,0,2,9,0,0}, {0,5,0,0,0,3,0,2,8}, {0,0,9,3,0,0,0,7,4}, {0,4,0,0,5,0,0,3,6}, {7,0,3,0,1,8,0,0,0}},
            {{0,0,0,0,0,0,0,1,2}, {0,0,0,0,0,0,7,0,0}, {5,0,0,0,0,0,0,0,8}, {0,6,0,0,7,5,0,0,0}, {0,9,1,8,4,6,5,3,0}, {0,0,0,9,2,0,0,4,0}, {7,0,0,0,0,0,0,0,5}, {0,0,8,0,0,0,0,0,0}, {9,2,0,0,0,0,0,0,0}}
        },
        {
            {{0,0,0,0,5,6}, {0,0,0,1,0,0}, {0,1,0,0,0,0}, {0,0,0,0,2,0}, {0,0,3,0,0,0}, {4,5,0,0,0,0}, {0}},
            {{1,0,3,4,6,5}, {4,5,6,1,3,2}, {5,6,4,2,1,3}, {3,4,5,6,2,1}, {6,1,2,5,4,3}, {2,3,1,7,5,4}, {0}},
            {{1,2,3,4,5,6}, {4,5,6,1,2,3}, {5,6,4,2,3,1}, {3,4,5,6,1,2}, {6,1,2,5,4,3}, {2,3,1,7,6,4}, {0}}
        }
    };
    // Copy the selected puzzle to the global sudoku grid
    memcpy(sudoku.Sudoku, testPuzzle[temp][num], sizeof(sudoku.Sudoku));
}

void progressBar()          // Function to display a progress bar while solving the Sudoku puzzle
{
    printf("\nSolving Sudoku...\n[");

    for(int i = 0; i <= 20; i++)
    {
        printf("\033[31m#\033[0m");
        Sleep(100);
    }

    printf("] 100%%\n");
}

void printlines(int num)        // Function to print a specified number of separator lines for better readability
{
    printf("\n");
    for (int j = 0; j < num; j++) {
        printf("-");
    }
    printf("\n");
}

enum MenuOption     // Enum to represent the menu options in the Sudoku solver
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

    while (1) {                         // Main loop to display the menu and handle user input
        printf("\033[33m");
        printf("|-------------------------------------|\n");
        printf("|          SUDOKU SOLVER              |\n");
        printf("|-------------------------------------|\n");
        printf("| Size      : %-24d|\n", sudoku.SIZE);
        printf("| Loaded    : %-24s|\n", sudoku.puzzleLoaded ? "YES" : "NO");
        printf("| Solved    : %-24s|\n", sudoku.puzzleSolved ? "YES" : "NO");
        printf("|-------------------------------------|\n");
        printf("| 1. Enter Sudoku Puzzle              |\n");
        printf("| 2. Display Sudoku                   |\n");
        printf("| 3. Solve Sudoku                     |\n");
        printf("| 4. Test Puzzles                     |\n");
        printf("| 5. Reset Grid                       |\n");
        printf("| 6. Exit                             |\n");
        printf("|-------------------------------------|\n");
        printf("\033[92mEnter Choice: \033[0m");

        if (scanf("%d",&choice) != 1) {
            printf("\033[31mInvalid input. Please enter a number.\033[0m\n\n");
            while(getchar() != '\n'); // Clear invalid input
            continue;
        }
        if (choice < 1 || choice > 6) {
            printf("\033[31mInvalid choice. Please enter a number between 1 and 6.\033[0m\n");
            printlines(90);
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
                        printf("\033[31mOverwriting cancelled.\033[0m\n");
                    }
                    resetGrid();
                    sudoku.puzzleLoaded = false;
                    printf("\033[31mCurrent grid reset. You can now enter a new puzzle.\033[0m\n");
                }
                printf("\033[92m\n\nInput Sudoku Puzzle:\033[0m");
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
                    progressBar();
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
                    printf("\033[92mAre you sure you want to load a test puzzle? This will overwrite the current grid. (y/n): \033[0m");
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
                    printf("\033[92mEnter choice: \033[0m");
                    
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
                         printf("\033[92mAre you sure you want to reset the grid? (y/n): \033[0m");
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