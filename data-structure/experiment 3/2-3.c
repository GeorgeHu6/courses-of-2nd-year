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

void sortByTotal(StuList);

Stu *getCopy(Stu *);

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

    //进行排序并输出
    printf("\nAfter sorting:\n");
    sortByTotal(studentsList);
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

//使用选择排序思想进行排序
void sortByTotal(StuList head) {
    Stu *k, *i = head, *j;
    Stu *small, *origin;
    //i及之前的认为已经排好
    while (i->next->next != NULL) {
        k = i;
        j = k->next;
        while (j->next != NULL) {
            if (j->next->total < k->next->total)
                k = j;
            j = j->next;
        }
        //找到比k->next总分更小的，就交换k->next和i->next
        //相邻交换比较特殊，单独处理
        if (k != i) {
            if (i->next == k) {
                i->next = k->next;
                k->next = k->next->next;
                i->next->next = k;
            } else {
                small = getCopy(k->next);
                origin = getCopy(i->next);
                small->next = origin->next;
                origin->next = k->next->next;
                free(i->next);
                i->next = small;
                free(k->next);
                k->next = origin;
            }

        }
        i = i->next;
    }
}

Stu *getCopy(Stu *source) {
    Stu *res;

    res = (Stu *) malloc(sizeof(Stu));
    res->id = source->id;
    res->chinese = source->chinese;
    res->math = source->math;
    res->english = source->english;
    res->total = source->total;
    res->average = source->average;
    res->next = source->next;

    return res;
}
