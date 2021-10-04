#include <stdio.h>
#include <stdlib.h>

//使用栈存储每个柱子
typedef struct {
    char name;
    int *arr;
    int num;
} STK;

//使用一个字符作为标签初始化一个柱子
void STK_init(STK *, char);

void STK_pop(STK *);

int STK_push(STK *, int);

int main() {
    int num = 0, n;
    //绝对地存储三个柱子
    STK first, second, third;
    //current指向当前处理的柱子，next指向下一个要处理的柱子
    //another指向作为辅助的其他柱子
    STK *current, *next, *another, *tmp;

    //初始化三个柱子
    STK_init(&first, 'A');
    STK_init(&second, 'B');
    STK_init(&third, 'C');

    printf("input n: ");
    scanf("%d", &n);

    //奇数个盘时左移，即当前柱子为1号，下一个柱子为3号
    //偶数个盘时右移，即当前柱子为1号，下一个柱子为2号
    if (n % 2 == 1) {
        current = &first;
        next = &third;
        another = &second;
    } else {
        current = &first;
        next = &second;
        another = &third;
    }

    //将盘放入1号柱子初始化，数字越大代表越大的盘，即1号盘是最小的
    for (int i = n; i >= 1; i--) {
        STK_push(current, i);
    }

    //由于所有步骤都是在满足题目要求的情况下进行移动的
    //则当3号柱有n个盘时就完成了汉诺塔游戏
    while (third.num != n) {
        //先将最小的盘移到下一个柱子
        STK_push(next, 1);
        STK_pop(current);
        printf("%c -> %c\n", current->name, next->name);

        //下一个柱子上已经有了最小盘，不再做移动
        //在辅助柱子和当前柱子之间进行一次移动，分为4种情况

        //情况1：辅助柱子为空，将当前柱子有盘
        //情况2：当前柱子为空，辅助柱子有盘
        //情况3：当前柱子和辅助柱子都有盘，但是当前柱顶的盘比辅助柱顶的盘小
        //情况4：当前柱子和辅助柱子都有盘，但是辅助柱顶的盘比当前柱顶的盘小
        if (another->num == 0 && current->num != 0) {
            STK_push(another, *(current->arr + current->num - 1));
            STK_pop(current);
            printf("%c -> %c\n", current->name, another->name);
        } else if (current->num == 0 && another->num != 0){
            STK_push(current, *(another->arr + another->num - 1));
            STK_pop(another);
            printf("%c -> %c\n", another->name, current->name);
        } else if (current->num != 0 && another->num != 0 && *(current->arr + current->num - 1) < *(another->arr + another->num - 1)) {
            STK_push(another, *(current->arr + current->num - 1));
            STK_pop(current);
            printf("%c -> %c\n", current->name, another->name);
        } else if (current->num != 0 && another->num != 0 && *(another->arr + another->num - 1) < *(current->arr + current->num - 1)) {
            STK_push(current, *(another->arr + another->num - 1));
            STK_pop(another);
            printf("%c -> %c\n", another->name, current->name);
        }
        
        //循环交替进行
        tmp = current;
        current = next;
        next = another;
        another = tmp;
    }

    return 0;
}

void STK_pop(STK *stack) {
    (stack->num)--;
    stack->arr = (int *) realloc(stack->arr, sizeof(int) * (stack->num));
}

void STK_init(STK *stack, char name) {
    stack->name = name;
    stack->num = 0;
    stack->arr = NULL;
}

int STK_push(STK *stack, int x) {
    (stack->num)++;
    if (stack->num == 1) {
        stack->arr = (int *) malloc(sizeof(int));
        *(stack->arr) = x;
    } else {
        stack->arr = (int *) realloc(stack->arr, sizeof(int)*(stack->num+1));
        if (stack->arr == NULL)
            return -1;
        *(stack->arr + stack->num - 1) = x;
    }

    return 1;
}
