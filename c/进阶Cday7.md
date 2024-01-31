# 进阶Cday7

[TOC]

## 预处理

C语言对源程序处理的四个步骤：预处理、编译、汇编、链接。

预处理是在程序源代码被编译之前，由预处理器（Preprocessor）对程序源代码进行的处理。不对程序的源代码语法进行解析，把源代码分割或处理成为特定的符号为下一步的编译做准备工作。

### 文件包含（库展开）

比如`inlcude`的引用就在预处理展开，双引号引用指现在该目录下找库，然后再去系统目录中找，而单箭括号是直接在系统目录中找

### 宏定义

\#define num 100

在编译预处理时，将程序中在该语句以后出现的所有的num都用100代替。这种方法使用户能以一个简单的名字代替一个长的字符串，在预编译时将宏名替换成字符串的过程称为“宏展开”。宏定义，只在宏定义的文件中起作用。

1. 宏名一般用大写，以便于与变量区别；

            2)     宏定义可以是常数、表达式等；
            2)      宏定义不作语法检查，只有在编译被宏展开后的源程序才会报错；
            
            4)     宏定义不是C语言，不在行末加分号；
            4)      宏名有效范围为从定义到本源文件结束；
            
            6)     可以用#undef命令终止宏定义的作用域；
            6)     在宏定义中，可以引用已定义的宏名；

### 宏函数

把一些短小而又频繁使用的函数写成宏函数，这是由于宏函数没有普通函数参数压栈、跳转、返回等的开销，可以调高程序的效率。

宏通过使用参数，可以创建外形和作用都与函数类似地类函数宏(function-like macro). 宏的参数也用圆括号括起来。

比如：

```
#define SUM(x,y) ((x)+(y))
void test(){
	
	//仅仅只是做文本替换 下例替换为 int ret = ((10)+(20));
	//不进行计算
	int ret = SUM(10, 20);
	printf("ret:%d\n",ret);
}
```

**注意:**

​            1)     宏的名字中不能有空格，但是在替换的字符串中可以有空格。

​            2)     用括号括住每一个参数，并括住宏的整体定义。

​            3)     用大写字母表示宏的函数名。

​            4）   如果打算宏代替函数来加快程序运行速度。那么要对宏函数大量引用。

### 条件编译

![image-20231128112958066](http://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231128112958066.png)

这里的标识符意思是 如果之前定义了一个，比如#define FLAG

那么这里标识符写FLAG，就会执行程序段1，如果标识符不变前面define部分删除，那么就会执行程序段2

常用的防止库函数重复定义

`#ifndef _SOMEFILE_H`

`#define _SOMEFILE_H`

## **一些特殊的预定宏**

C编译器，提供了几个特殊形式的预定义宏，在实际编程中可以直接使用，很方便。

//	\__FILE__			宏所在文件的源文件名 

//	\__LINE__			宏所在行的行号

//	\__DATE__			代码编译的日期

//	\__TIME__			代码编译的时间



void test**()**

**{**

​	printf**(**"%s\n"**,** __FILE__**);**

​	printf**(**"%d\n"**,** __LINE__**);**

​	printf**(**"%s\n"**,** __DATE__**);**

​	printf**(**"%s\n"**,** __TIME__**);**

**}**

## 库

### 静态库

静态库结尾为lib，库在linux中也是如此，ubuntu应该在etc/ld.conf.so.d中，这里含有静态库，外部头文件比如apache库链接就会在这里，绑定新库需要 sudo ldconfig使环境变量和编译时可以顺利链接到该函数库。

因此编译阶段就进行了链接，进入了exe可执行文件中，与程序运行的时候无关，因此方便移植

静态库缺点也很明显，如果多进程使用，会把同一个静态库加载多遍，非常占用内存。当静态库需要更新时所有依赖该静态库的程序都要进行更新，每次都要重新下载一遍静态库，浪费时间，占用空间

### 动态库

使用动态库提供一个引入库（.lib）文件（也称“导入库文件”）和一个DLL（.dll）文件（动态库链接），在程序运行时再进行链接，从而解决浪费时间和空间的问题。

动态库的引入库文件和静态库文件有着本质的区别，在使用动态库的情况下，在编译链接可执行文件时，只需要链接该DLL的引入库文件，该DLL中的函数代码和数据并不复制到可执行文件，直到可执行程序运行时，才去加载所需的DLL，将该DLL映射到进程的地址空间中，然后访问DLL中导出的函数。

也就是说动态库不会使用大量硬盘空间，实际提供的是一个链接，使用的时候会自动链接过去。

### c中库的总结

静态

你可以使用`ar`和`ranlib`来构建它，就像上个练习中的`libYOUR_LIBRARY.a`那样（Windows下后缀为`.lib`）。这种库可以当做一系列`.o`对象文件和函数的容器，以及当你构建程序时，可以当做是一个大型的`.o`文件。

动态

它们通常以`.so`（Linux）或`.dll`（Windows）结尾。在OSX中，差不多有一百万种后缀，取决于版本和编写它的人。严格来讲，OSX中的`.dylib`，`.bundle`和`framework`这三个之间没什么不同。这些文件都被构建好并且放置到指定的地方。当你运行程序时，OS会动态加载这些文件并且“凭空”链接到你的程序中。

## 递归函数

首先确定递归的退出条件，然后要自己明白递归函数的调用过程，能够按照自己的想法按正确的顺序去递归

递归函数常用来进行某些数据的逆向打印，比如链表或字符串的逆序输出

缺点是空间时间复杂度高，一般使用较少

## 面向接口编程

软件设计要求：模块要求松、接口要求紧。因此函数指针使用较多，提高灵活性

如下为企业之间合作写项目的过程，首先两企业会共谈项目接口，如下四个函数接口就是一个企业负责实现的（注意使用的时候都是typedef，将函数指针重定义为函数指针的方式去使用接口，接口设计的时候同平常函数相同），然后业务代码为另一个公司负责的，会直接使用那个公司的接口（注意是函数指针的形式调用）

注意这里的handle参数为数据库指针，实现对数据库的链接

![image-20231129172132149](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231129172132149.png)

简单的接口实现

```
struct Info
{
	char data[1024];
	int len;
};
void init_CSocketProtocol(void **handle)
{
	if(NULL == handle)
	{
		return;
	}
	struct Info *info = malloc(sizeof(struct Info));
	memset(info,0,sizeof(struct(struct Info)));
	*handle = info;
}
void send_CSocketProtocol(void *handle, unsigned char* sentData, intsendLen)
{
	if (NULL == handle)
	{
		return;
	}
	if (NULL == sendData)
	{
		return;
	}
	struct Info *info = (struct Info *)handle;
	//看！这里handle派上用场链接数据库
	strncpy(info->data,sendData,sendLen);
	info->len = sendLen;
}
void recv_CSocketProtocol(void *handle, unsigned char* recvData,int* recvLen)
{
	if (NULL == handle)
	{
		return;
	}
	if (NULL == recvData)
	{
		return;
	}
	if (NULL == recvLen)
	{
		return;
	}
	struct Info *info = (struct Info *)handle;
	strncpy(recvData, info->data,info->len);
	*recvLen = info->len; 
}
void close_CSocketProtocol(void *handle)
{	
	if (NULL == handle)
	{
		return;
	}
	free(handle);
    handle = Null;
}
```
