#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int row = 6;
int col = 6;
int box_row = 2;
int box_col = 3;
int EMPTY = 0;
int sudoku[6][6] = {0};
int i=0,j=0;

bool isValidValue(int value) 
{
    return value >= 0 && value <= 6;
}

int checkValidValue(int value, int r, int c) {
    if (!isValidValue(value)) {
        printf("Invalid value at row %d, column %d. Use numbers from 0 to 6.\n", r + 1, c + 1);
        printf("\n");
        return 0;
    }

    return 1;
}

void printSeparator()
{
        printf("+-------+-------+\n");
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
                printf("+-------+-------+\n");
        }
    } 


void input_sudoku()
{

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
                    printf("Invalid input. Please enter a number.\n");
                    while(getchar() != '\n'); // Clear invalid input
                    goto repeat_input;
                }
                if (!checkValidValue(temp, i, j)) {
                    goto repeat_input;
                }
                sudoku[i][j] = temp;
            }
        }
        
        printf("The sudoku is: \n");
        printSeparator();
    
}

int main()
{
    printf("==== Sudoku Solver ====\n");
    input_sudoku();
    return 0;
}