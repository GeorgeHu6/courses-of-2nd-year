#include <stdio.h>
#include <stdlib.h>

int max_score(int*, int);
int min_score(int*, int);
double avg_score(int*, int);

int main() {
    //使用动态数组来存储分数，count记录数组中存储的分数的个数
    int *score, count=0;

    score = (int *)malloc(sizeof(int));
    
    printf("Please input few scores between 0 and 100 (interval with space, ending with q):\n");
    while (scanf("%d", score+count)) {
        //忽略不在0到100之间的分数
        if (*(score+count) < 0 || *(score+count) > 100)
            continue;
        else {
            count++;
            score = (int *) realloc(score, count*sizeof(int));
            if (score == NULL)
                return 1;
        }
	}

    printf("\nmax score: %d", max_score(score, count));
    printf("\nmin score: %d", min_score(score, count));
    printf("\naverage score: %.2f", avg_score(score, count));

    return 0;
}

//在长为n的动态数组score_arr中寻找最高分数
int max_score(int* score_arr, int n) {
   int max=-1;

   for (int i = 0; i < n; i++)
       max = score_arr[i] > max ? score_arr[i] : max;

   return max;
}

//在长为n的动态数组score_arr中寻找最低分数
int min_score(int* score_arr, int n) {
   int min=200;

   for (int i = 0; i < n; i++)
       min = score_arr[i] < min ? score_arr[i] : min;

   return min;
}

////求取长为n的动态数组score_arr中分数的平均值
double avg_score(int* score_arr, int n) {
    double sum=0.0;

    for (int i = 0; i < n; i++) {
        sum += score_arr[i];
    }

    return sum/n;
}
