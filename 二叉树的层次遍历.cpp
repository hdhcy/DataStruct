#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct node{
	char data;
	struct node *lchild;
	struct node *rchild;
}BTNode;

typedef struct
{
	BTNode *data[50];
	int front,rear;
}SqQueue;

//���������� 
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
bool enQueue(SqQueue *&q,BTNode *e)
{
	if(q->rear==50-1)
		return false;
	q->rear++;
	q->data[q->rear]=e;
	return true;
}

//������ 
bool deQueue(SqQueue *&q,BTNode *&e)
{
	if(q->front==q->rear)
		return false;
	q->front++;
	e=q->data[q->front];
	return true;
}

//��α��� 
void LevelOrder(BTNode *b)
{
	BTNode *p;
	SqQueue *qu;
	InitQueue(qu);
	enQueue(qu,b);
	while(!QueueEmpty(qu))
	{
		deQueue(qu,p);
		printf("%4c",p->data);
		if(p->lchild!=NULL)
			enQueue(qu,p->lchild);
		if(p->rchild!=NULL)
			enQueue(qu,p->rchild);
	}
	printf("\n");
	DestroyQueue(qu);
}

int main(void)
{
	BTNode *b;
	CreateBTree(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	printf("��α�����"); 
	LevelOrder(b); 
}












