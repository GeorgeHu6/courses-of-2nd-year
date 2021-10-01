#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name;
    int *bottom, *top;
    int num;
} STK;

void STK_init(STK *, char);

void STK_pop(STK *);

int STK_top(STK);

int STK_push(STK *, int);

int STK_length(STK);

int main() {
    int num = 0, n;
    STK first, second, third;
    STK *current, *next, *another;
    STK_init(&first, 'A');
    STK_init(&second, 'B');
    STK_init(&third, 'C');

    printf("input n: ");
    scanf("%d", &n);

    if (n % 2 == 1) {
        current = &first;
        next = &third;
        another = &second;
    } else {
        current = &first;
        next = &second;
        another = &third;
    }


    printf("input n: ");
    scanf("%d", &n);

    return 0;
}

void STK_pop(STK *stack) {
    (stack->num)--;
    stack->bottom = (int *) realloc(stack->bottom, sizeof(int) * (stack->num));
    stack->top = stack->bottom + stack->num;
}

int STK_top(STK stack) {
    return stack.num;
}

void STK_init(STK *stack, char name) {
    stack->name = name;
    stack->num = 0;
    stack->bottom = (int *) malloc(sizeof(int));
    stack->top = stack->bottom;
}

int STK_push(STK *stack, int x) {
    (stack->num)++;
    stack->bottom = (int *) realloc(stack->bottom, sizeof(int) * (stack->num));
    if (stack->bottom == NULL)
        return -1;
    stack->top = stack->bottom + stack->num;
    (*stack->top) = x;
    return 1;
}

int STK_length(STK stack) {
    return stack.num;
}

