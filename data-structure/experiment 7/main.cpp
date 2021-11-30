#include "bitree.h"
#include <iostream>

using namespace std;

int main() {
    SqBiTree root, root2;
    position pos;
    char ch;
    int LR;
    InitBiTree(root);
    InitBiTree(root2);
    LinkQueue queue;
    InitQueue(queue);

    cout << "进行函数测试，有些函数在其他函数中已经有调用，不再单独测试" << endl;
    cout << "按层序构造二叉树root" << endl;
    CreateBiTree(root);
    cout << "二叉树根结点的值为" << Root(root) << endl;

    cout << "查询某个位置的结点" << endl;
    cout << "请输入层号（根结点为第1层）" << endl;
    cin >> pos.level;
    cout << "请输入该层的某个位置（该层最左边的结点为第1个）" << endl;
    cin >> pos.order;
    cout << "第" << pos.level << "层" << "的第" << pos.order << "个结点的值为" << Value(root, pos) << endl;

    cout << "修改某个位置的结点" << endl;
    cout << "请输入层号（根结点为第1层）" << endl;
    cin >> pos.level;
    cout << "请输入该层的某个位置（该层最左边的结点为第1个）" << endl;
    cin >> pos.order;
    cout << "修改为（字符型）" << endl;
    cin >> ch;
    if (Assign(root, pos, ch) == ERROR)
        cout << "修改失败" << endl;
    else
        cout << "修改成功" << endl;

    cout << "按值查询结点" << endl;
    cout << "查询父结点，请输入要查询的值（字符型）" << endl;
    cin >> ch;
    cout << ch << "的父结点的值为" << Parent(root, ch) << endl;
    cout << "查询左子结点，请输入要查询的值（字符型）" << endl;
    cin >> ch;
    cout << ch << "的左子结点的值为" << LeftChild(root, ch) << endl;
    cout << "查询右子结点，请输入要查询的值（字符型）" << endl;
    cin >> ch;
    cout << ch << "的右子结点的值为" << RightChild(root, ch) << endl;
    cout << "查询左兄弟结点，请输入要查询的值（字符型）" << endl;
    cin >> ch;
    cout << ch << "的左兄弟结点的值为" << LeftSibling(root, ch) << endl;
    cout << "查询右兄弟结点，请输入要查询的值（字符型）" << endl;
    cin >> ch;
    cout << ch << "的右兄弟结点的值为" << RightSibling(root, ch) << endl;

    cout << "构造一棵只有右结点的树root2" << endl;
    CreateBiTree(root2);
    cout << "将root2移至root的一个结点上" << endl;
    cout << "请输入目标结点" << endl;
    cin >> ch;
    cout << "移至" << ch << "的左（0）/右（1）结点，请输入0或1" << endl;
    cin >> LR;
    InsertChild(root, ch, LR, root2);
    cout << "操作完成" << endl;

    cout << "删除root中某一结点的左/右子树" << endl;
    cout << "请输入目标层号（根结点为第1层）" << endl;
    cin >> pos.level;
    cout << "请输入目标层的某个位置（该层最左边的结点为第1个）" << endl;
    cin >> pos.order;
    cout << "删除" << Value(root, pos) << "结点的左（0）/右（1）子树，请输入0或1" << endl;
    cin >> LR;
    DeleteChild(root, pos, LR);

    cout << "遍历二叉树root" << endl;
    cout << "前序遍历：";
    PreOrderTraverse(root);
    cout << endl << "中序遍历：";
    InOrderTraverse(root);
    cout << endl << "后序遍历：";
    PostOrderTraverse(root);
    cout << "调用Print层序遍历：" << endl;
    Print(root);
    cout << "调用LevelOrderTraverse层序遍历：";
    LevelOrderTraverse(root);


    cout << "测试队列销毁DestroyQueue函数" << endl;
    EnQueue(queue, 10);
    if (DestroyQueue(queue))
        cout << "测试通过" << endl;
    else
        cout << "测试失败" << endl;
    system("pause");
    return 0;
}