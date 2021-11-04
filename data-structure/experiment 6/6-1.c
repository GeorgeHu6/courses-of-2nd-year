#include <stdio.h>
#include <stdlib.h>

#define QElemType char
#define Status int
#define OK 1
#define ERROR 0

typedef struct QNode {
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

Status InitQueue(LinkQueue *);

int main() {

}

Status InitQueue(LinkQueue *Q) {
    QNode *tmp = (QNode *) malloc(sizeof(QNode));
    tmp->data = '\0';
    tmp->next = NULL;
    Q->front = tmp;
    Q->rear = tmp;
}

Status empty(LinkQueue Q) {
    return Q.front == Q.rear
}
