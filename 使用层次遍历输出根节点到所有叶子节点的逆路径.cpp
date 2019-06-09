#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct node
{
	char data;
	struct node *lchild;
	struct node *rchild;
}BTNode;

typedef struct snode
{
	BTNode *pt;
	int parent;
}NodeType;

typedef struct 
{
	NodeType data[50];
	int front,rear;
}SqQueue;

//创建二叉树 
void CreateBTree(BTNode *&b,const char *str)
{
	BTNode *st[50],*p;
	int top=-1,k,j=0;
	char ch;
	b=NULL;
	ch=str[j];
	while(ch!='\0')
	{
		switch(ch)
		{
			case '(':
				top++;
				st[top]=p;
				k=1;
				break;
			case ')':
				top--;
				break;
			case ',':
				k=2;
				break;
			default:
				p=(BTNode *)malloc(sizeof(BTNode));
				p->data=ch;
				p->lchild=p->rchild=NULL;
				if(b==NULL)
					b=p;
				else{
					switch(k)
					{
						case 1:
							st[top]->lchild=p;
							break;
						case 2:
							st[top]->rchild=p;
							break;
					}
				}
		}
		j++;
		ch=str[j];
	}
}

//队列初始化 
void InitQueue(SqQueue *&q)
{
	q=(SqQueue *)malloc(sizeof(SqQueue));
	q->front=q->rear=-1;
}

//销毁队列 
void DestroyQueue(SqQueue *&q)
{
	free(q);
}

//判断队列是否为空 
bool QueueEmpty(SqQueue *q)
{
	return q->front==q->rear;
}

//进队列 
bool enQueue(SqQueue *&q,NodeType e)
{
	if(q->rear==50-1)
		return false;
	q->rear++;
	q->data[q->rear]=e;
	return true;
}

//出队列 
bool deQueue(SqQueue *&q,NodeType &e)
{
	if(q->front==q->rear)
		return false;
	q->front++;
	e=q->data[q->front];
	return true;
}

//输出从根节点到所有叶子节点的路径的逆序列
void AllPath(BTNode *b)
{
	int k;
	BTNode *p;
	NodeType qelem;
	SqQueue *qu;
	InitQueue(qu);
	qelem.pt=b;	qelem.parent=-1;
	enQueue(qu,qelem);
	while(!QueueEmpty(qu))
	{
		deQueue(qu,qelem);
		p=qelem.pt;
		if(p->lchild==NULL&&p->rchild==NULL)
		{
			k=qu->front;
			printf("%c  叶子节点到根节点的路径为：",qu->data[k].pt->data);
			while(qu->data[k].parent!=-1)
			{
				printf("%4c",qu->data[k].pt->data);
				k=qu->data[k].parent;	
			}	
			printf("%4c\n",qu->data[k].pt->data);
		}	
		if(p->lchild!=NULL)
		{
			qelem.pt=p->lchild;
			qelem.parent=qu->front;
			enQueue(qu,qelem);
		}
		if(p->rchild!=NULL)
		{
			qelem.pt=p->rchild;
			qelem.parent=qu->front;
			enQueue(qu,qelem);
		}
	}	
	printf("\n");
	DestroyQueue(qu);
} 

int main(void)
{
	BTNode *b;
	CreateBTree(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("输出从根节点到所有叶子节点的路径的逆序列：\n"); 
	AllPath(b);
}

















