# 进阶Cday2

[TOC]



## 	函数调用

![image-20231116170247326](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231116170247326.png)

## 栈深入讨论

​	最重要的特性：先进后出；----用户可以将数据压入栈中(**压栈**，push)，也可以将压入栈中的数据弹出(**出栈**，pop),但是栈容器必须遵循一条规则：**先入栈的数据最后出栈**(First In First Out,FIFO).![image-20231116171429781](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231116171429781.png)

**栈总是向下增长的**。压栈的操作使得栈顶的地址减小，弹出操作使得栈顶地址增大。<!--即上图的缸应该是向下的，倒着压栈出栈-->

如下图：函数调用过程中的压栈出栈过程，**返回地址即为函数的跳转**，跳到该函数中进一步压栈。函数结果数据量小在寄存器中，反之在栈中储存

![QQ截图20231116173326](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/QQ%E6%88%AA%E5%9B%BE20231116173326.png)

也是因为函数繁琐的栈使用过程，**要频繁调用时简单的宏函数可以节约大部分空间及时间**

完整的函数调用栈变化过程：

![image](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image.png)

### 函数的调用惯例

事实上，在c语言里，存在着多个调用惯例，而默认的是cdecl.任何一个没有显示指定调用惯例的函数都是默认是cdecl惯例。

完整的函数写法：int _cdecl func(int a,int b);

**注意: _cdecl不是标准的关键字，在不同的编译器里可能有不同的写法，例如gcc里就不存在_cdecl这样的关键字，而是使用__attribute__((cdecl)).**如图为c的多种调用惯例

![image-20231116175029660](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231116175029660.png)

### 栈的生长方向和内存存放方向

内存生长方向**(小端模式-高位字节放在高地址，低位字节放在低地址)**![image](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image.jpg)

## 指针进阶

### 警惕野指针的出现  

​              ■ **初始化时置 NULL**

指针变量一定要初始化为NULL，因为任何指针变量刚被创建时不会自动成为NULL指针，它的缺省值是随机的。

​                ■ **释放时置 NULL**

当指针p指向的内存空间释放时，没有设置指针p的值为NULL。delete和free只是把内存空间释放了，但是并没有将指针p的值赋为NULL。通常判断一个指针是否合法，都是使用if语句测试该指针是否为NULL。

### 指针的步长

**重点**		指该指针**+-**时跳跃的内存大小

- **指针+1跳完该指针内存，如：int* a，那么a+1即为原地址后四个字节处；char* a，a+1为后一个字节处**

- 指针的类型转换实际为步长的转换，因此注意指针类型，适当改变以得到自己想要的内容

- 指针的类型，不单单决定指针的步长，**还决定解引用的时候从给定地址开始取类型大小的字节数**

- 记住每一步指针的跳跃情况，通过偏移量进行该处的赋值，若不同类型的指针和变量赋值*如： 

  ` char buf[1024] = { 0 };`

 	 `int a = 100;`
 	
 	`memcpy(buf+1,&a,sizeof(int));`
 	
 	`char *p3 = buf;`
 	
 	`*(int *)(p3 + 1)`

char一个字节，int四个字节将int塞入char数组中，再要读出需要进行强转把char类型转为int，才可以将原数字取出

- 由上一步的步长，可以更好地控制结构体，如下：**&取结构体p的地址**，再转为**char类型**（char一个字节更好控制）随后通过offsetof函数得到结构体中**每个量的占用内存情况**，得到你想取得数的地址，随后可以通过**强制转型取出结构体中你想要的任何变量**

  ```
  struct Person{
  
  	int a;
  
  	char b;
  
  	char buf[64];
  
  	int d;
  
  } 
  
  
  
  void text02(){
  
     struct Person p ={ 10,'a',"hello world!",100 };
  
     char b;
  
     printf("a off: %d\n",offsetof(struct Person,b));//a off:4
  
     printf("d = %d\n",*(int *)((char *)&p + offsetof(struct Person,d)));//d = 100
  
  }
  ```

offsetof为stddef头文件函数库中得到指针偏移量的函数

### 间接赋值

