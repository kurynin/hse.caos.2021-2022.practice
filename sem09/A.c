#include <stdio.h>

float diag(float x, float y, float z);

int main()
{
    float x;
    float y;
    float z;

    while (scanf("%f%f%f", &x, &y, &z) == 3)
    {
        float ans = diag(x, y, z);
        printf("%f, %f, %f => %f\n", x, y, z, ans);
    }
}
