#include <stdio.h>
#include <stdlib.h>

#define Status int
#define OK 1
#define ERROR 0
#define STACK_INT_SIZE 100
#define STACKINCREMENT 10

typedef char SElemType;
typedef struct Node {
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

Status InitStack(SqStack *);
Status Push(SqStack *, SElemType);
Status Pop(SqStack *, SElemType *);

int main() {
    SqStack t;
    SElemType *num;
    num = (SElemType *) malloc(sizeof(SElemType));
    InitStack(&t);
    Push(&t, 'a');
    Push(&t, 'b');
    Push(&t, 'd');
    Push(&t, 'e');
    Push(&t, '0');
    Pop(&t, num);
    printf("%c\n", *num);
    Pop(&t, num);
    printf("%c\n", *num);
    Pop(&t, num);
    printf("%c\n", *num);
    Pop(&t, num);
    printf("%c\n", *num);
    Pop(&t, num);
    printf("%c\n", *num);

    return 0;
}

Status InitStack(SqStack *S) {
    S->base = (SElemType *) malloc(sizeof(SElemType) * STACK_INT_SIZE);
    if (S->base == NULL)
        return ERROR;
    S->stacksize = STACK_INT_SIZE;
    S->top = S->base;
    return OK;
}

Status Push(SqStack *S, SElemType e) {
    int length = (int) (S->top - S->base);
    //把e放入就满了，需要多申请STACKINCREMENT个位置
    if (length + 1 == S->stacksize) {
        S->base = realloc(S->base, sizeof(SElemType) * (S->stacksize + STACKINCREMENT));
        if (S->base == NULL)
            return ERROR;
    }
    *(S->top) = e;
    S->top++;
    return OK;
}

Status Pop(SqStack *S, SElemType *e) {
    //栈为空，无法弹出
    if (S->base == S->top)
        return ERROR;
    *e = *(--S->top);
    return OK;
}