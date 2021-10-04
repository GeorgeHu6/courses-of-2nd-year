#include <stdio.h>
#include <stdlib.h>

int main() {
	int m, n, sum;
    while (1) {
	    printf("input n: \n");
	    scanf("%d", &n);
	    if (n == -1) { return 0; }
	    printf("input m: \n");
	    scanf("%d", &m);
        if (m == -1) { return 0; }
        //初始化桃子数量
        sum = m;
        //通过倒推的方法不断将桃子数量+1再乘2，倒推n次即可
        while (n--) {
            sum = (sum + 1)*2;
        }
        printf("origin peach: %d\n", sum);
    }

    return 0;
}
