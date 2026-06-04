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
    // blue color code: \033[34m
    // red color code: \033[31m
    // green color code: \033[32m
    // yellow color code: \033[33m
    // reset color code: \033[0m
    // other colors: https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
    getche();
}