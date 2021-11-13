/*
Написать программу-приветствие.
Программа печатает приглашение представиться, ожидает ввода беспробельной строки (<user>), длиной не более 20 символов,
и выводит фразу-приветствие HELLO <user>
*/

void print(const char *buf, int length);
int input(char *buf, int buf_size); // возвращает число считанных байт

int main()
{
    char enter[] = "Enter your name: ";
    char hello[] = "Hello ";
    char nl[] = "\n";

    char buf[21] = {0};
    int n;
    print(enter, sizeof(enter) - 1);
    if ((n = input(buf, sizeof(buf) - 1)) > 0)
    {
        print(hello, sizeof(hello) - 1);
        print(buf, n);
        //print(nl, sizeof(nl) - 1);
    }
    return 0;
}