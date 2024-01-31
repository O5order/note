# 进阶Cday4

[TOC]

## 一维数组

### 数组名

​	在C中，在几乎所有数组名的表达式中，数组名的值是一个**指针常量**，也就是**数组第一个元素的地址**。它的类型取决于数组元素的类型：如果他们是int类型，那么数组名的类型就是“指向int的常量指针”；如果它们是其他类型，那么数组名的类型也就是“指向**其他类型**的常量指针”。

那么数组在什么情况下不能作为指针常量呢？在以下两种场景下： 

 ■ 当数组名作为sizeof操作符的操作数的时候，此时sizeof返回的是整个数组的长度，而不是指针数组指针的长度。

■ 当数组名作为&操作符的操作数的时候，此时返回的是一个指向数组的指针，而不是指向某个数组元素的指针常量。如：

```
int arr[10];
//arr = NULL; 	//arr数组会作为指针常量，因此不可修改
int *p = arr; 	//此时arr作为指针常量来使用
printf("sizeof(arr):%d\n", sizeof(arr)); //此时sizeof结果为整个数组的长度
printf("&arr type is %s\n",&arr + 1); 	//此时步长不是4，因为此时返回的是指向数组的指针，步长为数组大小
```

因此除了以上两种情况，数组名可以当作指向首地址的指针使用

### 数组指针

定义方式有三种，

- 一：通过typedef定义

```
void test01(){

	//先定义数组类型，再用数组类型定义数组指针
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	//有typedef是定义类型，没有则是定义变量,下面代码定义了一个数组类型ArrayType
	typedef int(ArrayType)[10];
	//int ArrayType[10]; //定义一个数组，数组名为ArrayType

	ArrayType myarr; //等价于 int myarr[10];
	ArrayType* pArr = &arr; //定义了一个数组指针pArr，并且指针指向数组arr
	for (int i = 0; i < 10;i++){
		printf("%d ",(*pArr)[i]);
	}
	printf("\n");
}

```



- 方式二：通过typedef直接定义一个数组指针

**typedef** int**(\***ArrayType**)[**10**];**

​	`ArrayType pArr` **=** **&**arr**;** //定义了一个数组指针pArr，并且指针指向数组arr

- 方式三：直接定义

int arr**[**10**];**

int**(\***pArr**)[**10**]** **=** **&**arr**;**

## 多维数组（二维数组）

### 数组名

二维数组名较为特殊，由于二位数组本身的特性，二维数组名本身为（void *__[---]）即为一个指向指针数组的数组指针，引用时有：

如：`arr[3][3] = {0,1,2, 3,4,5, 6,7,8}   ` ;

**(*(arr + 2)+2)**里面的小括号代表第一个中括号，即指针数组中的第几个数组指针，两个小括号之间就是该指针在数组中的指向

这里得到的就是`arr[2][2]`即8

由此可以得到二维数组函数传递，形参应该写为void (*arr)[3]

### 选择排序

对二维数组的进一步使用

//数组做函数函数，退化为指针
void array_sort(char** arr,int len){

​	for (int i = 0; i < len; i++){
​		for (int j = len - 1; j > i; j --){
​			//比较两个字符串
​			if (strcmp(arr[j-1],arr[j]) > 0){
​				char* temp = arr[j - 1];
​				arr[j - 1] = arr[j];
​				arr[j] = temp;
​			}
​		}
​	}

}

//打印数组
void array_print(char** arr,int len){
	for (int i = 0; i < len;i++){
		printf("%s\n",arr[i]);
	} 		//注意//  //这里实际上是读到二级指针下的一级指针，从一级指针开始读取%s，遇到空格结束
	printf("----------------------\n");
}

void test(){
	
	//主调函数分配内存
	//指针数组
	char* p[] = { "bbb", "aaa", "ccc", "eee", "ddd"};		//指向多个字符串的数组
	//char** p = { "aaa", "bbb", "ccc", "ddd", "eee" }; //错误
	int len = sizeof(p) / sizeof(char*);
	//打印数组
	array_print(p, len);
	//对字符串进行排序
	array_sort(p, len);
	//打印数组
	array_print(p, len);
}

## 总结

### **编程提示**

■ 源代码的可读性几乎总是比程序的运行时效率更为重要

 ■ 只要有可能，函数的指针形参都应该声明为const，防止形参的修改导致意外的原数据改变bug

 ■ 在多维数组的初始值列表中使用完整的多层花括号提供可读性

### 内容总结

​	在绝大多数表达式中，数组名的值是指向数组第1个元素的指针。这个规则只有两个例外，sizeof和对数组名&。

​	指针和数组并不相等。当我们声明一个数组的时候，同时也分配了内存。但是声明指针的时候，只分配容纳指针本身的空间。

​	当数组名作为函数参数时，<u>**实际传递给函数的是一个指向数组第1个元素的指针。**</u>极其重要！！！！！！

​	我们不单可以创建指向普通变量的指针，也可创建指向数组的指针。

## 结构体（**重点**）

### 结构体初始化

