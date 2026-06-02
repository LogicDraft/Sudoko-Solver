#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_SIZE 9
#define EMPTY 0

int row = MAX_SIZE;
int col = MAX_SIZE;
int box_row, box_col;
int SIZE;
int sudoku[MAX_SIZE][MAX_SIZE] = {0};
bool puzzleLoaded = false;
bool puzzleSolved = false;
long backtrackingsteps = 0;

void SizeofBox()                // Function to determine the size of the Sudoku grid and the corresponding box dimensions
{
    printf("\nEnter the size of Sudoku (6 or 9): ");
    if (scanf("%d", &SIZE) != 1) {
        printf("Invalid input. Please enter a number.\n");
        while(getchar() != '\n');
        SizeofBox();
    }
    if (SIZE == 9)
    {
        box_row = 3;
        box_col = 3;
    }
    else if (SIZE == 6)
    {
        row = 6;
        col = 6;
        box_row = 2;
        box_col = 3;
    }
    else {
        printf("Invalid size. Please enter 6 or 9.\n");
        SizeofBox();
    }
}

bool isValidValue(int value)                          // Function to check if the input value is valid
{
    return value >= 0 && value <= SIZE;
}

int checkValidValue(int value)                     // Function to check if the input value is valid
{    
    if (!isValidValue(value)) {
        printf("Invalid value. Use numbers from 0 to %d.\n", SIZE);
        printf("\n");
        return 0;
    }
    return 1;
}

void printline()                                // Function to print the separator line 
{
    if (SIZE == 9)
        printf("+-------+-------+-------+\n");
    else if (SIZE == 6)
        printf("+-------+-------+\n");
}

void printSeparator()                          // Function to print the Sudoku grid
{
    printline();
    for (int r = 0; r < row; r++) 
    {
        printf("|");
        for (int c = 0; c < col; c++) 
        {
            if (sudoku[r][c] == EMPTY) {
                printf(" .");
            } 
            else {
                printf(" %d", sudoku[r][c]);
            }
            if ((c + 1) % box_col == 0)
                printf(" |");
        }
            printf("\n");

        if ((r + 1) % box_row == 0)
            printline();
    }
} 



void input_sudoku()                                    // Function to input the Sudoku puzzle from the user
{
    SizeofBox();
    printf("Enter the Sudoku values directly into the grid below.\n");
    printf("Use 0 for empty cells.\n");
    printSeparator();
    int temp;
    for (int r = 0; r < row; r++) {
        printf("Row : %d \n", r + 1);
        for (int c = 0; c < col; c++) {
            while (1) {
                printf("Enter the value of sudoku[%d]: ", c + 1);
                if (scanf("%d", &temp) != 1) {
                    printf("Invalid input. Please enter a number.\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (!checkValidValue(temp)) {
                    continue;
                }
                sudoku[r][c] = temp;
                break;
            }
        }
        printf("\n");
    }
}



int isSafe(int row, int col, int num)               // Check if it's safe to place a number in the given cell
{
    // Row check
    for (int x = 0; x < SIZE; x++)
        if (sudoku[row][x] == num)
            return false;
    
    // Column check
    for (int x = 0; x < SIZE; x++)
        if (sudoku[x][col] == num)
            return false;

    // Box check
    int startRow = row - row % box_row;
    int startCol = col - col % box_col;
    for (int r = 0; r < box_row; r++)
        for (int c = 0; c < box_col; c++)
            if (sudoku[r + startRow][c + startCol] == num)
                return false;

    return true;
}

int SudokuSolver()                                   // Backtracking algorithm to solve the Sudoku puzzle
{
    int row, col;
    bool isEmpty = false;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (sudoku[row][col] == EMPTY) {
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

    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(row, col, num)) {
            sudoku[row][col] = num;

            if (SudokuSolver()) {
                return true;
            }

            sudoku[row][col] = EMPTY; // Backtrack
            backtrackingsteps++;
        }
    }

    return false; // Trigger backtracking
}


void resetGrid() {                                  // Reset the Sudoku grid to empty
    for (int r = 0; r < MAX_SIZE; r++) {
        for (int c = 0; c < MAX_SIZE; c++) {
            sudoku[r][c] = EMPTY;
        }
    }
}



