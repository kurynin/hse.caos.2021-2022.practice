#include <stdio.h>

union C {
    unsigned u;
    float f;
    struct {
        unsigned m : 23;
        unsigned e : 8;
        unsigned s : 1;
    } b;
};


int main() {
    union C temp;
    while (scanf("%f", &temp.f) == 1) {
        printf ("u = %x s = %u e = %u m = %x\n", temp.u, temp.b.s, temp.b.e, temp.b.m);
    }
}
