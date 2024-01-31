# 进阶Cday5

[TOC]



## 结构体嵌套二级指针

如下为图详解：

![image-20231122163628862](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231122163628862.png)

​    练习：

```
#include<stdio.h>
#include <string.h>
#include<stdlib.h>

struct Teacher
{
    char *name;     //当作数组使用
    char **student;      //当作指针数组使用
};

int arr_space(struct Teacher ***temp)
{
    if(NULL == temp)
    {   //错误码，得知哪里发生的错误
        return -1;
    }
    struct Teacher **ts = malloc(sizeof(struct Teacher *) * 3);        //给二级指针分配大空间
    for(int i=0; i<3; i++)
    {
        ts[i]=malloc(sizeof(struct Teacher));   //给结构体分配空间
        ts[i]->name=malloc(sizeof(char)*64);       //给结构体内部数组内容分配空间
        sprintf(ts[i]->name,"Name_%d", i + 1);
        ts[i]->student=malloc(sizeof(char *) * 4);      //给结构体内部指针数组的指针分配空间
        for(int j=0;j<4;j++)
        {
            ts[i]->student[j]=malloc(sizeof(char) * 64);        //给结构体内部指针数组指向的内容分配空间
            sprintf(ts[i]->student[j],"%s_stu_%d", ts[i]->name,j+1);
        }
    }
    *temp = ts;
    return 0;
}

int print_teachers(struct Teacher **teacher)   //涵盖三个结构体的数组
{
    if(NULL == teacher)
    {
        return -1;
    }
    for(int i = 0; i < 3;i++){
        printf("%s\n", teacher[i]->name);       //三个结构体指针
        for(int j = 0; j < 4;j++)
        {
            printf("    %s %d \n", teacher[i]->student[j], j);      //每个结构体指针向下指每一个数组
        }
    }
    return 0;
}

int free_space(struct Teacher **teacher)
{
    if( NULL == teacher)
    {
        return -1;
    }

    for(int i = 0; i < 3;i++)
    {
        if(NULL == teacher[i]->name)
        {
            return -1;
        }
        free(teacher[i]->name);      //每个结构体指针下name数组空间释放
        teacher[i]->name=NULL;


        for(int j = 0; j < 4;j++)
        {
            if(teacher[i]->student[j] == NULL)
            {
                continue;
            }
            free(teacher[i]->student[j]);      //每个结构体指针向下指每一个student数组空间释放
            teacher[i]->student[j]=NULL;
        }


        free(teacher[i]->student);              //每个结构体指针指向student的部分释放
        teacher[i]->student = NULL;


        free(teacher[i]);                   //每个结构体指针释放
        teacher[i] = NULL;
    }
    free(teacher);              //释放二级指针
    teacher = NULL;

}

int main(void)
{
    struct Teacher **temp = NULL;
    int exm=0;
    exm = arr_space(&temp);
    exm = print_teachers(temp);
    exm = free_space(temp);
    if(exm < 0)
    {
        printf("ERROR");

    }
    return 0;
}
```

**顺着思维向下构建函数，指针，数组之间的关系；**使用完后**倒着释放空间**，/////注意//////**一定要充分释放，每一个指针，指针指向的内容，数组**都要将进行释放！！！！

## 结构体偏移量

```
typedef struct Teacher
{
	char a;  
	int b;      
	int c;        

} Teacher;

void test(){
	
	Teacher  t1;
	Teacher*p = NULL;
	p = &t1;

	int offsize1 = (int)&(p->b) - (int)p;  //age 相对于结构体 Teacher的偏移量
	int offsize2 = (int)&(((Teacher *)0)->b);//绝对0地址 age的偏移量
	int offsize3 = offsetof(Teacher, b);
//offserof函数由include<stddef.h>申请，用于计算偏移量
	printf("offsize1:%d \n", offsize1);
	printf("offsize2:%d \n", offsize2);
	printf("offsize3:%d \n", offsize3);
}

```

![image-20231123135324290](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231123135324290.png)

如图三个printf中地址其实是相同的

## 内存对齐

### 概念	

