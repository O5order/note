# Learn C hard way(未完)

[TOC]



## bug调试宏

​	参考练习20，通过宏定义进行bug调试，并通过巧妙的是否`define NDEBUG`决定是否debug，通过makefile向c源文件中添加宏定义，

格式是 `CFLAGS+= -D 宏定义名称`

` ##__VA_ARGS__与...`指剩余的所有额外参数: 如  #define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

`__FILE__`和`__LINE__`来获取当前`fine:line`用于调试信息

**重点**：通过自己的宏定义使得错误筛除简单快捷明显，可以找到哪里是监测错误的代码，使得自己的代码天衣无缝

## 数据类型

### 无符号有符号的选择

**一般情况下不要为了内存选择无符号变量**，因为c语言会在运算之前将较小边的变量转换为较大边，这导致使用无符号变量，有时候会使有符号变量转化，从而引起bug。除非及时用断言检查不是负数

### `stdint.h`库，`C99`

定义了 `int8_t    8位符号整数。uint8_t    8位无符号整数。int16_t    16位符号整数。uint16_t 	16位无符号整数。int32_t	32位符号整数。uint32_t	32位无符号整数。int64_t	64位符号整数。uint64_t	64位无符号整数 等整型`，在需要确定大小的整型时可以使用它们代替 short 、 unsigned long long 等，在 C 整型中，只使用 int 。适当情况下，推荐使用标准类型如 `size_t `和 `ptrdiff_t `

1. `1字节     uint8_t`  
2. `2字节     uint16_t  `
3. `4字节     uint32_t  `
4. `8字节     uint64_t`

### 位移动赋值符（>>,<< ,^,|）

