#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define INF 32767 

//�߽�� 
typedef struct ANode
{
	int adjvex;
	struct ANode *nextarc;
	int weight;
}ArcNode;

//ͷ��� 
typedef struct Vnode
{
	char info;
	ArcNode *firstarc;
}VNode;

//������ͼ�ڽӱ����� 
typedef struct
{
	VNode adjlist[50];
	int n,e;
}AdjGraph;


typedef struct 
{
	int data[50];
	int front,rear;
}SqQueue;

typedef struct
{
	int data;
	int parent;
}QUERE;

//���г�ʼ�� 
void InitQueue(SqQueue *&q)
{
	q=(SqQueue *)malloc(sizeof(SqQueue));
	q->front=q->rear=-1;
}

//���ٶ��� 
void DestroyQueue(SqQueue *&q)
{
	free(q);
}

//�ж϶����Ƿ�Ϊ�� 
bool QueueEmpty(SqQueue *q)
{
	return q->front==q->rear;
}

//������ 
bool enQueue(SqQueue *&q,int e)
{
	if(q->rear==50-1)
		return false;
	q->rear++;
	q->data[q->rear]=e;
	return true;
}

//������ 
bool deQueue(SqQueue *&q,int &e)
{
	if(q->front==q->rear)
		return false;
	q->front++;
	e=q->data[q->front];
	return true;
}

//ͨ��ͼ���ڽӾ��󴴽��ڽӱ� 
void CreateAdj(AdjGraph *&G,int A[50][50],int n,int e)
{
	ArcNode *p;
	G=(AdjGraph *)malloc(sizeof(AdjGraph));
	for(int i=0;i<n;i++)
		G->adjlist[i].firstarc=NULL;
	for(int i=0;i<n;i++)
		for(int j=n-1;j>=0;j--)
			if(A[i][j]!=0&&A[i][j]!=INF)
			{
				p=(ArcNode *)malloc(sizeof(ArcNode));
				p->adjvex=j;
				p->weight=A[i][j];
				p->nextarc=G->adjlist[i].firstarc;
				G->adjlist[i].firstarc=p;
			}
	G->n=n;
	G->e=e;
}

//����ڽӱ�G
void DispAdj(AdjGraph *G)
{
	ArcNode *p;
	for(int i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstarc;
		printf("%4d",i);
		while(p!=NULL)
		{
			printf("%4d[%d]  ->",p->adjvex,p->weight);
			p=p->nextarc;
		}
		printf("   #\n");
	}
} 

//�����ڽӱ�G
void DestroyAdj(AdjGraph *&G)
{
	ArcNode *pre,*p;
	for(int i=0;i<G->n;i++)
	{
		pre=G->adjlist[i].firstarc;
		if(pre!=NULL)
		{
			p=pre->nextarc;
			while(p!=NULL)
			{
				free(pre);
				pre=p;
				p=p->nextarc;
			}
			free(pre);
		}		
	}
	free(G);	
} 

//ͼ������ȱ��� 
void BFS(AdjGraph *G,int v)
{
	int w;
	ArcNode *p;
	SqQueue *qu;
	InitQueue(qu);
	int visited[50];
	for(int i=0;i<G->n;i++)
		visited[i]=0;
	visited[v]=1;
	printf("%4d",v);
	enQueue(qu,v);
	while(!QueueEmpty(qu))
	{
		deQueue(qu,w);
		p=G->adjlist[w].firstarc;
		while(p!=NULL)
		{
			if(visited[p->adjvex]==0)
			{
				printf("%4d",p->adjvex);
				visited[p->adjvex]=1;
				enQueue(qu,p->adjvex);
			}
			p=p->nextarc;
		}
	} 
	printf("\n");	
} 

//��ͼG�дӶ���u������v��һ�����·��
void ShortPath(AdjGraph *G,int u,int v)
{
	ArcNode *p;
	int w,i;
	QUERE qu[50];
	int front=-1,rear=-1;
	int visited[50];
	for(int i=0;i<G->n;i++)
		visited[i]=0;
		
	rear++;
	qu[rear].data=u;
	qu[rear].parent=-1;
	visited[u]=1;
	
	while(front!=rear)
	{
		front++;
		w=qu[front].data;
		
		if(w==v)
		{
			i=front;
			w=qu[front].data;
	
			while(qu[i].parent!=-1)
			{
				printf("%4d",qu[i].data);
				i=qu[i].parent;
			}
			printf("%4d\n",qu[i].data);
			break;	
		}
		
		p=G->adjlist[w].firstarc;
		while(p!=NULL)
		{
			if(visited[p->adjvex]==0)
			{
				visited[p->adjvex]=1;
				
				rear++;
				qu[rear].data=p->adjvex;
				qu[rear].parent=front;
			}
			p=p->nextarc;
		} 
	}
} 

//��ͼG�о��붥��v��Զ��һ������
int Maxdist(AdjGraph *G,int v)
{
	ArcNode *p;
	int w;
	QUERE qu[50];
	int front=-1,rear=-1;
	int visited[50];
	for(int i=0;i<G->n;i++)
		visited[i]=0;
	
	rear++;
	qu[rear].data=v;
	qu[rear].parent=-1;
	visited[v]=1;
	
	while(front!=rear)
	{
		front++;
		w=qu[front].data;
		
		p=G->adjlist[w].firstarc;
		while(p!=NULL)
		{
			if(visited[p->adjvex]==0)
			{
				visited[p->adjvex]=1;
				
				rear++;
				qu[rear].data=p->adjvex;
				qu[rear].parent=front;
			}
			p=p->nextarc;
		}
	}
	return w;	
} 

int main(void)
{
	int n=5,e=7;
	int u=0,v=4; 
//	int A[50][50]={{0,8,INF,5,INF},
//				   {INF,0,3,INF,INF},
//				   {INF,INF,0,INF,6},
//				   {INF,INF,9,0,INF},
//				   {INF,INF,INF,INF,0}};
			
	int A[50][50]={{0,1,1,0,0},
				   {0,0,1,0,0},
				   {0,0,0,1,1},
				   {0,0,0,0,1},
				   {1,0,0,0,0}};
					
	AdjGraph *G;
	CreateAdj(G,A,n,e);
	DispAdj(G);
	printf("������ȱ�����");
	BFS(G,0);
	printf("����%d������%d�����·��Ϊ��",u,v);
	ShortPath(G,u,v);
	printf("����Ȩ����ͼG�о��붥��%d��Զ�Ķ���Ϊ%d",v,Maxdist(G,v)); 
}






















