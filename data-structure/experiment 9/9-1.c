#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef char dataType;

void quickSort(dataType [], int, int);

int main() {
    dataType *test, ch;
    int num;

    printf("请输入要排序的元素个数：\n");
    scanf("%d", &num);
    test = (char *) malloc(num*sizeof(char));

    printf("请输入要排序的字符元素（以空格分隔）\n");
    
    for (int i = 0; i < num; i++) {
        while((ch = getchar()) && isspace(ch));
        test[i] = ch;
    }

    quickSort(test, 0, num-1);

    printf("排序结果为：\n");
    for (int i = 0; i < num; i++)
        printf("%c ", test[i]);

    printf("\n");
    system("pause");
    return 0;
}

//交换数组元素的函数
void swap(dataType *a, dataType *b) {
    dataType t=*a;
    *a = *b;
    *b = t;
}

//对arr序列的[left,right]区间进行快速排序
void quickSort(dataType arr[], int left, int right) {
    int mid=arr[(left+right)/2];
    int l=left, r=right;
    while (l <= r) {
        //找到第一个大于等于mid的
        while (arr[l] < mid) l++;
        //找到第一个小于等于mid的
        while (arr[r] > mid) r--;
        //将两个元素交换，即分别放入比mid小/大的两边
        if (l <= r) {
            swap(arr+l, arr+r);
            l++;
            r--;
        }
    }
    //继续递归快排每个分段
    if (left < r) quickSort(arr, left, r);
    if (right > l) quickSort(arr, l, right);
}
