/*
 * Программа бесконечно выводит заранее заданную строку на экран
 * и ожидает сигналов SIGUSR1 и SIGUSR2. При получении
 * каждого из сигналов она меняет выводимую строку.
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

char str[23] = "Waiting your for signal.\n";                    // строка, отправляемая в консоль

                                                                // обраотчик сигналов
void handler(int signal)
{
    switch (signal)
    {
        case SIGUSR1:
            strcpy(str, "Received signal: SIGUSR1\n");   // прееопределение строки, отправляемой в консоль
            break;
        case SIGUSR2:
            strcpy(str, "Received signal: SIGUSR2\n");
            break;
    }
}

int main()
{
                                                                // регистрация сигналов
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    printf("Current PID: %d\n", getpid());
    while (1)
    {
        printf("%s", str);                               // вывод строки
        sleep(1);
    }
    return 0;
}