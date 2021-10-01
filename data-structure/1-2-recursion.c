#include <stdio.h>
#include <stdlib.h>

int n, k;
int f(int);

int main() {
    printf("input k: ");
    scanf("%d", &k);
    //对读入数据的有效性进行判断
    if (k < 1 || k > 5) {
        printf("error input k");
        return 1;
    }
    printf("input n: ");
    scanf("%d", &n);
    if (n < 0 || n > 30) {
        printf("error input n");
        return 1;
    }

    printf("fn=%d", f(n));

    return 0;
}

//递归计算fn的值，x <= k-1时为递归的边界
int f(int x) {
    int tmp=0;
    if (x < k-1)
        return 0;
    else if (x == k-1)
        return 1;
    else {
        for (int i = x-1; i >= 0; i--) {
            tmp += f(i);
        }
        return tmp;
    }
}

