# 进阶Cday6

[TOC]

## 函数指针

函数三要素： 名称、参数、返回值。C语言中的函数有自己特定的类型

函数在编译时被分配入口地址，这个地址就称为函数的指针，函数名代表函数的入口地址。

### 函数指针及调用

```
typedef int(p)(int, int);

void my_func(int a,int b){
	printf("%d %d\n",a,b);
}

void test(){

	p p1;
	//p1(10,20); //错误，不能直接调用，只描述了函数类型，但是并没有定义函数体，没有函数体无法调用
	p* p2 = my_func;
	p2(10,20); //正确，指向有函数体的函数入口地址
}
```

函数调用：typedef重命名相同类型相同参数的函数，如下图1.重定义FUN_TYPE，随后便可以定义函数指针如上的pFunc或其他函数指针，调用即可运行函数（可用来突出一个函数再不同情景下的作用）（实际也没什么用）			

也可以如2.，直接定义为指针，这样运用可以直接赋值指向地址 			

或如3.直接定义函数指针，然后把函数地址赋值给它，随后便可以调用。

这里的myfunc函数为

```
int myfunc（int a， char b）{

}
```

![image-20231126173134434](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231126173134434.png)

### 函数指针做参数

函数指针错参数常与typedef联用，用typedef去定义函数指针，然后写出该种函数指针的多种变形，这就具有了多态性，可以方便调用或修改，减少维护量，避免冗杂代码，提高灵活性。如下：

```
int calculate(int a, int b, fun_t operation)      //作为参数传入，这样不同模式（mod）都适用，提高灵活性
{  
 int result;
 result = operation(a, b);   <!--灵活函数体调用-->
 return result;
}
-------------------------------------------------------
其中，fun_t是一个<----函数指针---->，其定义为：

typedef int (*fun_t)(int, int);
-------------------------------------------------------
根据函数指针变量operation指向不同的运算函数可实现加法运算、减法运算、乘法运算、除法运算。

主函数代码调用即可灵活多变，如下实现四种功能调用格式都一样，都为 calculate（int,int,mode)这样就使得格式相对统一，调用更加方便，后续更改也相对简单，只需更改函数调用的实参即可修改功能，而不用去修改函数体：

int main(void)
{
 int result;
 int a = 192, b = 48;

 /* 两个数相加的操作 */
 result = calculate(a, b, add2);
 printf("加法运算: %d+%d = %d\n",a, b, result);
 
 /* 两个数相减的操作 */
 result = calculate(a, b, sub2);
 printf("减法运算: %d-%d = %d\n",a, b, result);
 
 /* 两个数相乘的操作 */
 result = calculate(a, b, mul2);
 printf("乘法运算: %d*%d = %d\n",a, b, result);
 
 /* 两个数相除的操作 */
 result = calculate(a, b, div2);
 printf("除法运算: %d/%d = %d\n",a, b, result);
 
 return 0;
}

实现运算的4个副函数，如下：

int add2(int a, int b)
{
 return a+b;
}

int sub2(int a, int b)
{
 return a-b;
}

int mul2(int a, int b)
{
 return a*b;
}

int div2(int a, int b)
{
 return a/b;
}
```

数组函数指针也可以做到，调用格式与之前的相似   如下：

![image-20231127111642644](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231127111642644.png)

这里函数指针数组实质为二级指针，因为赋值函数实际给的是地址，也就是函数名为一级指针，因此这里为一级指针数组。

## 链表

### 简介，与数组比较

​		链表由（**节点**）一个要存储的数据和一个指针构成，指针用来寻找下一个数据存储的位置

● 链表是一种常用的数据结构，它通过指针将一些列数据结点，连接成一个数据链。相对于数组，链表具有更好的动态性（**非顺序存储**）。

● 数据域用来存储数据，指针域用于建立与下一个结点的联系。

● 建立链表时无需预先知道数据总量的，可以随机的分配空间，可以高效的在链表中的任意位置实时插入或删除数据。（只需修改指针域指针的指向即可）

● 链表的开销，主要是访问顺序性和组织链的空间损失。（查找通过指针一个个找，效率低下，同时多存储了指针域，因此相对于数组空间开销大些）



**数组**：一次性分配一块连续的存储区域。

优点：随机访问元素效率高(因为连续存储，访问下一内存块即可)

缺点：

​	1) 需要分配一块连续的存储区域（很大区域，有可能分配失败）

​	2)删除和插入某个元素效率低



**链表**：无需一次性分配一块连续的存储区域，只需分配n块节点存储区域，通过指针建立关系。

优点：

​	1) 不需要一块连续的存储区域

​	2) 删除和插入某个元素效率高

缺点：随机访问元素效率低（因为非连续存储，通过指针访问其他元素，导致随机访问一个值过程很慢，要去遍历，而不能像数组一样使用下标）



### 分类

- 静态链表

  ```
  typedef struct Stu
  {
  	int id;				//数据域
  	char name[100];
  
  	struct Stu *next; 	//指针域
  }Stu;
  
  void test()
  {
  	//初始化结构体变量
  	Stu s1 = { 1, "yuri", NULL };
  	Stu s2 = { 2, "lily", NULL };
  	Stu s3 = { 3, "lilei", NULL };
  
  	s1.next = &s2; 			//next指针向后指
  	s2.next = &s3;			//指针域连接
  	s3.next = NULL; 		//尾结点
  
  	Stu *p = &s1;			//结构体指针定义，用于访问链表
  	while (p != NULL)
  	{
  		printf("id = %d, name = %s\n", p->id, p->name);
  
  		//每遍历一次，节点往后移动一位
  		p = p->next; 
  	}
  }
  ```

