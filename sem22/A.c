// ### A

// Программе в аргументах командной строки задаются натуральные числа числа

// X0 dx nx Y0 dy ny

// Есть 4 счета с начальным состоянием:
// A  B  C  G
// -----------
// X0 Y0 0  0

// Требуется двумя нитями реализовать логику:
// Нить 1 nx раз вычитает из A величину dx, при этом 15% кладет на счет G, остальное - в B.
// Нить 2 ny раз вычитает из B величину dy, при этом 20% кладет на счет G, остальное - в C.

// Определить инвариант(ы) для этой задачи.
// Проверить их выполнение в начале и в конце работы программы.


#include <pthread.h>
#include <stdio.h>

int A, B, C, G;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void *vvoid) {
    volatile int *pin, *pout;
    int tax;
    volatile int *v = vvoid;
    if (v[0] == 1) {
        pin = &A;
        pout = &B;
        tax = 15;
    } else {
        pin = &B;
        pout = &C;
        tax = 20;
    }
    int tax_sum = (v[1] * tax) / 100;
    int other_sum = v[1] - tax_sum;
    for (int i = 0; i < v[2]; ++i) {
        pthread_mutex_lock(&counter_mutex);
        *pin -= v[1];
        *pout += other_sum;
        G += tax_sum;
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}


void work(int x0, int dx, int nx, int y0, int dy, int ny) {
    A = x0;
    B = y0;
    C = G = 0;
    int v1[3] = {1, dx, nx}, v2[3] = {2, dy, ny};
    pthread_t treads[2];
    pthread_create(treads, NULL, thread_func, v1);
    pthread_create(treads + 1, NULL, thread_func, v2);
    pthread_join(treads[0], NULL);
    pthread_join(treads[1], NULL);
    printf("%d %d\n", x0 + y0, A + B + C + G);
}

int main() {
    int x0, dx, nx, y0, dy, ny;
    while (scanf("%d%d%d%d%d%d", &x0, &dx, &nx, &y0, &dy, &ny) != EOF) {
        work(x0, dx, nx, y0, dy, ny);
    }
}
