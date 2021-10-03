#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name;
    int *bottom, *top;
    int num;
} STK;

void STK_init(STK *, char);

void STK_pop(STK *);

int STK_push(STK *, int);

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

    for (int i = n; i >= 1; i--) {
        STK_push(current, i);
    }

    while (third.num != n) {
        STK_push(next, 1);
        STK_pop(current);

        if (another->num == 0 && current->num != 0) {
            STK_push(another, *(current->top));
            STK_pop(current);
            printf("%c -> %c\n", current->name, another->name);
        } else if (current->num == 0 && another->num != 0){
            STK_push(current, *(another->top));
            STK_pop(another);
            printf("%c -> %c\n", another->name, current->name);
        } else if (current->num != 0 && another->num != 0 && *(current->top) < *(another->top)) {
            STK_push(another, *(current->top));
            STK_pop(current);
            printf("%c -> %c\n", current->name, another->name);
        } else if (current->num != 0 && another->num != 0 && *(another->top) < *(current->top)) {
            STK_push(current, *(another->top));
            STK_pop(another);
            printf("%c -> %c\n", another->name, current->name);
        }
    }

    return 0;
}

void STK_pop(STK *stack) {
    (stack->num)--;
    stack->bottom = (int *) realloc(stack->bottom, sizeof(int) * (stack->num));
    stack->top = stack->bottom + stack->num;
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
