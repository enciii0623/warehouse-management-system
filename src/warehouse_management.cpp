#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include <cstring>
#include<iostream>
#include<iomanip>
using namespace std; 
typedef struct Date//日期的结构体 
{
	int year;//年 
	int month;//月 
	int day;//日 
}date;
typedef struct goods//定义货物的结构体 
{
	char num[30];//编码 
	char name[150];//名称 
	float volume;//大小 
	float weight; //重量 
	float price;//价格 
	int year;//保质期 
	char buyname[10];//采购人 
	char recname[10];//验收人 
	char place[15];//存放地点 
	struct Date intime;//入库日期 
	struct Date outtime;//出库日期 
	char factory[50];//生产厂家 
	struct goods *next;
}good;

typedef struct User//定义管理员的结构体 
{
	char name[50];//姓名 
	char pwd[50];//密码 
	char tel[12];//联系方式 
	char home[50]; //联系地址 
	struct User *unext; 
}user;
typedef struct Pro//供应商的结构体 
{
	char name[80];//供应商名 
	char tel[12];//联系方式 
	struct Pro*pnext;
}pro;
typedef struct Outgood//出库货物 
{
	char num[20];//编号 
	char name[150];//名称 
	struct Date outtime;//出库时间 
	char use[15];//去向 
	char tel[12];//联系方式 
	struct Outgood*outnext; 
}outgood; 

good *head=(good*)malloc(sizeof(good));//货物的头结点 
user *uhead=(user*)malloc(sizeof(user));//管理员的头结点 
pro *phead=(pro*)malloc(sizeof(pro));//供应商的头结点 
outgood *outhead=(outgood*)malloc(sizeof(outgood));//出库信息头结点 

pro *pend=(pro*)malloc(sizeof(pro));//供应商尾结点
good *gend=(good*)malloc(sizeof(good));//货物的尾结点 
outgood *outend=(outgood*)malloc(sizeof(outgood));//出库信息尾结点 



void main1();
void quit();//退出系统
void change();//改动货物信息 
void denglu1();//登录 
void denglu2(); //登录 
void writefile(int flag);//将内容写入文件 
void Register();//注册管理员
void menu();//管理员的菜单函数 
void readfile();//读取文件 
void output1();//按数量排序浏览 
void denglu0();//总管登录 
void manager1();//总管登录界面
void manager2();//管理管理员的页面 
void readuser();//浏览管理员信息
void adduser();//增加管理员的信息 
void Deleteuser();//删除管理员的信息 
void menu1();//显示管理员的功能菜单 
void system();
void manager22();
void denglu00();
void denglu11();
void main11();

void gin();//入库 
void generate_code(good *head, good *s);//商品编码生成 
int count_same_name(good *head, const char *name);//入库生成编码重复货物部分 
void generate_code(good *head, good *s);//入库生成货物编码

void gout();                          // 出库主菜单入口
void gout_by_num();                   // 按编号出库
void gout_by_name_and_count();        // 按名称和数量出库
void add_out_record(good *g);         // 生成出库记录并加入出库链表
void free_out_list();
 

void readoutfile() ;// 从“出库信息.txt”文件中读取数据并创建出库货物链表
void readprofile();//从“供应商信息.txt”文件中读取数据创建供应商链表 
void writegoodfile(int flag);//把信息存入货物文件 flag=1覆盖写入，flag=0追加写入
void writeOutgoodfile(int flag) ;// “出库信息.txt”写回文件 flag=1覆盖写入，flag=0追加写入
void writeProFile(int flag); //“供应商信息.txt”写回文件 flag=1覆盖写入，flag=0追加写入

void searchSuplier(char* name);//查询供应商
void scanSupplier(const pro& p);//浏览供应商
int getDisplayWidth(const std::string& str);//获得供应商名字长度 
void addSupplier(string name,string tel);//添加供应商
void Supplier_Menu();//供应商管理
void print_menu();//报表打印
void printIn();//打印入库报表
void printOut();//打印出库报表
void inventory_menu(); 

void output();
void browse_by_category();
void select_menu();
void Delete();
void manage();

bool is_expired(good *item, int current_year, int current_month, int current_day); 
int compare_by_num(const void *a, const void *b);
int compare_by_name(const void *a, const void *b);
int compare_by_place(const void *a, const void *b);
int compare_by_factory(const void *a, const void *b);
int compare_by_time(const void *a, const void *b);
int binary_search_left(good **arr, int size, const char *target, int (*compare)(const void *, const void *), int field_type);
int binary_search_right(good **arr, int size, const char *target, int (*compare)(const void *, const void *), int field_type);
good **search_good(const char *target, int (*compare)(const void *, const void *),
                 int (*convert)(good *, char *), int field_type, 
                 good **arr, int count, int *result_count);
good **search_by_num(const char *target_num, good **arr, int count, int *result_count);
good **search_by_name(const char *target_name, good **arr, int count, int *result_count);
good **search_by_place(const char *target_place, good **arr, int count, int *result_count);
good **search_by_factory(const char *target_factory, good **arr, int count, int *result_count);
good **list_to_array(int *count);
void print_all_matching_goods(good *first_match, int count);
void print_good(good *p);
void print_header();
void print_sorted_by_name(good **arr, int count);
void print_sorted_by_time(good **arr, int count);
void deleteOutboundGoods();// 删除货物信息中已出库货物 


void trim_trailing_spaces(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[--len] = '\0';
    }
}

