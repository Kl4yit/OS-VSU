#include <stdio.h>
#include <stdlib.h>
#include <linux/ipc.h>
#include <linux/msg.h>
#include <sys/types.h>

/* Redefines the message structure */
typedef struct mymsgbuf
{
    long mtype;               // "mtype" -
    float first;              // uses 2 message types
    float second;             // 1 - collector to calculator, 2 - calculator to collector
    float result;
    char operation;
    char repeat;
} mess_t;





float mkcalc(float first, float second, char operation){
    float n = first;
    float result;
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





int main()
{
    int qid;
    int length;
    int cont;
    key_t msgkey;
    pid_t pid;
    mess_t send;
    mess_t receive;



    length = sizeof(mess_t) - sizeof(long);

    msgkey = ftok(".",'m');

    qid = msgget(msgkey, IPC_CREAT | 0660);




    if(!(pid = fork())){
        printf("Calculator starts - QID = %d\n", qid);

        msgrcv(qid, &receive, length, 1, 0);
        send.mtype = 2;
        send.first = 0;
        send.second = 0;
        send.operation = 'n';
        send.repeat = 'n';

        while (receive.repeat == 'y'){
            send.result = mkcalc(receive.first, receive.second, receive.operation);
            msgsnd(qid, &send, length, 0);
            msgrcv(qid, &receive, length, 1, 0);
        }

        printf("Calculator stops\n");
        msgctl(qid, IPC_RMID, 0);
        return 0;
    }


    printf("Collector starts - QID = %d\n", qid);


    send.repeat = 'y';
    while (send.repeat == 'y'){
        puts("Enter the first number: ");
        scanf("%f", &send.first);
        puts("Enter your operation(+-*/^!): ");
        scanf(" %c", &send.operation);
        if (send.operation != '!')
        {
            puts("Enter the second  number: ");
            scanf("%f", &send.second);
        }else{
            send.second = 0;
        }
        send.mtype = 1;
        send.result = 0;
        msgsnd(qid, &send, length, 0);
        msgrcv(qid, &receive, length, 2, 0);
        printf("Result = %f", receive.result);
        puts("\nEnter \"y\" to continue");
        scanf(" %c", &send.repeat);
    }

    printf("Collector stops\n");
    msgsnd(qid, &send, length, 0);
    msgctl(qid, IPC_RMID, 0);

    return 0;
}