只要得到地址，就可以间接赋值，如得到一个地址2686652--------那么`*（* int）2686652 = 100;`把该地址赋给一个指针`printf该指针`可以顺利将100打印出来

### 指针的输入输出特性

- 主调函数使用内存，被调函数分配内存 ：指针输入特性

- 主调函数分配内存，被调函数使用内存  ：输出特性

- 地址的遍历，由此可以转化为数组使用，数组名会变为指向该数组首地址的指针

- **“ 字符串 ”**若字符串被双引号引用，则说明该字符串转为char *型别

- ```
  //-- str不需要取地址（若取还需要改变s的指向）
  void printString(const char *str){
      //--  printf输出时只要首地址，一直往后找直到\0
      //strlen();同上
      printf("打印内容：%s\n",str);//I am Polly!(str+2-am Polly!)
  }
  
  void pringStringArray(char **arr,int len){
  
    //arr[0]是char*类型的
  
    //arr[0] = *(arr + 0)
  
    for(int i = 0;i < len;++i){
  
     	printf("%s\n",arr[i]);
  
    }
  
  }
  void text01(){
      //堆上分配内存
      char *s = malloc(sizeof(char)* 100);
      memset(s, 0, 100);
      strcpy(s,"I am Polly!");
      printString(s);
      
      //数组名做函数参数就会退化为指向数组首元素的指针
      //void printIntArray(int *arr,int len){}
      int arr[] = { 1, 2, 3, 4, 5 };    
      
      //栈上分配
      char *strs[] = {
          "aaaaa",//常量区（地址）
          "bbbbb",
          "ccccc",
          "ddddd",
          "eeeee",
      };//指针数组，里面存储的是指针，双引号引用的字符串实际为地址
      
      int len = sizeof(strs) / sizeof(strs[0]);
      
      pringStringArray(strs, len);//因此这里的形参不需要取地址&，因为strs指针数组本身传递的就是地址
  }
  
  ```

  

### 副函数打开堆空间，主函数引用

标准格式：<!--副函数中malloc打开堆空间，主函数使用空间-->

`void array(int** p){`

​	`int *tmp=malloc(sizeof(int)*100);`

​	`*p=tmp;`

`}`

`int main(){`

​	`int *p=NULL;`

​	`array(&p);`

​	`if(NULL!=*p){`

​		`free(p);`

​		`p=NULL;`

`}`

## 字符串，字符数组

### 字符串，字符数组定义及初始化	

**memset（字符串首地址，0，长度）**

**大多时候用于该字符串赋0初始化**

//字符数组结尾必须为0或 \0 ，如下赋值打印会出现乱码（没有填长度，结尾没有赋结尾符）

​	char str1**[]** **=** **{** 'h'**,** 'e'**,** 'l'**,** 'l'**,** 'o' **};**

​	printf**(**"%s\n"**,**str1**);**



​	//字符数组部分初始化，剩余填0

​	char str2**[**100**]** **=** **{** 'h'**,** 'e'**,** 'l'**,** 'l'**,** 'o' **};**

​	printf**(**"%s\n"**,** str2**);**



​	//如果以字符串初始化，那么编译器默认会在字符串尾部添加'\0'

​	char str3**[]** **=** "hello"**;**



sizeof计算数组大小，数组包含'\0'字符，因此为定义的长度

strlen计算字符串的长度，到'\0'结束，因此为实际的长度

![QQ截图20231116215230](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/QQ%E6%88%AA%E5%9B%BE20231116215230.png)

<!--strlen与%s遇到\0结束，因此字符串中加入\0导致了二者的提前结束-->

<!--涉及\ddd为八进制数而八进制\012刚好代表换行，所以这里打印出来了换行而没有结束。十六进制字符的一般形式是'\xhh'-->

<!--同时‘\’代表转义，如第三个打印的‘\012’那里再加一个'\'会原样打出\012,不会转换为八进制-->

### 字符串复制拷贝

- ​	**被赋值的字符串**要**确保长度足够**，之后要**确保初始化**或者复制之后**结尾添加\0**确保正常复制，防止打印时乱码的产生

