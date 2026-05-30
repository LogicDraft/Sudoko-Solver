#include<stdio.h>
#include<conio.h>

int main()
{
    int sudoko[6][6];
        for(int i=0;i<6;i++)
        {
            printf("Row : %d \n",i+1);
            for(int j=0;j<6;j++)
            {
                printf("Enter the value of sudoko[%d]: ",j+1);
                scanf("%d",&sudoko[i][j]);
            }
        }
        printf("The sudoko is: \n");
        
        for(int i=0;i<6;i++)
        {
            printf("+---+---+---+---+---+---+\n");
            for(int j=0;j<6;j++)
            {
                printf("| %d ",sudoko[i][j]);
            }
            printf("|\n");
        }
        printf("+---+---+---+---+---+---+\n");
    return 0;
}