void readgoodfile() {
    FILE *fp = fopen("货物信息.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    good *pre = head;
    good *p;
    char line[1024];  // 一行缓冲

    head->next = NULL;

    while (fgets(line, sizeof(line), fp)) {
        // 跳过空行
        if (strlen(line) < 10) continue;

        p = (good *)malloc(sizeof(good));
        if (!p) {
            printf("内存分配失败！\n");
            break;
        }
        memset(p, 0, sizeof(good));

        // 从整行读取并解析字段（名称允许空格）
        int result = sscanf(line,
            "%30s %149[^\t\n] %f %f %f %d %9s %9s %14s %d-%d-%d %d-%d-%d %49[^\n]",
            p->num,          // 编号
            p->name,         // 名称（含空格）
            &p->volume,
            &p->weight,
            &p->price,
            &p->year,
            p->buyname,
            p->recname,
            p->place,
            &p->intime.year, &p->intime.month, &p->intime.day,
            &p->outtime.year, &p->outtime.month, &p->outtime.day,
            p->factory
        );

        // 清理名称尾部空格
        trim_trailing_spaces(p->name);

        if (result < 9) {
            printf("跳过格式错误的行: %s", line);
            free(p);
            continue;
        }

        if (result < 12) {
            p->intime.year = p->intime.month = p->intime.day = 0;
        }
        if (result < 15) {
            p->outtime.year = p->outtime.month = p->outtime.day = 0;
        }
        if (result < 16) {
            strcpy(p->factory, "");
        }
        pre->next = p;
        pre = p;
    }

    if (pre != NULL) {
        pre->next = NULL;
        gend = pre;
    }

    fclose(fp);
}

void readoutfile() // 从文件中读取数据并创建出库货物链表
{
    FILE *fpout = fopen("出库信息.txt", "r");
    if (fpout == NULL) {
        printf("无法打开文件！\n");
        return;
    }
    
    outgood *pre = outhead;
    outgood *p;
    char line[1024]; // 增加缓冲区读取整行
    
    outhead->outnext = NULL; // 初始化链表头
    
    while (fgets(line, sizeof(line), fpout)) {
        // 跳过空行或无效行
        if (strlen(line) < 10) continue;
        
        p = (outgood*)malloc(sizeof(outgood)); 
        if (!p) {
            printf("内存不足！");
            break; 
        }
        
        // 初始化结构体
        memset(p, 0, sizeof(outgood));
        
        // 更灵活的读取方式，处理可能缺失的字段
        int result = sscanf(line, "%19s %149[^\t\n] %d-%d-%d %14[^0-9] %11s",
            p->num, 
            p->name, 
            &p->outtime.year, &p->outtime.month, &p->outtime.day,
            p->use,
            p->tel);
            
        // 检查读取结果，至少需要读取前3个字段
        if (result < 5) { // 需要读取5个基本字段
            free(p);
            printf("跳过格式错误的行: %s", line);
            continue;
        }
        
        // 处理可能缺失的字段
        if (result < 6) {
            strcpy(p->tel, "");
        }
        
            
        if (pre == NULL) {
            outhead = p;
        } else {
            pre->outnext = p;
        }
        pre = p;
        outend = p;
    } 
    
    if (pre != NULL) {
        pre->outnext = NULL;
    }
    
    fclose(fpout);
}
void readprofile() // 从文件中读取数据并创建供应商链表
{
    FILE *fp = fopen("供应商信息.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件！\n");
        return;
    }
    
    pro *pre = phead;
    pro *p;
    char line[1024]; // 增加缓冲区读取整行
    
    phead->pnext = NULL; // 初始化链表头
    
    while (fgets(line, sizeof(line), fp)) {
        // 跳过空行或无效行
        if (strlen(line) < 5) continue; // 供应商信息较短，适当调整阈值
        
        p = (pro*)malloc(sizeof(pro)); 
        if (!p) {
            printf("内存不足！");
            break; 
        }
        
        // 初始化结构体
        memset(p, 0, sizeof(pro));
        
        // 更灵活的读取方式，处理可能的分隔符
        int result = sscanf(line, "%80[^\t\n] %11s",
            p->name,
            p->tel);
            
        // 检查读取结果
        if (result < 2) { // 需要读取2个基本字段
            free(p);
            printf("跳过格式错误的行: %s", line);
            continue;
        }
        
        // 输出读取结果用于调试
       // printf("%s %s\n", p->name, p->tel);
        
        // 链表操作
        if (pre == NULL) {
            phead = p;
        } else {
            pre->pnext = p;
        }
        pre = p;
        pend= p;
    } 
    
    if (pre != NULL) {
        pre->pnext = NULL;
    }
    
    fclose(fp);
}

void writegoodfile(int flag)//把信息存入货物文件 flag=1覆盖写入，flag=0追加写入
{
	FILE *fp;
	if (flag == 1)
	{
		fp=fopen("货物信息.txt","w");
	  if(fp==NULL)
	   {
	   	printf("文件打开失败！");
	   	return ;
	   }
   for(good *m=head->next;m!=NULL;m=m->next)
	   {
	   	fprintf(fp, "%s\t%s\t%f\t%f\t%f\t%d\t%s\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%s\n",
            m->num, 
            m->name, 
            m->volume, 
            m->weight, 
            m->price, 
            m->year,
            m->buyname, 
            m->recname, 
            m->place,
            m->intime.year, m->intime.month, m->intime.day,
            m->outtime.year, m->outtime.month, m->outtime.day,
            m->factory);
	   } 
	}
	 else 
	{
		fp=fopen("货物信息.txt","a+");
	  if(fp==NULL)
	   {
	   	printf("文件打开失败！");
	   	return ;
	   }
   for(good *m=head->next;m!=NULL;m=m->next)
	   {
	   	fprintf(fp, "%s\t%s\t%f\t%f\t%f\t%d\t%s\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%s\n",
            m->num, 
            m->name, 
            m->volume, 
            m->weight, 
            m->price, 
            m->year,
            m->buyname, 
            m->recname, 
            m->place,
            m->intime.year, m->intime.month, m->intime.day,
            m->outtime.year, m->outtime.month, m->outtime.day,
            m->factory);
	   } 
	}
      
   fclose(fp);
}
void writeOutgoodfile(int flag) // 出库商品写回文件 flag=1覆盖写入，flag=0追加写入
{
    FILE *fp;
    if (flag == 1)
    {
        fp = fopen("出库信息.txt", "w");
    }
    else
    {
        fp = fopen("出库信息.txt", "a+");
    }

    if (fp == NULL)
    {
        printf("文件打开失败！");
        return;
    }

    for (outgood *out = outhead->outnext; out != NULL; out = out->outnext)
    {
        fprintf(fp, "%s\t%s\t%d-%d-%d\t%s\t%s\n",
                out->num,
                out->name,
                out->outtime.year, out->outtime.month, out->outtime.day,
                out->use,
                out->tel);
    }
    fclose(fp);
}

void writeProFile(int flag) //供应商写回文件 flag=1覆盖写入，flag=0追加写入
{
    FILE *fp;
    if (flag == 1)
    {
        fp = fopen("供应商信息.txt", "w");
    }
    else
    {
        fp = fopen("供应商信息.txt", "a+");
    }

    if (fp == NULL)
    {
        printf("供应商文件打开失败！");
        return;
    }

    // 遍历供应商链表（假设 phead 是头节点，pnext 指向第一个实际节点）
    for (pro *p = phead->pnext; p != NULL; p = p->pnext)
    {
        fprintf(fp, "%s\t%s\n", p->name, p->tel);
    }
    fclose(fp);
}
int main()
{
	head->next = NULL;
	readgoodfile();
	main1();
	return 0;
}
void main1()
{
	while(1)
	{
		main11();
		int num;
		scanf("%d",&num);
	    fflush(stdin);
		if(num==1)
		{
			system("cls");
		    denglu0();//经理登录	
		}
		else if(num==2)
		{
			system("cls");
			denglu1();//管理员登录 
		}
		else if(num==3)
		{
			quit();
		}
		else
		{
			printf("无效输入！");
			system("pause");
			system("cls");
		}
	}
}
void main11()
{
	system(); 
		printf("                            仓库货物管理系统\n");
		printf("      ****************************MENU****************************\n");
		printf("      *                     1.管理经理登录                       *\n");
		printf("      *                     2.管理员                             *\n");
		printf("      *                     3.退出                               *\n");
		printf("      ************************************************************\n");
		printf("\n\n请选择：");
}

void denglu0()//仓库总管登陆页面 
{
	while(1)
	{
	    denglu00();
		int  num;
		scanf("%d",&num);
		fflush(stdin);
		switch(num)
		{
		case 1: 
				manager1();
				system("pause");
				system("cls");
				break;
		case 2: 
				system("cls");
				main1();
				break;
		case 3: 
				quit();
				break;		
		default:
				printf("无效输入！");
				system("pause");
				system("cls"); 
   		 }	
	}
} 

