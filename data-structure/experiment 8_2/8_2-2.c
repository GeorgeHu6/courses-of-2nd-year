#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_VERTEX_NUM 20
#define TRUE 1
#define FALSE 0
#define colorA 1
#define colorB 2

typedef int Boolean;
//�ֱ�Ϊ����ͼ��������������ͼ��������
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;
//��ʾ�����ϵ������
typedef int VRType;
//��ʾ����Ϣ������
typedef char InfoType;

//ͼ/���еĶ�������
typedef int VertexType;

//�ڽӱ�����ͨԪ�ص�����
typedef struct ArcNode {
    int adjvex;//�߻��������Ķ����λ�ã����߻򻡵��յ�
    struct ArcNode *nextarc;//ָ����һ����������ı߻򻡵�ָ��
    InfoType *info;//�߻򻡵������Ϣָ��
} ArcNode;

//�ڽӱ���ͷ�������
typedef struct {
    VertexType data;//������Ϣ
    ArcNode *firstarc;//ָ���һ������������ı߻򻡵�ָ��
    int color, colorStatus;//colorΪ��ǰ������ɫ��colorStatusΪ��ǰ����ڽӵ����ɫ���
} VNode, AdjList[MAX_VERTEX_NUM];

//�ڽӱ��������
typedef struct {
    AdjList vertices;//ͼ��ͷ�������
    int vexnum, arcnum;//ͼ�Ķ������ͱ߻���
} ALGraph;

void initALGraph(ALGraph *graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->vertices[i].color = 0;
        graph->vertices[i].colorStatus = 0;
        graph->vertices[i].firstarc = NULL;
        graph->vertices[i].data = i;
    }
}

/* ��������ͼ */
Boolean constructUDG(ALGraph *graph);
/* ������ȸ�ͼ��ɫ */
Boolean bfsFilling(ALGraph *graph);
/* �����ɫ��� */
void printColor(ALGraph graph);

int main() {
    ALGraph graph;
    Boolean res;
    initALGraph(&graph);

    printf("��������ͼ\n");
    constructUDG(&graph);

    res = bfsFilling(&graph);
    if (res == FALSE) {
        printf("��ͼ�޷���ɫ");
    } else {
        printf("------------------------\n");
        printf("��ɫ�ɹ�����ɫ�������\n");
        printColor(graph);
    }

    printf("\n");

    system("pause");
    return 0;
}

void printColor(ALGraph graph) {
    for (int i = 0; i < graph.vexnum; i++) {
        if (graph.vertices[i].color == colorA)
            printf("%d��colorA\n", i);
        else if(graph.vertices[i].color == colorB)
            printf("%d��colorB\n", i);
        else
            printf("%d��δ��ɫ\n", i);
    }
}

Boolean constructUDG(ALGraph *graph) {
    int start, end;
    ArcNode *newNode;
    ArcNode *pt;
    printf("-----------------\n");
    printf("��ʼ��������ͼ\n");
    printf("�����붥���������ܳ���20����\n");
    scanf("%d", &graph->vexnum);
    printf("�����������\n");
    scanf("%d", &graph->arcnum);
    printf("����������ߵ������յ㣨����յ�֮���Կո��������\n");
    //���������
    for (int i = 0; i < graph->arcnum; i++) {
        scanf("%d %d", &start, &end);
        if (start >= graph->vexnum || start < 0 ||
            end >= graph->vexnum || end < 0) {
            printf("����������������������뵱ǰ����\n");
            i--;
            continue;
        }
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        //����ͼ��ͷ�巨���߲����ڽӱ�
        newNode->adjvex = end;
        newNode->info = (char *) malloc(sizeof(char)*15);
        sprintf(newNode->info, "%d->%d", start, end);
        newNode->nextarc = graph->vertices[start].firstarc;
        graph->vertices[start].firstarc = newNode;
        //��һ����
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        newNode->adjvex = start;
        newNode->info = (char *) malloc(sizeof(char)*15);
        sprintf(newNode->info, "%d->%d", end, start);
        newNode->nextarc = graph->vertices[end].firstarc;
        graph->vertices[end].firstarc = newNode;
    }
    printf("--------�ڽӱ�Ԥ��--------\n");
    for (int i = 0; i < graph->vexnum; i++) {
        printf("%d��", graph->vertices[i].data);
        pt = graph->vertices[i].firstarc;
        while (pt != NULL) {
            printf("%s  ", pt->info);
            pt = pt->nextarc;
        }
        printf("\n");
    }

    return TRUE;
}

Boolean bfsFilling(ALGraph *graph) {
    ArcNode *pt;
    QElemType cur;
    LinkQueue queue;
    Initqueue(&queue);

    //���±�Ϊ0�Ķ��㿪ʼ���������
    Enqueue(&queue, 0);
    while (!Emptyqueue(queue)) {
        //����һ��Ԫ��
        Dequeue(&queue, &cur);
        //δ��ɫ������������ɫ
        if (graph->vertices[cur].color == 0) {
            //cur���ڽӵ����Ѿ�����colorA��colorB��˵���޷���ɫ
            if (graph->vertices[cur].colorStatus == 3) {
                return FALSE;
            } else if ((graph->vertices[cur].colorStatus & colorA) == colorA) {//cur�ڽӵ����Ѿ�����colorA������colorB�����������ڽӵ�
                graph->vertices[cur].color = colorB;
                pt = graph->vertices[cur].firstarc;
                while (pt != NULL) {
                    graph->vertices[pt->adjvex].colorStatus |= colorB;
                    pt = pt->nextarc;
                }
            } else if ((graph->vertices[cur].color & colorB) == colorB) {//cur�ڽӵ����Ѿ�����colorB������colorA�����������ڽӵ�
                graph->vertices[cur].color = colorA;
                pt = graph->vertices[cur].firstarc;
                while (pt != NULL) {
                    graph->vertices[pt->adjvex].colorStatus |= colorA;
                    pt = pt->nextarc;
                }
            } else {//cur���ڽӵ��л�û����ɫ��������colorA
                graph->vertices[cur].color = colorA;
                pt = graph->vertices[cur].firstarc;
                while (pt != NULL) {
                    graph->vertices[pt->adjvex].colorStatus |= colorA;
                    pt = pt->nextarc;
                }
            }
            pt = graph->vertices[cur].firstarc;
            //����cur�������ڽӵ�
            while (pt != NULL) {
                //����ǰ�����δ��ɫ�ڽӵ����
                if (graph->vertices[pt->adjvex].color == 0) {
                    Enqueue(&queue, pt->adjvex);
                }
                pt = pt->nextarc;
            }
        }
        //�������ͨͼ
        if (Emptyqueue(queue)) {
            for (int i = 0; i < graph->vexnum; i++) {
                if (graph->vertices[i].color == 0) {
                    Enqueue(&queue, i);
                    break;
                }
            }
        }
    }
}
