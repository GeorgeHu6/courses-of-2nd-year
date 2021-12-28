#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef int dataType;

int binarySearch(dataType [], int n, dataType);

int main() {
    dataType test[10]={'A','C','D','E','J','L','O','a','d','g'};
    int index;
    dataType ch;
    printf("待查找字符序列为：\n");
    for (int i = 0; i < 10; i++)
        printf("%c ", test[i]);
    printf("\n");

    while (1) {
        printf("请输入要查找的字符（减号-为退出）\n");
        //去除空格、换行符
        while ((ch = getchar()) && isspace(ch));
        if (ch == '-')
            break;
        index = binarySearch(test, 10, ch);
        if (index == -1)
            printf("未找到\n");
        else
            printf("找到了，第一个'%c'的下标为%d\n", ch, index);
    }

    system("pause");
    return 0;
}

//在非递减序列arr中二分查找keyword，若在arr中找到了，则返回下标；若没找到，则返回-1
//需要给入arr的长度n
int binarySearch(dataType arr[], int n, dataType keyword) {
    int left=0, right=n-1;
    int mid;
    while (left <= right) {
        mid = (left+right)/2;
        if (arr[mid]==keyword)
            return mid;
        else if (arr[mid] < keyword)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
