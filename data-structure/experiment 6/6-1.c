#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define QElemType char
#define Status int
#define OK 1
#define ERROR 0

typedef struct QNode {
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr rear;
    QueuePtr front;
} LinkQueue;

Status InitQueue(LinkQueue *);
Status EnQueue(LinkQueue *, QElemType);
Status DeQueue(LinkQueue *, QElemType *);
Status empty(LinkQueue);

int main() {
    LinkQueue queue;
    InitQueue(&queue);
    char ch;

    printf("input some chars separate with space or enter(ending with #)\n");
    //以“#”作为输入的结尾，以此判断输入结束
    while (1) {
        scanf("%c", &ch);
        if (ch == '#')
            break;
        if (isspace(ch))
            continue;
        EnQueue(&queue, ch);
    }

    printf("DeQueue:\n");
    while (DeQueue(&queue, &ch) == OK)
        printf("%c ", ch);
    printf("\n");

    system("pause");
    return 0;
}

Status InitQueue(LinkQueue *Q) {
    QNode *tmp = (QNode *) malloc(sizeof(QNode));
    if (tmp == NULL)
        return ERROR;
    tmp->data = '\0';
    tmp->next = NULL;
    Q->rear = tmp;
    Q->front = tmp;
    return OK;
}

Status EnQueue(LinkQueue *Q, QElemType e) {
    QNode *tmp = (QNode *) malloc(sizeof(QNode));
    if (tmp == NULL)
        return ERROR;
    tmp->data = '\0';
    tmp->next = NULL;
    Q->rear->data = e;
    Q->rear->next = tmp;
    Q->rear = tmp;
    return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e) {
    QNode *tmp=Q->front;
    if (empty(*Q) == OK)
        return ERROR;
    Q->front = Q->front->next;
    *e = tmp->data;
    free(tmp);
    return OK;
}

Status empty(LinkQueue Q) {
    return Q.rear == Q.front ? OK : ERROR;
}
