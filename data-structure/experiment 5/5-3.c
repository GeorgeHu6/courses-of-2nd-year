#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Status int
#define OK 1
#define ERROR 0
#define STACK_INT_SIZE 100
#define STACKINCREMENT 10

typedef struct {
    char *base;
    char *top;
    int stacksize;
} charStack;

typedef struct {
    int *base;
    int *top;
    int stacksize;
} intStack;

Status initCharStack(charStack *);
Status pushCharStack(charStack *, char);
Status popCharStack(charStack *, char *);
char frontCharStack(charStack);

Status initIntStack(intStack *);
Status pushIntStack(intStack *, int);
Status popIntStack(intStack *, int *);

char compareOp(char, char);
Status isNum(char);
int cal(int, int, char);

//下标0代表+、-，1代表*、/，2代表(，3代表)，4代表开始/结束符#
char rules[5][5] = {{'>', '<', '<', '>', '>'},
                    {'>', '>', '<', '>', '>'},
                    {'<', '<', '<', '=', '!'},
                    {'>', '>', '!', '>', '>'},
                    {'<', '<', '<', '!', '='}};

int main() {
    char inputString[200] = {'\0'};
    int p = 0, tmp;
    char res, op;
    int num1, num2;
    intStack opNum;
    charStack opEr;
    initCharStack(&opEr);
    initIntStack(&opNum);

    printf("input an expression:\n");
    gets(inputString);
    //#作为垫底和结尾元素,即作为开始符和结束符
    pushCharStack(&opEr, '#');
    inputString[strlen(inputString)] = '#';

    while (inputString[p] != '#' || frontCharStack(opEr) != '#') {
        //操作数直接进栈
        if (isNum(inputString[p])) {
            tmp = 0;
            while (isNum(inputString[p])) {
                tmp = tmp * 10 + (inputString[p] - '0');
                p++;
            }
            pushIntStack(&opNum, tmp);
        } else {
            res = compareOp(frontCharStack(opEr), inputString[p]);
            if (res == '<') {
                //当前操作符优先级高，将当前操作符加入操作符栈
                pushCharStack(&opEr, inputString[p]);
                p++;
            } else if (res == '=') {
                //右括号碰到左括号，消去
                popCharStack(&opEr, &op);
                p++;
            } else if (res == '>') {
                //当前操作符优先级低于栈顶的，弹出两个操作数进行计算
                //通过操作数栈中元素是否够以判断是否有形如2++5的无效表达式
                if (popIntStack(&opNum, &num1) != OK || popIntStack(&opNum, &num2) != OK) {
                    printf("Expression invalid.\n");
                    system("pause");
                    return 0;
                }
                popCharStack(&opEr, &op);
                pushIntStack(&opNum, cal(num2, num1, op));
            } else if (res == '!') {
                printf("Expression invalid.\n");
                system("pause");
                return 0;
            }
        }
    }

    popIntStack(&opNum, &num1);
    printf("= %d\n", num1);

    system("pause");
    return 0;
}

//比较firstOp和secondOp的优先级
//返回'<'表示secondOp优先级较高
//返回'>'表示firstOp优先级较高
//返回'='表示优先级相当，用于匹配消去括号
//返回'!'表示有语法错误
char compareOp(char firstOp, char secondOp) {
    int i, j;
    switch (firstOp) {
        case '+':
        case '-':
            i = 0;
            break;
        case '*':
        case '/':
            i = 1;
            break;
        case '(':
            i = 2;
            break;
        case ')':
            i = 3;
            break;
        case '#':
            i = 4;
            break;
        default:
            return '!';
    }
    switch (secondOp) {
        case '+':
        case '-':
            j = 0;
            break;
        case '*':
        case '/':
            j = 1;
            break;
        case '(':
            j = 2;
            break;
        case ')':
            j = 3;
            break;
        case '#':
            j = 4;
            break;
        default:
            return '!';
    }
    return rules[i][j];
}

Status isNum(char ch) {
    return ch <= '9' && ch >= '0' ? OK : ERROR;
}

int cal(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:;
    }
}

Status initCharStack(charStack *S) {
    S->base = (char *) malloc(sizeof(char) * STACK_INT_SIZE);
    memset(S->base, '\0', STACK_INT_SIZE);
    if (S->base == NULL)
        return ERROR;
    S->stacksize = STACK_INT_SIZE;
    S->top = S->base;
    return OK;
}

Status initIntStack(intStack *S) {
    S->base = (int *) malloc(sizeof(int) * STACK_INT_SIZE);
    memset(S->base, '\0', STACK_INT_SIZE);
    if (S->base == NULL)
        return ERROR;
    S->stacksize = STACK_INT_SIZE;
    S->top = S->base;
    return OK;
}

Status pushCharStack(charStack *S, char e) {
    int length = (int) (S->top - S->base);
    //把e放入就满了，需要多申请STACKINCREMENT个位置
    if (length + 1 == S->stacksize) {
        S->base = (char *) realloc(S->base, sizeof(char) * (S->stacksize + STACKINCREMENT));
        if (S->base == NULL)
            return ERROR;
    }
    *(S->top) = e;
    S->top++;
    return OK;
}

Status pushIntStack(intStack *S, int e) {
    int length = (int) (S->top - S->base);
    //把e放入就满了，需要多申请STACKINCREMENT个位置
    if (length + 1 == S->stacksize) {
        S->base = (int *) realloc(S->base, sizeof(int) * (S->stacksize + STACKINCREMENT));
        if (S->base == NULL)
            return ERROR;
    }
    *(S->top) = e;
    S->top++;
    return OK;
}

Status popCharStack(charStack *S, char *e) {
    //栈为空，无法弹出
    if (S->base == S->top)
        return ERROR;
    *e = *(--S->top);
    return OK;
}

char frontCharStack(charStack S) {
    if (S.base == S.top)
        return '\0';
    return *(S.top - 1);
}

Status popIntStack(intStack *S, int *e) {
    //栈为空，无法弹出
    if (S->base == S->top)
        return ERROR;
    *e = *(--S->top);
    return OK;
}
