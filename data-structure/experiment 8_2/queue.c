#include "queue.h"
#include <stdlib.h>


Status Emptyqueue(LinkQueue q) {
    if (q.head->next == NULL)
        return OK;
    return ERROR;
}

Status Enqueue(queuePtr q, QElemType elem) {
    QNode* tmp = (QNode *) malloc(sizeof(QNode));
    if (tmp == NULL)
        return ERROR;
    tmp->pt = elem;
    tmp->next = NULL;

    q->rear->next = tmp;
    q->rear = tmp;
    return OK;
}

Status Dequeue(queuePtr q, QElemType *out) {
    if (Emptyqueue(*q) == OK)
        return ERROR;
    QNode *tmp=q->head->next;
    *out = q->head->next->pt;
    q->head->next = tmp->next;
    //由于队列是有头结点的，对出队后变为空队列的情况做特殊处理
    if (q->head->next == NULL)
        q->rear = q->head;
    free(tmp);

    return OK;
}

Status Initqueue(queuePtr q) {
    if (q == NULL)
        return ERROR;
    q->rear = q->head = (QNode *) malloc(sizeof(QNode));
    if (q->rear == NULL)
        return ERROR;
    q->head->next = NULL;

    return OK;
}

