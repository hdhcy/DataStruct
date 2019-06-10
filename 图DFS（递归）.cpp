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

//�ж�����ͼG�Ƿ���ͨ
bool Connect(AdjGraph *G)
{
	bool flag=true;
	for(int i=0;i<G->n;i++)
		visited[i]=0;
	DFS(G,0);
	for(int i=0;i<G->n;i++)
		if(visited[i]==0)
		{
			flag=false;
			break;
		}	
	printf("\n");
	return flag;
} 

//�ж�ͼG�дӶ���v������u�Ƿ���ڼ�·��
void ExistPath(AdjGraph *G,int u,int v,bool &has)
{
	ArcNode *p;
	for(int i=0;i<G->n;i++)
		visited[i]=0;
	visited[u]=1;
	if(u==v)
	{
		has=true;
		return;
	}
	
	p=G->adjlist[u].firstarc;
	while(p!=NULL)
	{
		if(visited[p->adjvex]==0)
			ExistPath(G,p->adjvex,v,has);
		p=p->nextarc;		
	}	
} 

//���ͼG�дӶ���u������v�����м�·��
void FindaPath(AdjGraph *G,int u,int v,int path[],int d)
{
	ArcNode *p;
	for(int i=0;i<G->n;i++)
		visited[i]=0;
	visited[u]=1;
	d++; path[d]=u;
	if(u==v)
	{
		for(int i=0;i<=d;i++)
			printf("%4d",path[i]);
		printf("\n");
		return;
	} 
	
	p=G->adjlist[u].firstarc;
	while(p!=NULL)
	{
		if(visited[p->adjvex]==0)
			FindaPath(G,p->adjvex,v,path,d);
		p=p->nextarc;
	}
} 

//���ͼG�дӶ���u������v�����м�·��
void FindAllPath(AdjGraph *G,int u,int v,int path[],int d) 
{
	ArcNode *p;
	for(int i=0;i<G->n;i++)
		visited[i]=0;
	visited[u]=1;
	d++; path[d]=u;
	
	if(u==v)
	{
		for(int i=0;i<=d;i++)
			printf("%4d",path[i]);
		printf("\n");
	} 
	
	p=G->adjlist[u].firstarc;
	while(p!=NULL)
	{
		if(visited[p->adjvex]==0)
			FindAllPath(G,p->adjvex,v,path,d);
		p=p->nextarc; 
	}
	//visited[u]=0;
}

//���ͼG�ж���u������v�ĳ���Ϊl�����м�·��
void PathlenAll(AdjGraph *G,int u,int v,int l,int path[],int d) 
{
	ArcNode *p;
	for(int i=0;i<G->n;i++)
		visited[i]=0;
	visited[u]=1;
	d++; path[d]=u;
	
	if(u==v&&d==l)
	{
		for(int i=0;i<=d;i++)
			printf("%4d",path[i]);
		printf("\n");
	}
	
	p=G->adjlist[u].firstarc;
	while(p!=NULL)
	{
		if(visited[p->adjvex]==0)
			PathlenAll(G,p->adjvex,v,l,path,d);
		p=p->nextarc;
	}
}

//���ͼG�о���ĳ������k�����м򵥻�·
int visited2[50]={0};
void DFSPath(AdjGraph *G,int u,int v,int path[],int d)
{
	ArcNode *p;
	visited2[u]=1;
	d++; path[d]=u;
	p=G->adjlist[u].firstarc;
	while(p!=NULL)
	{
		if(p->adjvex==v&d>0)
		{
			for(int i=0;i<=d;i++)
				printf("%4d",path[i]);
			printf("%4d\n",v);
		}
		
		if(visited2[p->adjvex]==0)
			DFSPath(G,p->adjvex,v,path,d);
		p=p->nextarc;
	}
	visited2[u]=0;
} 

void FindCyclePath(AdjGraph *G,int k)
{
	int path[50];
	int d=-1;
	DFSPath(G,k,k,path,d);
}

int main(void)
{
	int n=5,e=7;
	int u=0,v=4,d=-1,l=3,k=0;
	int path[50];
	bool has;
	int A[50][50]={{0,8,INF,5,INF},
				   {INF,0,3,INF,INF},
				   {INF,INF,0,INF,6},
				   {INF,INF,9,0,INF},
				   {INF,INF,INF,INF,0}};
  
  	int B[50][50]={{0,1,1,0,0},
				   {0,0,1,0,0},
				   {0,0,0,1,1},
				   {0,0,0,0,1},
				   {1,0,0,0,0}};
					
	AdjGraph *G;
	AdjGraph *G2;
	CreateAdj(G,A,n,e);
	DispAdj(G);
	printf("������ȱ�����");
	DFS(G,0);
	printf("\n");
	printf("������ȱ�����");
	bool g = Connect(G);
	printf("��ͼ�Ƿ���ͨ��");
	printf("%4d\n",g);
	ExistPath(G,u,v,has);
	printf("%d��%d�Ƿ����·����%4d\n",u,v,has);
	printf("%d��%d��һ����·����\n",u,v);
	FindaPath(G,u,v,path,d);
	printf("%d��%d�����м�·����\n",u,v);
	FindAllPath(G,u,v,path,d); 
	printf("%d��%d�����г���Ϊ%d��·����\n",u,v,l);
	PathlenAll(G,u,v,l,path,d);
	
	CreateAdj(G2,B,n,e);
	DispAdj(G2);
	printf("��������%d�����л�·��\n",k);
	FindCyclePath(G2,k); 
}























