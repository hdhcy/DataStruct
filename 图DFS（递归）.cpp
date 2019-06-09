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

//ͼ��������ȱ����㷨DFS 
int visited[50]={0};
void DFS(AdjGraph *G,int v)
{
	ArcNode *p;
	visited[v]=1;
	printf("%4d",v);
	p=G->adjlist[v].firstarc;
	while(p!=NULL)
	{
		if(visited[p->adjvex]==0)
			DFS(G,p->adjvex);
		p=p->nextarc;
	}
}

int main(void)
{
	int n=5,e=7;
	int A[50][50]={{0,8,INF,5,INF},
				   {INF,0,3,INF,INF},
				   {INF,INF,0,INF,6},
				   {INF,INF,9,0,INF},
				   {INF,INF,INF,INF,0}};
					
	AdjGraph *G;
	CreateAdj(G,A,n,e);
	DispAdj(G);
	printf("������ȱ�����");
	DFS(G,0);
}























