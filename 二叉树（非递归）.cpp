#include<stdio.h>
#include<string.h>
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
	int top;
}SqStack;

//初始化栈 
void InitStack(SqStack *&s)
{
	s=(SqStack *)malloc(sizeof(SqStack));
	s->top=-1;
}

//销毁栈
void DestoryStack(SqStack *&s)
{
	free(s);
} 

//判断栈是否为空
bool StackEmpty(SqStack *s)
{
	return s->top==-1;
} 

//进栈
bool Push(SqStack *&s,BTNode *e) 
{
	if(s->top==50-1)
		return false;
	s->top++;
	s->data[s->top]=e;
	return true;
}

//出栈
bool Pop(SqStack *&s,BTNode *&e)
{
	if(s->top==-1)
		return false;
	e=s->data[s->top];
	s->top--;
	return true;
} 

//取栈顶元素
bool GetTop(SqStack *s,BTNode *&e)
{
	if(s->top==-1)
		return false;
	e=s->data[s->top];
	return true;
} 

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

//先序遍历的非递归算法
void PreOrder1(BTNode *b)
{
	BTNode *p;
	SqStack *st;
	InitStack(st);
	if(b!=NULL)
	{
		Push(st,b);
		while(!StackEmpty(st))
		{
			Pop(st,p);
			printf("%4c",p->data);
			if(p->rchild!=NULL)
				Push(st,p->rchild);
			if(p->lchild!=NULL)
				Push(st,p->lchild); 
		}
		printf("\n");
	} 
	DestoryStack(st);
} 

void PreOrder2(BTNode *b)
{
	BTNode *p;
	SqStack *st;
	InitStack(st);
	p=b;
	while(!StackEmpty(st)||p!=NULL)
	{
		while(p!=NULL)
		{
			printf("%4c",p->data);
			Push(st,p);
			p=p->lchild;
		}
		if(!StackEmpty(st))
		{
			Pop(st,p);
			p=p->rchild;
		}
	}
	printf("\n");
	DestoryStack(st);
}

void InOrder(BTNode *b)
{
	BTNode *p;
	SqStack *st;
	InitStack(st);
	p=b;
	while(!StackEmpty(st)||p!=NULL)
	{
		while(p!=NULL)
		{
			Push(st,p);
			p=p->lchild;
		}
		if(!StackEmpty(st))
		{
			Pop(st,p);
			printf("%4c",p->data);
			p=p->rchild; 
		}
	}
	printf("\n");
	DestoryStack(st);
}

int main(void)
{
	BTNode *b;
	CreateBTree(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
	PreOrder1(b);
	PreOrder2(b);
	InOrder(b);
}



























