#include <stdio.h>
#include <stdlib.h>
#define Status int
#define OK 1
#define ERROR 0

typedef struct Lnode {
    int data;
    struct Lnode *next;
} Lnode, *Link;

Status createLoopLink (Link, int);
Status displayLink (Link);
Status solve (Link, int);

int main() {
    Link linklist;
    int n, k;

    linklist = (Link) malloc(sizeof(Lnode));
    linklist->data = -1;
    linklist->next = NULL;

    printf("input n: ");
    scanf("%d", &n);
    printf("input k: ");
    scanf("%d", &k);

    createLoopLink(linklist, n);
    //displayLink(linklist);

    solve(linklist, k);

    printf("\n");
    system("pause");
    return 0;
}

Status solve(Link head, int k) {
    int count=0;
    Link cur=head, pre=head;
    Lnode *tmp;
    //找到“尾结点”作为头结点的前一个结点
    while (pre->next != head)
        pre = pre->next;

    while (cur != cur->next) {
        count++;
        count %= k;
        //删除第k个结点
        if (count == 0) {
            printf("%d\n", cur->data);
            pre->next = cur->next;
            tmp = cur;
            cur = cur->next;
            free(tmp);
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
    printf("%d", cur->data);
    free(cur);

    return OK;
}

Status createLoopLink (Link head, int n) {
    Lnode *tmp;
    Lnode *rear;
    head->data = 1;
    rear = head;
    for (int i = 2; i <= n; i++) {
       tmp = (Lnode *) malloc(sizeof(Lnode));
       if (tmp == NULL)
           return ERROR;
       tmp->data = i;
       tmp->next = NULL;
       rear->next = tmp;
       rear = tmp;
    }
    rear->next = head;

    return OK;
}

Status displayLink (Link head) {
    if (head == NULL)
        return ERROR;
    Link p=head;
    printf("%d", p->data);
    p = p->next;

    while(p) {
        printf("->%d", p->data);
        p = p->next;
    }
    return OK;
}
