/*
Написать программу-приветствие.
Программа печатает приглашение представиться, ожидает ввода беспробельной строки (<user>), длиной не более 20 символов,
и выводит фразу-приветствие HELLO <user>
*/
#include <stdio.h>

int main()
{
    char buf[21];
    printf("Enter your name: ");
    if (scanf("%20s", buf) == 1)
    {
        printf("HELLO %s\n", buf);
    }
    return 0;
}