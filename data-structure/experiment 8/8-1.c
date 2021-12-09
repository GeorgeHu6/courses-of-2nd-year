#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Status int
#define TElemType char
#define OK 1
#define ERROR 0
#define MAX_NODE 100

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

Status constructByPreAndIn(BiTree, const TElemType *, int, const TElemType *, int, int);

void preTraverse(BiTNode root);
void inTraverse(BiTNode root);
void postTraverse(BiTNode root);

int countLeaf(BiTNode root);
int countDepth(BiTree root);


int main() {
    TElemType pre[MAX_NODE];
    TElemType in[MAX_NODE];
    BiTNode root;
    root.lchild = root.rchild = NULL;

    memset(pre, '\0', sizeof(pre));
    memset(in, '\0', sizeof(in));
    printf("输入前序序列：\n");
    gets(pre);
    printf("输入中序序列：\n");
    gets(in);

    if (strlen(pre) != strlen(in)) {
        printf("错误！两个序列的结点个数不同");
        system("pause");
        return 0;
    }


    if (constructByPreAndIn(&root, pre, 0, in, 0, (int) strlen(pre)-1) == ERROR) {
        printf("错误！这两个序列无法构造出二叉树");
        system("pause");
        return 0;
    }

    printf("先序遍历：");
    preTraverse(root);
    printf("\n");

    printf("中序遍历：");
    inTraverse(root);
    printf("\n");

    printf("后序遍历：");
    postTraverse(root);
    printf("\n");

    printf("叶子数目为：%d\n", countLeaf(root));
    printf("深度为：%d\n", countDepth(&root));

    system("pause");

    return 0;
}

//中序区间为[in_start, in_end]
Status constructByPreAndIn(BiTree root, const TElemType *preOrder, int cur, const TElemType *inOrder, int in_start,
                           int in_end) {
    //当前前序序列的开始第一个即为当前根结点元素
    root->data = preOrder[cur];

    BiTNode *tmp;

    int i;
    //在中序序列中找当前根结点
    for (i = in_start; i <= in_end; i++) {
        if (inOrder[i] == preOrder[cur])
            break;
    }
    //找不到结点，说明序列有错误
    if (i == in_end+1)
        return ERROR;
    //构建左子树（前提是左子树有结点）
    if (i - in_start > 0) {
        tmp = (BiTNode *) malloc(sizeof(BiTNode));
        tmp->lchild = tmp->rchild = NULL;
        root->lchild = tmp;
        if (constructByPreAndIn(root->lchild, preOrder, cur + 1, inOrder, in_start, i - 1) == ERROR)
            return ERROR;
    }
    //构建右子树（前提是右子树有结点）
    if (in_end - i > 0) {
        tmp = (BiTNode *) malloc(sizeof(BiTNode));
        tmp->lchild = tmp->rchild = NULL;
        root->rchild = tmp;
        if (constructByPreAndIn(root->rchild, preOrder, cur + i - in_start + 1, inOrder, i + 1, in_end) == ERROR)
            return ERROR;
    }
    return OK;
}

void preTraverse(BiTNode root) {
    printf("%c ", root.data);
    if (root.lchild != NULL)
        preTraverse(*root.lchild);
    if (root.rchild != NULL)
        preTraverse(*root.rchild);
}

void inTraverse(BiTNode root) {
    if (root.lchild != NULL)
        inTraverse(*root.lchild);
    printf("%c ", root.data);
    if (root.rchild != NULL)
        inTraverse(*root.rchild);
}

void postTraverse(BiTNode root) {
    if (root.lchild != NULL)
        postTraverse(*root.lchild);
    if (root.rchild != NULL)
        postTraverse(*root.rchild);
    printf("%c ", root.data);
}

int countLeaf(BiTNode root) {
    int res = 0;
    if (root.lchild == NULL && root.rchild == NULL)
        res++;
    if (root.lchild != NULL)
        res += countLeaf(*root.lchild);
    if (root.rchild != NULL)
        res += countLeaf(*root.rchild);

    return res;
}

int countDepth(BiTree root) {
    int leftDepth = 0, rightDepth = 0;
    if (root == NULL)
        return 0;
    else {
        leftDepth = countDepth(root->lchild);
        rightDepth = countDepth(root->rchild);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }
}