- 动态链表

-------------------------------------------------------------------------------------------

- 单向链表
- 双向链表：指针域多一个指针指向前一个节点位置
- 循环链表：尾部指针再指回头部节点
  - 单向循环链表
  - 双向循环链表

链表带头不带头就是看要不要头结点，有头结点（即第一个节点不带数据域）此时当对链表进行修改时就不用再去考虑是否修改或插在了头结点位置上，因为头结点只有指针域，永远在第一位

### 链表插入，删除，遍历，销毁函数（重点）

```
struct LinkNode
{
	int data;
	struct LinkNode *next;
};
			---------链表修改的多功能函数-----------
初始化链表					//除了初始化函数，其他每个函数都要把链表头地址传进去，进行相应修改。
struct LinkNode *Init_LinkList();
插入新数据
void InsertByValue_LinkList(struct LinkNode *header, int oldval, int newval)
删除
void DeleteByValue_LinkList(struct LinkNode *header, int delval)
遍历
void Foreach_LinkList(struct LinkNode *header)
销毁
void Destroy_LinkList(struct LinkNode *header)
清空
void Clean_LinkList(struct LinkNode *header)
```

具体实现

```
//初始化链表
struct LinkNode *Init_LinkList()
{
	struct LinkNode *header = malloc(sizeof(struct LinkNode));
	header->data = -1;		//头结点不赋值
	header->next = NULL;
	
	struct LinkNode *pRear = header;		//尾指针
	int val = -1;
	while(1)
	{
		printf("enter the data");
		scanf("%d", &val);
		if(val == -1)
		{
			break;
		}
		struct LinkNode *newnode = malloc (sizeof(struct LinkNode));
		newnode->data = val;
		newnode->next = NULL;		//新节点创建
		header->next = newnode;		//前节点指针修改
		pRear = newnode;		//尾指针后移
	}
	return header;
}
//插入新数据
void InsertByValue_LinkList(struct LinkNode *header, int oldval, int newval)
{
	if(NULL == header)
	{
		return;
	}
	//辅助指针pPrev为要插入位置前节点，另一个指针为插入后下一节点
	 struct LinkNode *pPrev = header;
	 struct LinkNode *pCurrent = pPrev->next;
	 
	 while(pCurrent != NULL)
	 {
	 	if(pCurrent->data == oldval)	//找到需要插入的位置
	 	{
	 		break;
	 	}
	 	pPrev = pCurrent;			//找到位置更改辅助指针状态
	 	pCurrent = pCurrent->next;
	 }
	 if(pCurrent == NULL)
	 {
	 	return;			//未找见需要插入值
	 }
	 //创建新节点
	 struct LinkNode *newnode = malloc(sizeof(struct LinkNode));
	 newnode->data = newval;
	 newnode->next = NULL;
	 //插入
	 newnode->next = pCurrent;
	 pPrev->next = newnode;
}
//删除
void DeleteByValue_LinkList(struct LinkNode *header, int delval)}
{
	if(NULL == header)
	{
		return;
	}
	//辅助指针
	struct LinkNode *pPrev = header;
	struct LinkNode *pCurrent = pPrev->next;
	while (pCurrent != NULL)
	{
	if(pCurrent->data == delval)
		break;
	//移动辅助指针
	pPrev = pCurrent;
	pCurrent = pCurrent->next;
	}
	if(NULL == pCurrent)
	{
		return;
	}
	//重新建立删除节点的前后关系
	pPrev->next = pCurrent->next;
	
	free(pCurrent);
	pCurrent = NULL;
}
//遍历
void Foreach_LinkList(struct LinkNode *header)
{
	if(NULL == header)
	{
		return;
	}
	struct LinkNode *pCurrent = header->next; 	//头节点无数据跳过
	while(NULL != pCurrent)
	{
		printf("%d", pCurrent->data);
		pCurrent = pCurrent->next;
	}
}
//销毁   //与清空几乎相同，只少了最后一步
void Destroy_LinkList(struct LinkNode *header)
{	
	if(NULL == header)
	{
		return;
	}
	struct LinkNode *pCurrent = header;
	while (pCurrent != NULL)
	{
		struct LinkNode *pNext = pCurrent->next;
		free(pCurrent);
		pCurrent = pNext;
	}
}
//清空
void Clean_LinkList(struct LinkNode *header)
{
	if(NULL == header)
	{
		return;
	}
	 struct LinkNode *pCurrent = header;
	 while (pCurrent != NULL)
	 {
	 	//保存下一个节点
	 	struct LinkNode *pNext = pCurrent->next;
	 	//释放当前节点
	 	free(pCurrent);
	 	//pCurrent向下指
	 	pCurrent = pNext;
	 }
	 header->next = NULL;
}
```

### 链表逆序

```
void Reverse_LinkList(struct LInkNode *header)
{
	if(NULL == header)
	{
		return;
	}
	//三个辅助指针
	struct LInkNode *pPrev = NULL;
	struct LInkNode *pCurrent = header->next;
	struct LInkNode *pNext = NULL;
	while (pCurrent != NULL)
	{
		pNext = pCurrent->next;
		pCurrent->next = pPrev;		//指针域向前
		
		pPrev = pCurrent;		//辅助指针向后移位
		pCurrent = pNext;
	}
	header->next = pPrev;
}
```

