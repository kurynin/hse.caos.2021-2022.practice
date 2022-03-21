// ### B.c
// В аргументах командной строки передаются 2 строки с датами
// Da Db
// Затем на вход подаются строки Di. Следует для каждой из них вывести YES/NO
// в зависимости от того, выполняется ли Da <= Di <= Db
// Формат даты: YYYY-MM-DD hh:mm:ss

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

time_t gettime(const char *s) {
    struct tm dt = { .tm_isdst = -1 };
    sscanf(s, "%d-%d-%d%d:%d:%d", &dt.tm_year, &dt.tm_mon, &dt.tm_mday, &dt.tm_hour, &dt.tm_min, &dt.tm_sec);
    dt.tm_year -= 1900;
    --dt.tm_mon;
    return mktime(&dt);
}

int main(int argc, char *argv[]) {
    char s[100];
    time_t first = gettime(argv[1]);
    time_t last = gettime(argv[2]);
    while (fgets(s, sizeof(s), stdin)) {
        time_t cur = gettime(s);
        printf((first <= cur && cur <= last) ? "YES\n" : "NO\n");
    }
    return 0;
}
