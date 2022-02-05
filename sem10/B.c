#include <stdio.h>
int get_ebx()
{
    int res;

    asm volatile(
        "movl %%ebx, %0\n"
        : "=g"(res)
        :
        : "ebx"
    );

    return res;
}

int f(int x)
{
    int res;

    asm volatile(
        "movl %1, %%ebx\n"
        "call get_ebx\n"
        "incl %%eax\n"
        "movl %%eax, %0\n"
        : "=g"(res) // %0 - lvalue
        : "g"(x) // %1
        : "eax", "ebx"
    );
    return res;
}

int main()
{
    int x = 213453;
    int y = f(x);

    printf("%d %d\n", x, y);
}