#include <stdio.h>
#include <stdlib.h>

int n, k;

int main() {
    int *F;
    int sum;
    printf("input k: ");
    scanf("%d", &k);
    if (k < 1 || k > 5) {
        printf("error input k");
        return 1;
    }
    printf("input n: ");
    scanf("%d", &n);
    if (n < 0 || n > 30 || n < k) {
        printf("error input n");
        return 1;
    }

    //使用动态数组，不浪费空间
    F = (int *) malloc((n+1)*sizeof(int));
    //初始化条件
    for (int i = 0; i < k-1; i++)
        F[i] = 0;
    F[k-1] = 1;
    sum = 1;

    //使用滑动窗口思想大幅减少时间复杂度
    for (int i = k; i <= n; i++) {
        F[i] = sum;
        sum -= F[i-k];
        sum += F[i];
    }

    printf("fn=%d", F[n]);
    
    return 0;
}