- ​	由于数组及指针之间的相互关系，数组首地址可以当作指针使用，指针因此可以当数组使用，如下图：<!--赋值结束后会把\0付给dst，这时while内就为0，循环结束-->
- ![20231116220450](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/20231116220450.png)

### 字符串反转

字符串前后全部颠倒，实例：

​	int begin **=** 0**;**

​	int end **=** strlen**(**str**)** **-** 1**;**

​	

​	**while** **(**begin **<** end**){**

​		//交换两个字符元素

​		char temp **=** str**[**begin**];**

​		str**[**begin**]** **=** str**[**end**];**

​		str**[**end**]** **=** temp**;**



​		begin**++;**

​		end**--;**

​	**}**或使用指针实现：

char *pstart = str;

char *pend = str + len - 1;

while(pstart<pend){

​		char temp **=** ***pstart;**

​		***pstart **=*pend;

​		***pend **=** temp**;**

​		++pstart;

​		  --pend;

}

### 字符串格式化（转换）

- sprintf

  - int sprintf**(**char *****str**,** const char *****format**,** **...);**

    <!--记住str应该足够大，数据量过多时应该在堆上开辟内存-->

    <!--各种格式字符都可以sprintf塞入字符串中-->

    功能：

       根据参数format字符串来转换并格式化数据，然后将结果输出到str指定的空间中，（将提供的数值存储在str字符串中）直到出现字符串结束符 '\0' 为止。

    参数： 

    ​	str：字符串首地址

    ​	format：字符串格式，用法和printf**()**一样

    返回值：

    ​	成功：实际格式化的字符个数

    ​	失败： **-** 1

    详细使用：

    - ​	//1. 格式化字符串

      ​	char buf**[**1024**]** **=** **{** 0 **};**

      ​	sprintf**(**buf**,** "你好,%s,欢迎加入我们!"**,** "John"**);**

      ​	memset**(**buf**,** 0**,** 1024**);**

      ​	sprintf**(**buf**,** "我今年%d岁了!"**,** 20**);**

      ​	**//2. 拼接字符串**

      ​	memset**(**buf**,** 0**,** 1024**);**

      ​	char str1**[]** **=** "hello"**;**

      ​	char str2**[]** **=** "world"**;**

      ​	int len **=** sprintf**(**buf**,**"%s %s"**,**str1**,**str2**);**

      ​	**//3. 数字转字符串**

      ​	memset**(**buf**,** 0**,** 1024**);**

      ​	int num **=** 100**;**

      ​	sprintf**(**buf**,** "%d"**,** num**);**

      ​	//设置宽度 右对齐

      ​	memset**(**buf**,** 0**,** 1024**);**

      ​	sprintf**(**buf**,** "%8d"**,** num**);**

      ​	//设置宽度 左对齐

      ​	memset**(**buf**,** 0**,** 1024**);**

      ​	sprintf**(**buf**,** "%-8d"**,** num**);**

      ​	//转成16进制字符串 小写

      ​	memset**(**buf**,** 0**,** 1024**);**

      ​	sprintf**(**buf**,** "0x%x"**,** num**);**

      ​	//转成8进制字符串

      ​	memset**(**buf**,** 0**,** 1024**);**

      ​	sprintf**(**buf**,** "0%o"**,** num**);**

    功能：

       根据参数format字符串来转换并格式化数据，然后将结果输出到str指定的空间中，（将提供的数值存储在str字符串中）直到出现字符串结束符 '\0' 为止。

    参数： 

    ​	str：字符串首地址

    ​	format：字符串格式，用法和printf**()**一样  

    返回值：

    ​	成功：实际格式化的字符个数

    ​	失败： **-** 1

- sscanf

  - 使用详解：<!--注意下面格式中三条贪婪性**更强调sscanf会读取完整段直到结束**-->

![](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231117105002625.png)

