/*
1.1. Создать библиотеку libA.so, позволяющую в runtime загрузку и вызов реализованной в ней функции.
1.2. Написать программу на Си, подключающую в runtime libA.so и вызывающая функции из нее.
*/

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    void *handle = dlopen("libA.so", RTLD_LAZY); // если так не подключится, указать относительный путь: ./libA.so
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    float (*sumf)(float, float) = dlsym(handle, "sumf");
    if (!sumf) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    dlerror();
    float a, b;
    while (scanf("%f%f", &a, &b) == 2) {
        printf("%f\n", sumf(a, b));
    }
    dlclose(handle);
}
