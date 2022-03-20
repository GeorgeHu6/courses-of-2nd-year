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

//用于存放正整数对
typedef struct Pair<int> intPair;

//正整数对数组，加入size便于记录个数
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

/* 第num组正整数序列a，a中有N个元素，目标和为B */
void solve(int *a, int N, int B, int num);
/* 按照题目要求格式对结果进行输出 */
void display(int num, int N, int *a, int B, intPairArr ans);
/* 快速排序函数 */
void quickSort(dataType [], int left, int right);

int main()
{
    int *a;
    int B, n, count = 0;
    //创建或清空文件原来的内容
    FILE *f = fopen("./IntegerPair.txt", "w+");
    f = nullptr;

    while (true)
    {
        count++;
        cout << "请输入要处理的正整数个数（输入-1以退出）：" << endl;
        cin >> n;
        if (n == -1) break;
        //申请正整数序列的空间
        a = new int[n];
        cout << "请输入要求的两数之和B：" << endl;
        cin >> B;
        cout << "请输入" << n << "个正整数的序列（空格隔开）：" << endl;
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
    //先对数组a进行快排
    quickSort(a, 0, N - 1);

    int left = 0, right = N - 1;
    int resNum=0;
    intPairArr res;//用于存放找到的正整数对
    res.arr = new intPair[N/2];//最多可能有N/2个整数对

    while (left < right)
    {
        if (a[left]+a[right] == B)//找到一对
        {
            res.arr[resNum].first = a[left];
            res.arr[resNum].second = a[right];
            resNum++;
            res.size++;
            //推进查找
            left++;
            right--;
        }
        else if (a[left]+a[right] < B)//不够大
        {
            left++;
        }
        else//太大了
        {
            right--;
        }
    }

    //重定向输出到文件并输出
    freopen("./IntegerPair.txt", "a", stdout);
    display(num, N, a, B, res);
    //重定向到控制台，再输出一次，以便观察
    freopen("CON", "w", stdout);
    display(num, N, a, B, res);
}

void display(int num, int N, int *a, int B, intPairArr ans)
{
    cout << "第" << num << "组测试数据" << endl;
    cout << N << "个不同的正整数：";
    for (int i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl << "正整数B：" << B << endl;
    cout << "查找结果：有" << ans.size << "对整数对：";
    //无正整数对就不输出
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

//交换数组元素的函数
void swap(dataType *a, dataType *b)
{
    dataType t = *a;
    *a = *b;
    *b = t;
}

//对arr序列的[left,right]区间进行快速排序
void quickSort(dataType arr[], int left, int right)
{
    int mid = arr[(left + right) / 2];
    int l = left, r = right;
    while (l <= r)
    {
        //找到第一个大于等于mid的
        while (arr[l] < mid) l++;
        //找到第一个小于等于mid的
        while (arr[r] > mid) r--;
        //将两个元素交换，即分别放入比mid小/大的两边
        if (l <= r)
        {
            swap(arr + l, arr + r);
            l++;
            r--;
        }
    }
    //继续递归快排每个分段
    if (left < r) quickSort(arr, left, r);
    if (right > l) quickSort(arr, l, right);
}
