#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef int dataType;

int binarySearch(dataType [], int n, dataType);

int main() {
    dataType test[10]={'A','C','D','E','J','L','O','a','d','g'};
    int index;
    dataType ch;
    printf("�������ַ�����Ϊ��\n");
    for (int i = 0; i < 10; i++)
        printf("%c ", test[i]);
    printf("\n");

    while (1) {
        printf("������Ҫ���ҵ��ַ�������-Ϊ�˳���\n");
        //ȥ���ո񡢻��з�
        while ((ch = getchar()) && isspace(ch));
        if (ch == '-')
            break;
        index = binarySearch(test, 10, ch);
        if (index == -1)
            printf("δ�ҵ�\n");
        else
            printf("�ҵ��ˣ���һ��'%c'���±�Ϊ%d\n", ch, index);
    }

    system("pause");
    return 0;
}

//�ڷǵݼ�����arr�ж��ֲ���keyword������arr���ҵ��ˣ��򷵻��±ꣻ��û�ҵ����򷵻�-1
//��Ҫ����arr�ĳ���n
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
