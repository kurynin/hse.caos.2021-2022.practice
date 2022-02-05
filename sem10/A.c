int f(int x)
{
    int j = x + 2;
    asm volatile (
        "It's just the text\n"
        "Inside " "asm block\n"
    );

    return j << 1;
}

// gcc -m32 -S A.c -o A.S - увидим текст внутри S-файла
// gcc -m32 -c A.c - будет ошибка компиляции
