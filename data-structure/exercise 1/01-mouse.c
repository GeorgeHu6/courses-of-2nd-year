#include <stdio.h>
#include <stdlib.h>
#define EAST  MAZE[x][y+1]  /*���嶫�������λ��*/
#define WEST  MAZE[x][y-1]  /*�������������λ��*/
#define SOUTH MAZE[x+1][y]	/*�����Ϸ������λ��*/
#define NORTH MAZE[x-1][y]	/*���山�������λ��*/
#define ExitX 8			/*������ڵ�X�����ڵ�8��*/
#define ExitY 10			/*������ڵ�Y�����ڵ�10��*/
struct list
{
	int x,y;
	struct list* next;
};
typedef struct list node;
typedef node* link;
//�Զ�ά�����ʾ�Թ���ͼ��1��ʾǽ��2��ʾ��ڻ���·�������ݻ�����·������3��ʾ����
int MAZE[10][12] = {2,1,1,1,1,0,0,0,1,1,1,1,	/*�����Թ�����*/
		            1,0,0,0,1,1,1,1,1,1,1,1,
				    1,1,1,0,1,1,0,0,0,0,1,1,
					1,1,1,0,1,1,0,1,1,0,1,1,
					1,1,1,0,0,0,0,1,1,0,1,1,
					1,1,1,0,1,1,0,1,1,0,1,1,
					1,1,1,0,1,1,0,1,1,0,1,1,
					1,1,1,0,1,1,0,0,1,0,1,1,
					1,1,0,0,0,0,0,0,1,0,0,1,
					1,1,1,1,1,1,1,1,1,1,1,3};
link push(link stack,int x,int y)
{
	link newnode;
	newnode = (link)malloc(sizeof(node));
	if(!newnode)
	{
		printf("Error!�ڴ����ʧ��!\n");
		return NULL;
	}
	newnode->x=x;
	newnode->y=y;
	newnode->next=stack;
	stack=newnode;
    return stack;
}
//����stackջ�е�Ԫ�أ����ҽ���ջ֮��ջ��Ԫ�ص�������ֵ��x��y
link pop(link stack,int* x,int* y)
{
	link top;
	if(stack!=NULL)
	{
		top=stack;
		stack=stack->next;
		*x=top->x;
		*y=top->y;
		free(top);
		return stack;
	}
	else
		*x=-1;
	return stack;
}
//�ж���ex��eyΪ�յ㣬��ǰλ��Ϊx��yʱ�Ƿ����߳��Թ�
int chkExit(int x,int y,int ex,int ey)
{
	if(x==ex&&y==ey)
	{
		if(NORTH==1||SOUTH==1||WEST==1||EAST==2)
			return 1;
		if(NORTH==1||SOUTH==1||WEST==2||EAST==1)
			return 1;
		if(NORTH==1||SOUTH==2||WEST==1||EAST==1)
			return 1;
		if(NORTH==2||SOUTH==1||WEST==1||EAST==1)
			return 1;
    }
	return 0;
}

int main()
{
	int i,j,x,y;
	link path = NULL;
	x=1;		/*��ڵ�X����*/
	y=1;    /*��ڵ�Y����*/
	printf("[�Թ��ĵ�ģ��ͼ(1��ʾǽ,2��ʾ���,3��ʾ����]\n"); /*��ӡ���Թ���·��ͼ*/
	for(i=0;i<10;i++)
	{
		for(j=0;j<12;j++)
			printf("%2d",MAZE[i][j]);
		printf("\n");
	}
	while(x<=ExitX&&y<=ExitY)
	{
		//����ǰ�ߵ���λ�ñ��Ϊ6�����Ұ�˳��ֱ����������ϡ��������ĸ�������
		MAZE[x][y]=6;
		if(NORTH==0)
		{
			x -= 1;
			path=push(path,x,y);
		}
		else if(SOUTH==0)
		{
			x+=1;
			path=push(path,x,y);
		}
		else if(WEST==0)
		{
			y-=1;
			path=push(path,x,y);
		}
		else if(EAST==0)
		{
			y+=1;
			path=push(path,x,y);
		}
		else if(chkExit(x,y,ExitX,ExitY)==1) /*����Ƿ��ߵ�������*/
			break;
		else
		{
			MAZE[x][y]=2;
			path=pop(path,&x,&y);
		}
	}
	printf("---------------------------\n");
	printf("[6��ʾ�����߹���·��]\n"); /*��ӡ�����������Թ����·��ͼ*/
	printf("---------------------------\n");
	for(i=0;i<10;i++)
	{
		for(j=0;j<12;j++)
			printf("%2d",MAZE[i][j]);
		printf("\n");
	}
	system("pause");
	return 0;
}