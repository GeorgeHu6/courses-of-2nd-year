#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define TRUE 1
#define FALSE 0

typedef int Boolean;
//�ֱ�Ϊ����ͼ��������������ͼ��������
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;
//��ʾ�����ϵ������
typedef int VRType;
//��ʾ����Ϣ������
typedef char *InfoType;

//ͼ/���еĶ�������
typedef int VertexType;

//�ڽӾ�����Ԫ�ص�����
typedef struct ArcCell {
    VRType adj;//�����ϵ��Ϊ1/0��ʾ�Ƿ����ڻ��ʾȨֵ
    InfoType *info;//�߻򻡵������Ϣָ��
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
/* �ڽӾ�����Ԫ�ص�Setter */
void setArcCell(ArcCell *cell, VRType value, InfoType *infoPt) {
    cell->adj = value;
    cell->info = infoPt;
}
/* ��n*n���ڽӾ���matrix�еĳ�ʼ���������ϵΪvalue */
Boolean initAdjMat(AdjMatrix matrix, int n, int value) {
    if (n > MAX_VERTEX_NUM)
        return FALSE;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            setArcCell(&matrix[i][j], value, NULL);
    return TRUE;
}

//�ڽӾ��������
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;//�ڽӾ���
    int vexnum, arcnum;//����������/����
    GraphKind kind;
} Mgraph;

/* ��������ͼ */
Boolean constructDG(Mgraph *mgraph);
/* ���������� */
Boolean constructDN(Mgraph *mgraph);
/* ��������ͼ */
Boolean constructUDG(Mgraph *mgraph);
/* ���������� */
Boolean constructUDN(Mgraph *mgraph);
/* ������ȱ���ͼ */
void deepTraverseMap(Mgraph mgraph);
/* ������ȱ���ͼ */
void breadthTraverseMap(Mgraph mgraph);


int main() {
    Mgraph graph;
    int code;

    //����Ҫ�����ͼ������
    while (1) {
        printf("-------------\n");
        printf("0������ͼ\n1��������\n2������ͼ\n3��������\n-1���˳�\n��ѡ��Ҫ���������\n");
        scanf("%d", &code);
        if (code == -1) {
            system("pause");
            return 0;
        } else if (code < -1 || code > 3) {
            printf("�����������������\n");
        } else {
            graph.kind = code;
            break;
        }
    }
    //���ݲ�ͬͼ���͵�����Ӧ�Ĺ��캯��
    if (graph.kind == DG) {
        constructDG(&graph);
    } else if (graph.kind == DN) {
        constructDN(&graph);
    } else if (graph.kind == UDG) {
        constructUDG(&graph);
    } else if (graph.kind == UDN) {
        constructUDN(&graph);
    }

    deepTraverseMap(graph);//������ȱ���ͼgraph
    breadthTraverseMap(graph);//������ȱ���ͼgraph

    printf("\n");

    system("pause");
    return 0;
}

Boolean constructDG(Mgraph *mgraph) {
    int start, end;
    printf("-----------------\n");
    printf("��ʼ��������ͼ\n");
    printf("�����붥���������ܳ���20����\n");
    scanf("%d", &mgraph->vexnum);
    initAdjMat(mgraph->arcs, mgraph->vexnum, 0);
    printf("�����뻡����\n");
    scanf("%d", &mgraph->arcnum);
    printf("������������������յ㣨����յ�֮���Կո��������\n");
    //���������
    for (int i = 0; i < mgraph->arcnum; i++) {
        scanf("%d %d", &start, &end);
        if (start >= mgraph->vexnum || start < 0 ||
            end >= mgraph->vexnum || end < 0) {
            printf("����������������������뵱ǰ����\n");
            i--;
            continue;
        }
        setArcCell(&mgraph->arcs[start][end], 1, NULL);
    }
    printf("--------�ڽӾ���Ԥ��--------\n");
    for (int i = 0; i < mgraph->vexnum; i++) {
        for (int j = 0; j < mgraph->vexnum; j++)
            printf("%6d", mgraph->arcs[i][j].adj);
        printf("\n");
    }

    return TRUE;
}

Boolean constructDN(Mgraph *mgraph) {
    int start, end, weight;
    printf("-----------------\n");
    printf("��ʼ����������\n");
    printf("�����붥���������ܳ���20����\n");
    scanf("%d", &mgraph->vexnum);
    initAdjMat(mgraph->arcs, mgraph->vexnum, INFINITY);
    printf("�����뻡����\n");
    scanf("%d", &mgraph->arcnum);
    printf("���������������㡢�յ���Ȩֵ���Կո��������\n");
    //���������
    for (int i = 0; i < mgraph->arcnum; i++) {
        scanf("%d %d %d", &start, &end, &weight);
        if (start >= mgraph->vexnum || start < 0 ||
            end >= mgraph->vexnum || end < 0) {
            printf("����������������������뵱ǰ����\n");
            i--;
            continue;
        }
        setArcCell(&mgraph->arcs[start][end], weight, NULL);
    }
    printf("--------�ڽӾ���Ԥ��--------\n");
    for (int i = 0; i < mgraph->vexnum; i++) {
        for (int j = 0; j < mgraph->vexnum; j++) {
            if (mgraph->arcs[i][j].adj != INFINITY)
                printf("%6d", mgraph->arcs[i][j].adj);
            else
                printf("   INF");
        }

        printf("\n");
    }

    return TRUE;
}

