#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include"umbrella.hpp"
#include"student.hpp"
#include"teacher.hpp"
#include"test.hpp"

#define MAX_DATA 128
#define MAX_save 2048

struct Address {                 //每个人的基础数据存储
    char name[MAX_DATA];
    char key[MAX_DATA];
    char account[MAX_DATA];
    char character[MAX_DATA];
    int age;
    int classroom;
    int ID;
    int set;  //验证是否注册过
};

struct Database {               //数据库
    struct Address rows[MAX_save];
};

struct  Total{                 //结构体嵌套，不同的文件名区分不同身份的数据表
    FILE *file;
    struct Database *db;
};

void die(const char *message, struct Total *conn){      //出现错误停止运行
    if(errno) {
        perror(message);
    } else {
    	printf("ERROR: %s\n", message);
    }if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
    exit(1);
}
 
void well_fgets(char data[], int num){
    fgets(data, num, stdin);
    char *find=strchr(data, '\n');
    if(find)
        *find='\0';   
}

void Database_write(struct Total *conn){             //写入数据库
    rewind(conn->file);
    int wr=fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(wr!=1) die("Failed to write database.", conn);
    wr=fflush(conn->file);              //保证数据充分写入
    if(wr==-1) die("Cannot flush database.", conn);
}

void Database_str(struct Total *conn, int age, int classroom,int ID, const char *name, const char *key, const char *account,const char *character){
    struct Address *add=&conn->db->rows[ID];             //注册写入数据
    if(add->set) die("Already had,please register", conn);     //防止重复注册
    add->set=1;                  //设该身份被注册过
    char *res=strncpy(add->name, name, MAX_DATA);
    if(!res) die("Error：copy failed", conn);

    res=strncpy(add->key, key, MAX_DATA);
    if(!res) die("Error：copy failed", conn);

    res=strncpy(add->account, account, MAX_DATA);
    if(!res) die("Error：copy failed", conn);

    res=strncpy(add->character, character, MAX_DATA);
    if(!res) die("Error：copy failed", conn);

    add->ID=ID;
    add->age=age;
    add->classroom=classroom;         //各项数据赋值完成
}
			//数据库重载
struct Total *Database_open(const char *filename, char mode){
    struct Total *conn=malloc(sizeof(struct Total));
    if(!conn) die("Error: failed to open database", conn);
    conn->db=malloc(sizeof(struct Database));         //打开存储空间
    if(!conn->db) die("Error: failed to open database", conn);
    if(mode=='s') {                       //打开文件
        conn->file=fopen(filename, "w");
    } else {
        conn->file=fopen(filename, "r+");
        if(conn->file) {
            int r=fread(conn->db, sizeof(struct Database), 1, conn->file);
            if(r!=1) die("Failed to load database.", conn);          //数据载入到db中
        }
    }
    if(!conn->file) die("Failed to open the file", conn);
    return conn;
}
				
void Database_all(struct Total *conn){        //列出所有可以登陆的账户
        int i;
        struct Database *db=conn->db;
        printf("----------------------\n");
        printf("account key character ID name age classment\n");
        for(i=0;i<MAX_save;i++) {
            struct Address *prt=&db->rows[i];
            if(prt->set) {
                printf("%s %s %s %d %s %d %d\n",
                    prt->account, prt->key, prt->character, prt->ID, prt->name, prt->age, prt->classroom);
            }
        }
    }

void Database_register(struct Total *conn, const char*account, const char*key, const char*character){
    	struct Database *db=conn->db;
    	int i=0;
    	for(i=0;i<MAX_save;i++) {
            struct Address *add=&db->rows[i];
            if(add->set) {
    		if(strcmp(add->account,account)==0){
    		     if(strcmp(add->key,key)==0){
        		printf("register succeed!\n");
        		if(strcmp(character,"student")==0)
                		student(add->ID);
        		else if(strcmp(character,"teacher")==0)
        			teacher(add->ID);
                     }else die("please enter the right keyword", conn);
                }    	    
    	    }
         }
}				/*登录*/

void Database_return0(struct Total *conn, int ID){
	struct Address *db=&conn->db->rows[ID];
	if(db->set){
	struct Address add={.ID=ID, .set = 0};
        conn->db->rows[ID]=add;
        }else die("not find information,sign in first", conn);
}

			/*查找的三种模式*/
void Database_find_id(struct Total *conn, int ID){
    struct Address *add = &conn->db->rows[ID];
    if(add->set==1) {
        printf("----------------------\n");
        printf("account key character studentID\n%s %s %s %d\n",
                    add->account, add->key, add->character, add->ID);
    } else {
        die("can`t find the id", conn);
    }
}
                   
void Database_find_class(struct Total *conn, int classroom){
    	int i;
        struct Database *db=conn->db;
        printf("----------------------\n");
        printf("account key character studentID\n");
        for(i=0;i<MAX_save;i++) {
            struct Address *prt=&db->rows[i];
            if(prt->set==1){
            	if(prt->classroom==classroom) 
               	    printf("%s %s %s %d\n",
                    	prt->account, prt->key, prt->character, prt->ID);
            }
        }
}

void Database_find_name(struct Total *conn, const char* name){
    	int i;
        struct Database *db=conn->db;
        printf("----------------------\n");
        for(i=0;i<MAX_save;i++) {
            struct Address *prt=&db->rows[i];
            if(prt->set==1){
            	if(strcmp(prt->name,name)==0) 
                     printf("account key character studentID\n%s %s %s %d\n",
               		 prt->account, prt->key, prt->character, prt->ID);
            }
        }
}                 
			/*查找的三种模式over*/
