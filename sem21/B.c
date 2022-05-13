/* ### B

В аргументах комнадной строки передается N >= 1 и B > 0.

Требуется создать массив под N элементов и заполнить его первыми N простыми числами,
бОльшими числа B.

Следует породить N нитей. Каждая i-ая нить должна найти i-ое простое число.
Для поиска очередного числа следует "оттолкнуться" от результата поиска предыдущего
числа.
*/

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

int* results;
pthread_t* threads;

void* work(void* tmp) {
    int index = (int)(intptr_t)(tmp);
    int b;

    if (index) {
        pthread_join(threads[index - 1], NULL);
        b = results[index - 1];
    } else {
        b = results[0];
    }

    int cur = b + 1;
    while (!is_prime(cur)) {
        ++cur;
    }
    results[index] = cur;

    return NULL;
}


int main(int argc, char** argv) {
    int nthreads = atoi(argv[1]);
    int B = atoi(argv[2]);
    results = calloc(nthreads, (sizeof(*results)));
    results[0] = B;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);


    threads = calloc(nthreads, sizeof(*threads));
    for (int i = 0; i < nthreads; ++i) {
        // const pthread_attr_t *attr
        pthread_create(threads + i, &attr, work, (void *)(intptr_t)i);
    }
    pthread_attr_destroy(&attr);


    pthread_join(threads[nthreads - 1], NULL);
    for (int i = 0; i < nthreads; ++i) {
        printf("%d\n", results[i]);
    }
}
