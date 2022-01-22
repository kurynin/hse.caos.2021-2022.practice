#include <stdio.h>
#include <math.h>

int main()
{
    float x = -1e10;
    x = x / -.0f;
    float y = x * 0.; // inf - inf; +-inf * 0
    float z = log(-1.);
    //y = -y;

    printf("x=%f isinf=%d isnan=%d isequal=%d\n", x, isinf(x), isnanf(x), (x == x));
    printf("y=%f isinf=%d isnan=%d\n", y, isinf(y), isnanf(y));
    printf("z=%f isinf=%d isnan=%d isequal=%d\n", z, isinf(z), isnanf(z), (z == z));
    return 0;
}