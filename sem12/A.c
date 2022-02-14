/*
Программа принимает на вход положительные числа n и k.
Следует распечатать в обратном порядке n первых чисел, делящихся на k.
Рекурсией и функциями *alloc пользоваться запрещено.
*/

#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>

int main(int argc, char **argv) {
    int n, k;
    while (scanf("%d %d", &n, &k) == 2) {
        int *arr = mmap(NULL, n * sizeof(int), PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (arr == MAP_FAILED) {
            perror(argv[0]);
            fprintf(stderr, "error\n");
            return 1;
        }
        for (int i = 0; i != n; ++i) {
            arr[i] = k * i;
        }
        for (int i = 0; i != n; ++i) {
            printf("[%d] - %d\n", i, arr[n - 1 - i]);
        }
        munmap(arr, n * sizeof(int));
    }
}
