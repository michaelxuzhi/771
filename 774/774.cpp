#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define MAX 60
#define DEMAX 15
#define NULL 0
char string1[MAX];
char string2[MAX];
int j=0;
struct node
{
	char data;
	int num;
	struct node *next;
};

struct node *Initialization()
{
	struct node *top;
	top=(struct node *)malloc(sizeof(struct node));
	top->data='@';
	top->num=0;
	top->next=NULL;
	return top;
}

struct node *assort(struct node *s)
{
	struct node *p,*top;
	int i;
	top=s;
	int m;
	char a;
	gets(string1);
	m=strlen(string1);
	for(i=0;i<=m;i++)
	{
		a=string1[i];
		if('0'<=string1[i]&&string1[i]<='9')
		{
			string2[j]=string1[i];j++;
		}
		else
		{
			switch(a)
			{
			case'(':{
				p=(struct node *)malloc(sizeof(struct node));
				p->data=a;p->next=top;
				top=p;
				break;
					}
			case'*':
			case'/':
				string2[j]=' ';j++;
				if((top->data=='*')||(top->data=='/'))
				{
					string2[j]=top->data;j++;
					top->data=a;
					break;
				}
				else
				{
					p=(struct node *)malloc(sizeof(struct node));
					p->data=a;p->next=top;
					top=p;
					break;
				}
			case'+':
			case'-':{
				string2[j]=' ';j++;
				if(top->data=='+'||top->data=='-'||top->data=='*'||top->data=='/')
				{
					string2[j]=top->data;j++;
					top->data=a;
					break;
				}
				else
				{
					p=(struct node *)malloc(sizeof(struct node));
					p->data=a;p->next=top;
					top=p;
					break;
				}
					}
			case')':
				{
					string2[j]=' ';j++;
					if(top->data=='@'){
						printf("intput error");
						break;}
						while(top->data!='(')
						{
							string2[j]=top->data;j++;
							p=top;
							top=top->next;
							free(p);
						}
						p=top;top=top->next;free(p);
						break;
					}
				}
			}
		}
		while(top->data!='@')
		{
			string2[j]=top->data;j++;
			p=top;
			top=top->next;
			free(p);
		}
		string2[j]='#';
		printf("转换后的后缀表达式为：%s\n",string2);
		return top;
	}

	struct node *calcolate(struct node *s)
	{
		struct node *top,*p;
		char *q;
		int x,y,a;
		int i,n;
		top=s;
		for(i=0;i<=j;j++)
		{
			if(string2[i]>='0'&&string2[i]<='9')
			{
				q=&string2[i];
				a=atoi(q);
				for(n=i;string2[n]>='0'&&string2[n]<='9';n++){}
				p=(struct node *)malloc(sizeof(struct node));
				p->num=a;p->next=top;top=p;
				i=n-1;
			}
			else 
			if(string2[i]=='#')
			{
					printf("计算结果为：%d\n",top->num);
			}
			else
			{
				if(string2[i]==' '){}
				else
				{
					y=top->num;p=top;top=top->next;free(p);
					x=top->num;p=top;top=top->next;free(p);
					switch(string2[i])
					{
					case'+':{a=x+y;
						p=(struct node *)malloc(sizeof(struct node));
						p->num=a;p->next=top;top=p;
						break;}
					case'-':{a=x-y;
						p=(struct node *)malloc(sizeof(struct node));
						p->num=a;p->next=top;top=p;
						break;}
					case'*':{a=x*y;
						p=(struct node *)malloc(sizeof(struct node));
						p->num=a;p->next=top;top=p;
						break;}
					case'/':{a=x/y;
						p=(struct node *)malloc(sizeof(struct node));
						p->num=a;p->next=top;top=p;
						break;}
					}
				}
			}
		}
		return 0;
	}
int main()
{
		struct node *top,*head;
		top=Initialization();
		printf("请输入表达式：");
		head=assort(top);
		calcolate(head);
		return 0;
}


		