​	在用sizeof运算符求算某结构体所占空间时，并不是简单地将结构体中所有元素各自占的空间相加，这里涉及到内存字节对齐的问题。

​	从理论上讲，对于任何变量的访问都可以从任何地址开始访问，但是事实上不是如此，实际上访问特定类型的变量只能在特定的地址访问，这就需要各个变量在空间上按一定的规则排列， 而不是简单地顺序排列，这就是内存对齐。

### 内存对齐原因

我们知道内存的最小单元是一个字节，当cpu从内存中读取数据的时候，是一个一个字节读取，cpu将内存当成多个块，每次从内存中读取一个块，这个块的大小可能是2、4、8、16等，

内存对齐是操作系统为了提高访问内存的策略。操作系统在访问内存的时候，每次读取一定长度(这个长度是操作系统默认的对齐数，或者默认对齐数的整数倍)。如果没有对齐，为了访问一个变量可能产生二次访问。

● 提高存取数据的速度。比如有的平台每次都是从偶地址处读取数据，对于一个int型的变量，若从偶地址单元处存放，则只需一个读取周期即可读取该变量；但是若从奇地址单元处存放，则需要2个读取周期读取该变量。               

 ● 某些平台只能在特定的地址处访问特定类型的数据，否则抛出硬件异常给操作系统。

### **如何内存对齐**

#### 共用体，结构体之间的字节对齐

结构体会把共用体之间的部分拆开看，共用体用的内存是最大数据类型，并满足最大整数基本类型整数倍的原则，结构体因为会把共用体拆开，所以如下两个例子，结构体最大数据类型不是共用体，而是共用体内最大的一部分，考虑字节对齐也要按此考虑，

如图1，结构体考虑的最大数据类型是拆开的20，不是共用体的24，因此结构体最后为40，是20整数倍。图2同理。![Cache_-68ad5522f6fc00cc.](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/Cache_-68ad5522f6fc00cc..jpg) ■![Cache_-594520009052e1eb.](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/Cache_-594520009052e1eb..jpg) 对于标准数据类型，它的地址只要是它的长度的整数倍。

 ■ 对于非标准数据类型，比如结构体，要遵循一下对齐原则：



1. 数组成员对齐规则。第一个数组成员应该放在offset为0的地方，以后每个数组成员应该放在offset为**min（当前成员的大小，#pargama pack(n)）**整数倍的地方开始（比如int在32位机器为４字节，#pargama pack(2)，那么从2的倍数地方开始存储）。
2. 结构体总的大小，也就是sizeof的结果，必须是**min（结构体内部最大成员，#pargama pack(n)）**的整数倍，不足要补齐
3. 结构体做为成员的对齐规则。如果一个结构体B里嵌套另一个结构体A,还是以最大成员类型的大小对齐，但是结构体A的起点为A内部最大成员的整数倍的地方。（struct B里存有struct A，A里有char，int，double等成员，那A应该从8的整数倍开始存储。），结构体A中的成员的对齐规则仍满足原则1、原则2。

```
手动设置对齐模数:
■#pragma pack(show)
显示当前packing alignment的字节数，以warning message的形式被显示。
■#pragma pack(push) 
将当前指定的packing alignment数组进行压栈操作，这里的栈是the internal compiler stack,同时设置当前的packing alignment为n；如果n没有指定，则将当前的packing alignment数组压栈。
■#pragma pack(pop) 
从internal compiler stack中删除最顶端的reaord; 如果没有指定n,则当前栈顶record即为新的packing alignement数值；如果指定了n，则n成为新的packing alignment值
■#pragma pack(n)
指定packing的数值，以字节为单位，缺省数值是8，合法的数值分别是1,2,4,8,16。 
```

## 文件操作

打开文件**读取/写入**实际上为把文件内容放到缓冲区中，然后从缓冲区进行**读取/写入**，当读取完缓冲区后，会再将文件内容**读取/写入**到缓冲区中；重复这个过程。

优点：有利于磁盘寿命，有利于读写效率，比在磁盘中读写更快

### 判断文件结束

`while ((ch = fget(file)) != EOF)`