```
struct Person{
	char name[64];
	int age;
}p1 = {"john",10}; //定义类型同时初始化变量

struct{
	char name[64];
	int age;
}p2 = {"Obama",30}; //定义类型同时初始化变量

struct Person p3 = {"Edward",33}; //通过类型直接定义
注意这里用typedef定义以后就不用struct了，比如：
typedef struct Person Myperson
初始化就是：Myperson p3={----------}；
```

### 结构体使用

- 在栈上使用，正常初始化，结构体名后加‘  .  ’即可
- 在堆上使用

```
	struct Person* p2 = (struct Person*)malloc(sizeof(struct Person));
	strcpy(p2->name, "Obama");
	p2->age = 33;
	//如果是指针变量，通过->操作结构体成员
	printf("Name:%s Age:%d\n", p2->name, p2->age);
```

### 结构体数组

```
struct Person{
	char name[64];
	int age;
};

void test(){
	//在栈上分配空间
	struct Person p1[3] = {
		{ "John", 30 },
		{ "Obama", 33 },
		{ "Edward", 25}
	};

	struct Person p2[3] = { "John", 30, "Obama", 33, "Edward", 25 };
	for (int i = 0; i < 3;i ++){
		printf("Name:%s Age:%d\n",p1[i].name,p1[i].age);
	}
	//在堆上分配结构体数组
	struct Person* p3 = (struct Person*)malloc(sizeof(struct Person) * 3);
	for (int i = 0; i < 3;i++){
		sprintf(p3[i].name, "Name_%d", i + 1);
		p3[i].age = 20 + i;
	}
	for (int i = 0; i < 3; i++){
		printf("Name:%s Age:%d\n", p3[i].name, p3[i].age);
	}
}
```

### 结构体赋值（复制和指针冲突问题）

//重点//

**这里可以直接拷贝如下**，可是结构体内如果有指针，那么拷贝过去的是地址，此时会**导致原指针指向空间丢失，不能释放，（内存泄漏）**同时一个地址空间在接下来被释放了两次。

```
typedef struct _TEACHER{
	char* name;
}Teacher;


void test(){
	
	Teacher t1;
	t1.name = malloc(64);
	strcpy(t1.name , "John");

	Teacher t2;
	t2 = t1;	//重点//有上述问题因此-》》》》
	//对手动开辟的内存（或含指针），需要手动拷贝
	t2.name = malloc(64);
	strcpy(t2.name, t1.name);

	if (t1.name != NULL){
		free(t1.name);
		t1.name = NULL;
	}
	if (t2.name != NULL){
		free(t2.name);
		t1.name = NULL;
	}
}		//释放
```

### 结构体嵌套一级指针

 **极其常用的结构体指针**，与指针数组，函数等等密切相关，非常重要

```
struct person
{
    char *name;		//结构体构建，含有一级指针，（当作数组使用）
    int age;
};

struct person** space_open()		//空间开辟
{
    struct person **temp=malloc(sizeof(struct person*)*3); 	//通过二级指针构建多个一级结构体（相当于一个一级指针数组）
    for(int i = 0;i < 3; i++)
    {
        temp[i]=malloc(sizeof(struct person)); 				//一级结构体开辟空间
        temp[i]->name=malloc(sizeof(char) * 64);			//结构体内部内容空间开辟
        sprintf(temp[i]->name,"Name_%d", i+1);				//结构体内容覆写
        temp[i]->age=100;
    }
    return temp;							//回传二级指针
}

void print_str(struct person **person)     //二级指针使用
{
    if(NULL == person)
    {
        return;
    }
    for(int i=0;i<3;i++)					//二级指针当作指针数组使用
    {
        printf("Name_%s,age_%d\n", person[i]->name,person[i]->age);		//相当于三个指针的数组使用
    }
}

void free_space(struct person **person)				//内存释放
{
    if(NULL == person)
    {
        return;
    }
    for(int i=0;i<3;i++){
        if(person == NULL)
        {
            continue;
        }
        if(person[i]->name != NULL)			
        {
            free(person[i]->name);				//释放一级指针中内容所占的空间
            person[i]->name=NULL;
        }
        free(person[i]);		//释放一级指针本身所占空间
        person[i]=NULL;
    }
    free(person);				//释放二级指针（指针数组）所占的空间
    person = NULL;
}

int main(void)
{
    struct person** person = space_open();
    print_str(person);
    free_space(person);
    return 0;
}
```

## 总结

- 注意malloc，realloc等内存开辟函数成功返回的是**地址**，所以应该等于一个指针

- 二级数组名本身是一个指针数组，如`int[3][3]`数组名就是（*int )[3], 因此注意函数之间传递的格式
- 注意二级指针与指针数组之间的联系，巧妙的进行运用，然后注意指针的步长，因此**二级指针经常当作一级指针数组使用**，利用其步长变成数组使用。
- 灵活利用typedef，对复杂的数据结构进行命名替代<!--注意用typedef定义的格式变量与之前的格式已经不再相同-->比如：typedef int* array_type;    int *p1;   **此时p1不可以赋给array_type虽然实际数据结构相同，但是必须经过强转否则会报错。
- 注意结构体拷贝，只要结构体内部不涉及指针且不指向堆空间，就可以直接      **=赋值**。