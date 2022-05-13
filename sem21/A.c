// ### A

// В аргументах командной строки передается N >= 1.

// Следует породить N нитей, каждая из которых считывает со стандартного входа
// натуральное число Ki и находит Ki простое число, печатает его, и цикл повторяется.
// Если на стандартном потоке данных нет, то нити должны завершить свое выполнение.

// Дополнительное требование
// Предусмотреть ситуацию, когда нитей будет "очень много".

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


bool is_prime(int val) {
    if (val == 1) {
        return false;
    }
    if (val == 2) {
        return true;
    }
    int val_sqrt = sqrt(val) + 1;
    for (int i = 2; i <= val_sqrt; ++i) {
        if (val % i == 0) {
            return false;
        }
    }
    return true;
}


void* work(void* tmp) {
    int val;
    while (scanf("%d", &val) > 0) {
        int count = 0;
        int cur = 1;
        while (count != val) {
            if (is_prime(cur)) {
                ++count;
            }
            ++cur;
        }
        printf("%d\n", cur - 1);
    }
    return NULL;
}


int main(int argc, char** argv) {
    int nthreads = atoi(argv[1]);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);


    pthread_t* threads = calloc(nthreads, sizeof(*threads));
    for (int i = 0; i < nthreads; ++i) {
        // const pthread_attr_t *attr
        pthread_create(threads + i, &attr, work, NULL);
    }
    pthread_attr_destroy(&attr);

    for (int i = 0; i < nthreads; ++i) {
        pthread_join(threads[i], NULL);
    }

}
