#include <stdio.h>
#include <stdlib.h>

//使用结构体来存储每个学生的学号及成绩信息
typedef struct {
    long long id;
    double chinese, math, english;
    double total, average;
} Stu;

void displayStudents(Stu *, int); 
int readinStudents(Stu **, int, int); 
void sortByTotal(Stu *, int, int);

int main() {
    Stu *students;
    int count=0;
    int n;
    
    //申请动态数组的空间
    students = (Stu *) malloc(sizeof(Stu));

    //先读取将要输入的学生人数
    printf("How many students?\n");
    scanf("%d", &n);

    //使用封装好的函数读取数据
    count = readinStudents(&students, count, n);
    displayStudents(students, count);

    //进行排序并输出
    printf("After sorting:\n");
    sortByTotal(students, 0, count-1);
    displayStudents(students, count);

    //释放动态数组占用的空间
    free(students);
    
    return 0;
}

//规范格式更美观地输出
//给入需要输出的Stu数组首地址指针，和动态数组的元素个数count
void displayStudents(Stu *students, int count) {
    printf("-----id-----|--Chinese--|--Math--|--English--|--Total--|--Avg--|\n");
    for (int i = 0; i < count; i++) {
        printf("%12lld|%11.2f|%8.2f|%11.2f|%9.2f|%7.2f|\n", students[i].id, students[i].chinese, students[i].math, students[i].english, students[i].total, students[i].average);
    }
}

//封装读入学生数据
//由于需要修改指向Stu数组首地址的指针，所以需要传入指向Stu数组首地址指针的指针
//还要传入动态数组的元素个数origin_num及将要读入的学生的人数
int readinStudents(Stu **students, int origin_num, int n) {
    printf("Input students\' information(id, Chinese score, Math score, English score)\n");
    int count = origin_num;
    double chi, math, eng;
    long long num;

    while (n--) {
        scanf("%lld %lf %lf %lf", &num, &chi, &math, &eng);
        (*students)[count].id = num;
        (*students+count)->chinese = chi;
        (*students+count)->math = math;
        (*students+count)->english = eng;
        (*students+count)->total = chi + math + eng;
        (*students+count)->average = 0.3*chi + 0.5*math + 0.2*eng;
        count++;
        *students = (Stu *) realloc(*students, (count+1)*sizeof(Stu));
    }

    return count;
}

//使用优化的快速排序对Stu数组进行排序
//由于需要修改指向Stu数组首地址的指针，所以需要传入指向Stu数组首地址指针的指针
//left, right为当前进行处理的数组区间，且为闭区间
void sortByTotal(Stu *students, int left, int right) {
    int i=left, j=right;
    double mid;
    Stu tmp;
    mid = students[(left+right)/2].total;
    while (i <= j) {
        while (students[i].total < mid) i++;
        while (students[j].total > mid) j--;
        if (i <= j) {
            tmp = students[i];
            students[i] = students[j];
            students[j] = tmp;
            i++;
            j--;
        }
    }
    if (j > left) sortByTotal(students, left, j);
    if (i < right) sortByTotal(students, i, right);
}
