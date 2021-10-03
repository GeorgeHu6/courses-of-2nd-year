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
        sum = m;
        while (n--) {
            sum = (sum + 1)*2;
        }
        printf("%d\n", sum);
    }

    return 0;
}
