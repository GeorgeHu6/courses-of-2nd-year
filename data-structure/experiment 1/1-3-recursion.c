#include <stdio.h>
#include <stdlib.h>

void hanoi(int, char, char, char, int*);

int main() {
    int num=0, n;

    printf("input n: ");
    scanf("%d", &n);

    hanoi(n, 'A', 'B', 'C', &num);

    return 0;
}

void hanoi(int n, char a, char b, char c, int* times) {
    if (n == 1) {
        printf("%c -> %c\n", a, c);
        (*times)++;
    } else {
        hanoi(n-1, a, c, b, times);
        printf("%c -> %c\n", a, c);
        (*times)++;
        hanoi(n-1, b, a, c, times);
    }
}
