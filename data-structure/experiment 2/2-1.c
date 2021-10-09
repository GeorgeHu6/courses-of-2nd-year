#include <stdio.h>
#include <stdlib.h>

//使用结构体来存储每个学生的学号及成绩信息
typedef struct {
    long long id;
    double chinese, math, english;
    double total, average;
} Stu;

int main() {
    Stu *students;
    int count=0;
    long long num;
    double chi, math, eng;
    int n;

    //申请动态数组的空间
    students = (Stu *) malloc(sizeof(Stu));


    //先读取将要输入的学生人数
    printf("How many students?\n");
    scanf("%d", &n);

    //读入每个学生的相关信息
    while (n--) {
        scanf("%lld %lf %lf %lf", &num, &chi, &math, &eng);
        (students+count)->id = num;
        (students+count)->chinese = chi;
        (students+count)->math = math;
        (students+count)->english = eng;
        (students+count)->total = chi + math + eng;
        (students+count)->average = 0.3*chi + 0.5*math + 0.2*eng;
        count++;
        //每次读入之后都重新多申请一个Stu结构体的空间，准备下次读入
        students = (Stu *) realloc(students, (count+1)*sizeof(Stu));
    }

    //规范格式更美观地输出
    printf("-----id-----|--Chinese--|--Math--|--English--|--Total--|--Avg--|\n");
    for (int i = 0; i < count; i++) {
        printf("%12lld|%11.2f|%8.2f|%11.2f|%9.2f|%7.2f|\n", students[i].id, students[i].chinese, students[i].math, students[i].english, students[i].total, students[i].average);
    }

    //释放动态数组占用的空间
    free(students);

    return 0;
}


