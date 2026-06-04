#include<stdio.h>
#include<conio.h>

int main()
{
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (num % 2 == 0) {
        printf("The number is even.\n");
    } else {
        printf("The number is odd.\n");
    }
    printf("\033[33mSolved!\033[0m\n");
    getche();
}