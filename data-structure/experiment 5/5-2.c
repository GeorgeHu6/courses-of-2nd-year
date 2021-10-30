#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Status Empty(SqStack);

Status leftJudge(char);
Status rightJudge(char);
Status match(char, char);

int main() {
    SqStack t;
    SElemType *tmpElem;
    char inputString[500] = {'\0',};
    int p = 0;

    tmpElem = (SElemType *) malloc(sizeof(SElemType));
    *tmpElem = '\0';
    InitStack(&t);

    printf("input an expression:\n");
    //读取一整行输入
    gets(inputString);

    while (p < 500 && inputString[p] != '\0') {
        //由于只需要知道括号是否匹配，只要对括号进行处理即可
        //处理的是左括号，直接入栈
        if (leftJudge(inputString[p])) {
            Push(&t, inputString[p]);
            p++;
        } else if (rightJudge(inputString[p])) {
            //处理的是右括号，先把栈顶取出以进行匹配
            //栈空，当前右括号没有东西可以匹配了
            if (Pop(&t, tmpElem) != OK) {
                printf("Fail to match all brackets.\n");
                system("pause");
                return 0;
            }
            //若不匹配，输出错误信息直接退出程序
            if (!match(*tmpElem, inputString[p])) {
                printf("Fail to match all brackets.\n");
                system("pause");
                return 0;
            } else {
                //若匹配，继续判断下一个
                p++;
                continue;
            }
        } else {
            //处理的不是括号，直接跳过看下一个字符
            p++;
        }
    }

    //栈为空，说明括号全部匹配完成
    //栈不为空，说明有括号没有匹配上
    if (Empty(t))
        printf("All brackets matched.\n");
    else
        printf("Fail to match all brackets.\n");

    system("pause");
    return 0;
}

//判断是否为左括号
Status leftJudge(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

//判断是否为右括号
Status rightJudge(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

//判断ch1与ch2是否为匹配的括号
Status match(char ch1, char ch2) {
    return (ch1 == '(' && ch2 == ')') ||
           (ch1 == '[' && ch2 == ']') ||
           (ch1 == '{' && ch2 == '}');
}

Status InitStack(SqStack *S) {
    S->base = (SElemType *) malloc(sizeof(SElemType) * STACK_INT_SIZE);
    memset(S->base, '\0', STACK_INT_SIZE);
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

Status Empty(SqStack S) {
    return S.base == S.top ? OK : ERROR;
}