void denglu00()
{
	    system(); 
		printf("\t    **********************仓库经理页面*******************\n");
		printf("\t    *                        1.登录                     *\n");
		printf("\t    *                        2.返回                     *\n");
		printf("\t    *                        3.退出                     *\n");
		printf("\t    *****************************************************");
		printf("\n\n请选择：");
}
void  denglu1()//管理员 界面 
{
	   while(1)
	{
		denglu11();
		int  num;
		scanf("%d",&num);
		fflush(stdin); 
	    switch(num)
		{
			case 1: 
					denglu2();
					system("pause");
					system("cls");
					break;
			case 2: 
					Register();
					break;
			case 3: 
					system("cls");
					main1();
					break;		
			case 4: 
					quit();
					break;
			default:
					printf("无效输入！");
					system("pause");
				    system("cls"); 
	    }
	}
}
void  denglu11()//管理员注册登录页面
{
	system(); 
		printf("\t    **********管理员注册登录页面**********\n");
		printf("\t    *         1.登录                     *\n");
		printf("\t    *         2.注册                     *\n");
		printf("\t    *         3.返回                     *\n");
		printf("\t    *         4.退出                     *\n");
		printf("\t    **************************************\n");
		printf("\n\n请选择：");
}
void manager1()//经理登录操作 
{
		char name[20];
		printf("请输入账户：\n");
		scanf("%s",name);
		printf("\n");
		printf("请输入密码：\n");
		char a[20];
		char c;
		int i;
		while((c=getch())!='\r')         /*输入密码以及回删*/
		{
			if(c!='\b')
			{
				printf("*");
				a[i]=c;
				i++;
			}
			else if(i!=0)
			{
				printf("\b \b");
				i--;
			}
		 } 
		 a[i]='\0';
	printf("\n"); 
	if(strcmp(name,"1")==0 && strcmp(a,"1")==0)//经理的密码 
	{
		printf("登录成功！"); 
		system("pause");
		system("cls");
		manager2();//执行经理的功能 
	}
	else
	{
		printf("登陆失败！");
	}	
}

void denglu2()//管理员登录 
{
	char password[200];
    char users[200];
    int flag=1,i;
    FILE *fw=fopen("管理员信息.txt","r");//读取之前的管理员信息 
    if(fw == NULL)
    {
    	printf("文件读取失败！");
    	return ;
	}
	char ch;
	ch=fgetc(fw);
	if(ch==EOF)
	{
		printf("无信息！");
		return ;
	}
		rewind(fw); 
		printf("管理员姓名:\n");
		user *p = uhead;
		scanf("%s",users);
		printf("管理员密码：\n"); 
		char a[20];
		char c;
		while((c=getch())!='\r')         /*输入密码以及回删*/
		{
			if(c!='\b')
			{
				printf("*");
				a[i]=c;
				i++;
			}
			else if(i!=0)
			{
				printf("\b \b");
				i--;
			}
		 } 
		 a[i]='\0';
		printf("\n"); 
		while(!feof(fw))
		{
			p->unext=(user*)malloc(sizeof(user));
			p->unext->unext=NULL;
			p=p->unext;
			fscanf(fw,"%s %s %s %s",p->name,p->pwd,p->tel,p->home);//提取信息到链表中 
	    }
		p=uhead->unext;
	while(p!=NULL)
	{
  		if(strcmp(p->name,users) == 0&&strcmp(a,p->pwd) == 0 )
		{
			printf("登录成功！\n"); 
			system("pause");
			system("cls");
			menu();
  		 }
  		 p=p->unext;
	}
	    printf("登陆失败！");
}
void menu1()
{
	system(); 
	    printf("\t\t                          仓库货物管理系统\n");
		printf("\t         *************************MENU**********************\n");
		printf("\t         *                   1.入库                        *\n");
		printf("\t         *                   2.出库                        *\n");
		printf("\t         *                   3.货物管理                    *\n");
		printf("\t         *                   4.货物盘点                    *\n");
		printf("\t         *                   5.供应商管理                  *\n");
		printf("\t         *                   6.报表生成                    *\n");
		printf("\t         *                   7.返回                        *\n");
		printf("\t         *                   0.退出系统                    *\n");
	    printf("\t         ***************************************************\n\n");
	    printf("请选择：");
} 

void menu()
{
	int a;
	while(1)
	{
		menu1();
	    scanf("%d",&a);  
	    fflush(stdin);
	    switch (a)
      {
        case 1:
		    	gin(); 
				system("pause");
				system("cls");
				break;
        case 2: 
        	    system("cls");
			    gout();
			    system("pause");
			    system("cls");
				break;
        case 3: 
                system("cls");
				manage();
				system("pause");
				system("cls");
				break;
    	case 4:  
				inventory_menu();
				system("pause");
				system("cls");
				break;
    	case 5:   
    	        system("cls");
				Supplier_Menu();
				system("pause");
				system("cls");
				break;
    	case 6: 
    	        system("cls");
				print_menu();
				system("pause");
				system("cls");
				break;
		case 7:   //返回上一菜单 
	         	system("cls");
	         	denglu1();//上一菜单函数 
				break;
		case 0:   //退出 
	         	quit();
				break;		
    	default:  
				printf("输入无效！");
				system("pause");
				system("cls");
				break; 	
	  }
   }
} 

void gin() {
    good *p = head;
    int n;
    printf("\n请输入要录入的货物个数：");
    scanf("%d", &n);
    // 找到链表尾部
    while (p->next != NULL) {
        p = p->next;
    }
    good *q = p;
    for (int m = 0; m < n; m++) {
        good *s = (good*)malloc(sizeof(good));
        if (!s) {
            printf("\n内存分配失败");
            return;
        }
        q->next = s;
        s->next = NULL;
        q = s;
        printf("\n正在录入第 %d 个货物信息：\n", m + 1);
        printf("\n请输入货物名称（英文）：");
		getchar(); // 吃掉上一个回车
		fgets(s->name, sizeof(s->name), stdin);
		s->name[strcspn(s->name, "\n")] = '\0'; // 删除末尾换行
        printf("\n请输入货物体积（立方米）：");
        scanf("%f", &s->volume);
        printf("\n请输入货物重量（千克）：");
        scanf("%f", &s->weight);
        printf("\n请输入货物价格（元）：");
        scanf("%f", &s->price);
        printf("\n请输入货物保质期（年）：");
        scanf("%d", &s->year);
        printf("\n请输入采购人姓名：");
        scanf("%s", s->buyname);
        printf("\n请输入验收人姓名：");
        scanf("%s", s->recname);
        printf("\n请输入入库日期（年 月 日）：");
        scanf("%d %d %d", &s->intime.year, &s->intime.month, &s->intime.day);
        s->outtime.year=0; 
		s->outtime.month=0;
		s->outtime.day=0;
        printf("\n请输入生产厂家：");
        scanf("%s", s->factory);
        generate_code(head, s);
        
        printf("\n第%d个货物信息录入成功\n", m + 1);
    }
    writegoodfile(1);
    printf("\n货物信息已全部录入完毕\n");
    return;
}