void loadTestPuzzle(int num) 
{                           // Function to test the Sudoku solver with a predefined puzzle
    int temp = (SIZE == 6) ? 0 : 1; // Determine index for 6x6 or 9x9 puzzles
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
            sudoku[r][c] = testPuzzle[temp][num][r][c];
        }
    }
}

int main()                                        // Main function to run the Sudoku solver
{
    int choice;

    while (1) {
        printf("\n===== SUDOKU SOLVER =====\n");
        printf("1. Enter Sudoku Puzzle\n");
        printf("2. Display Sudoku\n");
        printf("3. Solve Sudoku\n");
        printf("4. Test Puzzles\n");
        printf("5. Reset Grid\n");
        printf("6. Exit\n");
        printf("\nEnter Choice: ");

        if (scanf("%d",&choice) != 1) {
            printf("Invalid input. Please enter a number.\n\n");
            while(getchar() != '\n'); // Clear invalid input
            continue;
        }
        if (choice < 1 || choice > 6) {
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
            continue;
        }

        switch (choice) 
        {
            case 1:
                printf("\n\nInput Sudoku Puzzle:\n");
                input_sudoku();
                puzzleLoaded = true;
                break;

            case 2:
                if (puzzleLoaded == false) {
                    printf("The Sudoku grid is empty. Please enter a puzzle first.\n");
                }
                else {
                    printf("\nCurrent Sudoku Grid:\n");
                    printSeparator();
                }
                break;

            case 3:

                if (puzzleLoaded == false) {
                    printf("The Sudoku grid is empty. Please enter a puzzle first.\n");
                    break;
                }
                if (puzzleSolved==true) {
                    printSeparator();
                    printf("The Sudoku puzzle is already solved.\n");
                    break;
                }

                if (SudokuSolver() == true) {
                    printf("\nSudoku solved successfully:\n");
                    printf("Backtracking steps taken: %ld\n", backtrackingsteps);
                    printSeparator();
                    puzzleSolved = true;
                } else {
                    printf("\nNo solution exists for the given Sudoku.\n");
                }
                break;

            case 4:
                if (puzzleLoaded == true) {
                    printf("Are you sure you want to load a test puzzle? This will overwrite the current grid. (y/n): ");
                    char confirm;
                    scanf(" %c", &confirm);
                    if (confirm != 'y' && confirm != 'Y') {
                        printf("Loading test puzzle cancelled.\n");
                        break;
                    }
                }

                if (puzzleLoaded == true) {
                    printf("Resetting the current grid before loading a test puzzle...\n");
                    resetGrid();
                    puzzleLoaded = false;
                    puzzleSolved = false;
                    backtrackingsteps = 0;
                }
                SizeofBox();
                while (1)
                {
                    printf("\nSelect a test puzzle:\n");
                    printf("1. Easy Puzzle\n");
                    printf("2. Medium Puzzle\n");
                    printf("3. Hard Puzzle\n");
                    printf("Enter choice: ");
                    
                    int puzzleChoice;
                    if (scanf("%d", &puzzleChoice) != 1) {
                        printf("\nInvalid input. Please enter a number.\n");
                        while(getchar() != '\n'); // Clear invalid input
                        continue;
                    }
                    if (puzzleChoice < 1 || puzzleChoice > 3) {
                        printf("\nInvalid choice. Please enter a number between 1 and 3.\n");
                        continue;
                    }
                    loadTestPuzzle(puzzleChoice - 1);
                    printSeparator();
                    printf("Test puzzle loaded successfully.\n");
                    puzzleLoaded = true;
                    break;
                }
                break;
            
            case 5:
                if (puzzleLoaded == false) {
                    printf("The Sudoku grid is already empty.\n");
                    break;
                }
                else {
                    if (puzzleLoaded == true) {
                         printf("Are you sure you want to reset the grid? (y/n): ");
                         char confirm;
                         scanf(" %c", &confirm);
                         if (confirm != 'y' && confirm != 'Y') {
                             printf("Grid reset cancelled.\n");
                             break;
                         }
                    }
                    printf("Resetting the Sudoku grid...\n");
                    resetGrid();
                    puzzleLoaded = false;
                    puzzleSolved = false;
                    backtrackingsteps = 0;
                }
                break;
    
            case 6:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }
    }
    getche();
}