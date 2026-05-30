#include<stdio.h>
#include<conio.h>

int row = 6;
int col = 6;
int box_row = 2;
int box_col = 3;
int EMPTY = 0;

int sudoku[6][6];



void printSeparator()
{
        printf("+-------+-------+\n");
        for(int i=0;i<row;i++)
        {
            printf("|");
            for(int j=0;j<col;j++)
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
        for(int i=0;i<row;i++)
        {
            printf("Row : %d \n",i+1);
            for(int j=0;j<col;j++)
            {
                printf("Enter the value of sudoku[%d]: ",j+1);
                scanf("%d",&sudoku[i][j]);
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