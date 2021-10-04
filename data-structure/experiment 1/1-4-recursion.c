#include <stdio.h>
#include <stdlib.h>

int solve(int, int);

int main() {
	int m, n;
    while (1) {
        //若输入的n和m中有一个为-1就退出程序
	    printf("input n: \n");
	    scanf("%d", &n);
	    if (n == -1) { return 0; }
	    printf("input m: \n");
	    scanf("%d", &m);
        if (m == -1) { return 0; }
        printf("origin peach: %d\n", solve(n, m));
    }

    return 0;
}

//返回第days天剩余peaches个桃时，一开始桃的个数
int solve(int days, int peaches) {
    if (days == 0)
        return peaches;
    else
        return solve(days-1, (peaches+1)*2); 
}
