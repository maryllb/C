#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node
{
	int data;
	struct node *next;
}Lnode,*linklist;

void link_print(linklist head);

int link_getLength(linklist head);


linklist link_create()
{
	linklist phead = NULL;
	int x;
	linklist s=NULL;
	scanf("%d",&x);
	while(x!=0)
	{
		s=(linklist)malloc(sizeof(Lnode));
		if(s==NULL)
		{
			printf("malloc error\n");
			assert(s!=NULL);
			return phead;
		}
		s->data = x;
		if(phead == NULL)/*The first node*/
		{
			s->next = NULL;
			phead = s;
		}
		else /*other node*/
		{
			s->next = phead;
			phead = s;
		}
		scanf("%d",&x);
	}
	return phead;
}
/*
*函数名：link_searchByindex
*功能：链表的按序号查找
*入参：head：头指针，index:节点序号
*返回值：查找成功，返回查到节点的地址，查找失败返回NULL
*其他说明：index的值从1开始，index=1表示查找第一个节点
*/
linklist link_searchByindex(linklist head,int index)
{
	int i;
	linklist p=head;
	/*入参检查*/
	if((index<1)||(index>link_getLength(head)))
	{
		printf("index param error!\n");
		return NULL;
	}
	for(i=1;i<index;i++)
	{
		p=p->next;
	}
	return p;
}
/*
*函数名：link_searchByData
*功能：按值查找单链表，找到第一个节点返回
*入参：head:头指针，data查找节点的数据
*返回值：找到返回节点地址，找不到返回NULL
*/
linklist link_searchByData(linklist head,int data)
{
	linklist p=head;
	if(head == NULL)
		return NULL;
	while(p!=NULL)
	{
		if(p->data ==data)
			break;
		p=p->next;
	}
	return p;
	
}
/*
*函数名：link_searchByDataAll
*功能：按值查找单链表，找到的所有节点的地址存储在p_arr指向的指针数组中
*入参：head:头指针，data查找节点的数据，num:指针数组p_arr的数组大小
*出参：p_arr:查找到节点的指针数组
*返回值：返回查找实际找到的节点个数
*/
int link_searchByDataAll(linklist head,int data,linklist *p_arr,int num)
{
	linklist p=head;
	int i=0;
	if(head == NULL)
		return 0;
	while(p!=NULL)
	{
		if((p->data ==data)&&(i<num))
			p_arr[i++]=p;
		p=p->next;
	}
	return i;
	
}
/*
*入参：head:头指针，data插入的数据，index:插入位置，从1开始
*返回值：返回插入后链表的头指针
*/
linklist link_insert(linklist head,int data,int index)
{
	return head;
}
/*
*入参：head:要插入链表头指针的地址，data插入的数据，index:插入位置
*返回值：插入成功返回0，插入失败返回－1，
*/
int link_insert_add(linklist *head,int data,int index)
{
	linklist s=NULL;
	/*入参检查*/
	if(index<1)
	{
		printf("index param error!\n");
		return -1;
	}
#if 0
	if((index == 1)||(*head == NULL))/*前插入*/
	{
	}

	else if(index >link_getLength(*head))/*尾插入*/
	{
	}
	else/*中间插入*/
	{
	}
#endif
	/*申请空间*/
	s=(linklist)malloc(sizeof(Lnode));

	if(s==NULL)
	{
		printf("malloc error\n");
		return -1;
	}
	s->data=data;
	if((index == 1)||(*head == NULL))/*前插入*/
	{
		s->next=*head;
		*head = s;
	}
	else/*其他位置插入*/
	{
		int len = link_getLength(*head);
		linklist p=NULL;
		if(index>len+1)
			index = len+1;
		p=link_searchByindex(*head,index-1);
		if(p!=NULL)
		{
			s->next=p->next;
			p->next = s;
		}
		else
		{
			printf("insert error!\n");
			free(s);
			return -1;	
		}
		
	}
	return 0;
}
linklist link_delete(linklist head,int index)
{
	return head;
}
int link_delete_2(linklist *head,int index)
{
	
}
linklist getMaxFormOld(linklist pold)
{
	linklist pMax=pold;
	linklist p=pold->next;
	while(p!=NULL)
	{
		if(pMax->data < p->data)
			pMax=p;
		p=p->next;
	}
	return pMax;
}
linklist removeFormOld(linklist pold,linklist pmax)
{
	if(pold == pmax)/*移出的最大值节点是第一个节点*/
	{
		pold=pold->next;
	}
	else /*其他节点*/
	{
		linklist p=pold;
		while(p!=NULL)
		{
			if(p->next == pmax)
				break;
			p=p->next;
		}
		p->next=pmax->next;
	}
	
	return pold;
}
linklist addToNew(linklist pnew,linklist pmax)
{
	pmax->next = pnew;
	pnew = pmax; 
	return pnew;
}
//单链表按选择排序算法实现排序功能
linklist link_sort(linklist pOld)
{
	linklist pNew = NULL;
	linklist pmax;
	while(pOld!=NULL)
	{
		/*从旧链表上找最大值节点的地址*/
		pmax = getMaxFormOld(pOld);
		//printf("pmax=%d\n",pmax->data);
		/*将最大值节点从旧链表上拆下来*/
		pOld=removeFormOld(pOld,pmax);
		//link_print(pOld);
		/*将最大值节点以前插入的方式插入到新链表*/
		pNew=addToNew(pNew,pmax);
		//link_print(pNew);
	}
	return pNew;

}
//将两条分别有序的单链表 合并成一条有序链表，要求时间复杂度比较低
linklist link_merge(linklist s1,linklist s2)
{
	linklist pnew = NULL,q=NULL,tail=NULL;

	while((s1!=NULL)&&(s2!=NULL))
	{
		if(s1->data < s2->data)
		{
			q=s1;
			s1=s1->next;
		}
		else
		{
			q=s2;
			s2=s2->next;
		}
		q->next = NULL;
		if(pnew == NULL)
		{	
			pnew = q;	
		}
		else
		{
			tail->next = q;
		}
		tail = q;
	}
	if(s1!=NULL)
	{
		if(tail!=NULL)
		{
			tail->next = s1;
		}
		else
		{
			pnew = s1;
		}
	}
	else if(s2 != NULL)
	{
		if(tail != NULL)
		{
			tail->next = s2;
		}
		else 
		{
			pnew = s2;
		}
	}
	else
	{
	}
	return pnew;
}
int link_getLength(linklist head)
{
	linklist p=head;
	int len=0;
	while(p!=NULL)
	{
		len++;
		p=p->next;
	}
	return len;
}
void link_print(linklist head)
{
	linklist p = head;
	/*入参检查*/
	if(head == NULL)
	{
		printf("empty link\n");
		return ;
	}
	while(p!=NULL)
	{
		printf("[%d]->",p->data);
		p=p->next;
	}
	printf("\n");
}
/*链表的销毁函数*/
linklist link_destory(linklist head)
{
	linklist p=head,q;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		free(q);
	}
	return p;
}

