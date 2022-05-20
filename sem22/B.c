#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

int X0, dx, n, prime;

pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
bool f = false;

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

int get_prime(int cur, int X0) {
    int count = 0;
    while (count != X0) {
        if (is_prime(cur)) {
            ++count;
        }
        ++cur;
    }
    return cur - 1;
}



void* work(void* tmp) {
    int cur = 0;
    int index = X0;
    while (1) {
        cur = get_prime(cur + 1, index);
        index = dx;
        pthread_mutex_lock(&m);
        prime = cur;
        f = true;
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m);
        // sleep(1);
    }
    return NULL;
}


int main() {
    scanf("%d%d%d", &X0, &dx, &n);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);

    pthread_t thread;
    pthread_create(&thread, NULL, work, NULL);


    for (int i = 0; i < n; ++i) {
        pthread_mutex_lock(&m);
        int p;
        while (!f) {
            pthread_cond_wait(&c, &m);
        }
        p = prime;
        f = false;
        pthread_mutex_unlock(&m);
        printf("%d\n", p);
    }
}