int get_smallest_available_suffix(good *head, const char *name) {
    int used[1000] = {0};  // 标记001~999是否已用

    good *p = head->next;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0) {
            // 提取后三位编号
            const char *num = p->num;
            int len = strlen(num);
            if (len >= 3) {
                int suffix = atoi(num + len - 3);
                if (suffix > 0 && suffix < 1000) {
                    used[suffix] = 1;
                }
            }
        }
        p = p->next;
    }

    // 找最小未使用的编号
    for (int i = 1; i < 1000; i++) {
        if (!used[i]) {
            return i;
        }
    }

    return 999; // 超出限制了
}


void generate_code(good *head, good *s) {
    char code[100] = {0};
    char class_type;

    // 1. 分类判断
    if (s->volume >= 1 || s->weight >= 15)
        class_type = 'A';
    else if (s->volume >= 0.5 || s->weight >= 10)
        class_type = 'B';
    else
        class_type = 'C';

    // 2. 日期 + 类别字母
    sprintf(code, "%04d%02d%02d%c", s->intime.year, s->intime.month, s->intime.day, class_type);

    // 3. 提取名称首字母，最多3个，不足补 '_'
    char initials[4] = {'_', '_', '_', '\0'};
    int idx = 0;
    char name_copy[30];
    strncpy(name_copy, s->name, sizeof(name_copy) - 1);
    name_copy[sizeof(name_copy) - 1] = '\0';

    char *token = strtok(name_copy, " ");
    while (token != NULL && idx < 3) {
        initials[idx++] = toupper(token[0]);
        token = strtok(NULL, " ");
    }

    strcat(code, initials);  // 追加首字母

    // 4. 同名编号（从000开始）
    int suffix_num = get_smallest_available_suffix(head, s->name);
	char suffix[4];
	sprintf(suffix, "%03d", suffix_num);

    strcat(code, suffix);  // 拼接编号

    // 5. 最终赋值
    strcpy(s->num, code); // 编码
    sprintf(s->place, "%c%s%s", class_type, initials, suffix); // 存放地点
}




void gout() {
	system(); 
	readoutfile();
    int choice;
	printf("\t    ************************出库页面*********************\n");
	printf("\t    *                   1.按货物编号出库                *\n");
	printf("\t    *                   2.按货物名称和数量出库          *\n");
	printf("\t    *                   3.返回                          *\n");
	printf("\t    *                   4.退出                          *\n");
	printf("\t    *****************************************************");
	printf("\n\n请选择：");
    scanf("%d", &choice);
    if (choice == 1) {
        gout_by_num();
    } else if (choice == 2) {
        gout_by_name_and_count();
    } else if (choice == 3){
    	system("cls");
    	menu1();
	} else if (choice == 4){
		quit();
    } else {
        printf("无效选项\n");
    }
}

void gout_by_num() {
    char search_num[20];
    printf("\n请输入要出库的货物编号：");
    scanf("%s", search_num);

    good *p = head->next;
    while (p != NULL) {
        if (strcmp(p->num, search_num) == 0) {
            if (p->outtime.year != 0) {
                printf("该货物已出库，不能重复出库\n");
                return;
            }

            printf("请输入出库日期（年 月 日）：");
            scanf("%d %d %d", &p->outtime.year, &p->outtime.month, &p->outtime.day);
            writegoodfile(1);
            add_out_record(p);
            writeOutgoodfile(1); 
            free_out_list(); 
            printf("货物 %s（编号：%s）出库成功\n", p->name, p->num);
            return;
        }
        p = p->next;
    }
    printf("未找到编号为 %s 的货物\n", search_num);
}

void gout_by_name_and_count() {
    int original_request_count;
    char search_name[30];
    int count, matched = 0;

    printf("请输入要出库的货物名称（英文）：");
    getchar();  // 吃掉残留换行
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = '\0';  // 去掉换行

    printf("请输入要出库的数量：");
    scanf("%d", &original_request_count);
    count = original_request_count;

    // 第一次遍历：收集所有匹配且未出库的货物
    good *matches[1000];  // 假设最多1000个匹配项
    int total_matches = 0;

    good *p = head->next;
    while (p != NULL) {
        if (strcasecmp(p->name, search_name) == 0 && p->outtime.year == 0) {
            matches[total_matches++] = p;
        }
        p = p->next;
    }

    // 从后往前出库
    for (int i = total_matches - 1; i >= 0 && count > 0; i--) {
        good *match = matches[i];
        printf("为货物 %s（编号：%s）设置出库日期（年 月 日）：", match->name, match->num);
        scanf("%d %d %d", &match->outtime.year, &match->outtime.month, &match->outtime.day);
        add_out_record(match);
        matched++;
        count--;
    }

    if (matched > 0) {
        writegoodfile(1);
        writeOutgoodfile(1); 
        free_out_list(); 

        if (matched < original_request_count) {
            printf("只成功出库了 %d 个货物，库存不足（原本请求 %d 个）\n", matched, original_request_count);
        } else {
            printf("成功出库 %d 个货物\n", matched);
        }
    } else {
        printf("未找到该货物\n");
    }
}

void add_out_record(good *g) {
    outgood *newout = (outgood*)malloc(sizeof(outgood));
    if (!newout) {
        printf("内存分配失败，出库记录创建失败\n");
        return;
    }

    strcpy(newout->num, g->num);
    strcpy(newout->name, g->name);
    newout->outtime = g->outtime;

    printf("请输入货物去向：");
    scanf("%s", newout->use);

    printf("请输入联系方式：");
    scanf("%s", newout->tel);

    newout->outnext = NULL;

    outgood *q = outhead;
    while (q->outnext != NULL) {
        q = q->outnext;
    }
    q->outnext = newout;
}

void free_out_list() {
    outgood *p = outhead->outnext;
    while (p != NULL) {
        outgood *temp = p;
        p = p->outnext;
        free(temp);
    }
}