int main(){
    scan:
    printf("\n===============================\n");
    printf("enter 'r' to sign in\nenter 'w' to register\nenter 'f' to find specific person\nenter 's' to reset\nenter 'l' to list\nenter 'c' to correct data you have set\nenter 'd' to delete one`s data\nenter 'h' for help");
    char mode='0';
    printf("\n===============================\n");
    scanf(" %c", &mode);                                 //确定注册还是登录还是查找
    getchar();
    printf("\nwhat`s the character(student,teacher)\n");
    char filename[8];
    well_fgets(filename,8);                 //确定身份
    getchar();
    if(strcmp(filename,"student")==0)
        printf("student: \n");
    else if(strcmp(filename,"teacher")==0)
        printf("teacher: \n");  		    //防止身份输入错误
    else {printf("didn`t find this character");goto scan;}
    if(mode=='0'){
    	printf("please enter the correct word");
    	goto scan;                  //防止注册登录输入错误
    }
    struct Total *conn=Database_open(filename, mode);           //申请内存空间并打开文件
    FILE *fp;
    int i=0;			        //定义变量
    char name[MAX_DATA];
    int classroom;
    int age;
    int ID;
    char j[1200];
    char key[MAX_DATA];
    char account[MAX_DATA];
    char find_mode[MAX_DATA];
    char com_name[5]="name";
    char com_id[3]="id";
    char com_class[6]="class";
    switch(mode) {
        case 'w':			//登录
            if(test()==1) die("you are a robot!", conn);
            printf("please enter your information: (account)\n");
            well_fgets(account,MAX_DATA);
            printf("please enter your information: (key)\n");
            well_fgets(key,MAX_DATA);
            Database_register(conn, account, key, filename);
            break;
        case 'r': 			//注册
            if(test()==1) die("you are a robot!", conn);
            printf("please enter your information: (name)\n");
            well_fgets(name,MAX_DATA);
            if(atoi(name)!=0) die("please enter right name", conn);
            printf("please enter your information: (account)\n");
            well_fgets(account,MAX_DATA);
            printf("please enter your information: (key)\n");
            well_fgets(key,MAX_DATA);
            printf("please enter your information: (classroom age ID)\n");
            if((scanf(" %d %d %d", &classroom, &age, &ID))==0){   //输入数据
            	printf("please enter right data");
            	break;
            }
            Database_str(conn, age, classroom, ID, name, key, account, filename);
            Database_write(conn);
            printf("\nsigh in succeed\n");
            break;
        case 'h':
            if((fp=fopen("help.txt","r"))==NULL){
		printf("the help.txt can`t open");
		exit(0);
       	    }
	    fread(j,sizeof(char)*1200-1,1,fp);		
            printf(" %s", j);	
	    fclose(fp);
	    break;
        case 'c':			//更改用户
            printf("please enter what id you want to correct: ");
	    scanf("%d", &ID);
	    i=ID;
	    Database_return0(conn, ID);       //更改的set设为0
	    getchar();
    	    printf("please enter your information: (name)\n");
            well_fgets(name,MAX_DATA);
            if(atoi(name)!=0) die("please enter right name", conn);
            printf("please enter your information: (account)\n");
            well_fgets(account,MAX_DATA);
            printf("please enter your information: (key)\n");
            well_fgets(key,MAX_DATA);
            printf("please enter your information: (classroom age ID)\n");
            if((scanf(" %d %d %d", &classroom, &age, &ID))==0){   //输入数据
            	printf("please enter right data");
            	break;
            }
            Database_str(conn, age, classroom, ID, name, key, account, filename);
            Database_write(conn);
            printf("\ncorrect succeed\n");
            break;
        case 'd':		     //删除用户信息
            printf("please enter what id you want to delete: ");
	    scanf("%d", &ID);
            Database_return0(conn, ID);
            break;
        case 'l':		     //列出所有用户
            Database_all(conn);
            break;
        case 'f':		    //查找的三种模式
            printf("\n========================\n");
            printf("enter name to search by name\nenter id to search by ID\nenter class to search by class\n");
            printf("\n========================\n");
            scanf(" %s", find_mode);
            getchar();
            if(strcmp(find_mode,com_name)==0){			//利用比较函数和间接变量j确定输入结果
		printf("please enter name you want to search\n");
		well_fgets(name,MAX_DATA);
		if(atoi(name)!=0) die("please enter right name", conn);
		Database_find_name(conn, name);
		
	    }else if(strcmp(find_mode,com_id)==0){
	    	printf("please enter id you want to search\n");
	    	scanf("%d", &ID);
		Database_find_id(conn, ID);
		
	    }else if(strcmp(find_mode,com_class)==0){
	    	printf("please enter class you want to search\n");
		scanf("%d", &classroom);
		Database_find_class(conn, classroom);
            
            }else die("please enter right searching mode", conn);
	    break;	
        case 's':				//数据库重载
            for(i=0; i < MAX_save; i++) {
                struct Address                 first={.name="NULL", .ID=0, .classroom=0, .age=0, .set=0, .key="NULL", .account="NULL"};
                conn->db->rows[i]=first;
            }
            Database_write(conn);       //保证初始化结束
            break;                   
        default:
            printf("Invalid action");
    }
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
    return 0;
}
