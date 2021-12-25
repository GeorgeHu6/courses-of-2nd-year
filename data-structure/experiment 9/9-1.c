#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef char dataType;

void quickSort(dataType [], int, int);

int main() {
    dataType *test, ch;
    int num;

    printf("������Ҫ�����Ԫ�ظ�����\n");
    scanf("%d", &num);
    test = (char *) malloc(num*sizeof(char));

    printf("������Ҫ������ַ�Ԫ�أ��Կո�ָ���\n");
    
    for (int i = 0; i < num; i++) {
        while((ch = getchar()) && isspace(ch));
        test[i] = ch;
    }

    quickSort(test, 0, num-1);

    printf("������Ϊ��\n");
    for (int i = 0; i < num; i++)
        printf("%c ", test[i]);

    printf("\n");
    system("pause");
    return 0;
}

//��������Ԫ�صĺ���
void swap(dataType *a, dataType *b) {
    dataType t=*a;
    *a = *b;
    *b = t;
}

//��arr���е�[left,right]������п�������
void quickSort(dataType arr[], int left, int right) {
    int mid=arr[(left+right)/2];
    int l=left, r=right;
    while (l <= r) {
        //�ҵ���һ�����ڵ���mid��
        while (arr[l] < mid) l++;
        //�ҵ���һ��С�ڵ���mid��
        while (arr[r] > mid) r--;
        //������Ԫ�ؽ��������ֱ�����midС/�������
        if (l <= r) {
            swap(arr+l, arr+r);
            l++;
            r--;
        }
    }
    //�����ݹ����ÿ���ֶ�
    if (left < r) quickSort(arr, left, r);
    if (right > l) quickSort(arr, l, right);
}
