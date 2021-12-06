#include <stdio.h>
#include <stdlib.h>

#define TElemType int
#define MAX_NODE 200

//二叉树结点
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode;

/* 堆的操作 */
/* 堆的向下调整 */
void downAdjust(BiTNode* [], int, int);
/* 堆的向上调整 */
void upAdjust(BiTNode* [], int, int);
/* 弹出堆顶的最小结点（的指针） */
BiTNode* deleteTop(int *n, BiTNode* heap[]);
/* 指向结点的指针数组，创建树的结点并创建最小堆 */
void createHeap(int, BiTNode* []);
/* 在最小堆中插入一个新结点（的指针） */
void insertElem(BiTNode* newNode, BiTNode* heap[], int *n);

/* 交换辅助函数，用于在堆中交换两个树结点（的指针） */
void swap(BiTNode* *, BiTNode* *);
/* 输出数据域的辅助函数 */
void displayData(BiTNode *node);

/* 分别为先序、中序遍历，以此唯一确定一棵二叉树 */
void DLRTree(BiTNode *treeNode, void(*TreeNodeData)(BiTNode *p));
void LDRTree(BiTNode *treeNode, void(*TreeNodeData)(BiTNode *p));


/* 由于纯C中没有STL，手打小顶堆以实现优先队列来完成哈夫曼树构建 */
/* 堆是完全二叉树，就使用顺序存储结构（从下标1开始）来存储堆 */

int main() {
    int n = 0;
    //使用指针作为最小堆中的元素，即使用指针数组来表示
    BiTNode* trees[MAX_NODE+1];
    BiTNode *tmp, *min1, *min2;

    printf("请输入数据（总结点）个数\n");
    scanf("%d", &n);
    printf("请输入%d个数据（空格或回车分隔）\n", n);
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

    printf("哈夫曼树构造完成！\n前序遍历为：\n");
    DLRTree(trees[1], displayData);
    printf("\n中序遍历为：\n");
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

/* 在[start, end]之间向下调整，一般start为开始调整的结点 */
void downAdjust(BiTNode* heap[], int start, int end) {
    int target = start, min_child = start * 2;
    while (min_child <= end) {
        //选出target左右结点中较小的
        //首先要存在右结点，才能与左结点比较
        if (min_child + 1 <= end) {
            //右结点更小
            if (heap[min_child]->data > heap[min_child+1]->data)
                min_child = min_child + 1;
        }

        //有子结点更小，交换
        if (heap[min_child]->data < heap[target]->data) {
            swap(&heap[min_child], &heap[target]);
            //还有继续向下调整的可能
            target = min_child;
            min_child = target * 2;
        } else {
            //已经没得调整了，说明heap[start]已经调整到合适位置
            break;
        }
    }
}

/* 在[start, end]之间向上调整，一般end为开始调整的结点 */
void upAdjust(BiTNode* heap[], int start, int end) {
    int target = end, father = end/2;
    while (father >= start) {
        //父结点比待调整结点大，需要交换
        if (heap[father]->data > heap[target]->data) {
            swap(&heap[father], &heap[target]);
            //还有继续向上调整的可能
            target = father;
            father = target / 2;
        } else {
            //已经没得调整了，说明heap[end]已经调整到合适位置
            break;
        }
    }
}

/* 根据结点指针数组heap构建小顶堆 */
void createHeap(int n, BiTNode* heap[]) {
    //根据完全二叉树与堆的性质，从n/2倒着往前操作
    for (int i = n / 2; i >= 1; i--) {
        downAdjust(heap, i, n);
    }
}

/* 弹出堆顶（即指向最小的结点的指针） */
BiTNode* deleteTop(int *n, BiTNode* heap[]) {
    BiTNode* res;
    res = heap[1];
    //堆中最后一个元素放到第一个
    heap[1] = heap[*n];
    (*n)--;
    downAdjust(heap, 1, *n);

    return res;
}

/* 在长度为n的结点指针数组heap中插入新结点的指针newNode */
void insertElem(BiTNode* newNode, BiTNode* heap[], int *n) {
    (*n)++;
    heap[*n] = newNode;
    upAdjust(heap, 1, *n);
}

/* 根据指向结点的指针输出其数据域 */
void displayData(BiTNode *node) {
    printf("%d ", node->data);
}

/* 递归前序遍历 */
void DLRTree(BiTNode *treeNode, void TreeNodeData(BiTNode *)) {
    //访问当前根结点
    TreeNodeData(treeNode);
    //左子树不为空，则遍历左子树
    if (treeNode->lchild != NULL)
        DLRTree(treeNode->lchild, TreeNodeData);
    //右子树不为空，则遍历右子树
    if (treeNode->rchild != NULL)
        DLRTree(treeNode->rchild, TreeNodeData);
}

/* 递归中序遍历 */
void LDRTree(BiTNode *treeNode, void TreeNodeData(BiTNode *)) {
    //左子树不为空，则遍历左子树
    if (treeNode->lchild != NULL)
        LDRTree(treeNode->lchild, TreeNodeData);
    //访问当前根结点
    TreeNodeData(treeNode);
    //右子树不为空，则遍历右子树
    if (treeNode->rchild != NULL)
        LDRTree(treeNode->rchild, TreeNodeData);
}