//链表的倒置，非递归实现,将节点一个一个摘下来，前插入的方式插入到新链表上
linklist link_reverse(linklist head)
{
	linklist pNew = NULL;
	//入参检查
	if(head == NULL)
		return NULL;
	linklist p = head;
	while(head!=NULL)
	{
		p=head;
		head = head->next;
		p->next = pNew;
		pNew = p;
	}
	return pNew;
}


//写入文件  一条链表  整体写入，覆盖原有数据 
int WriteStu(linklist head)
{
	FILE *fp = NULL;
	fp = fopen("stuLinkData","wb+");  //清空原有文件
	if(fp == NULL)
	{
		printf("打开文件失败\n");
		return -1;
	}
	linklist p = head;
	int ret;	
	while(p!=NULL)
	{
		ret = fwrite(p,sizeof(Lnode),1,fp);
		if(ret<1)
		{
			assert(ret>=1);
			printf("写入失败\n");
			return -1;
		}
		p=p->next;
	}
	fclose(fp);
	return 0;
}
linklist readStu()
{
	FILE *fp = NULL;
	fp = fopen("stuLinkData","rb");  //读出一整条链表
	if(fp == NULL)
	{
		printf("打开文件失败\n");
		return NULL;
	}
	linklist phead = NULL;
	linklist s = NULL;
	int ret;
	while(1)
	{
		s = malloc(sizeof(Lnode));
		ret = fread(s,sizeof(Lnode),1,fp);
		if(ret == 0)
			break;
		
		s->next = phead;
		phead = s;
	}
	free(s);
	fclose(fp);
	return phead;
}
int main()
{
	linklist head1=NULL;
	
	//head1 = link_create(); 
	//link_print(head1);   
	//WriteStu(head1);       
	head1 = readStu();
	link_print(head1); 
	//link_destory(head1); 
	return 0;
}