EOF为文件结束标志，这样可以判断到文件结束，而且不会考虑EOF这个空格，否则用feof判断，需要考虑EOF这个空格

函数以三种基本的形式处理数据：**单个字符**、**文本行**和**二进制数据**。对于每种形式都有一组特定的函数对它们进行处理。

**输入/输出函数家族**

| 家族名  | 目的       | 可用于所有流 | 只用于stdin和stdout |
| ------- | ---------- | ------------ | ------------------- |
| getchar | 字符输入   | fgetc、getc  | getchar             |
| putchar | 字符输出   | fputc、putc  | putchar             |
| gets    | 文本行输入 | fgets        | gets                |
| puts    | 文本行输出 | fputs        | puts                |
| scanf   | 格式化输入 | fscanf       | scanf               |
| printf  | 格式化输出 | fprintf      | printf              |

### 文本形式读写

```
struct info{
	char key[64];
	char val[128];
};

struct config{
	FILE *fp; //保存文件指针
	struct info *list; //保存配置信息
	int lines; //配置信息条数
};

//加载配置文件
int load_file(char *path, struct config **myconfig){
	if (NULL == path){
		return -1;
	}
	//以读写的方式打开文件
	FILE *fp = fopen(path, "r+");
	if (NULL ==fp){
		printf("文件打开失败!\n");
		return -2;
	}

	//配置文件信息分配内存
	struct config *conf = (struct config *)malloc(sizeof(struct config));
	conf->fp = fp;
	conf->list = NULL;

	//指针的间接赋值，从而将开辟的空间向外传递
	*myconfig = conf;

	return 0;
}

//统计文件行数
int count_file(struct config *config){
	if (NULL == config){
		return -1;
	}
	char buf[1024] = { 0 };
	int lines = 0;
	while (fgets(buf, 1024, config->fp)){
		//如果是注释则不统计
		if (buf[0] == '#'){ continue; }
		lines++;
	}
	//将文件指针重置到开始位置（也可以rewind）
	fseek(config->fp,0, SEEK_SET);

	return lines;
}

//解析配置文件（每一行需要的文本信息向内结构体存储
int parse_file(struct config *config){
	if (NULL == config){
		return -1;
	}

	//获得配置文件行数
	config->lines = count_file(config);
	//给每一行配置信息分配内存
	config->list = (struct info *)malloc(sizeof(struct info) * config->lines);
	int index = 0;
	char buf[1024] = { 0 };
	while (fgets(buf, 1024, config->fp)){
		//去除每一行最后的\n字符
		buf[strlen(buf) - 1] = '\0';
		//如果是注释则不显示
		if (buf[0] == '#'){
			continue;
		}

		memset(config->list[index].key, 0, 64);
		memset(config->list[index].val, 0, 128);
	
		char *delimit = strchr(buf, ':');			//strchr找到’：‘的位置
		strncpy(config->list[index].key, buf, delimit - buf);	//‘：’后打印进去
		strncpy(config->list[index].val, delimit + 1, strlen(delimit + 1));

		memset(buf, 0 , 1024);

		index++;
	}

	return 0;
}

const char *get_file(struct config *config, char *key){
	if (NULL == config){
		return NULL;
	}
	if (NULL == key){
		return NULL;
	}
	
	for (int i = 0; i < config->lines;i ++){
		if (strcmp(config->list[i].key,key) == 0){
			return config->list[i].val;
		}
	}

	return NULL;
}

void destroy_file(struct config *config){
	if (NULL == config){
		return;
	}
	//关闭文件指针
	fclose(config->fp);
	config->fp = NULL;
	//释放配置信息
	free(config->list);
	config->list = NULL;
	free(config);
}

void test(){
	char *path = "./my.ini";
	struct config *conf = NULL;
	load_file(path, &conf);
	parse_file(conf);
	printf("%s\n", get_file(conf, "username"));
	printf("%s\n", get_file(conf, "password"));
	printf("%s\n", get_file(conf, "server_ip"));
	printf("%s\n", get_file(conf, "server_port"));
	printf("%s\n", get_file(conf, "aaaa"));
	destroy_file(conf);
}

```

其他格式参考伪数据库构建