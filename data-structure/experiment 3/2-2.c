#include <stdio.h>
#include <stdlib.h>

//使用结构体来存储每个学生的学号及成绩信息
struct Stu {
    long long id;
    double chinese, math, english;
    double total, average;
    struct Stu *next;
};
typedef struct Stu *StuList;
typedef struct Stu Stu;

void insert(StuList, Stu *);

void createList(StuList);

void apply2All(StuList, void (*)(Stu));

void display(Stu stu);

void readinStudents(StuList, int);

void deleteStudents(StuList, long long);

int main() {
    StuList studentsList;
    int n;
    long long id_num;

    //创建一个用于存储Stu的链表并初始化
    studentsList = (StuList) malloc(sizeof(Stu));
    createList(studentsList);

    //先读取将要输入的学生人数
    printf("How many students?\n");
    scanf("%d", &n);

    //使用封装好的函数读取数据
    readinStudents(studentsList, n);

    //输出表头
    printf("-----id-----|--Chinese--|--Math--|--English--|--Total--|--Avg--|\n");
    apply2All(studentsList, display);

    //再读入一个学生的数据
    printf("Add one student at the end of the array\n");
    readinStudents(studentsList, 1);
    //输出表头
    printf("-----id-----|--Chinese--|--Math--|--English--|--Total--|--Avg--|\n");
    apply2All(studentsList, display);

    //使用封装好的函数删除指定id学生
    printf("Delete one student by id\n");
    printf("input id:\n");
    scanf("%lld", &id_num);
    deleteStudents(studentsList, id_num);
    //输出表头
    printf("-----id-----|--Chinese--|--Math--|--English--|--Total--|--Avg--|\n");
    apply2All(studentsList, display);

    return 0;
}

void readinStudents(StuList head, int n) {
    long long num;
    double chi, math, eng;
    Stu *tmp;
    StuList res;

    while (n--) {
        //创建新结点
        tmp = (Stu *) malloc(sizeof(Stu));
        scanf("%lld %lf %lf %lf", &num, &chi, &math, &eng);
        tmp->id = num;
        tmp->chinese = chi;
        tmp->math = math;
        tmp->english = eng;
        tmp->total = chi + math + eng;
        tmp->average = 0.3 * chi + 0.5 * math + 0.2 * eng;
        //每次读入之后就往链表中插入
        insert(head, tmp);
    }

}

//封装从动态数组中删除学生的功能
void deleteStudents(StuList head, long long id) {
    Stu *cur = head;
    Stu *target;
    while (cur->next != NULL) {
        if (cur->next->id == id) {
            target = cur->next;
            cur->next = target->next;
            printf("Deleted\n");
            free(target);
            return;
        }
        cur = cur->next;
    }
    printf("id Not Found!\n");
}

//头插法把结点插入链表
void insert(StuList head, Stu *new_student) {
    StuList new_head;
    new_head = (StuList) malloc(sizeof(Stu));
    new_student->next = head->next;
    head->next = new_student;
}

//初始化链表
void createList(StuList head) {
    head->next = NULL;
    head->id = -1;
    head->chinese = head->math = head->english = -1;
    head->total = head->average = -1;
}

//对Stu链表中的每个元素应用func函数
void apply2All(StuList head, void (*func)(Stu item)) {
    Stu *cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
        (*func)(*cur);
    }
}

//规范格式化输出
void display(Stu stu) {
    printf("%12lld|%11.2f|%8.2f|%11.2f|%9.2f|%7.2f|\n", stu.id, stu.chinese, stu.math, stu.english, stu.total,
           stu.average);
}
