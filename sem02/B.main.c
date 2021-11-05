#include <stdio.h>
#include <stdlib.h>

char *hello;
void print_hello_length(void);

int main()
{
    // считываение строк до ближайшего пробельного символа, выделение необходимого
    // объема динамической памяти под считанную строку (в случае успешного чтения)
    while (scanf("%ms", &hello) == 1)
    {
        print_hello_length();
        free(hello); // освобождение выделенной динамической памяти
    }

    return 0;
}