- 使用重点在于从**给定的**混杂**各种格式的字符串**中揪出**你想要的部分**，使用示例如下：
  - //1. 跳过数据
  
    void test01**(){**
  
    ​	char buf**[**1024**]** **=** **{** 0 **};**
  
    ​	//跳过前面的数字
  
    ​	//匹配第一个字符是否是数字，如果是，则跳过
  
    ​	//如果不是则停止匹配
  
    ​	sscanf**(**"123456aaaa"**,** "<u>**%*d**</u>%s"**,** buf**);** 
  
    ​	printf**(**"buf:%s\n"**,**buf**);**
  
    **}**
  
    <!--忽略字符串%s，读到空格或\t结束-->
  
  - //2. 读取指定宽度数据
  
    void test02**(){**
  
    ​	char buf**[**1024**]** **=** **{** 0 **};**
  
    ​	sscanf**(**"123456aaaa"**,** "%7s"**,** buf**);**
  
    ​	printf**(**"buf:%s\n"**,** buf**);**<!--印出七个数即123456a-->
  
    **}**
  
  - //3. 匹配a-z中任意字符
  
    void test03**(){**
  
    ​	char buf**[**1024**]** **=** **{** 0 **};**
  
    ​	//先匹配第一个字符，判断字符是否是a-z中的字符，如果是匹配
  
    ​	**//如果不是则停止匹配**
  
    ​	sscanf**(**"abcdefg123456"**,** "%[a-z]"**,** buf**);**
  
    ​	printf**(**"buf:%s\n"**,** buf**);**
  
  **}**
  
  - //4. 匹配aBc中的任何一个
  
    void test04**(){**
  
    ​	char buf**[**1024**]** **=** **{** 0 **};**
  
    ​	//先匹配第一个字符是否是aBc中的一个，如果是，则匹配，如果不是则停止匹配
  
    ​	sscanf**(**"abcdefg123456"**,** "%[aBc]"**,** buf**);**
  
    ​	printf**(**"buf:%s\n"**,** buf**);**<!--有中括号里的部分就填到buf中-->
  
    **}**
  
  - //5. 匹配非a的任意字符
  
    void test05**(){**
  
    ​	char buf**[**1024**]** **=** **{** 0 **};**
  
    ​	//跳过前面的数字
    ​	//如果是，则匹配，**如果不是则停止匹配**
  
    ​	sscanf**(**"bcdefag123456"**,** "%【^a】"**,** buf**);**
  
    ​	printf**(**"buf:%s\n"**,** buf**);**
  
    **}**
  
  - //6. 匹配非a-z中的任意字符
  
    void test06**(){**
  
    ​	char buf**[**1024**]** **=** **{** 0 **};**
  
    ​	//如果是，则匹配，**如果不是则停止匹配**
  
    ​	sscanf**(**"123456ABCDbcdefag"**,** "%【^a-z】"**,** buf**);**
  
    ​	printf**(**"buf:%s\n"**,** buf**);**

    **}**
  
- 额外用法：

彼此规则间相连互用，如：跳过*与非【】规则

**如：`%*[^@]@`  表明跳过@之前及其本身的所有字符**

\#include <stdio.h>
int main(void)
{  
  unsigned int info = 0;
  char *ptr = &info;
  if(sscanf("192.168.1.10", "%hhu.%hhu.%hhu.%hhu", &ptr[0], &ptr[1], &ptr[2], &ptr[3]) != 4)<!--按规定格式读入-->
  {
    printf("parse faild\n");
  }
  else
  {
    printf("info = %hhu %hhu %hhu %hhu\n", ptr[0], ptr[1], ptr[2], ptr[3]);
  }
  return 0;
}
运行结果：info = 192 168 1 10



\#include <stdio.h>
int main(void)
{
  char string[] = "192.168.1.10/24, 192.168.1.254";
  char address[16] = {0};
  char mask[16] = {0};
  char gateway[16] = {0};
  sscanf(string, "%[^/]/%[^,],%s", address, mask, gateway);<!--除去不要的字符筛选出要的字符-->

  printf("address=%s\n", address);
  printf("mask=%s\n", mask);
  printf("gateway=%s\n", gateway);
  return 0;
}
输出结果：
address=192.168.1.10
mask=24
gateway=192.168.1.254