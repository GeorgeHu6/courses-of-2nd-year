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
int cmp(const void *, const void *);
int deleteStudents(Stu **, int); 

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

    //再读入一个学生的数据
    printf("Add one student at the end of the array\n");
    count = readinStudents(&students, count, 1);
    displayStudents(students, count);

    //使用封装好的函数删除指定id学生
    printf("Delete one student by id\n");
    count = deleteStudents(&students, count);
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
//此处为了使用realloc不断调整动态数组的空间大小，也就是需要修改指向Stu数组首地址的指针
//所以需要传入指向Stu数组首地址指针的指针
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

//封装从动态数组中删除学生的功能
//与readinStudents函数相同，由于需要修改指向Stu数组首地址的指针
//需要传入指向Stu数组首地址指针的指针
//还需要传入动态数组中的元素个数origin_num
int deleteStudents(Stu **students, int origin_num) {
    long long id;
    int left, right, mid;
    int new_num=origin_num;
    qsort(*students, origin_num, sizeof(Stu), cmp);
    scanf("%lld", &id);
    left = 0;
    right = origin_num - 1;
    while (left <= right) {
        mid = (left + right)/2;
        if ((*students)[mid].id == id)
            break;
        else if ((*students)[mid].id > id)
            right = mid - 1;
        else if ((*students)[mid].id < id)
            left = mid + 1;
    }
    if (left > right)
        printf("id Not Found!\n");
    else {
        for (int i = mid; i < new_num-1; i++)
            students[i] = students[i+1];
        new_num--;
        *students = (Stu *) realloc(*students, (new_num+1)*sizeof(Stu));
    }
    printf("input id:\n");

    return new_num;
}

//用于qsort的比较函数
int cmp(const void *a, const void *b) {
    const Stu *first=(const Stu *) a;
    const Stu *second=(const Stu *) b;

    return first->id - second->id;
}


