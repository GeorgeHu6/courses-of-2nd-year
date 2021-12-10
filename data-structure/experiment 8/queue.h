#ifndef UNTITLED3_QUEUE_H
#define UNTITLED3_QUEUE_H

#define Status int
#define OK 1
#define ERROR 0
typedef int QElemType;

typedef struct QNode{
    QElemType pt;
    struct QNode *next;
} QNode;

typedef struct LinkQueue {
    QNode *head, *rear;
} LinkQueue, *queuePtr;

/* 队列基本操作 */
Status Enqueue(queuePtr, QElemType);
Status Dequeue(queuePtr, QElemType *);
Status Emptyqueue(LinkQueue q);
Status Initqueue(queuePtr q);

#endif //UNTITLED3_QUEUE_H
