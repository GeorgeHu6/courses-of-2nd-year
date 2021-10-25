#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define Status int
#define OK 1
#define ERROR 0

typedef struct Lnode {
    //存储系数
    int coefficient;
    //存储次数
    int frequency;
    struct Lnode *next;
} Lnode, *Link;

Status OrderInsert(Link, Lnode *, int (*)(Lnode, Lnode));
Status createPoly(Link head, int num, ...);
Status addPloy(Link, Link, Link, int (*)(Lnode, Lnode));

Lnode *createNode(int, int);
Lnode *deepCpy(const Lnode *);
int byAscending(Lnode, Lnode);
void displayPoly(Link);

int main() {
    Link poly1, poly2, poly3;

    poly1 = createNode(-1, -1);
    poly2 = createNode(-1, -1);
    poly3 = createNode(-1, -1);
    createPoly(poly1, 2, 1, 2, 5, 6);
    createPoly(poly2, 3, 1, 2, 1, 1, 1, 3);
    printf(" ");
    displayPoly(poly1);
    printf("+");
    displayPoly(poly2);
    printf("=");

    addPloy(poly1, poly2, poly3, byAscending);
    displayPoly(poly3);

    printf("\n");
    system("pause");
    return 0;
}

//创建多项式，使用以head为头结点的链表存储
//num为要创建的多项式的项数
//后面的参数依次为对应的系数、次数的交替
Status createPoly(Link head, int num, ...) {
    Lnode *tmp;
    int tmpCoe, tmpFre;
    //定义可变长度数组，用来接收多项式的系数和次数
    va_list coeAndFre;
    //初始化参数列表
    va_start(coeAndFre, num);

    while (num--) {
        tmpCoe = va_arg(coeAndFre, int);
        tmpFre = va_arg(coeAndFre, int);
        tmp = createNode(tmpCoe, tmpFre);
        OrderInsert(head, tmp, byAscending);
    }

    va_end(coeAndFre);

    return OK;
}

//将polyA与polyB两个多项式相加的结果存在polyC中
//polyA、polyB不能为空，polyC必须为空
//若compare的返回值不为0，认为a应该在b的前面
Status addPloy(Link polyA, Link polyB, Link polyC, int (*compare)(Lnode a, Lnode b)) {
    if (polyA->next == NULL || polyB->next == NULL || polyC->next != NULL)
        return ERROR;
    Link pA = polyA->next, pB = polyB->next;
    //使用尾插法构造Lc
    Link rear = polyC;
    Lnode *tmp;

    while (pA != NULL && pB != NULL) {
        //pA必处于较前位置，说明polyB中没有对应项，直接加入polyC中
        if (compare(*pA, *pB)) {
            //深拷贝结点
            tmp = deepCpy(pA);
            rear->next = tmp;
            rear = tmp;
            pA = pA->next;
            rear->next = NULL;
        }
        //pA与pB次数相等，相加后加入polyC
        else if (pA->frequency == pB->frequency) {
            tmp = createNode(pA->coefficient + pB->coefficient, pA->frequency);
            rear->next = tmp;
            rear = tmp;
            pA = pA->next;
            pB = pB->next;
            rear->next = NULL;
        }
        //pB必处于较前位置，说明polyA中没有对应项，直接加入polyC中
        else {
            tmp = deepCpy(pB);
            rear->next = tmp;
            rear = tmp;
            pB = pB->next;
            rear->next = NULL;
        }
    }

    //剩余元素放入
    while (pA != NULL) {
        tmp = deepCpy(pA);
        rear->next = tmp;
        rear = tmp;
        pA = pA->next;
        rear->next = NULL;
    }
    while (pB != NULL) {
        tmp = deepCpy(pB);
        rear->next = tmp;
        rear = tmp;
        pB = pB->next;
        rear->next = NULL;
    }

    return OK;
}


//若compare的返回值不为0，认为a应该在b的前面
Status OrderInsert(Link head, Lnode *new_node, int (*compare)(Lnode a, Lnode b)) {
    Link cur = head;

    if (head->next == NULL) {
        new_node->next = NULL;
        head->next = new_node;
        return OK;
    }

    while (cur->next != NULL) {
        if (!compare(*(cur->next), *new_node)) {
            new_node->next = cur->next;
            cur->next = new_node;
            break;
        }
        cur = cur->next;
    }
    if (cur->next == NULL) {
        cur->next = new_node;
        new_node->next = NULL;
    }

    return OK;
}

//若compare的返回值不为0，认为a应该在b的前面
//若compare的返回值不为0，认为a应该在b的前面
//La与Lb必须是与将要产生的Lc一样，按照同一种compare方法构造的有序表

int byAscending(Lnode a, Lnode b) {
    return a.frequency < b.frequency;
}

Lnode *createNode(int coe, int fre) {
    Link p;
    p = (Link) malloc(sizeof(Lnode));
    p->coefficient = coe;
    p->frequency = fre;
    p->next = NULL;
    return p;
}

void displayPoly(Link head) {
    //空链表，无需输出，直接返回
    if (head->next == NULL)
        return;
    int tmpCoe, tmpFre;
    Link p = head->next;
    tmpCoe = p->coefficient;
    tmpFre = p->frequency;

    //首项特殊处理输出，正号无需输出
    //0次方不用输出x，1次方不用输出次方号
    if (tmpFre == 0) {
        printf("%d", tmpCoe);
    } else if (tmpFre == 1 && tmpCoe == 1) {
        printf("x");
    } else if (tmpFre == 1 && tmpCoe == -1) {
        printf("-x");
    } else if (tmpCoe == 1) {
        printf("x^%d", tmpFre);
    } else if (tmpCoe == -1) {
        printf("-x^%d", tmpFre);
    } else {
        printf("%dx^%d", tmpCoe, tmpFre);
    }

    p = p->next;
    while (p) {
        tmpCoe = p->coefficient;
        tmpFre = p->frequency;
        if (tmpFre == 1 && tmpCoe == 1) {
            printf("x");
        } else if (tmpFre == 1 && tmpCoe == -1) {
            printf("-x");
        } else if (tmpCoe == 1) {
            printf("+x^%d", tmpFre);
        } else if (tmpCoe > 0) {
            printf("+%dx^%d", tmpCoe, tmpFre);
        } else if (tmpCoe == -1) {
            printf("-x^%d", tmpFre);
        } else {
            printf("%dx^%d", tmpCoe, tmpFre);
        }
        p = p->next;
    }
    printf("\n");
}

//返回对src结点的一份深拷贝
Lnode *deepCpy(const Lnode *src) {
    Lnode *res;
    res = (Lnode *) malloc(sizeof(Lnode));
    res = (Lnode *) memcpy(res, src, sizeof(Lnode));

    return res;
}