void Register()//管理员注册 
{
		user *uhead=(user*)malloc(sizeof(user));
		uhead->unext=NULL;
		user *p = uhead;
		p->unext=(user*)malloc(sizeof(user));//用链表存储管理员的信息 
		p=p->unext;
		printf("请输入要注册的管理员名：\n" );
		scanf("%s",p->name);
		printf("请输入密码\n" );
	    scanf("%s",p->pwd);
	    printf("请输入联系方式\n" );
	    scanf("%s",p->tel);
	    printf("请输入地址\n" );
	    scanf("%s",p->home);
	    FILE *fw=fopen("管理员信息.txt","r");
	  if(fw==NULL)
	  	 {
		   	printf("文件打开失败！");
		   	exit(0);
	  	 }
		user *q=uhead;//让q指向头 
     while(!feof(fw)) //打开文件读取 
     {
     	q->unext=(user*)malloc(sizeof(user));
		q->unext->unext=NULL;//创建完节点后赋空 
		q=q->unext;
		fscanf(fw,"%s %s %s %s\n",q->name,q->pwd,q->tel,q->home);//用链表来存储读取到的内容 
     	if(strcmp(q->name,p->name) == 0)//判断管理员姓名是否被注册过 
     	{
     		printf("管理员姓名重复请重新输入\n");
     		system("pause");
     		return;
		}
	 }
	 fclose(fw);
    //和之前的信息比较是否重复
	//判断是否重复到此结束	
	
	//把管理员的信息录入文件 
	 FILE *fp=fopen("管理员信息.txt","a+");
	  if(fp==NULL)
	   {
	   	printf("文件打开失败！");
	   	exit(0);
	   }
	   else
	   {
	   	fprintf(fp,"\n%s %s %s %s",p->name,p->pwd,p->tel,p->home);
	   }
	   fclose(fp);
	   system("pause");
	   system("cls");
}
void manager22()
{
	system(); 
		printf("\t    ****************经理页面****************\n");
		printf("\t    *         1.浏览管理员信息             *\n");
		printf("\t    *         2.增加管理员                 *\n");
		printf("\t    *         3.删除管理员                 *\n");
		printf("\t    *         4.返回                       *\n");
		printf("\t    *         5.退出                       *\n");
		printf("\t    ****************************************\n");
		printf("\n\n请选择：");
}
void manager2()//经理操作 
{
		while(1)
	{
		manager22();
		int  num;
		scanf("%d",&num);
		fflush(stdin);
		switch(num)
		{
			case 1:
					readuser();
					system("pause"); 
					system("cls");
					break;
			case 2:
					adduser();
					system("pause"); 
					system("cls");
					break;
			case 3:
					Deleteuser();
					system("pause");
					system("cls");
					break;
			case 4: 
					system("cls"); 
					denglu0();
					break;
			case 5: 
					quit();
					break;		
			default:
					 printf("无效输入！"); 
					 system("pause");
					 system("cls"); 
					 denglu1();
        }
	}
}
void readuser()//经理读取管理员信息 
{
		FILE *fp=fopen("管理员信息.txt","r");
		user *p=uhead;
		char ch;
		ch=fgetc(fp);
		if(ch==EOF)
		{
			printf("无管理员信息！");
			return ;
		}
		rewind(fp); 
		while(!feof(fp))
		{
		p->unext=(user *)malloc(sizeof(user));
		p=p->unext;
		fscanf(fp,"%s %s %s %s\n",p->name,p->pwd,p->tel,p->home);
		p->unext=NULL;
		}
		fclose(fp);
		p=uhead->unext;
		printf("姓名\t密码\t联系方式\t联系地址\n"); 
		while(p != NULL)
		{
			printf("%s\t%s\t%s\t%s\n",p->name,p->pwd,p->tel,p->home);
			printf("\n");
			p = p->unext;
		}
		return;
}
void adduser()
{
	char name[20];
	char password[20];
	char tel[12];
	char home[50];
	printf("请输入要增加的管理员名：\n" );
	scanf("%s",name);
	printf("请输入密码\n" );
    scanf("%s",password);
    printf("请输入联系方式\n");
	scanf("%s",tel);
	printf("请输入联系地址\n");
	scanf("%s",home); 
    user *p=uhead; 
    	/*查重*/ 
    	FILE *fp=fopen("管理员信息.txt","r");
    	while(!feof(fp))
		{
			p->unext=(user *)malloc(sizeof(user));
			p=p->unext;
			fscanf(fp,"%s %s %s %s\n",p->name,p->pwd,p->tel,p->home);
			p->unext=NULL;
		}
		fclose(fp);
		p=uhead->unext;
		while(p!=NULL)
		{
			if(strcmp(p->name,name)==0)
			{
				printf("该管理员已存在请重新输入！\n");
				printf("请输入要增加的管理员名：\n" );
				scanf("%s",name);
				printf("请输入密码\n");
				scanf("%s",password);
				printf("请输入联系方式\n");
	            scanf("%s",tel);
	            printf("请输入联系地址\n");
	            scanf("%s",home);
				continue;
			}
			p=p->unext;
		}
    	FILE *fw=fopen("管理员信息.txt","a+");
	  	if(fw==NULL)
	   	{
	   	printf("文件打开失败！");
	   	exit(0);
	   	}
	   else
	   {
	   		fprintf(fw,"\n%s %s %s %s",name,password,tel,home);
	   		printf("\n添加成功！");
	   }
	   fclose(fw);		
}

void Deleteuser()
{
	printf("请输入你要删除的管理员姓名：\n");
	char  name[20];
	scanf("%s",name);
	int flag=1; 
	user *p=uhead;
	FILE *fp=fopen("管理员信息.txt","r");
	while(!feof(fp))
	{
		p->unext=(user*)malloc(sizeof(user));
	    p=p->unext;
	    fscanf(fp,"%s %s %s %s\n",p->name,p->pwd,p->tel,p->home);
	    p->unext=NULL;
	}
	fclose(fp);
	p=uhead->unext;
	user *q=uhead;
	while(p != NULL)
	{
		if(strcmp(p->name,name) == 0)
	   {
		    q->unext=p->unext;                                                                             
			free(p);
			flag=0;
			printf("删除成功\n");
		    break;
       }
		q=q->unext;
		p=p->unext;
    }
    
       if(flag == 1 )
		{
		printf("未找到该管理员删除失败\n");
		return ;
		}
    	FILE *fw=fopen("管理员信息.txt","w");//管理员信息刷新 
    	q = uhead->unext;
    	while(q != NULL)
    	{
    	fprintf(fw,"%s %s %s %s\n",q->name,q->pwd,q->tel,q->home);
    	q =q->unext;
	    }
	    fclose(fw);
}

void system()
{
	system("color f1");
	system("date/t");
	system("time/t");
	system("title 仓库管理系统");
}

void quit()//退出系统 
{
	int a=3;
	printf(" 秒后关闭程序"); 
	while(--a>=1)
	{
		printf("\r%d",a);
		printf("\b");
		Sleep(1000);
	}
		system("cls");
		printf("感谢您的使用！再见\n");
		exit(0);
}

