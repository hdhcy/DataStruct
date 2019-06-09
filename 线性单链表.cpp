#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef int  ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode *next; 
}LinkNode;

//初始化线性表 
void InitList(LinkNode *&L)
{
	L=(LinkNode *)malloc(sizeof(LinkNode));
	L->next=NULL; 
}

//头插法插入数据
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

//尾插法插入数据
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

//销毁线性表
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

//判断线性表是否为空表 
bool ListEmpty(LinkNode *L)
{
	return(L->next==NULL);
}

//求线性表的长度
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

//输出线性表
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

//求线性表中某个数据元素值
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

//按元素值查找
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

//插入数据元素
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

//删除数据元素
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
例2.6有一个带头结点的单链表L=(a1,b1,a2,b2,...,an,bn),设计一个算法将其拆分成两个带头结点的单链表L1和L2，其中
L1=(a1,a2,...,an),L2=(bn,bn-1,...,b1),要求L1使用L的头结点 
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


//例2.7设计一个算法，删除一个单链表L中元素最大的结点（假设这样的结点唯一）
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

//例2.8有一个带头结点的单链表L（至少有一个数据结点）,设计一个算法使得其元素递增有序排列 
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

//将一个线性表反转
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
	printf("尾插法构建的链表为：\n");
	DispList(L);
	reLinkNode(L);
	printf("反转后的链表为：\n");
	DispList(L);
} 


















