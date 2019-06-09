#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct node{
	char data;
	struct node *lchild;
	struct node *rchild;
}BTNode;
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
//���ٶ����� 
void DestroyBTree(BTNode *&b)
{
	if(b!=NULL)
	{
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
//����һ�������������н����� 
int Nodes(BTNode *b)
{
	if(b==NULL)
		return 0;
	
	return Nodes(b->lchild)+Nodes(b->rchild)+1;
}
//���������������������Ҷ�ӽ�� 
void DispLeaf(BTNode *b)
{
	if(b!=NULL)
	{
		if(b->lchild==NULL&&b->rchild==NULL)
			printf("%4c",b->data); 
		DispLeaf(b->lchild);
		DispLeaf(b->rchild); 
	}
}
//���ҵ������������������Ҷ�ӽ�� 
void DispLeaf1(BTNode *b)
{
	if(b!=NULL)
	{
		if(b->lchild==NULL&&b->rchild==NULL)
			printf("%4c",b->data);
		DispLeaf1(b->rchild);
		DispLeaf1(b->lchild);
	}
}
//����ֵΪx�Ľ�����ڵĲ�� 
int Level(BTNode *b,char x,int h)
{
	int level;
	if(b==NULL)
		return 0;
	else if(b->data==x)
		return h;
	else{
		level=Level(b->lchild,x,h+1);
		if(level!=0)
			return level;
		else
			return level=Level(b->rchild,x,h+1); 
	}
}
//���������k��Ľ����� 
void Lnodenum(BTNode *b,int h,int k,int &n)
{
	if(b==NULL)
	   return ;
	else{
		if(h==k)
			n++;
		if(h<k)
			Lnodenum(b->lchild,h+1,k,n);
			Lnodenum(b->rchild,h+1,k,n);
	}
}
//�ж������������Ƿ����� 
bool Like(BTNode *b1,BTNode *b2)
{
	bool like1,like2;
	if(b1==NULL&&b2==NULL)
	   return true;
	else if(b1==NULL||b2==NULL)
	   return false;
	else
	{
		like1=Like(b1->lchild,b2->lchild);
		like2=Like(b2->rchild,b2->rchild);
		return (like1&&like2);
	}
}
//���ֵΪx�Ľ����������� 
bool ancestor(BTNode *b,char x)
{
	if(b==NULL)
		return false;
	else if(b->lchild!=NULL&&b->lchild->data==x||
			b->rchild!=NULL&&b->rchild->data==x){
		printf("%4c",b->data);
		return true;		
	}else if(ancestor(b->lchild,x)||ancestor(b->rchild,x)){
		printf("%4c",b->data);
		return true;
	}else
		return false;

}

//��������ݹ��㷨
void PreOrder(BTNode *b)
{
	if(b!=NULL)
	{
		printf("%4c",b->data);
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
} 

//��������ݹ��㷨
void InOrder(BTNode *b)
{
	if(b!=NULL)
	{
		InOrder(b->lchild);
		printf("%4c",b->data);
		InOrder(b->rchild); 
	}
} 

//��������ݹ��㷨
void PostOrder(BTNode *b)
{
	if(b!=NULL)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		printf("%4c",b->data);
	}	
} 
 
int main(void)
{
	BTNode *b;
	int m,n,item=0;
	bool mm;
	CreateBTree(b,"A(B(D(,G)),C(E,F))");
	printf("���������������");
	PreOrder(b);
	printf("\n");
	printf("���������������");
	InOrder(b);
	printf("\n");
	printf("�������������: ");
	PostOrder(b);
	printf("\n");
	printf("�������Ľ�����:  ");
	m=Nodes(b);
	printf("%d\n",m);
	printf("��������Ķ�����������Ҷ�ӽ��:");
	DispLeaf(b);
	printf("\n");
	printf("��������Ķ�����������Ҷ�ӽ��:  ");
	DispLeaf1(b);
	printf("\n");
	printf("������ֵΪG�Ľ�����ڶ������Ĳ���:  ");
	n=Level(b,'G',1);
	printf("%d\n",n);
	printf("�����3��Ľ�����:  ");
	Lnodenum(b,1,3,item);
	printf("%d\n",item);
	printf("�ж����Ŷ������Ƿ�����:  ");
	mm=Like(b,b);
	if(mm)
	   printf("����");
	else
	   printf("������");
	printf("\n");
	printf("���ֵΪG�Ľ�����������:  ");
	ancestor(b,'G');
	
}
































