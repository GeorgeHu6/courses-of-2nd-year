#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_VERTEX_NUM 20
#define TRUE 1
#define FALSE 0

typedef int Boolean;
//�ֱ�Ϊ����ͼ��������������ͼ��������
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;
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
} VNode, AdjList[MAX_VERTEX_NUM];

//�ڽӱ��������
typedef struct {
    AdjList vertices;//ͼ��ͷ�������
    int vexnum, arcnum;//ͼ�Ķ������ͱ߻���
    int kind;//ͼ������
} ALGraph;

void initALGraph(ALGraph *graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->vertices[i].firstarc = NULL;
        graph->vertices[i].data = i;
    }
}

/* ��������ͼ */
Boolean constructDG(ALGraph *graph);
/* ���������� */
Boolean constructDN(ALGraph *graph);
/* ��������ͼ */
Boolean constructUDG(ALGraph *graph);
/* ���������� */
Boolean constructUDN(ALGraph *graph);
/* ������ȱ���ͼ */
void deepTraverseMap(ALGraph graph);
/* ������ȱ���ͼ */
void breadthTraverseMap(ALGraph graph);


int main() {
    ALGraph graph;
    initALGraph(&graph);
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

Boolean constructDG(ALGraph *graph) {
    int start, end;
    ArcNode *newNode;
    ArcNode *pt;
    printf("-----------------\n");
    printf("��ʼ��������ͼ\n");
    printf("�����붥���������ܳ���20����\n");
    scanf("%d", &graph->vexnum);
    printf("�����뻡����\n");
    scanf("%d", &graph->arcnum);
    printf("������������������յ㣨����յ�֮���Կո��������\n");
    //���������
    for (int i = 0; i < graph->arcnum; i++) {
        scanf("%d %d", &start, &end);
        if (start >= graph->vexnum || start < 0 ||
            end >= graph->vexnum || end < 0) {
            printf("����������������������뵱ǰ����\n");
            i--;
            continue;
        }
        //ʹ��ͷ�巨���߲��뵽�ڽӱ���
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        newNode->adjvex = end;
        newNode->info = (char *) malloc(sizeof(char)*15);
        sprintf(newNode->info, "%d->%d", start, end);
        newNode->nextarc = graph->vertices[start].firstarc;
        graph->vertices[start].firstarc = newNode;
    }
    printf("--------�ڽӱ�Ԥ��--------\n");
    for (int i = 0; i < graph->vexnum; i++) {
        printf("%d��", graph->vertices[i].data);
        pt = graph->vertices[i].firstarc;
        while (pt != NULL) {
            printf("%s ", pt->info);
            pt = pt->nextarc;
        }
        printf("\n");
    }

    return TRUE;
}


Boolean constructDN(ALGraph *graph) {
    int start, end, weight;
    ArcNode *newNode;
    ArcNode *pt;
    printf("-----------------\n");
    printf("��ʼ����������\n");
    printf("�����붥���������ܳ���20����\n");
    scanf("%d", &graph->vexnum);
    printf("�����뻡����\n");
    scanf("%d", &graph->arcnum);
    printf("���������������㡢�յ���Ȩֵ���Կո��������\n");
    //���������
    for (int i = 0; i < graph->arcnum; i++) {
        scanf("%d %d %d", &start, &end, &weight);
        if (start >= graph->vexnum || start < 0 ||
            end >= graph->vexnum || end < 0) {
            printf("����������������������뵱ǰ����\n");
            i--;
            continue;
        }
        //ʹ��ͷ�巨���߲��뵽�ڽӱ���
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        newNode->adjvex = end;
        newNode->info = (char *) malloc(sizeof(char)*50);
        sprintf(newNode->info, "%d--%d-->%d", start, weight, end);
        newNode->nextarc = graph->vertices[start].firstarc;
        graph->vertices[start].firstarc = newNode;
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
        //����ͼ��ʹ��ͷ�巨���߲��뵽�ڽӱ���
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

Boolean constructUDN(ALGraph *graph) {
    int start, end, weight;
    ArcNode *newNode;
    ArcNode *pt;
    printf("-----------------\n");
    printf("��ʼ����������\n");
    printf("�����붥���������ܳ���20����\n");
    scanf("%d", &graph->vexnum);
    printf("�����������\n");
    scanf("%d", &graph->arcnum);
    printf("����������ߵ���㡢�յ���Ȩֵ���Կո��������\n");
    //���������
    for (int i = 0; i < graph->arcnum; i++) {
        scanf("%d %d %d", &start, &end, &weight);
        if (start >= graph->vexnum || start < 0 ||
            end >= graph->vexnum || end < 0) {
            printf("����������������������뵱ǰ����\n");
            i--;
            continue;
        }
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        //����ͼ��ʹ��ͷ�巨���߲��뵽�ڽӱ���
        newNode->adjvex = end;
        newNode->info = (char *) malloc(sizeof(char)*50);
        sprintf(newNode->info, "%d--%d-->%d", start, weight, end);
        newNode->nextarc = graph->vertices[start].firstarc;
        graph->vertices[start].firstarc = newNode;
        //��һ����
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        newNode->adjvex = start;
        newNode->info = (char *) malloc(sizeof(char)*50);
        sprintf(newNode->info, "%d--%d-->%d", end, weight, start);
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

void dfs(Boolean visited[], ALGraph graph, int index) {
    ArcNode *pt=graph.vertices[index].firstarc;
    //���ʵ�ǰ����
    visited[index] = TRUE;
    printf("%d ", index);
    //ѭ��index���������ڽӵ�
    while (pt != NULL) {
        //��index�ĵ�һ��δ���ʵ��ڽӵ�
        while (pt != NULL && visited[pt->adjvex] == TRUE)
            pt = pt->nextarc;
        //�ҵ������
        if (pt != NULL)
            dfs(visited, graph, pt->adjvex);
    }
}

void deepTraverseMap(ALGraph graph) {
    Boolean visited[MAX_VERTEX_NUM]={0,};
    //ʹ����ͬʱ�����ڷ���ͨͼ
    printf("-------------\n������ȱ�����");
    for (int i = 0; i < graph.vexnum; i++) {
        if (visited[i] == FALSE)
            dfs(visited, graph, i);
    }
    printf("\n");
}

void breadthTraverseMap(ALGraph graph) {
    Boolean visited[MAX_VERTEX_NUM]={0,};
    ArcNode *pt;
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
            pt = graph.vertices[cur].firstarc;
            //����cur�������ڽӵ�
            while (pt != NULL) {
                //����ǰ�����δ�����ڽӵ����
                if (visited[pt->adjvex] == FALSE) {
                    Enqueue(&queue, pt->adjvex);
                }
                pt = pt->nextarc;
            }
        }
        //�������ͨͼ
        if (Emptyqueue(queue)) {
            for (int i = 0; i < graph.vexnum; i++) {
                if (!visited[i]) {
                    Enqueue(&queue, i);
                    break;
                }
            }
        }
    }
    printf("\n");

}
