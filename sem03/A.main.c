/*
Написать программу на Си, считывающая со стандартного входного потока тройки целых чисел (A, d, N) {N>0}
Для каждой тройки вывести N-ый член арифметической прогрессии
*/
#include <stdio.h>

int nth_element(int a, int d, int n);

int main()
{
    int a, d;
    unsigned n;
    while (scanf("%d%d%u", &a, &d, &n) == 3)
    {
        int res = nth_element(a, d, n);
        printf("if A[1]=%d d=%d then A[%u]=%d\n", a, d, n, res);
    }
    return 0;
}