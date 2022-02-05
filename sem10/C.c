#include <stdio.h>

void* get_address() {
    // push %ebp
    // mov %esp, %ebp - в %ebp старый %ebp
    void* res;
    asm volatile (
            "mov (%%ebp), %%eax\n" // %eax - старый %ebp
            "mov 4(%%eax), %0\n"
            : "=r"(res)
            :
            : "eax"
        );
    return res;
}

void function(int x) {
    if (x != 0) {
        function(x - 1);
    }
    printf("%p %d\n", get_address(), x);
}

int main() {
    function(5);
    printf("%p %s\n", get_address(), "main");
    return 0;
}
