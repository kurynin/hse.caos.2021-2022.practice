#include <math.h>
#include <stdio.h>

int main() {
    float x;
    while (scanf("%f", &x) == 1) {
        unsigned u = *(unsigned *) &x;
        unsigned sign = u >> 31;
        int exp = (u >> 23 & 0xff) - 127;
        unsigned m = (u & 0x7fffff) << 1;
        printf("(-1)^{%u} * 1.%x * 2^{%d} = %a\n", sign, m, exp, x);
    }
}
