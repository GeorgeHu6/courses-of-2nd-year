#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define QElemType char
#define Status int
#define OK 1
#define ERROR 0
#define MAXQSIZE 100

typedef struct {
    QElemType *base;
    int front;
    int rear;
} SqQueue;

Status InitQueue(SqQueue *);

Status EnQueue(SqQueue *, QElemType);

Status DeQueue(SqQueue *, QElemType *);

Status empty(SqQueue);
Status full(SqQueue);

int main() {
    SqQueue queue;
    InitQueue(&queue);
    char ch;

    printf("input some chars separate with space or enter(ending with #)\n");
    printf("input character should be fewer than 100\n");
    //以“#”作为输入的结尾，以此判断输入结束
    while (1) {
        scanf("%c", &ch);
        if (ch == '#')
            break;
        if (isspace(ch))
            continue;
        if (EnQueue(&queue, ch) == ERROR){
            printf("Too many chars!\n");
            break;
        }
    }

    printf("DeQueue:\n");
    while (DeQueue(&queue, &ch) == OK)
        printf("%c ", ch);
    printf("\n");

    system("pause");
    return 0;
}

Status InitQueue(SqQueue *Q) {
    Q->base = (QElemType *) malloc(sizeof(QElemType) * (MAXQSIZE+1));
    if (Q->base == NULL)
        return ERROR;
    Q->front = Q->rear = 0;
    return OK;
}

Status EnQueue(SqQueue *Q, QElemType e) {
    if (full(*Q))
        return ERROR;
    (Q->base)[Q->rear] = e;
    Q->rear = (Q->rear + 1) % (MAXQSIZE+1);
    return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e) {
    if(empty(*Q))
        return ERROR;
    *e = (Q->base)[Q->front];
    Q->front = (Q->front + 1) % (MAXQSIZE+1);
    return OK;
}

Status empty(SqQueue Q) {
    return Q.front == Q.rear ? OK : ERROR;
}

Status full(SqQueue Q) {
    return (Q.rear + 1) % (MAXQSIZE+1) == Q.front ? OK : ERROR;
}
