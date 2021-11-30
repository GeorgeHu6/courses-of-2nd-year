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

    cout << "���к������ԣ���Щ�����������������Ѿ��е��ã����ٵ�������" << endl;
    cout << "�������������root" << endl;
    CreateBiTree(root);
    cout << "������������ֵΪ" << Root(root) << endl;

    cout << "��ѯĳ��λ�õĽ��" << endl;
    cout << "�������ţ������Ϊ��1�㣩" << endl;
    cin >> pos.level;
    cout << "������ò��ĳ��λ�ã��ò�����ߵĽ��Ϊ��1����" << endl;
    cin >> pos.order;
    cout << "��" << pos.level << "��" << "�ĵ�" << pos.order << "������ֵΪ" << Value(root, pos) << endl;

    cout << "�޸�ĳ��λ�õĽ��" << endl;
    cout << "�������ţ������Ϊ��1�㣩" << endl;
    cin >> pos.level;
    cout << "������ò��ĳ��λ�ã��ò�����ߵĽ��Ϊ��1����" << endl;
    cin >> pos.order;
    cout << "�޸�Ϊ���ַ��ͣ�" << endl;
    cin >> ch;
    if (Assign(root, pos, ch) == ERROR)
        cout << "�޸�ʧ��" << endl;
    else
        cout << "�޸ĳɹ�" << endl;

    cout << "��ֵ��ѯ���" << endl;
    cout << "��ѯ����㣬������Ҫ��ѯ��ֵ���ַ��ͣ�" << endl;
    cin >> ch;
    cout << ch << "�ĸ�����ֵΪ" << Parent(root, ch) << endl;
    cout << "��ѯ���ӽ�㣬������Ҫ��ѯ��ֵ���ַ��ͣ�" << endl;
    cin >> ch;
    cout << ch << "�����ӽ���ֵΪ" << LeftChild(root, ch) << endl;
    cout << "��ѯ���ӽ�㣬������Ҫ��ѯ��ֵ���ַ��ͣ�" << endl;
    cin >> ch;
    cout << ch << "�����ӽ���ֵΪ" << RightChild(root, ch) << endl;
    cout << "��ѯ���ֵܽ�㣬������Ҫ��ѯ��ֵ���ַ��ͣ�" << endl;
    cin >> ch;
    cout << ch << "�����ֵܽ���ֵΪ" << LeftSibling(root, ch) << endl;
    cout << "��ѯ���ֵܽ�㣬������Ҫ��ѯ��ֵ���ַ��ͣ�" << endl;
    cin >> ch;
    cout << ch << "�����ֵܽ���ֵΪ" << RightSibling(root, ch) << endl;

    cout << "����һ��ֻ���ҽ�����root2" << endl;
    CreateBiTree(root2);
    cout << "��root2����root��һ�������" << endl;
    cout << "������Ŀ����" << endl;
    cin >> ch;
    cout << "����" << ch << "����0��/�ң�1����㣬������0��1" << endl;
    cin >> LR;
    InsertChild(root, ch, LR, root2);
    cout << "�������" << endl;

    cout << "ɾ��root��ĳһ������/������" << endl;
    cout << "������Ŀ���ţ������Ϊ��1�㣩" << endl;
    cin >> pos.level;
    cout << "������Ŀ����ĳ��λ�ã��ò�����ߵĽ��Ϊ��1����" << endl;
    cin >> pos.order;
    cout << "ɾ��" << Value(root, pos) << "������0��/�ң�1��������������0��1" << endl;
    cin >> LR;
    DeleteChild(root, pos, LR);

    cout << "����������root" << endl;
    cout << "ǰ�������";
    PreOrderTraverse(root);
    cout << endl << "���������";
    InOrderTraverse(root);
    cout << endl << "���������";
    PostOrderTraverse(root);
    cout << "����Print���������" << endl;
    Print(root);
    cout << "����LevelOrderTraverse���������";
    LevelOrderTraverse(root);


    cout << "���Զ�������DestroyQueue����" << endl;
    EnQueue(queue, 10);
    if (DestroyQueue(queue))
        cout << "����ͨ��" << endl;
    else
        cout << "����ʧ��" << endl;
    system("pause");
    return 0;
}