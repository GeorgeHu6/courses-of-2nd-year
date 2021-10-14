#include <stdio.h>
#include <stdlib.h>

//使用结构体来存储每个学生的学号及成绩信息
struct Stu{
    long long id;
    double chinese, math, english;
    double total, average;
    struct Stu *next;
};
typedef struct Stu *StuList;
typedef struct Stu Stu;

StuList insert(StuList, Stu *);
void createList(StuList);
void apply2All(StuList, void (*)(Stu));
void display(Stu stu);

int main() {
    StuList studentsList;
    long long num;
    double chi, math, eng;
    int n;
    Stu *tmp;

    //创建一个用于存储Stu的链表
    createList(studentsList);


    //先读取将要输入的学生人数
    printf("How many students?\n");
    scanf("%d", &n);

    //读入每个学生的相关信息
    while (n--) {
        //创建新结点
        tmp = (Stu *) malloc(sizeof(Stu));
        scanf("%lld %lf %lf %lf", &num, &chi, &math, &eng);
        tmp->id = num;
        tmp->chinese = chi;
        tmp->math = math;
        tmp->english = eng;
        tmp->total = chi + math + eng;
        tmp->average = 0.3*chi + 0.5*math + 0.2*eng;
        //每次读入之后就往链表中插入
        studentsList = insert(studentsList, tmp);
    }

    //输出表头
    printf("-----id-----|--Chinese--|--Math--|--English--|--Total--|--Avg--|\n");
    apply2All(studentsList, display);

    return 0;
}

//头插法把结点插入链表
StuList insert(StuList head, Stu *new_student) {
    StuList new_head;
    new_student->next = head->next;
    new_head->next = new_student;
    return new_head;
}

//初始化链表
void createList(StuList head) {
    head->next = NULL;
    head->id = -1;
    head->chinese = head->math = head->english = -1;
    head->total = head->average = -1;
}

void apply2All(StuList head, void (*func)(Stu item)) {
    Stu *cur=head;
    while (cur->next != NULL) {
        cur = cur->next;
        (*func)(*cur);
    }
}

void display(Stu stu) {
    printf("%12lld|%11.2f|%8.2f|%11.2f|%9.2f|%7.2f|\n", stu.id, stu.chinese, stu.math, stu.english, stu.total, stu.average);
}