void searchSuplier(char* name){
    pro* p1=phead;
    while(p1!=NULL){
        if(strcmp(p1->name,name)==0){
            cout<<"供应商名称："<<p1->name<<endl;
            cout<<"联系方式："<<p1->tel<<endl;
            return;
        }
        p1=p1->pnext;
    }
    cout<<"该供应商不存在！"<<endl;
    cout<<"请重新查询！"<<endl; 
}
// 获取字符串的显示宽度（考虑中文字符）
int getDisplayWidth(const std::string& str) {
    int width = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = static_cast<unsigned char>(str[i]);
        if (c < 0x80) { // ASCII字符
            width += 1;
            i += 1;
        } else { //中文字符 
            width += 2;
            i += 2;
        }
    }
    return width;
}
void scanSupplier(){
    pro* p1 = phead->pnext;
    if (!p1) {
        cout << "没有供应商信息！" << endl;
        return;
    }
    int maxNameWidth = 0;//计算最大宽度 
    pro* current = p1;
    while (current) {
        int currentWidth = getDisplayWidth(current->name);
        if (currentWidth > maxNameWidth) {
            maxNameWidth = currentWidth;
        }
        current = current->pnext;
    }

    // 添加额外间隔（4个空格宽度）
    int totalWidth = maxNameWidth + 4;

    // 打印标题
    cout << "供应商信息" << endl;
    cout << "--------------------------------------------------" << endl;
    
    // 打印供应商信息
    current = p1;
    while (current) {
        // 打印供应商名称并填充空格
        cout << current->name;
        int currentWidth = getDisplayWidth(current->name);
        int spaceCount = totalWidth - currentWidth;
        for (int i = 0; i < spaceCount; ++i) {
            cout << ' ';
        }
        
        // 打印电话号码
        cout << current->tel << endl;
        current = current->pnext;
    }
    cout << "--------------------------------------------------" << endl;
}
void addSupplier(string name,string tel){
     pro* p1=pend;
  p1->pnext=(pro*)malloc(sizeof(pro));
  strcpy(p1->pnext->name,name.c_str());
  strcpy(p1->pnext->tel,tel.c_str());
  p1->pnext->pnext=NULL;
  cout<<"成功添加供应商！"<<endl;
  writeProFile(1);
}
void Supplier_Menu(){
	readprofile();
    int choice;
    while(1){
    	system();
	    printf("\t    **********************供应商管理界面*******************\n");
			printf("\t    *                        1.查询供应商信息                     *\n");
			printf("\t    *                        2.浏览供应商信息                     *\n");
			printf("\t    *                        3.添加供应商信息                     *\n");
			printf("\t    *                        4.返回                               *\n");
			printf("\t    *                        0.退出系统                           *\n");
			printf("\t    *****************************************************");
			printf("\n\n请选择：");
	        cin>>choice;
	        switch(choice){
	            case 1:{
	                char name[50];
	                printf("请输入供应商名称：");
	                cin>>name;
	                searchSuplier(name);
	                break;
	            }
	            case 2:{
	                scanSupplier();
	                break;
	            }
	            case 3:{
	                string name,tel;
	                printf("请输入供应商名称：");
	                cin>>name;
	                printf("请输入供应商联系方式：");
	                cin>>tel;
	                addSupplier(name,tel);
	                break;
	            }
	            case 4:{
	            	system("cls");
	            	menu();
					break;
				}
				case 0:{
					quit(); 
					break;
				}
	            default:{
	                printf("输入错误！");
	                break;
	            }
	    }
	    system("pause");
	    system("cls");
	}
}
void print_menu(){
    int choice;
    system(); 
    printf("\t    ************************报表打印界面*************************\n");
		printf("\t    *                        1.入库报表                         *\n");
		printf("\t    *                        2.出库报表                         *\n");
		printf("\t    *                        3.返回                             *\n");
		printf("\t    *                        0.退出系统                         *\n");
	printf("\t    *************************************************************");
		printf("\n\n请选择：");
        cin>>choice;
        switch(choice){
            case 1:
                printIn();
                break;
            case 2:
                printOut();
                break;
            case 3:
            	system("cls");
                menu();
                break;
            case 0:{
            	quit();
				break;
			} 
            default:
                printf("输入错误！");
                break;
    }   
}
void printIn() {
    int year;
    printf("请选择要导出的入库报表年份：");
    scanf("%d", &year);
    
    // 创建文件名
    char filename[50];
    sprintf(filename, "入库报表_%d.txt", year);
    
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法创建文件！\n");
        return;
    }
    
    int count = 0;
    // 写入表头
    fprintf(fp, "%-15s %-62s %-8s %-8s %-10s %-8s %-10s %-10s %-10s %-15s %-20s\n",
           "编号", "名称", "体积", "重量", "价格", "保质期", "采购人", "验收人", "存放地点", "入库日期", "生产厂家");
    fprintf(fp, "---------------------------------------------------------------------------------------------------------------\n");
    
    good* p = head->next;
    while (p != NULL) {
        if (p->intime.year == year) {
            count++;
            char inDate[20];
            sprintf(inDate, "%04d-%02d-%02d", p->intime.year, p->intime.month, p->intime.day);
            
            fprintf(fp, "%s\t%s\t%f\t%f\t%f\t%d\t%s\t%s\t%s\t%s\t%s\n",
                   p->num, p->name, p->volume, p->weight, p->price,
                   p->year, p->buyname, p->recname, p->place, inDate, p->factory);
        }
        p = p->next;
    }
    
    fprintf(fp, "---------------------------------------------------------------------------------------------------------------\n");
    fprintf(fp, "总计：%d条入库记录\n", count);
    
    fclose(fp);
    printf("入库报表已成功导出到文件：%s\n", filename);
}

void printOut() {
	readoutfile(); 
    if (outhead == NULL || outhead->outnext == NULL) {
        printf("出库信息为空！\n");
        return;
    }

    int year;
    printf("请选择要导出的出库报表年份：");
    scanf("%d", &year);

    char filename[50];
    sprintf(filename, "出库报表_%d.txt", year);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法创建文件！\n");
        return;
    }

    int count = 0;
    fprintf(fp, "%-15s %-62s %-15s %-15s %-15s\n",
           "编号", "名称", "出库日期", "去向", "联系方式");
    fprintf(fp, "--------------------------------------------------------------------\n");

    outgood* p = outhead->outnext; // 从头节点的下一个节点开始遍历
    while (p != NULL) {
        if (p->outtime.year == year) {
            count++;
            char outDate[20];
            sprintf(outDate, "%04d-%02d-%02d", p->outtime.year, p->outtime.month, p->outtime.day);

            fprintf(fp, "%-15s %-62s %-15s %-15s %-15s\n",
                   p->num, p->name, outDate, p->use, p->tel);
        }
        p = p->outnext;
    }
	free_out_list();
    fprintf(fp, "--------------------------------------------------------------------\n");
    fprintf(fp, "总计：%d条出库记录\n", count);

    fclose(fp);
    printf("出库报表已成功导出到文件：%s\n", filename);
}
// 判断商品是否过期 output()内调用
bool is_expired(good *item, int current_year, int current_month, int current_day) {
    // 计算到期日期
    int expire_year = item->intime.year + item->year;
    int expire_month = item->intime.month;
    int expire_day = item->intime.day;

    // 比较当前日期和到期日期
    if (current_year > expire_year) {
        return true;
    } else if (current_year == expire_year) {
        if (current_month > expire_month) {
            return true;
        } else if (current_month == expire_month) {
            if (current_day > expire_day) {
                return true;
            }
        }
    }
    return false;
}

void inventory_menu() {
    while(1)
	{
		
		int choice;
	system("cls");
    system(); 
    printf("\t    ************************货物盘点界面*************************\n");
    printf("\t    *                        1.删除已出库信息                   *\n");
    printf("\t    *                        2.查找报废货物                     *\n");
    printf("\t    *                        3.返回                             *\n");
    printf("\t    *                        0.退出系统                         *\n");
    printf("\t    *************************************************************\n");
    printf("\n请选择：");
    scanf("%d", &choice);
    fflush(stdin);
    switch(choice) {
        case 1:
            deleteOutboundGoods();
             system("pause");
            system("cls");
            break;
        case 2:
        	 output();
			 system("pause");
            system("cls"); 
            break;
        case 0:
            quit();
            break;
        default:
            printf("输入错误！");
            getchar(); // 清除输入缓冲区
            getchar(); // 等待用户按任意键
            inventory_menu();
            break;
    }
	 } 
}
void deleteOutboundGoods() {//删除货物信息中已出库的货物 
    if (head == NULL || head->next == NULL) {
        printf("货物列表为空！\n");
        return;
    }
    
    good *p = head->next;  // 第一个实际货物节点
    good *prev = head;      // 前驱节点
    
    while (p != NULL) {
        // 检查出库时间是否为非0-0-0（表示已出库）
        if (p->outtime.year != 0 || p->outtime.month != 0 || p->outtime.day != 0) {
            // 从链表中删除该节点
            prev->next = p->next;
            good *temp = p;
            p = p->next;
            free(temp);
        } else {
            prev = p;
            p = p->next;
        }
    }
    
    // 将剩余未出库货物信息覆盖写入文件
    writegoodfile(1);
    printf("已删除所有出库货物信息并更新文件！\n");
}


