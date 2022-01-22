#include <stdio.h>
double dp(int n, const double *x, const double *y);

int main() {

    double a[] = {1, -1};
    double b[] = {4.6, 4.7};

    int n = sizeof(a) / sizeof(*a);//размер массива (в compile time)

    double ans = dp(n, a, b);

    printf("%f\n", ans);
}
