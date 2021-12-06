#include <stdio.h>
#include <stdlib.h>

#define TElemType int
#define MAX_NODE 200

//���������
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode;

/* �ѵĲ��� */
/* �ѵ����µ��� */
void downAdjust(BiTNode* [], int, int);
/* �ѵ����ϵ��� */
void upAdjust(BiTNode* [], int, int);
/* �����Ѷ�����С��㣨��ָ�룩 */
BiTNode* deleteTop(int *n, BiTNode* heap[]);
/* ָ�����ָ�����飬�������Ľ�㲢������С�� */
void createHeap(int, BiTNode* []);
/* ����С���в���һ���½�㣨��ָ�룩 */
void insertElem(BiTNode* newNode, BiTNode* heap[], int *n);

/* �������������������ڶ��н�����������㣨��ָ�룩 */
void swap(BiTNode* *, BiTNode* *);
/* ���������ĸ������� */
void displayData(BiTNode *node);

/* �ֱ�Ϊ��������������Դ�Ψһȷ��һ�ö����� */
void DLRTree(BiTNode *treeNode, void(*TreeNodeData)(BiTNode *p));
void LDRTree(BiTNode *treeNode, void(*TreeNodeData)(BiTNode *p));


/* ���ڴ�C��û��STL���ִ�С������ʵ�����ȶ�������ɹ����������� */
/* ������ȫ����������ʹ��˳��洢�ṹ�����±�1��ʼ�����洢�� */

int main() {
    int n = 0;
    //ʹ��ָ����Ϊ��С���е�Ԫ�أ���ʹ��ָ����������ʾ
    BiTNode* trees[MAX_NODE+1];
    BiTNode *tmp, *min1, *min2;

    printf("���������ݣ��ܽ�㣩����\n");
    scanf("%d", &n);
    printf("������%d�����ݣ��ո��س��ָ���\n", n);
    for (int i = 1; i <= n; i++) {
        tmp = malloc(sizeof(BiTNode));
        scanf("%d", &tmp->data);
        tmp->lchild = tmp->rchild = NULL;
        trees[i] = tmp;
    }

    createHeap(n, trees);
    while (n > 1) {
        min1 = deleteTop(&n, trees);
        min2 = deleteTop(&n, trees);
        tmp = (BiTNode *) malloc(sizeof(BiTNode));
        tmp->data = min1->data+min2->data;
        tmp->lchild = min1;
        tmp->rchild = min2;
        insertElem(tmp, trees, &n);
    }

    printf("��������������ɣ�\nǰ�����Ϊ��\n");
    DLRTree(trees[1], displayData);
    printf("\n�������Ϊ��\n");
    LDRTree(trees[1], displayData);
    printf("\n");

    system("pause");
    return 0;
}

void swap(BiTNode* *a, BiTNode* *b) {
    BiTNode* tmp = *a;
    *a = *b;
    *b = tmp;
}

/* ��[start, end]֮�����µ�����һ��startΪ��ʼ�����Ľ�� */
void downAdjust(BiTNode* heap[], int start, int end) {
    int target = start, min_child = start * 2;
    while (min_child <= end) {
        //ѡ��target���ҽ���н�С��
        //����Ҫ�����ҽ�㣬����������Ƚ�
        if (min_child + 1 <= end) {
            //�ҽ���С
            if (heap[min_child]->data > heap[min_child+1]->data)
                min_child = min_child + 1;
        }

        //���ӽ���С������
        if (heap[min_child]->data < heap[target]->data) {
            swap(&heap[min_child], &heap[target]);
            //���м������µ����Ŀ���
            target = min_child;
            min_child = target * 2;
        } else {
            //�Ѿ�û�õ����ˣ�˵��heap[start]�Ѿ�����������λ��
            break;
        }
    }
}

/* ��[start, end]֮�����ϵ�����һ��endΪ��ʼ�����Ľ�� */
void upAdjust(BiTNode* heap[], int start, int end) {
    int target = end, father = end/2;
    while (father >= start) {
        //�����ȴ�����������Ҫ����
        if (heap[father]->data > heap[target]->data) {
            swap(&heap[father], &heap[target]);
            //���м������ϵ����Ŀ���
            target = father;
            father = target / 2;
        } else {
            //�Ѿ�û�õ����ˣ�˵��heap[end]�Ѿ�����������λ��
            break;
        }
    }
}

/* ���ݽ��ָ������heap����С���� */
void createHeap(int n, BiTNode* heap[]) {
    //������ȫ��������ѵ����ʣ���n/2������ǰ����
    for (int i = n / 2; i >= 1; i--) {
        downAdjust(heap, i, n);
    }
}

/* �����Ѷ�����ָ����С�Ľ���ָ�룩 */
BiTNode* deleteTop(int *n, BiTNode* heap[]) {
    BiTNode* res;
    res = heap[1];
    //�������һ��Ԫ�طŵ���һ��
    heap[1] = heap[*n];
    (*n)--;
    downAdjust(heap, 1, *n);

    return res;
}

/* �ڳ���Ϊn�Ľ��ָ������heap�в����½���ָ��newNode */
void insertElem(BiTNode* newNode, BiTNode* heap[], int *n) {
    (*n)++;
    heap[*n] = newNode;
    upAdjust(heap, 1, *n);
}

/* ����ָ�����ָ������������� */
void displayData(BiTNode *node) {
    printf("%d ", node->data);
}

/* �ݹ�ǰ����� */
void DLRTree(BiTNode *treeNode, void TreeNodeData(BiTNode *)) {
    //���ʵ�ǰ�����
    TreeNodeData(treeNode);
    //��������Ϊ�գ������������
    if (treeNode->lchild != NULL)
        DLRTree(treeNode->lchild, TreeNodeData);
    //��������Ϊ�գ������������
    if (treeNode->rchild != NULL)
        DLRTree(treeNode->rchild, TreeNodeData);
}

/* �ݹ�������� */
void LDRTree(BiTNode *treeNode, void TreeNodeData(BiTNode *)) {
    //��������Ϊ�գ������������
    if (treeNode->lchild != NULL)
        LDRTree(treeNode->lchild, TreeNodeData);
    //���ʵ�ǰ�����
    TreeNodeData(treeNode);
    //��������Ϊ�գ������������
    if (treeNode->rchild != NULL)
        LDRTree(treeNode->rchild, TreeNodeData);
}