//显示报废货物信息
void output() 
{
    readgoodfile();
	printf("正在检索请等待\n");
    printf("编号\t名称\t大小\t重量\t价格\t保质期\t采购人\t验收人\t存放地点\t入库日期\t出库日期\t生产厂家\n"); 

	time_t raw_time;
    struct tm *time_info;
    time(&raw_time);    // 获取当前时间
    time_info = localtime(&raw_time);
    // 直接从 tm 结构体获取年月日
    int year = time_info->tm_year + 1900;
    int month = time_info->tm_mon + 1;
    int day = time_info->tm_mday;

    good *p=head->next;
	int expired_count=0;
    while (p != NULL) {
        if (is_expired(p, year, month, day)) {
            printf("%s\t%s\t%.1f\t%.1f\t%.1f\t%d\t%s\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%s\n",
                   p->num, p->name, p->volume, p->weight, p->price, p->year,
                   p->buyname, p->recname, p->place,
                   p->intime.year, p->intime.month, p->intime.day,
                   p->outtime.year, p->outtime.month, p->outtime.day,
                   p->factory);
            expired_count++;
        }
        p = p->next;
    }

    if (expired_count == 0) {
        printf("没有过期商品！\n");
    } else {
        printf("已显示%d个过期商品！\n", expired_count);
    }
    
	return;
}

// 比较函数（用于qsort按编号排序）
int compare_by_num(const void *a, const void *b) {
    good *ga = *(good **)a;
    good *gb = *(good **)b;
    return strcmp(ga->num, gb->num);
}

// 比较函数（用于qsort按名称排序）
int compare_by_name(const void *a, const void *b) {
    good *ga = *(good **)a;
    good *gb = *(good **)b;
    return strcmp(ga->name, gb->name);
}

// 比较函数（用于qsort按区域排序）
int compare_by_place(const void *a, const void *b) {
    good *ga = *(good **)a;
    good *gb = *(good **)b;
    return strcmp(ga->place, gb->place);
}

// 比较函数（用于qsort按厂家排序）
int compare_by_factory(const void *a, const void *b) {
    good *ga = *(good **)a;
    good *gb = *(good **)b;
    return strcmp(ga->factory, gb->factory);
}

// 比较函数（按入库时间排序）
int compare_by_time(const void *a, const void *b) {
    good *ga = *(good **)a;
    good *gb = *(good **)b;
    
    // 先比较年
    if (ga->intime.year != gb->intime.year) {
        return ga->intime.year - gb->intime.year;
    }
    // 再比较月
    if (ga->intime.month != gb->intime.month) {
        return ga->intime.month - gb->intime.month;
    }
    // 最后比较日
    return ga->intime.day - gb->intime.day;
}

int result_count = 0;

