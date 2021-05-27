#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

double mkcalc(double first, double second, char operation){
    double n = first;
    double result;
    switch (operation) {
        case '+':
            result = first + second;
            break;
        case '-':
            result = first - second;
            break;
        case '*':
            result = first * second;
            break;
        case '/':
            if(second == 0){
                puts("err");
                break;
            }
            result = first / second;
            break;
        case '^':
            while (second > 1)
            {
                first *= n;
                second -= 1;
            }
            result = first;
            break;
        case '!':
            while (n > 1)
            {
                n -= 1;
                first *= n;
            }
            result = first;
            break;
        default:
            puts("Typo!!!");
            return 0;
    }
    return result;
}


int main(){
    double first, second, result, n;
    char operation;
    char repeat = 'y';
    int fd1[2];
    int fd2[2];
    pid_t pid;

    if ((pipe(fd1) == -1) || (pipe(fd2) == -1))
    {
        printf("An error occured with opening the pipe\n");
        return 1;
    }
    if(!(pid = fork())){

        /* Дочерний процесс */

        close(fd1[1]); // в этот дискриптор будет писать родительский процесс
        close(fd2[0]); // из этого дискриптора родительский процесс будет читать

        while(1){
            if (read(fd1[0], &repeat, sizeof(char)) == -1)
            {
                printf("An error occured with reading from the pipe\n");
                return 1;
            }
            if (repeat != 'y'){
                close(fd1[0]);
                close(fd2[1]);
                return 0;
            }
            if (read(fd1[0], &first, sizeof(double)) == -1)
            {
                printf("An error occured with reading from the pipe\n");
                return 1;
            }
            if (read(fd1[0], &operation, sizeof(char)) == -1)
            {
                printf("An error occured with reading from the pipe\n");
                return 1;
            }
            if (read(fd1[0], &second, sizeof(double)) == -1)
            {
                printf("An error occured with reading from the pipe\n");
                return 1;
            }


            result = mkcalc(first, second, operation);




            if (write(fd2[1], &result, sizeof(double)) == -1)
            {
                printf("An error occured with writing into the pipe(result)\n");
                return 1;
            }
        }

        return 0;
    }

    /* Родительский процесс */


    close(fd1[0]);  // из этого дискриптора будет читать дочерний процесс
    close(fd2[1]);  // в этот дискриптор будет писать дочерний процесс

    while (repeat == 'y'){
        puts("Enter the first number: ");
        scanf("%lf", &first);
        puts("Enter your operation(+-*/^!): ");
        scanf(" %c", &operation);
        n = first;
        if (operation != '!')
        {
            puts("Enter the second  number: ");
            scanf("%lf", &second);
        }else{
            second = 0;
        }


        if (write(fd1[1], &repeat, sizeof(char)) == -1)
        {
            printf("An error occured with writing to the pipe(second)\n");
            return 1;
        }
        if (write(fd1[1], &first, sizeof(double)) == -1)
        {
            printf("An error occured with writing to the calc(first)\n");
            return 1;
        }
        if (write(fd1[1], &operation, sizeof(char)) == -1)
        {
            printf("An error occured with writing to the calc(operation)\n");
            return 1;
        }
        if (write(fd1[1], &second, sizeof(double)) == -1)
        {
            printf("An error occured with writing to the pipe(second)\n");
            return 1;
        }







        if (read(fd2[0], &result, sizeof(double)) == -1)
        {
            printf("An error occured with reading from the pipe\n");
            return 6;
        }
        printf("Result = %f", result);
        puts("\nEnter \"y\" to continue");
        scanf(" %c", &repeat);
    }
    close(fd1[1]);
    close(fd2[0]);

    return 0;
}
