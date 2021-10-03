#include <stdio.h>
#include <stdlib.h>

int solve(int, int);

int main() {
	int m, n;
    while (1) {
	    printf("input n: \n");
	    scanf("%d", &n);
	    if (n == -1) { return 0; }
	    printf("input m: \n");
	    scanf("%d", &m);
        if (m == -1) { return 0; }
        printf("%d\n", solve(n, m));
    }

    return 0;
}

int solve(int days, int peaches) {
    if (days == 0)
        return peaches;
    else
        return solve(days-1, (peaches+1)*2); 
}