// 查找最左端索引
int binary_search_left(good **arr, int size, const char *target,
                     int (*compare)(const void *, const void *), int field_type) {
    int left = 0, right = size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp;
        
        // 根据字段类型进行比较
        switch(field_type) {
            case 0:  // 按编号比较
                cmp = strcmp(arr[mid]->num, target);
                break;
            case 1:  // 按名称比较
                cmp = strcmp(arr[mid]->name, target);
                break;
            case 2:  // 按区域比较
                cmp = strcmp(arr[mid]->place, target);
                break;
            case 3:  // 按厂家比较
                cmp = strcmp(arr[mid]->factory, target);
                break;
            default:
                return -1;
        }

        if (cmp == 0) {
            result = mid;
            right = mid - 1;  // 继续在左半边查找
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// 查找最右端索引
int binary_search_right(good **arr, int size, const char *target,
                      int (*compare)(const void *, const void *), int field_type) {
    int left = 0, right = size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp;
        
        // 根据字段类型进行比较
        switch(field_type) {
            case 0:  // 按编号比较
                cmp = strcmp(arr[mid]->num, target);
                break;
            case 1:  // 按名称比较
                cmp = strcmp(arr[mid]->name, target);
                break;
            case 2:  // 按区域比较
                cmp = strcmp(arr[mid]->place, target);
                break;
            case 3:  // 按厂家比较
                cmp = strcmp(arr[mid]->factory, target);
                break;
            default:
                return -1;
        }

        if (cmp == 0) {
            result = mid;
            left = mid + 1;  // 继续在右半边查找
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// 搜索函数 调用快排+二分

good **search_good(const char *target, int (*compare)(const void *, const void *),
                 int (*convert)(good *, char *), int field_type, 
                 good **arr, int count, int *result_count) {
    *result_count = 0;
    if (count == 0 || arr == NULL) {
        return NULL;
    }

    qsort(arr, count, sizeof(good *), compare);

    int left = binary_search_left(arr, count, target, compare, field_type);
    //printf("%d\n", left);
    if (left == -1) {
        return NULL;
    }
   
    int right = binary_search_right(arr, count, target, compare, field_type);
    *result_count = right - left + 1;
    //printf("%d\n", right);
    return &arr[left]; // 返回匹配范围的起始指针
}

// 查询函数
good **search_by_num(const char *target_num, good **arr, int count, int *result_count) {
    return search_good(target_num, compare_by_num, NULL, 0, arr, count, result_count);
}

good **search_by_name(const char *target_name, good **arr, int count, int *result_count) {
    return search_good(target_name, compare_by_name, NULL, 1, arr, count, result_count);
}

good **search_by_place(const char *target_place, good **arr, int count, int *result_count) {
    return search_good(target_place, compare_by_place, NULL, 2, arr, count, result_count);
}

good **search_by_factory(const char *target_factory, good **arr, int count, int *result_count) {
    return search_good(target_factory, compare_by_factory, NULL, 3, arr, count, result_count);
}

// 去除字符串末尾的空白字符（空格、制表符、换行符等）
void trim_trailing_whitespace(char *str) {
    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';
}
// 将链表转换为数组
good **list_to_array(int *count) {
    if (head == NULL || head->next == NULL) {
        *count = 0;
        return NULL;
    }

    *count = 0;
    good *p = head->next;
    while (p != NULL) {
        (*count)++;
        p = p->next;
    }

    good **arr = (good **)malloc((*count) * sizeof(good *));
    if (arr == NULL) {
        *count = 0;
        return NULL;
    }

    p = head->next;
    for (int i = 0; i < *count; i++) {
        arr[i] = p;
        trim_trailing_whitespace(arr[i]->name);  // 清理名称
        p = p->next;
    }
    return arr;
}

// 打印商品信息
void print_good(good *p) {
    if (p == NULL) {
        printf("商品不存在！\n");
        return;
    }

    printf("%-20s %-30s %6.1f %6.1f %7.1f %6d %-8s %-8s %-10s %04d-%02d-%02d  %04d-%02d-%02d  %-20s\n",
        p->num,
        p->name,
        p->volume,
        p->weight,
        p->price,
        p->year,
        p->buyname,
        p->recname,
        p->place,
        p->intime.year, p->intime.month, p->intime.day,
        p->outtime.year, p->outtime.month, p->outtime.day,
        p->factory);
}

void print_all_matching_goods(good **matches, int count) {
    if (matches == NULL || count <= 0) {
        printf("未找到匹配的商品！\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        print_good(matches[i]);
    }
}

// 打印表头
void print_header() {
    printf("%-20s %-30s %6s %6s %7s %4s %-8s %-8s %-10s %9s  %9s  %20s\n",
        "编号", "名称", "大小", "重量", "价格", "保质期", 
        "采购人", "验收人", "存放地点", "入库日期", "出库日期", "生产厂家");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

// 按名称排序并打印
void print_sorted_by_name(good **arr, int count) {
    if (arr == NULL || count == 0) {
        printf("没有商品信息可显示\n");
        return;
    }

    qsort(arr, count, sizeof(good *), compare_by_name);

    printf("\t    **********************按名称排序的商品列表*******************\n");
    print_header();
    for (int i = 0; i < count; i++) {
        print_good(arr[i]);
    }
}

// 按入库时间排序并打印
void print_sorted_by_time(good **arr, int count) {
    if (arr == NULL || count == 0) {
        printf("没有商品信息可显示\n");
        return;
    }

    qsort(arr, count, sizeof(good *), compare_by_time);

    printf("\t    **********************按入库时间排序的商品列表*******************\n");
    print_header();
    for (int i = 0; i < count; i++) {
        print_good(arr[i]);
    }
}

// 商品分类浏览
void browse_by_category()
{
    int choice;
    
    int count;
    good **arr = list_to_array(&count);
    while (1) {
        printf("\t    **********************商品分类浏览*******************\n");
		printf("\t    *                     1.按名称浏览                  *\n");
		printf("\t    *                     2.按入库时间浏览              *\n");
		printf("\t    *                     3.返回                        *\n");
        printf("\t    *                     0.退出                        *\n");
		printf("\t    *****************************************************");
		printf("\n\n请选择浏览方式：");
        
        if (scanf("%d", &choice) != 1) {
            printf("输入错误，请重新输入！\n");
            while (getchar() != '\n'); // 清空输入缓冲区
            continue;
        }
        
        switch (choice) {
            case 1:
                print_sorted_by_name(arr, count);
                system("pause");
				system("cls");
                break;
            case 2:
                print_sorted_by_time(arr, count);
                system("pause");
				system("cls");
                break;
			case 3:   //返回上一菜单 
	         	system("cls");
	         	manage();//上一菜单函数 
				break;
			case 0:   //退出 
	         	quit();
				break;		
    		default:  
				printf("输入无效！");
				system("pause");
				system("cls");
				break; 
        }
    }
    free(arr);
}

// 查询菜单
void select_menu() {
    char choice;
    char input[50];
    
    int count;
    good **arr = list_to_array(&count);

    while (1) {
    	system(); 
        printf("\t    **********************请选择查询方式*******************\n");
		printf("\t    *                     1.按编号查询                    *\n");
		printf("\t    *                     2.按名称查询                    *\n");
		printf("\t    *                     3.按区域查询                    *\n");
        printf("\t    *                     4.按厂家查询                    *\n");
        printf("\t    *                     5.返回                          *\n");
        printf("\t    *                     0.退出                          *\n");
		printf("\t    *****************************************************");
		printf("\n\n请选择：");

        scanf("%c", &choice);
        fflush(stdin);
good **first_match;
		
        switch (choice) {
            case '1':
                printf("请输入货物编号：");
    			fgets(input, sizeof(input), stdin);
    			input[strcspn(input, "\n")] = '\0'; 
                print_header();
                result_count = 0;
                first_match = search_by_num(input, arr, count, &result_count);
                print_all_matching_goods(first_match, result_count);
                system("pause");
				system("cls");
                break;
            case '2':
   				printf("请输入货物名称：");
    			fgets(input, sizeof(input), stdin);
    			input[strcspn(input, "\n")] = '\0';  
    			print_header();
    			result_count = 0;
    			first_match = search_by_name(input, arr, count, &result_count);
    			print_all_matching_goods(first_match, result_count);
    			system("pause");
				system("cls");
   				break;
            case '3':
                printf("请输入存放区域：");
                scanf("%s", input);
                fflush(stdin);
                print_header();
                result_count = 0;
                first_match = search_by_place(input, arr, count, &result_count);
                print_all_matching_goods(first_match, result_count);
                system("pause");
				system("cls");
                break;
            case '4':
                printf("请输入生产厂家：");
                scanf("%s", input);
                fflush(stdin);
                print_header();
                result_count = 0;
                first_match = search_by_factory(input, arr, count, &result_count);
                print_all_matching_goods(first_match, result_count);
                system("pause");
				system("cls");
                break;
            case '5':   //返回上一菜单 
	         	system("cls");
	         	manage();//上一菜单函数 
				break;
			case '0':   //退出 
	         	quit();
				break;		
    		default:  
				printf("输入无效！");
				system("pause");
				system("cls");
				break; 
        }
    }
    // 释放数组内存
    free(arr);
}

// 删除货物
void Delete()
{
	printf("请输入你要删除的货物编号：\n");  //调用查找编号
	char target[20];
	scanf("%s", target);

	fflush(stdin);
	good *q=head;
	int flag=1;//用flag判断是否删除成功 

	while(q->next != NULL)
	{
	if(strcmp(q->next->num, target) == 0)
	   {
		  	q->next=q->next->next;   //如果q的下一个节点是要找的编号那么把q->next赋值为下下个                                                                                       
			flag=0;
			printf("删除成功\n");
			writegoodfile(1);
		    return ;
     	}
			q=q->next;
    }
		if(flag == 1 )
		{
		printf("未找到该货物删除失败\n");
		return ;
		}	
}

// 商品管理界面
void manage()
{
    while(1){
    	system();
        printf("\t    **********************货物管理页面*******************\n");
	    printf("\t    *                     1.货物查找                    *\n");
	    printf("\t    *                     2.货物分类浏览                *\n");
		printf("\t    *                     3.货物信息删除                *\n");
        printf("\t    *                     4.返回                        *\n");
        printf("\t    *                     0.退出                        *\n");
		printf("\t    *****************************************************");
		printf("\n\n请选择：");

        int choice;
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice) {
            case 1:
            	system("cls");
                select_menu();
                system("pause");
				system("cls");
                break;
            case 2:
            	system("cls");
                browse_by_category();
                system("pause");
				system("cls");
                break;
            case 3:
            	system("cls");
                Delete();
                system("pause");
				system("cls");
                break;
            case 4:
                system("cls");
	         	menu();//上一菜单函数 
				break;
			case 0:   //退出 
	         	quit();
				break;		
    		default:  
				printf("输入无效！");
				system("pause");
				system("cls");
				break; 	
        }
    }
}