Boolean constructUDG(Mgraph *mgraph) {
    int start, end;
    printf("-----------------\n");
    printf("��ʼ��������ͼ\n");
    printf("�����붥���������ܳ���20����\n");
    scanf("%d", &mgraph->vexnum);
    initAdjMat(mgraph->arcs, mgraph->vexnum, 0);
    printf("�����������\n");
    scanf("%d", &mgraph->arcnum);
    printf("����������ߵ������յ㣨����յ�֮���Կո��������\n");
    //���������
    for (int i = 0; i < mgraph->arcnum; i++) {
        scanf("%d %d", &start, &end);
        if (start >= mgraph->vexnum || start < 0 ||
            end >= mgraph->vexnum || end < 0) {
            printf("����������������������뵱ǰ����\n");
            i--;
            continue;
        }
        //����ͼ�������ԳƵ��ڽӾ���
        setArcCell(&mgraph->arcs[start][end], 1, NULL);
        setArcCell(&mgraph->arcs[end][start], 1, NULL);
    }
    printf("--------�ڽӾ���Ԥ��--------\n");
    for (int i = 0; i < mgraph->vexnum; i++) {
        for (int j = 0; j < mgraph->vexnum; j++)
            printf("%6d", mgraph->arcs[i][j].adj);
        printf("\n");
    }

    return TRUE;
}

Boolean constructUDN(Mgraph *mgraph) {
    int start, end, weight;
    printf("-----------------\n");
    printf("��ʼ����������\n");
    printf("�����붥���������ܳ���20����\n");
    scanf("%d", &mgraph->vexnum);
    initAdjMat(mgraph->arcs, mgraph->vexnum, INFINITY);
    printf("�����������\n");
    scanf("%d", &mgraph->arcnum);
    printf("����������ߵ���㡢�յ���Ȩֵ���Կո��������\n");
    //���������
    for (int i = 0; i < mgraph->arcnum; i++) {
        scanf("%d %d %d", &start, &end, &weight);
        if (start >= mgraph->vexnum || start < 0 ||
            end >= mgraph->vexnum || end < 0) {
            printf("����������������������뵱ǰ����\n");
            i--;
            continue;
        }
        //����ͼ�������ԳƵ��ڽӾ���
        setArcCell(&mgraph->arcs[start][end], weight, NULL);
        setArcCell(&mgraph->arcs[end][start], weight, NULL);
    }
    printf("--------�ڽӾ���Ԥ��--------\n");
    for (int i = 0; i < mgraph->vexnum; i++) {
        for (int j = 0; j < mgraph->vexnum; j++) {
            if (mgraph->arcs[i][j].adj != INFINITY)
                printf("%6d", mgraph->arcs[i][j].adj);
            else
                printf("   INF");
        }

        printf("\n");
    }

    return TRUE;
}

void dfs(Boolean visited[], Mgraph mgraph, int index) {
    //���ʵ�ǰ����
    visited[index] = TRUE;
    printf("%d ", index);
    //�����ڽӵ�
    for (int i = 0; i < mgraph.vexnum; i++) {
        //�ڽӵ�δ���������
        if (visited[i] == FALSE && (
                ((mgraph.kind == DG || mgraph.kind == UDG) && mgraph.arcs[index][i].adj != 0) ||
                ((mgraph.kind == DN || mgraph.kind == UDN) && mgraph.arcs[index][i].adj != INFINITY))) {
            dfs(visited, mgraph, i);
        }
    }
}

void deepTraverseMap(Mgraph mgraph) {
    Boolean visited[MAX_VERTEX_NUM]={0,};
    //ʹ����ͬʱ�����ڷ���ͨͼ
    printf("-------------\n������ȱ�����");
    for (int i = 0; i < mgraph.vexnum; i++) {
        if (visited[i] == FALSE)
            dfs(visited, mgraph, i);
    }
    printf("\n");
}

void breadthTraverseMap(Mgraph mgraph) {
    Boolean visited[MAX_VERTEX_NUM]={0,};
    QElemType cur;
    LinkQueue queue;
    Initqueue(&queue);
    printf("-------------\n������ȱ�����");

    //���±�Ϊ0�Ķ��㿪ʼ���������
    Enqueue(&queue, 0);
    while (!Emptyqueue(queue)) {
        Dequeue(&queue, &cur);
        //���ʹ��Ͳ��ٷ��ʣ�δ���ʹ��ͷ���
        if (!visited[cur]) {
            visited[cur] = TRUE;
            printf("%d ", cur);
            for (int i = 0; i < mgraph.vexnum; i++) {
                //����ǰ�����δ�����ڽӵ����
                if (visited[i] == FALSE && (
                        ((mgraph.kind == DG || mgraph.kind == UDG) && mgraph.arcs[cur][i].adj != 0) ||
                        ((mgraph.kind == DN || mgraph.kind == UDN) && mgraph.arcs[cur][i].adj != INFINITY))) {
                    Enqueue(&queue, i);
                }
            }
        }
        //�������ͨͼ
        if (Emptyqueue(queue)) {
            for (int i = 0; i < mgraph.vexnum; i++) {
                if (!visited[i]) {
                    Enqueue(&queue, i);
                    break;
                }
            }
        }
    }
    printf("\n");

}
