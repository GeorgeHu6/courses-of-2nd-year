#include <iostream>
#include <cstdlib>

using namespace std;
typedef int dataType;


template<class T>
struct Pair
{
    T first;
    T second;
    Pair()
    {
        first = second = 0;
    }
};

//���ڴ����������
typedef struct Pair<int> intPair;

//�����������飬����size���ڼ�¼����
struct intPairArr
{
    intPair *arr;
    int size;
    intPairArr()
    {
        size = 0;
        arr = nullptr;
    }
};

/* ��num������������a��a����N��Ԫ�أ�Ŀ���ΪB */
void solve(int *a, int N, int B, int num);
/* ������ĿҪ���ʽ�Խ��������� */
void display(int num, int N, int *a, int B, intPairArr ans);
/* ���������� */
void quickSort(dataType [], int left, int right);

int main()
{
    int *a;
    int B, n, count = 0;
    //����������ļ�ԭ��������
    FILE *f = fopen("./IntegerPair.txt", "w+");
    f = nullptr;

    while (true)
    {
        count++;
        cout << "������Ҫ���������������������-1���˳�����" << endl;
        cin >> n;
        if (n == -1) break;
        //�������������еĿռ�
        a = new int[n];
        cout << "������Ҫ�������֮��B��" << endl;
        cin >> B;
        cout << "������" << n << "�������������У��ո��������" << endl;
        for (int i = 0; i < n; i++)
            cin >> a[i];
        solve(a, n, B, count);
        delete a;
    }

    system("pause");
    return 0;
}

void solve(int *a, int N, int B, int num)
{
    //�ȶ�����a���п���
    quickSort(a, 0, N - 1);

    int left = 0, right = N - 1;
    int resNum=0;
    intPairArr res;//���ڴ���ҵ�����������
    res.arr = new intPair[N/2];//��������N/2��������

    while (left < right)
    {
        if (a[left]+a[right] == B)//�ҵ�һ��
        {
            res.arr[resNum].first = a[left];
            res.arr[resNum].second = a[right];
            resNum++;
            res.size++;
            //�ƽ�����
            left++;
            right--;
        }
        else if (a[left]+a[right] < B)//������
        {
            left++;
        }
        else//̫����
        {
            right--;
        }
    }

    //�ض���������ļ������
    freopen("./IntegerPair.txt", "a", stdout);
    display(num, N, a, B, res);
    //�ض��򵽿���̨�������һ�Σ��Ա�۲�
    freopen("CON", "w", stdout);
    display(num, N, a, B, res);
}

void display(int num, int N, int *a, int B, intPairArr ans)
{
    cout << "��" << num << "���������" << endl;
    cout << N << "����ͬ����������";
    for (int i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl << "������B��" << B << endl;
    cout << "���ҽ������" << ans.size << "�������ԣ�";
    //���������ԾͲ����
    if (ans.size != 0)
    {
        cout << ans.arr[0].first << " " << ans.arr[0].second;
        for (int i = 1; i < ans.size; i++)
        {
            cout << ", " << ans.arr[i].first << " " << ans.arr[i].second;
        }
    }
    cout << endl << endl;
}

//��������Ԫ�صĺ���
void swap(dataType *a, dataType *b)
{
    dataType t = *a;
    *a = *b;
    *b = t;
}

//��arr���е�[left,right]������п�������
void quickSort(dataType arr[], int left, int right)
{
    int mid = arr[(left + right) / 2];
    int l = left, r = right;
    while (l <= r)
    {
        //�ҵ���һ�����ڵ���mid��
        while (arr[l] < mid) l++;
        //�ҵ���һ��С�ڵ���mid��
        while (arr[r] > mid) r--;
        //������Ԫ�ؽ��������ֱ�����midС/�������
        if (l <= r)
        {
            swap(arr + l, arr + r);
            l++;
            r--;
        }
    }
    //�����ݹ����ÿ���ֶ�
    if (left < r) quickSort(arr, left, r);
    if (right > l) quickSort(arr, l, right);
}
