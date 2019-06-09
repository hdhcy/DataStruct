#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef int  ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode *next; 
}LinkNode;

//��ʼ�����Ա� 
void InitList(LinkNode *&L)
{
	L=(LinkNode *)malloc(sizeof(LinkNode));
	L->next=NULL; 
}

//ͷ�巨��������
void CreateListF(LinkNode *&L,ElemType a[],int n)
{
	LinkNode *s;
	for(int i=0;i<n;i++)
	{
		s=(LinkNode *)malloc(sizeof(LinkNode));
		s->data=a[i];
		s->next=L->next;
		L->next=s;
	}
}

//β�巨��������
void CreateListR(LinkNode *&L,ElemType a[],int n)
{
	LinkNode *s,*r=L;	
	for(int i=0;i<n;i++)
	{
		s=(LinkNode *)malloc(sizeof(LinkNode));
		s->data=a[i];
		r->next=s;
		r=s;
	}
	r->next=NULL;
} 

//�������Ա�
void DestoryList(LinkNode *&L)
{
	LinkNode *pre=L,*p=L->next;
	while(p!=NULL)
	{
		free(pre);
		pre=p;
		p=pre->next;
	}
	free(pre);
} 

//�ж����Ա��Ƿ�Ϊ�ձ� 
bool ListEmpty(LinkNode *L)
{
	return(L->next==NULL);
}

//�����Ա�ĳ���
int ListLength(LinkNode *L)
{
	int n=0;
	LinkNode *p=L;
	while(p->next!=NULL)
	{
		n++;
		p=p->next;		
	}	
	return n;
} 

//������Ա�
void DispList(LinkNode *L)
{
	LinkNode *p=L->next;
	while(p!=NULL)
	{
		printf("%d  ",p->data);
		p=p->next;
	}
	printf("\n");
} 

//�����Ա���ĳ������Ԫ��ֵ
bool GetElem(LinkNode *L,int i,ElemType &e)
{
	int j=0;
	LinkNode *p=L;
	if(i<=0)
	{
		return false;
	}
	while(j<i&&p!=NULL)
	{
		j++;
		p=p->next;
	}
	if(p==NULL)
	{
		return false;
	}else{
		e=p->data;
		return true;
	}
} 

//��Ԫ��ֵ����
int LocateElem(LinkNode *L,ElemType e)
{
	int i=1;
	LinkNode *p=L->next;
	while(p!=NULL&&p->data!=e)
	{
		p=p->next;
		i++;
	}
	if(p==NULL)
	{
		return 0;
	}else
	{
		return i;
	}
} 

//��������Ԫ��
bool ListInsert(LinkNode *&L,int i,ElemType e)
{
	int j=0;
	LinkNode *p=L,*s;
	if(i<=0)
		return false;
	
	while(j<i-1&&p!=NULL)
	{
		j++;
		p=p->next;
	}
	if(p==NULL)
		return false;
	else{
		s=(LinkNode *)malloc(sizeof(LinkNode));
		s->data=e;
		s->next=p->next;
		p->next=s;
		return true;
	}
} 

//ɾ������Ԫ��
bool ListDelete(LinkNode *&L,int i,ElemType e)
{
	int j=0;
	LinkNode *p=L,*q;
	if(i<=0)
		return false;
	
	while(j<i-1&&p!=NULL)
	{
		j++;
		p=p->next;
	}	
	if(p==NULL)
		return false;
	else{
		q=p->next;
		if(q==NULL)
			return false;
		
		e=q->data;
		p->next=q->next;
		free(q);
		return true;
	}
} 

/*
��2.6��һ����ͷ���ĵ�����L=(a1,b1,a2,b2,...,an,bn),���һ���㷨�����ֳ�������ͷ���ĵ�����L1��L2������
L1=(a1,a2,...,an),L2=(bn,bn-1,...,b1),Ҫ��L1ʹ��L��ͷ��� 
*/ 
void split(LinkNode *&L,LinkNode *&L1,LinkNode *&L2)
{
	LinkNode *p=L->next,*r1,*q;
	L1=L;
	r1=L1;
	L2=(LinkNode *)malloc(sizeof(LinkNode));
	L2->next=NULL;
	while(p!=NULL)
	{
		r1->next=p;
		r1=p;
		
		p=p->next;
		q=p->next;
		p->next=L2->next;
		L2->next=p;
		 
		p=q; 
	}
	r1->next=NULL;
}


//��2.7���һ���㷨��ɾ��һ��������L��Ԫ�����Ľ�㣨���������Ľ��Ψһ��
void delmaxnode(LinkNode *&L,ElemType &e)
{
	LinkNode *p=L->next,*pre=L,*maxpre=pre,*maxp=p;
	
	while(p!=NULL)
	{
		if(maxp->data<p->data)
		{
			maxpre=pre;
			maxp=p;
		}
		pre=p;
		p=p->next;
	}
	e=maxp->data;
	maxpre->next=maxp->next;
	free(maxp);
} 

//��2.8��һ����ͷ���ĵ�����L��������һ�����ݽ�㣩,���һ���㷨ʹ����Ԫ�ص����������� 
void sort(LinkNode *L)
{
	LinkNode *p,*pre,*q;
	p=L->next->next;
	L->next->next=NULL;
	while(p!=NULL)
	{
		q=p->next;
		pre=L;
		while(pre->next!=NULL&&pre->next->data<p->data)
		{
			pre=pre->next;
		}
		
		p->next=pre->next;
		pre->next=p;
		p=q;
	}
}

//��һ�����Ա�ת
void reLinkNode(LinkNode *L)
{
	LinkNode *p,*q;
	p=L->next;
	L->next=NULL;
	while(p!=NULL)
	{
		q=p->next;
		p->next=L->next;
		L->next=p;
		p=q;
	}
	
}
int main(void)
{
	LinkNode *L,*L1,*L2;
	ElemType a[10]={10,9,8,7,6,5,4,3,2,1};
	ElemType e;
	
	InitList(L);
	CreateListR(L,a,10);
	printf("β�巨����������Ϊ��\n");
	DispList(L);
	reLinkNode(L);
	printf("��ת�������Ϊ��\n");
	DispList(L);
} 


















