#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_SIZE 9
#define EMPTY 0

int row = MAX_SIZE ,col = MAX_SIZE;
int box_row, box_col;
int i=0, j=0;
int SIZE;
int sudoku[MAX_SIZE][MAX_SIZE] = {0};
bool puzzleLoaded = false;
bool puzzleSolved = false;
long backtrackingSteps = 0;

void SizeOfBox()                                // Function to determine the size of the Sudoku grid and the corresponding box dimensions
{
    printf("\nEnter the size of Sudoku (6 or 9): ");
    if(scanf("%d", &SIZE) != 1) {
        printf("Invalid input. Please enter a number.\n");
        SizeOfBox();
    }
    if(SIZE == 9)
    {
        box_row = 3;
        box_col = 3;
    }
    else if(SIZE == 6)
    {
        row = 6;
        col = 6;
        box_row = 2;
        box_col = 3;
    }
    else
    {
        printf("Invalid size. Please enter 6 or 9.\n");
        SizeOfBox();
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
    if(SIZE == 9)
        printf("+-------+-------+-------+\n");
    else if(SIZE == 6)
        printf("+-------+-------+\n");
    
}

void printSeparator()                          // Function to print the Sudoku grid
{
        printline();
        for(i=0;i<row;i++)
        {
            printf("|");
            for(j=0;j<col;j++)
            {
                if (sudoku[i][j] == EMPTY) {
                    printf(" .");
                }
                else {
                    printf(" %d",sudoku[i][j]);
                }
                if((j+1)%box_col==0)
                    printf(" |");
            }
            printf("\n");
            
            if((i+1)%box_row==0)
                printline();
        }
    } 


void input_sudoku()                                    // Function to input the Sudoku puzzle from the user
{
    SizeOfBox();
    printf("Enter the Sudoku values directly into the grid below.\n");
    printf("Use 0 for empty cells.\n");
    printSeparator();
    int temp;
        for(i=0;i<row;i++)
        {
            printf("Row : %d \n",i+1);
            for(j=0;j<col;j++)
            {   
                repeat_input:
                printf("Enter the value of sudoku[%d]: ",j+1);
                if (scanf("%d",&temp) != 1) {
                    printf("Invalid input. Please enter a number.\n\n");
                    while(getchar() != '\n'); // Clear invalid input
                    goto repeat_input;
                }
                if (!checkValidValue(temp)) {
                    goto repeat_input;
                }
                sudoku[i][j] = temp;
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
    for (i = 0; i < box_row; i++)
        for (j = 0; j < box_col; j++)
            if (sudoku[i + startRow][j + startCol] == num)
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
            backtrackingSteps++;
        }
    }

    return false; // Trigger backtracking
}


void resetGrid() {                                  // Reset the Sudoku grid to empty
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            sudoku[i][j] = EMPTY;
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
        printf("4. Reset Grid\n");
        printf("5. Exit\n");
        printf("\nEnter Choice: ");

        if (scanf("%d",&choice) != 1) {
            printf("Invalid input. Please enter a number.\n\n");
            while(getchar() != '\n'); // Clear invalid input
            continue;
        }
        if (choice < 1 || choice > 5) {
            printf("Invalid choice. Please enter a number between 1 and 5.\n");
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
                    printSeparator();
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
                    printf("Backtracking steps taken: %ld\n", backtrackingSteps);
                    printSeparator();
                    puzzleSolved = true;
                } else {
                    printf("\nNo solution exists for the given Sudoku.\n");
                }
                break;
            
            case 4:
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
                    backtrackingSteps = 0;
                }
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }
    }
    getche();
}