#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdbool.h>
#define MAX_SIZE 9

int row = MAX_SIZE;
int col = MAX_SIZE;
int box_row;
int box_col;
int EMPTY = 0;
int sudoku[MAX_SIZE][MAX_SIZE] = {0};
int i=0,j=0;
int SIZE;

void SizeOfBox()
{
    printf("Enter the size of Sudoku (6 or 9): ");
    scanf("%d", &SIZE);
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

bool isValidValue(int value) 
{
    return value >= 0 && value <= SIZE;
}

int checkValidValue(int value) {
    if (!isValidValue(value)) {
        printf("Invalid value. Use numbers from 0 to %d.\n", SIZE);
        printf("\n");
        return 0;
    }

    return 1;
}

void printline()
{
    if(SIZE == 9)
        printf("+-------+-------+-------+\n");
    else if(SIZE == 6)
        printf("+-------+-------+\n");
    
}
void printSeparator()
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


void input_sudoku()
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



int isSafe(int row, int col, int num)
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
    for (int i = 0; i < box_row; i++)
        for (int j = 0; j < box_col; j++)
            if (sudoku[i + startRow][j + startCol] == num)
                return false;

    return true;
}

int SudokuSolver()
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
        }
    }

    return false; // Trigger backtracking
}

int main()
{
    printf("==== Sudoku Solver ====\n");
    input_sudoku();
    printf("Initial Sudoku:\n");
    printSeparator();
    if (SudokuSolver()) {
        printf("Sudoku solved successfully:\n");
        printSeparator();
    } else {
        printf("No solution exists for the given Sudoku.\n");
    }
    getche();
}