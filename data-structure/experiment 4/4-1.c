#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Status int
#define OK 1
#define ERROR 0

typedef struct Lnode {
    int data;
    struct Lnode *next;
} Lnode, *Link;

Status OrderInsert(Link, Lnode *, int (*)(Lnode, Lnode));
Status OrderInput(Link head, int (*)(Lnode, Lnode));
Status OrderMerge(Link, Link, Link, int (*)(Lnode, Lnode));
Status OrderSort(Link head, int (*)(Lnode, Lnode));

Lnode *createNode(int);
Lnode *deepCpy(const Lnode *);
int byAscending(Lnode, Lnode);
void displayLink(Link);

int main() {
    Link linkList1, linkList2;
    Link mergeList;
    Lnode *tmp;

    linkList1 = createNode(-1);
    linkList2 = createNode(-1);
    mergeList = createNode(-1);
    printf("Create linkList1\n");
    OrderInput(linkList1, byAscending);
    printf("Create linkList2\n");
    OrderInput(linkList2, byAscending);

    printf("linkList1: ");
    displayLink(linkList1);
    printf("linkList2: ");
    displayLink(linkList2);

    OrderMerge(linkList1, linkList2, mergeList, byAscending);
    printf("merged linklist1&2: ");
    displayLink(mergeList);

    printf("\n");
    system("pause");

    return 0;
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

Status OrderInput(Link head, int (*compare)(Lnode, Lnode)) {
    int n, tmp_data;
    Lnode *tmp;
    printf("Input the number of nodes to add:\n");
    scanf("%d", &n);
    printf("Input integer data to save in each node\n");
    printf("(each number ends with 'Enter' key or input in one line separating with space):\n");
    while (n--) {
        scanf("%d", &tmp_data);
        if ((tmp = createNode(tmp_data)) == ERROR)
            return ERROR;
        OrderInsert(head, tmp, compare);
    }
    return OK;
}

//若compare的返回值不为0，认为a应该在b的前面
Status OrderSort(Link head, int (*compare)(Lnode a, Lnode b)) {
    //需要调整的链表是空的，直接返回ERROR
    if (head->next == NULL)
        return ERROR;
    //p始终指向链表中还未调整位置的第一个结点
    Lnode *p = head->next->next, *tmp;
    head->next->next = NULL;

    while (p) {
        tmp = p->next;
        OrderInsert(head, p, compare);
        p = tmp;
    }

    return OK;
}
//若compare的返回值不为0，认为a应该在b的前面
//La与Lb必须是与将要产生的Lc一样，按照同一种compare方法构造的有序表
Status OrderMerge(Link La, Link Lb, Link Lc, int (*compare)(Lnode a, Lnode b)) {
    //Lc作为La和Lb合并后的链表的头结点，一开始需要是空的
    //La、Lb也都不能是空的，不然没有合并的意义
    if (Lc->next != NULL || La->next == NULL || Lb->next == NULL)
        return ERROR;

    //使用尾插法构造Lc
    Lnode *pa = La->next, *pb = Lb->next, *rear = Lc;
    Lnode *tmp;
    while (pa != NULL && pb != NULL) {
        //pa应该放前面
        if (compare(*pa, *pb)) {
            //深拷贝结点加入Lc中，防止La、Lb中的结点受到影响被改变
            tmp = deepCpy(pa);
            rear->next = tmp;
            rear = tmp;
            pa = pa->next;
            rear->next = NULL;
        } else {
            tmp = deepCpy(pb);
            rear->next = tmp;
            rear = tmp;
            pb = pb->next;
            rear->next = NULL;
        }
    }

    //剩余元素放入
    while (pa != NULL) {
        tmp = deepCpy(pa);
        rear->next = tmp;
        rear = tmp;
        pa = pa->next;
        rear->next = NULL;
    }
    while (pb != NULL) {
        tmp = deepCpy(pb);
        rear->next = tmp;
        rear = tmp;
        pb = pb->next;
        rear->next = NULL;
    }

    return OK;
}

int byAscending(Lnode a, Lnode b) {
    return a.data < b.data;
}

Lnode *createNode(int data) {
    Link p;
    p = (Link) malloc(sizeof(Lnode));
    p->data = data;
    p->next = NULL;
    return p;
}

void displayLink(Link head) {
    if (head->next == NULL)
        return;
    Link p = head->next;
    printf("%d", p->data);
    p = p->next;
    while (p) {
        printf("->%d", p->data);
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
