#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>
MYSQL mysql;
void login();
void zheng();
void del();
void change();
void SelecT();
int main()
{
	mysql_init(&mysql);
	
	if (!mysql_real_connect(&mysql,"127.0.0.1","root","","mis",0,NULL,0))
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n",
			  mysql_error(&mysql));
	}
	else
		printf("连接成功\n");
	
	mysql_query(&mysql,"set names utf8");
	
	printf("请登录：\n");
	login();
	
	
loop:	printf("\t欢迎使用窗帘信息管理系统\n");
	printf("\t\t菜单\t\t\n");
	printf("1.添加库存\n");
	printf("2.删除窗帘\n");
	printf("3.修改窗帘信息\n");
	printf("4.查找窗帘\n");
	printf("0.退出系统\n");
	
	printf("-->");
	int a;
	scanf("%d",&a);
	switch(a)
	{
		case 0: goto tui;
		case 1: zheng();break;
		case 2: del();break;
		case 3: change();break;
		case 4: SelecT();break;
		default:printf("输入错误，请重新输入\n");break;
		
	}
	
	goto loop;	
	
tui: mysql_close(&mysql);
	
	return 0;
}

void login()
{
	int login = 0;
	char s[100];
	int ID;
	int num1;
	char num[20];
	char name[20];
	char passwd[50];
	printf("请选择登录方式 1 ID 登录 0 名字登录\n");
	scanf("%d",&num1);
	if(1 == num1)
	{
		printf("请输入工作ID：");
		scanf("%s",num);
		ID=atoi(num);
		printf("请输入密码：");
		scanf("%s",passwd);
		sprintf(s,"select * from worker  where ID = %d and passwd=md5('%s');",ID,passwd);
	}
	else if(0==num1)
	{
		printf("请输入姓名：");
		scanf("%s",name);
		printf("请输入密码：");
		scanf("%s",passwd);
		sprintf(s,"select * from worker  where name = '%s' and passwd=md5('%s');",name,passwd);
	}
	else
		exit(1);
	
	if(mysql_query(&mysql, s))
    {
		fprintf(stderr, "Failed to select: Error: %s\n",
					mysql_error(&mysql));
    }
    else
    {
		MYSQL_RES* res;
		res = mysql_store_result(&mysql);

		if(mysql_num_rows(res) == 1)
		{
			//登录校验成功
			login = 1;
		}

			mysql_free_result(res);
		}
		if(!login)
		{
			printf("用户名或密码错误，登录失败！\n");
			exit(1);
		}


	printf("登录成功！\n");
	
}


void zheng()
{
	char s[100];
	unsigned int id;
	char name[20];
	char color[20];
	char types[20];
	float price;
	printf("请按提示输入：\n");
	printf("id = ");
	scanf("%d",&id);
	printf("name = ");
	scanf("%s",name);
	printf("color = ");
	scanf("%s",color);
	printf("types = ");
	scanf("%s",types);
	printf("price = ");
	scanf("%f",&price);
	printf("\n");
	sprintf(s,"insert into cl values('%d','%s','%s','%s','%.1f');",id, name,color,types,price);
	printf("%s\n",s);

	if(mysql_query(&mysql,s))
	{
		fprintf(stderr,"Faild to insert data to table cl :Error :%s\n",
			mysql_error(&mysql));
	}
	else
	{
		printf("插入成功!\n");
	}
	
	
}
void del()
{
	char s[100];
	int id;
	printf("请输入你要删除的窗帘id=");
	scanf("%d",&id);
	sprintf(s,"delete from cl where id= %d;",id);
	if(mysql_query(&mysql,s))
	{
		fprintf(stderr,"Faild to delete data to table cl :Error :%s\n",
			mysql_error(&mysql));
	}
	else
	{
		printf("删除成功!\n");
		
	}
	
}
void change()
{
	char s[100];
	char change[20];
	char changed[20];
	int id;
	printf("请输入你修改的窗帘id=");
	scanf("%d",&id);
	printf("请输入你要修改的属性\n");
	printf("-->");
	scanf("%s",change);
	printf("请输入修改后的值\n");
	printf("-->");
	scanf("%s",changed);
	sprintf(s,"update cl  set %s = '%s' where id = %d;",change,changed,id);
	printf("%s\n",s);
	if(mysql_query(&mysql,s))
	{
		fprintf(stderr,"Faild to update data to table cl :Error :%s\n",
			mysql_error(&mysql));
	}
	else
	{
		printf("修改成功!\n");
		
	}
	
		
}

void SelecT()
{
	char s[100];
	unsigned int id;
	char id1[10];
	char name[20];
	char color[20];
	char types[20];
	int price1;
	int price2;
	int num;
	char num1[10];
	
	printf("查询条件：\n");
	printf("1.按窗帘id查找\n");
	printf("2.按窗帘名字查找\n");
	printf("3.按窗帘颜色查找\n");
	printf("4.按窗帘类型查找\n");
	printf("5.按窗帘价格查找\n");
	printf("6.查询所有信息\n");
	printf("-->");
	scanf("%s",num1);
	num=atoi(num1);
	if(1 == num)
	{
		printf("请输入你查找的窗帘id=");
		scanf("%s",id1);
		id=atoi(id1);
		sprintf(s,"select * from cl  where id = %d;",id);
	}
	else if(2 == num)
	{
		printf("请输入你查找的窗帘name=");
		scanf("%s",name);
		sprintf(s,"select * from cl  where name = '%s';",name);
	}
	else if(3 == num)
	{
		printf("请输入你查找的窗帘color=");
		scanf("%s",color);
		sprintf(s,"select * from cl  where color = '%s';",color);
	}
	else if(4 == num)
	{
		printf("请输入你查找的窗帘types=");
		scanf("%s",types);
		sprintf(s,"select * from cl  where types = '%s';",types);
	}
	else if(5 == num)
	{
		printf("请输入你查找的窗帘价格范围为");
		scanf("%d %d",&price1,&price2);
		sprintf(s,"select * from cl where price >=%d and price <=%d;",price1,price2);
	}
	else if(6 == num)
	{
		sprintf(s,"select * from cl;");
	}
	if(mysql_query(&mysql,s))
	{
		fprintf(stderr,"Faild to select  data to table cl :Error :%s\n",
			mysql_error(&mysql));
			
	}
	else
	{
		MYSQL_RES* res;
		res = mysql_store_result(&mysql);
		MYSQL_ROW row;
		
		if(row= mysql_fetch_row(res))
		{
			printf("%s %s %s %s %s\n",row[0],row[1],row[2],row[3],row[4]);
			while(row= mysql_fetch_row(res))
			{
				
				printf("%s %s %s %s %s\n",row[0],row[1],row[2],row[3],row[4]);
				
			}
		}
		else
		{
			printf("对不起，没找到！\n");
		}
		printf("\n");
		mysql_free_result(res);
		
		printf("是否进行查找：1 继续 0 退出系统 其他数字返回\n");
		scanf("%s",num1);
		num=atoi(num1);
		if(1==num)
		{
			SelecT();
		}
		else if(0==num)
		{
			exit(1);
		}
		
	}		
}