目前用处不大，可参考[C语言移位运算符和 &=, ^=, |= ~= 的使用方法](https://blog.csdn.net/Beyond_Nothing/article/details/106343510#:~:text=^%3D ：按位异或后赋值 异或运算符（^） 参加运算的两个数据，按二进制位进行“异或”运算。,运算规则：0^0%3D0； 0^1%3D1； 1^0%3D1； 1^1%3D0； 即：参加运算的两个对象，如果两个相应位为“异”（值不同），则该位结果为1，否则为0。)

### 唯一的三目运算符

三元真值测试，`X ? Y : Z`读作“若X则Y否则Z”。

### 作用域

- 注意你每个变量的作用域，全局变量还是函数局部变量，还是外部变量

- 不要一个变量不同作用域多次定义，这可能会产生一些隐蔽的bug，你认为你改变了某个变量但实际上没有。

- 避免过多的全局变量，尤其是跨越多个文件。如果必须的话，要使用读写器函数，就像`get_age`。这并不适用于常量，因为它们是只读的，对于`THE_SIZE`这种变量，如果你希望别人能够修改它，就应该使用读写器函数。如下实例：

- ```c
  int get_age()
  {
      return THE_AGE;
  }
  
  void set_age(int age)
  {
      THE_AGE = age;
  }
  ```

- 在你不清楚的情况下，应该把它放在堆上。不要依赖于栈的语义，或者指定区域，而是要直接使用`malloc`创建它。防止栈溢出

- 不要使用函数级的静态变量，就像`update_ratio`。它们并不有用，而且当你想要使你的代码运行在多线程环境时，会有很大的隐患。对于良好的全局变量，它们也非常难于寻找。

- 避免复用函数参数，因为你搞不清楚仅仅想要复用它还是希望修改它的调用者版本。

## 传递方式

### 值传递

​	函数在调用时是隐含地把实参 a、b 的值分别赋值给了 x、y，之后在你写的 函数体内再也没有对 a、b 进行任何的操作了。交换的只是 x、y 变量。并不是 a、b。这就是值传递

### 地址传递

​	函数在调用时传递地址，如：指针 px、py的值已经分别是 a、b 变量的地址值了。接下来，对`*px、*py` 的操作当然也就是对 a、b 变量本身的操作了。所以函数里头的交换就是对 a、b 值的交换了，这就是所谓的地址传递

### 引用传递

```
void Exchg3(int &x, int &y) /* 注意定义处的形式参数的格式与
值传递不同 */ 
{ 
	int tmp = x; 
	x = y; 
	y = tmp; 
	printf("x = %d, y = %d.\n", x, y); 
} 
int main() 
{ 
	 int a = 4; 
	 int b = 6; 
	 Exchg3(a, b); /*注意：这里调用方式与值传递一样*/ 
	 printf("a = %d, b = %d.\n”, a, b); 
}
```

调用时我们可以像值传递（如： Exchg1(a, b); ）一样调用函数（如： Exchg3(a, b);）。但是 x、y 前都有一个取地址符号“&”。有了这个，调用 Exchg3 时函数会将 a、b 分别代替了 x、y 了，这就是引用传递

### 区别：

​	值传递和引用传递格式相同，传递的都是**变量本身**。

但是功能不同，值传递不能改变变量本身，而引用传递和指针传递都可以改变**变量本身**。

## 达夫设备

达夫设备将循环手动展开，加快循坏读取速度，**实际实现的是对极大数组的遍历**，可借此进行赋值或打印，或进行其他操作。

拷贝函数对比

1. memmove函数的功能同memcpy基本一致，但是当src区域和dst内存区域重叠时，memcpy可能会出现错误，而memmove能正确进行拷贝。
2. 若拷贝字串和被拷贝字串空间重叠，则**由memmove()函数处理，具体做法是从后往前cpy，从src的末端向前copycount个字节大小空间。**因此相对来说memmove速度更慢一些。
3. memset用于重置数组，一般用于初始化
4. memcpy与memmove都是对内存进行拷贝可以拷贝任何内容，而strcpy仅是对字符串进行操作。
5. memcpy与memmove拷贝多少是通过其第三个参数进行控制而strcpy是当拷贝至'\0'停止。

## IO函数

由于scanf本身吃回车的问题和过度读取的问题，一般不采用scanf，多用fgets

****

##### **枚举**

花括号里面的元素（枚举成员）是**常量**而不是变量，因为枚举成员是常量，**所以不能对它们赋值，只能将它们的值赋给其他的变量。**如：

enum DAY
{
MON=1, TUE, WED, THU, FRI, SAT, SUN
};

由于枚举中都是常量区存储，所以读取枚举中的非法数如：**负数，超过枚举数个数的数**；在堆区找不见枚举中相应的值，那么valgrind会报`not stack'd, malloc'd or (recently) free'd`即搜查出的是堆区free或未malloc的问题。而asan会报出on unknown address提示未找到对应的常量

****

##### freopen

描述：C 库函数 **FILE \*freopen(const char \*filename, const char \*mode, FILE \*stream)** 把一个新的文件名 **filename** 与给定的打开的流 **stream** 关联，同时关闭流中的旧文件。这也说明可以以此进行**多个文件和终端输入输出的重定向**

```
标准：fp = freopen("file.txt", "打开格式", stdout);
```

在调用 **freopen()** 之后，它会关联标准输出 STDOUT 到文件 **file.txt**，无论我们在标准输出 STDOUT 中写了什么都会被写入 file.txt，所以文件 file.txt 将有以下内容。

```
该文本重定向到 file.txt
```

成功返回指向该文件的文件指针。失败返回NULL，并把错误代码存在errno中

使用完后要    fclose(stdin);    **去关闭重定向输入**

****

#####  fdopen函数

使用格式：FILE *fdopen(int filename, const char *mode);

**函数说明**——把filename（文件描述符）转换成文件指针后返回此文件指针
**fildes**——文件描述符
**mode**——必须和此文件描述符对应文件的权限一样
**返回值**——成功返回指向该文件的文件指针。失败返回NULL，并把错误代码存在errno中

相当于`FILE filename`声明文件后再fopen打开

****

##### fcloseall

关闭所有流，即清除缓冲区后将所有打开的文件关闭

****

##### fgetpos

```
int fgetpos(FILE *stream, fpos_t *pos)
```

**stream** -- 这是指向 FILE 对象的指针，该 FILE 对象标识了流。

**pos** -- 这是指向 fpos_t 对象的指针。

用于获取流 **stream** 的当前文件位置，并把它写入到 **pos**。

相当于**直接利用指针对文件的当前位置进行拷贝**

成功返回非0，反之返回0

****

##### fseek

```
int fseek(FILE *stream, long int offset, int whence)
```

- **stream** -- 这是指向 FILE 对象的指针，该 FILE 对象标识了流。
- **offset** -- 这是相对 whence 的偏移量，以字节为单位。
- **whence** -- 这是表示开始添加偏移 offset 的位置。它一般指定为下列常量之一：

| 常量     | 描述               |
| :------- | :----------------- |
| SEEK_SET | 文件的开头         |
| SEEK_CUR | 文件指针的当前位置 |
| SEEK_END | 文件的末尾         |

成功返回非0，反之返回0

****

##### ftell

**long int ftell(FILE \*stream)** 返回给定流 stream 的当前文件位置。即找到当前位置，并用字节数表示，可与fseek联用

该函数返回位置标识符的当前值。如果发生错误，则返回 -1L，全局变量 errno 被设置为一个正值。

## 变参函数

```c
处于  include <stdarg.h>  库中
```

**va_list**
这是一个适用于 **va_start()、va_arg()** 和 **va_end()** 这三个宏存储信息的类型。

| void va_start(va_list ap, last_arg) | 这个宏初始化 **ap** 变量，它与 **va_arg** 和 **va_end** 宏是一起使用的。**last_arg** 是最后一个传递给函数的已知的固定参数，即省略号之前的参数。 |
| ----------------------------------- | ------------------------------------------------------------ |
| type va_arg(va_list ap, type)       | 这个宏检索函数参数列表中类型为 **type** 的下一个参数。       |
| void va_end(va_list ap)             | 这个宏允许使用了 **va_start** 宏的带有可变参数的函数返回。如果在从函数返回之前没有调用 **va_end**，则结果为未定义。 |

### 使用

首先va_list创建一个变量vl（亦或是指针）
然后va_start(vl,参数列表最后一个确定参数)
然后va_arg(vl,元素类型)获取元素，<!--获得的是下一个参数-->
最后va_end；

### 作用

为了自己构建更好的输入输出函数，然后再其他函数中调用

## **devpkg真正的程序**（重点）

unistd.h头文件用来标准定义unix类系统定义符号常量

[unistd.h详解](https://blog.csdn.net/qq_45662588/article/details/116267427)

### 具体函数

#### 数据库函数

1. DB_open 打开（数据库）文件  
2. DB_close关闭（数据库）文件   
3. DB_load  返回bstring型字串
4. DB_update   将传入的字符串加入数据库中
5. DB_find  在数据库中寻找字符串

#### shell函数

使用`extern`来表明其他的`.c`文件也能访问到`shell.c`中定义的变量。

此部分包含大多数shell命令，比如git，tar，curl，make，install等等



### 阿帕奇（重点）

apache函数都进行了多遍安全检查，确保使用时不再需要多遍debug，也防止重大错误的发生

#### apr封装函数（重点）含有apr，apu模块函数全接口

**简介**：apr 是 apache 使用的底层库，apache 是跨平台的，其跨平台正是基于 apr。

**好处**：

1. 使用apr写的程序可以跨平台

2. apr的pool（内存池）设计巧妙好用，在 pool上 分配的内存，是不用释放的，pool 销毁的时候自然会释放这些内存（所以销毁（清理）pool变得异常重要，千万不能忘了）。

   二是可以理解成资源管理器，分配资源后，然后在pool上注册一个释放资源的函数，pool 销毁（清理）的时候，会调用这个函数，释放资源。例如打开了一个文件，可以在 pool 上注册一个关闭文件的函数，让 pool 替你关闭文件。也可以在不销毁（清理）pool 时，手动的释放。具体可以看参考[apr手册](http://apr.apache.org/docs/apr/1.3/files.html)

****

**具体封装**

- **apr_status_t和返回值

在APR和APU中广泛采用的一个约定是：函数返回一个状态值，用来为调用者指示成功或者是返回一个错误代码。这个类型定义为apr_status_t，在apr_errno.h中定义，并赋予整数值。**实际就是为了验证一些操作是否能正常运行**，因此一个APR函数的常见原型就是：

APR_DECLARE(apr_status_t) apr_do_something(…function args…);

比如：

```c
	apr_pool_t *p = NULL;
    apr_status_t rv = APR_SUCCESS；		//定义该检测变量

    rv = apr_pool_create(&p, NULL);      //验证内存池创建是否成功
```

返回值应当在逻辑上进行判断，并且实现一个错误处理函数（进行回复或者对错误进行进一步的描述）。返回值APR_SUCCESS意味着成功，我们通常可以用如下的方式进行错误处理结构：

apr_status_t rv;
...
rv = apr_do_something(... args ...);
if (rv != APR_SUCCESS) {
/* 记录一个错误 */
return rv;
}



由于完整的shell需要多进程运行，所以需要以下两个对进程进行创建和管理的数据结构

[有关进程的详细资料](https://blog.csdn.net/m0_37925202/article/details/78759408)

- **procattr进程记录

​         在我们平时的**Unix进程**相关编程时，我们大致会接触两类进程操作函数**:进程创建函数(如fork和exec等)和进程属性操作函数(getpid、chdir等)**,APR将进程的相关属性信息封装到apr_procattr_t结构体中，因此我们写devpkg的shell部分需要进程记录和进程管理 ，在shell结构体中包含了apr_procattr_t *attr;这个重要的结构体定义:[procattr具体实现](https://blog.csdn.net/zhangge3663/article/details/79705751)

- **proc新进程创建

  同样， `apr_proc_t proc`也是与进程相关创建一个新的进程的接口为apr_proc_create,其参数也都很简单。前面说过apr_proc_create先fork出一个子进程，众所周知fork后子进程是父进程的复制品，然后子进程再通过exec函数加载新的程序映像，并开始执行新的程序。





- **常见函数**：

对系统内存池初始化,全局的,一个进程只要初始化一次

apr_status_t   apr_pool_initialize (void)

销毁内存池对象,及内部的结构和子内存池

void     apr_pool_terminate (void)

创建一个新的内存池

apr_status_t   apr_pool_create_ex (apr_pool_t **newpool, apr_pool_t *parent, apr_abortfunc_t abort_fn, apr_allocator_t *allocator)

创建一个新的内存池,apr_pool_create_ex的使用默认参数简化版

apr_status_t   apr_pool_create (apr_pool_t **newpool, apr_pool_t *parent)

获取内存池使用的内存分配器

apr_allocator_t *   apr_pool_allocator_get (apr_pool_t *pool)

清除一个内存池的内容,清除后内容为空，但可以再使用

void       apr_pool_clear (apr_pool_t *p)

释放一个内存池

void       apr_pool_destroy (apr_pool_t *p)

从池中分配内存

void *       apr_palloc (apr_pool_t *p, apr_size_t size)

从池中分配内存,并将分配出来的内存置0

void *       apr_pcalloc (apr_pool_t *p, apr_size_t size)

**APR模块**

| 名称          | 目的                     |
| ------------- | ------------------------ |
| apr_allocator | 内存分配，内部使用       |
| apr_atomic    | 原子操作                 |
| apr_dso       | 动态加载代码（.so/.dll） |
| apr_env       | 读取/设定环境变量        |
| apr_errno     | 定义错误条件和宏         |
| apr_file_info | 文件系统对象和路径的属性 |
| apr_file_io   | 文件系统输入/输出        |
| apr_fnmatch   | 文件系统模式匹配         |
| apr_general   | 初始化/终结，有用的宏    |

 

| 名称              | 目的                    |
| ----------------- | ----------------------- |
| apr_getopt        | 命令参数                |
| apr_global_mutex  | 全局锁                  |
| apr_hash          | 哈希表                  |
| apr_inherit       | 文件句柄继承助手        |
| apr_lib           | 奇数和末端              |
| apr_mmap          | 内存映射                |
| apr_network_io    | 网络输入/输出（套接字） |
| apr_poll          | 投票                    |
| apr_pools         | 资源管理                |
| apr_portable      | APR到本地映射转换       |
| apr_proc_mutex    | 进程锁                  |
| apr_random        | 随机数                  |
| apr_ring          | 环数据结构和宏          |
| apr_shm           | 共享内存                |
| apr_signal        | 信号处理                |
| apr_strings       | 字符串操作              |
| apr_support       | 内部支持函数            |
| apr_tables        | 表格和数组函数          |
| apr_thread_cond   | 线程条件                |
| apr_thread_mutex  | 线程锁                  |
| apr_thread_proc   | 线程和进程函数          |
| apr_thread_rwlock | 读写锁                  |
| apr_time          | 时间/日期函数           |
| apr_user          | 用户和组ID服务          |
| apr_version       | APR版本                 |
| apr_want          | 标准头文件支持          |

**APU模块**

| 名称               | 目的                                                |
| ------------------ | --------------------------------------------------- |
| apr_anylock        | 透明的、任何锁的封装                                |
| apr_base64         | Base-64编码                                         |
| apr_buckets        | Buckets/Bucket brigade                              |
| apr_date           | 时间字符串解析                                      |
| apr_dbd            | 针对SQL数据库的常用API                              |
| apr_dbm            | 针对DBM数据库的常用API                              |
| apr_hooks          | 钩子实现宏                                          |
| apr_ldap           | LDAP授权API                                         |
| apr_ldap_init      | LDAP初始化API，主要应用在和LDAP服务器的初始安全连接 |
| apr_ldap_option    | 设置LDAP选项的API                                   |
| apr_ldap_url       | 解析和处理LDAP URL的API                             |
| apr_md4            | MD4编码                                             |
| apr_md5            | MD5编码                                             |
| apr_optional       | 可选函数                                            |
| apr_optional_hooks | 可选钩子                                            |
| apr_queue          | 线程安全的FIFO队列                                  |
| apr_reslist        | 资源池                                              |
| apr_rmm            | 可再定位地址的内存                                  |

 

| 名称         | 目的               |
| ------------ | ------------------ |
| apr_sdbm     | SDBM库             |
| apr_sha1     | SHA1编码           |
| apr_strmatch | 字符串模式匹配     |
| apr_uri      | URI解析/构造       |
| apr_uuid     | 用户标识           |
| apr_xlate    | 字符集转换（I18N） |
| apr_xml      | XML解析            |





#### bstring（better string）

- bfromcstr（char *)将把一个C字符串转化为bstring，即产生一个bstring。

- 每一个调用完bstring本身的释放，可用bdestroy（bstring a)的形式。

- bstrcat(p = bfromcstr("Hello,"), q = bfromcstr(" World"));

用于把后面字符串添加到前面字符串的后面，注意后面字符串q拿bdestroy消除

- binstr

  `int binstr (const_bstring b1, int pos, const_bstring b2)`

在b1的这个bstring型字符串的中寻找b2这个bstring类型的字符串

- bconchar

  `int bconchar (bstring b, char c)`将c字符加到bstring类型字符串b的后面

- bstring

bstring是better string library为了避免c语言中字符串的诸多问题而开发的库，bstring 是一个头指针，它包装了一个指向 char 缓冲区的指针。 

bstring 是一个头指针，它包装了一个指向 char 缓冲区的指针。 如下是关于结构体 tagbstring 的声明：

struct tagbstring {
　　int mlen;
　　int slen;
unsigned char * data;
};

```
typedef struct tagbstring *bstring
```

其中，mlen 表示为数据字段分配的内存的下限。 slen 表示 bstring 的确切长度。data 是一个连续的无符号字符缓冲区。注意 unsigned char 缓冲区中， '\0' 字符不一定表示 bstring 的结尾。更规范地使用Bstrlib，mlen 字段必须至少是 slen 字段的长度，并且 slen 必须是非负数。 此外，data 必须指向一个有效的缓冲区，在该缓冲区中已获得对第一个 mlen 字符的访问。

****

- bread

typedef size_t (*bNread)(void *buff, size_t elsize, size_t nelem, void *parm); 

 **size_t fread(void \*ptr, size_t size, size_t nmemb, FILE \*stream)**

bNread与fread相似，第一个参数都是指向堆中的指针，第二个为存储大小，第三个为该存储大小个数，但第四个参数，二者就不相同了因为`fread`需要一个 `FILE *` 作为它的第四个参数而一个真正的函数`bNread` 指向的类型需要一个 `void *`，而void*可以强转为任何类型的指针。

extern bstring bread(bNread readPtr, void *parm);

`bread()` 是一个将指向函数的指针作为参数的函数。 `bNread` 类型用于指定函数的类型。 `fread()` 函数非常接近，只有第四个参数指针类型不同，因此可以强制转换作为bread的第一个参数—— `bread` 的第二个参数是作为第四个参数传递给 `bNread` 指向的函数的值。![image-20231128204639032](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231128204639032.png)

如上--------注意这里的bread参数里有个函数指针，因此调用时不需要函数参数，直接调用了func，就是这样相似的方式去实现无参数调用

[具体的fread和fNread](https://stackoverflow.com/questions/13441974/using-bread-to-return-a-bstring)

****

## 更多宏使用简化过程

使用宏定义，多利用宏的替代作用，如下：为利用宏进行链表的遍历，来源ex32，之后进行遍历，只需调用LIST_FOREACH,自动替换为for总的循环

```c
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)
```

****

## 系统化编程（重点）

### 建立一个c的目录框架

```
LICENSE
```

如果你在项目中发布源码，你会希望包含一份协议。如果你不这么做，虽然你有代码的版权，但是通常没有人有权使用。

```
README.md
```

对你项目的简要说明。作为Markdown来解析。

```
Makefile
```

这个项目的主要构建文件。

```
bin/
```

放置可运行程序的地方。这里通常是空的，Makefile会在这里生成程序。

```
build/
```

当值库和其它构建组件的地方。通常也是空的，Makefile会在这里生成这些东西。

```
src/
```

放置源码的地方，通常是`.c`和`.h`文件。

```
tests/
```

放置自动化测试的地方。

随后将编写的程序放在src中，编写makefile，输入make即可运行程序

注：这里的编写程序应为一堆不包含main函数的函数

tests放入自动化测试部分

### makefile

makefile通过一些基础设定后，将所有.c,.h文件转换为对应格式，随后进行tests测试，进行runtests.sh脚本

而该脚本中的内容，更是用valgrind实行tests.c自动化测试，从而跳到自动化测试的部分，并巧妙的运用了echo和重定向，将valgrind的结果重定向到了记录文件log中

同时通过正则表达式的灵活运用，确保了灵活性。

### 自动化测试

#### minunit

通过一些非常巧妙的宏定义，奠定灵活自动化测试的基础，在不同的程序中只需要更改不同头文件的包含位置，即可运行，非常巧妙通用性强。

原理是宏定义很多自动化测试中使用的函数，如

mu_suite_start代表自动化测试开始，

mu_assert为自动化测试中的断言，

mu_run_test为自动化测试中对于test.c文件中函数的调用，

mu_run_test（）巧妙的设计使其调用函数并正常返回调用信息，同时记录自动化测试调用函数验证的次数。

**重点来了**

RUN_TESTS宏函数展开为main主函数，这里包含了自动化测试的最终输出信息和运行基础main主函数，该部分验证了自动化测试是否正常，并输出了调用函数的次数，输出所有测验是否正常通过

#### test

主要的根据不同程序不一样编写的测试主体，主要功能是对src中编写的函数进行使用验证，因此一般会带有一大堆函数，每个函数去对应src中功能函数，并调用对应的函数

**但是**  无论什么程序，test.c最后都会包含一个all_tests()这样的伪主函数，在这里会对应minunit.h，也就是说自动化测试从这里开始，第一行必定是mu_suite_start(）自动化开始，随后用minunit中的mu_run_test调用test.c中其他编写的函数

最后写完所有函数后，在尾部添加RUN_TESTS(all_tests)对应minunit中的RUN_TEST，确保真主函数可以从伪主函数all_tests开始。

如此，自动化测试结束

## inline修饰符函数类型

为了解决一些频繁调用的小函数大量消耗栈空间（栈内存）的问题，特别的引入了 **inline** 修饰符，表示为内联函数。

### inline使用限制

**inline** 的使用是有所限制的，inline 只适合涵数体内代码简单的涵数使用，不能包含复杂的结构控制语句例如 while、switch，并且不能内联函数本身不能是直接递归函数（即，自己内部还调用自己的函数）。

### inline仅是一个对编译器的建议

**inline** 函数仅仅是一个对编译器的建议，所以最后能否真正内联，看编译器的意思，它如果认为函数不复杂，能在调用点展开，就会真正内联，并不是说声明了内联就会内联，声明内联只是一个建议而已。

### 建议 inline 函数的定义放在头文件中

其次，因为内联函数要在调用点展开，所以**编译器必须随处可见内联函数的定义**，要不然就成了非内联函数的调用了。所以，这要求每个调用了内联函数的文件都出现了该**内联函数的定义**。
