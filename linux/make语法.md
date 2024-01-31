# make语法

[TOC]



## 核心

```
target ... : prerequisites依赖 ...
    recipe方法
    ...
    ...
```

- target

  可以是一个object file（目标文件），也可以是一个可执行文件，还可以是一个标签（label）。

- prerequisites

  生成该target所依赖的文件和/或target。

- recipe

  该target要执行的命令（**任意的shell命令**）。每一条shell命令独自使用一个shell，如果想在一个shell中实现，要添加   .ONESHELL:          shell语句回写问题（每次执行语句会把命令本身也打印出来）在命令前方加一个@解决或者是在开头写   .SILENT：                 在命令前端加“-”

方法和依赖也可以写到同一行，但是要拿分号隔开。

order——only依赖：

在依赖文件右边添加竖线 “|” ，在竖线右边的依赖文件在make执行时不会再去检查依赖文件是否更改，也就是说依赖文件改动后也不会重新生成目标文件

****

后续的recipe行定义了如何生成目标文件的操作系统命令，一定要以一个 `Tab` 键作为开头

由于make的依赖性，make会在第一个target开始一层又一层地去找文件的依赖关系，**直到最终编译出第一个目标文件**。因此与第一个目标文件无直接或间接关系的target，make不会执行该target下的recipe命令

因此可以在makefile开头写   .DEFAULT_GOAL = 目标target    去手动指定最终目标

****

文件更新make是根据日期判断的，如果目标文件日期早于需要的依赖文件（即依赖文件被改变），那么就会重新编译该依赖文件，更新目标文件

使用别的文件名来书写Makefile，比如：“Make.Solaris”，“Make.Linux”等，要指定特定的Makefile，使用make的 `-f` 或 `--file` 参数，如： `make -f Make.Solaris` 或 `make --file Make.Linux` 。如果使用多条 `-f` 或 `--file` 参数，你可以指定多个makefile。

## **make执行规则：**

分两个阶段，第一阶段读取阶段——读取Makefile文件的所有内容，根据Makefile的内容在程序内建立起变量并在程序内构建起显式规则、隐式规则建立目标和依赖之间的依赖图。第二阶段目标更新阶段——用第一阶段构建起来的数据确定哪个目标需要更新然后执行对应的更新方法，变量和函数的展开如果发生在第一阶段，就称作立即展开，否则称为延迟展开。立即展开的变量或函数在第一个阶段，也就是Makefile被读取解析的时候就进行展开。延迟展开的变量或函数将会到用到的时候才会进行展开，有以下两种情况:

在一个立即展开的表达式中用到
在第二个阶段中用到
显式规则中，目标和依赖部分都是立即展开，在更新方法中延迟展开

由于其两阶段的特性，因此要区分第一第二阶段，搞清楚先后性，如果用“=”进行变量的命名，会等到第二阶段才进行展开（此时后面给变量赋值也可以），如果用“：=”就会立即展开

## 包含其他makefile及文件寻找

### 包含其他makefile

使用 `include` 指令可以把别的Makefile包含进来，被包含的部分会出现在原include的地方

```
include <filenames>...
```

`<filenames>` 可以是当前操作系统Shell的文件模式（可以包含路径和通配符）。

在 `include` 前面可以有一些空字符，但是绝不能是 `Tab` 键开始。 `include` 和 `<filenames>` 可以**用一个或多个空格隔开。**举个例子，你有这样几个Makefile： `a.mk` 、 `b.mk` 、 `c.mk` ，还有一个文件叫 `foo.make` ，以及一个变量 `$(bar)` ，其包含了 `bish` 和 `bash` ，那么，下面的语句：

```
include foo.make *.mk $(bar)
```

等价于：

```
include foo.make a.mk b.mk c.mk bish bash
```

****

### make文件寻找

make会在当前目录下首先寻找，如果当前目录下没有找到，那么，make还会在下面的几个目录下找：

1. 如果make执行时，有 `-I` 或 `--include-dir` 参数，那么make就会在这个参数所指定的目录下去寻找。
2. 接下来按顺序寻找目录 `<prefix>/include` （一般是 `/usr/local/bin` ）、 `/usr/gnu/include` 、 `/usr/local/include` 、 `/usr/include` 。

环境变量 `.INCLUDE_DIRS` 包含当前 make 会寻找的目录列表。你应当避免使用命令行参数 `-I` 来寻找以上这些默认目录，否则会使得 `make` “忘掉”所有已经设定的包含目录，包括默认目录。

让make不理那些无法读取的文件，而继续执行，你可以在include前加一个减号“-”。如：

```
-include <filenames>...
```

其表示，无论include过程中出现什么错误，都不要报错继续执行。如果要和其它版本 `make` 兼容，可以使用 `sinclude` 代替 `-include` 。

#### 特殊变量VPATH

没有指明这个变量，make只会在当前的目录中去找寻依赖文件和目标文件。有VPATH，make就会在当前目录找不到的情况下，到所指定的目录中去找寻文件

```
VPATH = src:../headers
```

上面的定义指定两个目录，“src”和“../headers”，make会按照这个顺序进行搜索。目录由“冒号”分隔。（当前目录永远是最高优先搜索的地方）

#### 关键字vpath（注意是小写）

更为灵活。它可以指定不同的文件在不同的搜索目录中。这是一个很灵活的功能。它的使用方法有三种：

- `vpath <pattern> <directories>`

  为符合模式<pattern>的文件指定搜索目录<directories>。

- `vpath <pattern>`

  清除符合模式<pattern>的文件的搜索目录。

- `vpath`

  清除所有已被设置好了的文件搜索目录。

vpath使用方法中的<pattern>需要包含 `%` 字符。 `%` 的意思是匹配零或若干字符，例如 `%.h` 表示所有以 `.h` 结尾的文件。<pattern>指定了要搜索的文件集，而<directories>则指定了< pattern>的文件集的搜索的目录。例如：

```
vpath %.h ../headers
```

该语句表示，要求make在“../headers”目录下搜索所有以 `.h` 结尾的文件。（如果某文件在当前目录没有找到的话）

我们可以连续地使用vpath语句，以指定不同搜索策略。如果连续的vpath语句中出现了相同的<pattern> ，或是被重复了的<pattern>，那么，make会按照vpath语句的先后顺序来执行搜索。如：

```
vpath %.c foo
vpath %.c blish
vpath %.c bar
```

其表示 `.c` 结尾的文件，先在“foo”目录，然后是“blish”，最后是“bar”目录。

```
vpath %.c foo:bar
vpath %.c blish
```

而上面的语句则表示 `.c` 结尾的文件，先在“foo”目录，然后是“bar”目录，最后才是“blish”目录。

****

### 特殊环境变量 `MAKEFILES`

make会把这个变量中的值做一个类似于 `include` 的动作。这个变量中的值是其它的Makefile，用空格分隔（相当于引入另一个makefile）。只是，它和 `include` 不同的是，从这个环境变量中引入的Makefile的“目标”不会起作用，如果环境变量中定义的文件发现错误，make也会不理。

只要这个变量一被定义，那么当你使用make时，所有的Makefile都会受到它的影响，这绝不是你想看到的。在这里提这个事，只是为了告诉大家，也许有时候你的Makefile出现了怪事，那么你可以看看当前环境中有没有定义这个变量。



## 书写规范

一般来说makefile中要有一个你最终要的文件，这个文件的实现就应该放到makefile的第一个目标，这样执行make就可以得到最终目标

同样地，makefile反斜杠（ `\` ）作为换行符。

### 通配符

支持三个通配符    ‘ * ’， ‘ ？ ’，‘ ~ ’。

### 伪目标

作为一个标签，为了避免和文件重名的这种情况，可以用标记“.PHONY”来显式地指明一个目标是“伪目标”，向make说明，不管是否有这个文件，这个目标就是“伪目标”。如：

```
.PHONY : clean
```

伪目标和目标之间可以彼此依赖，不过伪目标因为是一个标签，所以不会像target一样生成一个最终文件，伪目标内是命令，没有目标文件。

### 多目标

`$@` 表示目标的集合，就像一个数组， `$@` 依次取出目标，并执于命令。

### 静态模式

更加容易地定义多目标的规则

```
<targets ...> : <target-pattern> : <prereq-patterns ...>
    <commands>
    ...
```

targets定义了一系列的目标文件，可以有通配符。是目标的一个集合。

target-pattern是指明了targets的模式，也就是目标集。

prereq-patterns是目标的依赖文件，它对target-pattern形成的目标再进行一次依赖目标的定义。

看一个例子：

```
objects = foo.o bar.o

all: $(objects)

$(objects): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
```

上面的例子中，指明了我们的目标从$object中获取， `%.o` 表明要所有以 `.o` 结尾的目标，也就是 `foo.o bar.o` ，也就是变量 `$object` 集合的模式，而依赖模式 `%.c` 则取模式 `%.o` 的 `%` ，也就是 `foo bar` ，并为其加下 `.c` 的后缀，于是，我们的依赖目标就是 `foo.c bar.c` 。而命令中的 `$<` 和 `$@` 则是自动化变量， `$<` 表示第一个依赖文件， `$@` 表示目标集（也就是“foo.o bar.o”）。于是，上面的规则展开后等价于下面的规则：

```
foo.o : foo.c
    $(CC) -c $(CFLAGS) foo.c -o foo.o
bar.o : bar.c
    $(CC) -c $(CFLAGS) bar.c -o bar.o
```

“静态模式规则”的用法很灵活，如果用得好，那会是一个很强大的功能。再看一个例子：

```
files = foo.elc bar.o lose.o

$(filter %.o,$(files)): %.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@
$(filter %.elc,$(files)): %.elc: %.el
    emacs -f batch-byte-compile $<
```

$(filter %.o,$(files))表示调用Makefile的filter函数，过滤“$files”集，只要其中模式为“%.o”的内容。

### 自动依赖

大多数C/C++编译器支持“-M”选项，即自动找寻源文件中包含的头文件，并生成一个依赖关系。如果你使用GNU的C/C++编译器，你得用 `-MM` 参数，不然， `-M` 参数会把一些标准库的头文件也包含进来。命令使用如下

```
cc -MM main.c
```



可以把编译器为每一个源文件的自动生成的依赖关系放到一个文件中，为每一个 `name.c` 的文件都生成一个 `name.d` 的Makefile文件， `.d` 文件中就存放对应 `.c` 文件的依赖关系。

于是，我们可以写出 `.c` 文件和 `.d` 文件的依赖关系，并让make自动更新或生成 `.d` 文件，并把其包含在我们的主Makefile中，这样，我们就可以自动化地生成每个文件的依赖关系了。

这里，我们给出了一个模式规则来产生 `.d` 文件：

```
%.d: %.c
    @set -e; rm -f $@; \
    $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
    rm -f $@.$$$$
```

这个规则的意思是，所有的 `.d` 文件依赖于 `.c` 文件， `rm -f $@` 的意思是删除所有的目标，也就是 `.d` 文件，

第二行的意思是，为每个依赖文件 `$<` ，也就是 `.c` 文件生成依赖文件， `$@` 表示目标 `%.d` 文件，如果有一 个C文件是name.c，那么 `%` 就是 `name` ， `$$$$` 意为一个随机编号，第二行生成的文件有可能是“name.d.12345”，第三行使用sed命令做了一个替换。

完成后，把这些自动生成的规则放进我们的主Makefile中。使用Makefile的“include”命令，来引入别的Makefile文件，例如：

```
sources = foo.c bar.c

include $(sources:.c=.d)
```

上述语句中的 `$(sources:.c=.d)` 中的 `.c=.d` 的意思是做一个替换，把变量 `$(sources)` 所有 `.c` 的字串都替换成 `.d` 。

## 书写命令

每条命令都要以tab开头，#为注释符

### 命令显示

make执行时有“@”，那么，make将输出:

```
原命令：echo 正在编译XXX模块......
显示：正在编译XXX模块......
```

make执行时，带make参数 `-n` 或 `--just-print` ，那么其只是显示命令，但不会执行命令，用于调试Makefile，看看我们书写的命令是执行起来是什么样子的或是什么顺序的。

而make参数 `-s` 或 `--silent` 或 `--quiet` 则是全面禁止命令的显示。

### 命令执行

当目标文件需要更新时，make会执行其后的命令。让上一条命令的结果应用在下一条命令时，用分号分隔这两条命令。比如第一条命令是cd命令，你想打印出cd后的目录，即在cd后的基础上运行，那么你就不能把这两条命令写在两行上，而应该把这两条命令写在一行上，用分号分隔。如：

```
exec:
    cd /home/hchen; pwd
```

make一般使用环境变量SHELL中所定义的系统Shell来执行命令，即默认情况下使用UNIX的标准Shell——/bin/sh来执行命令。

寻找命令解释器：若UNIX风格的目录形式，首先，make会在SHELL所指定的路径中找寻命令解释器，如果找不到，其会在当前盘符中的当前目录中寻找，如果再找不到，其会在PATH环境变量中所定义的所有路径中寻找。

### 命令错误

因为有些命令出错后会终止执行，但有些命令我们不希望错误后退出，比如rm，mkdir只是确保某文件清除或建立，这时我们可以加一个  ’  -   ‘   号，确保无论成功与否都不会退出

或者给make加参数-i，或以.IGNORE作为目标，那么就不会跳出

-k会跳过报错的命令，继续执行其他命令

### 嵌套运行

在大的工程中，会包含多个不同模块的文件，这时候就涉及到了目录嵌套，

例如，我们有一个子目录叫subdir，这个目录下有个Makefile文件，那么我们总控的Makefile可以这样书写：

```
subsystem:
    cd subdir && $(MAKE)
```

以此实现多个Makefile文件在不同的文件夹中实现不同的功能

这里MAKE作为变量，确保了对下级目录make参数的修改功能

总控Makefile的变量可以传递到下级的Makefile中（如果你显示的声明），但是不会覆盖下层的Makefile中所定义的变量，除非指定了 `-e` 参数。

如果你要传递变量到下级Makefile中，那么你可以使用这样的声明:

```
export <variable ...>;
```

如果你不想让某些变量传递到下级Makefile中，那么你可以这样声明:

```
unexport <variable ...>;
```

想要传递所有上级变量，那么export后什么都不需要加，默认为全部

特殊变量：`SHELL` ，`MAKEFLAGS` ，这两个变量不管是否export，其总是要传递到下层 Makefile中，特别是 `MAKEFLAGS` 变量，其中包含了make的参数信息，只要执行“总控Makefile”时有make参数或是在上层 Makefile中定义了这个变量，那么 `MAKEFLAGS` 变量将会是这些参数，并会传递到下层Makefile中，这是一个系统级的环境变量。

但是make命令中的有几个参数并不往下传递，它们是 `-C` , `-f` , `-h`, `-o` 和 `-W` ，如果你不想往下层传递参数，那么，你可以这样来：

```
subsystem:
    cd subdir && $(MAKE) MAKEFLAGS=
```

如果你定义了环境变量 `MAKEFLAGS` ，那么你得确信其中的选项是大家都会用到的，如果其中有 `-t` , `-n` 和 `-q` 参数，那么将会有让你意想不到的结果。

还有一个在“嵌套执行”中比较有用的参数， `-w` 或是 `--print-directory` 会在make的过程中输出一些信息，让你看到目前的工作目录。比如，如果我们的下级make目录是“/home/hchen/gnu/make”，用make -w执行，有：

```
make: Entering directory `/home/hchen/gnu/make'.
```

而在完成下层make后离开目录时，有：

```
make: Leaving directory `/home/hchen/gnu/make'
```

注意：使用 `-C` 参数来指定make下层Makefile时， `-w` 会被自动打开。如果参数中有 `-s` （ `--slient` ）或是 `--no-print-directory` ，那么， `-w` 总是失效的。

### 命令包（命令合集）

为这些命令序列定义一个变量。定义这种命令序列的语法以 `define` 开始，以 `endef` 结束，如:

```
define run-yacc
yacc $(firstword $^)
mv y.tab.c $@
endef
```

这里，“run-yacc”是这个命令包的名字，注意不要和Makefile中的变量重名。在 `define` 和 `endef` 中间就是命令序列。这个命令包中的第一个命令是运行Yacc程序，因为Yacc程序总是生成“y.tab.c”的文件，所以第二行的命令就是把这个文件改名。

```
foo.c : foo.y
    $(run-yacc)
```

使用命令包，就像使用变量一样。命令包“run-yacc”中的 `$^` 就是 `foo.y` ， `$@` 就是 `foo.c` ，make在执行命令包时，命令包中的每个命令会被依次独立执行。

## 使用变量

### 变量基础概念

变量在声明时需要给予初值，在使用时，需要在变量名前加上 `$` 符号，用小括号 `()` 或是大括号 `{}` 把变量给包括起来。要使用真实的 `$` 字符，那么你需要用 `$$` 来表示。

变量就像c中的宏，只起到一个替换作用，**因此可以使用变量简化makefile**，将大量依赖文件给变量后，只需要简短的变量就可以实现替换。

注意makefile中可以用一个变量去赋值另一个变量，而且变量可以在任意一个地方被定义，即前面的变量也可以用后面变量的值，如下：

```
CFLAGS = $(include_dirs) -O
include_dirs = -Ifoo -Ibar
```

当 `CFLAGS` 在命令中被展开时，会是 `-Ifoo -Ibar -O` 。

但这种形式也有不好的地方，那就是递归定义，如：

```
CFLAGS = $(CFLAGS) -O
```

或：

```
A = $(B)
B = $(A)
```

这会使make进行无尽循环，虽然make可以查出这样的错误，另一个不好的地方就是，在变量中使用函数会使make运行非常缓慢

为了避免这种问题，另一种变量定义方式为“ := ”，如下：

```
x := foo
y := $(x) bar
```

这种方法，前面的变量不能使用后面的变量，只能使用前面已定义好了的变量。

条件操作符  ?=  若之前没有被定义过则执行，反之什么也不做

### 变量高级用法

替换变量中的共有的部分，格式是 `$(var:a=b)` 或是 `${var:a=b}` ，把变量“var”中所有以“a”字串“结尾”的“a”替换成“b”字串。这里的“结尾”意思是“空格”或是“结束符”。

示例：

```
foo := a.o b.o c.o
bar := $(foo:.o=.c)
```

定义`$(foo)` 变量，而第二行的意思是把 `$(foo)` 中所有以 `.o` 字串“结尾”全部替换成 `.c` ，所以我们的 `$(bar)` 的值就是“a.c b.c c.c”。

另外一种变量替换的技术是以“静态模式”（参见前面章节）定义的，如：

```
foo := a.o b.o c.o
bar := $(foo:%.o=%.c)
```

第二种高级用法是——“把变量的值再当成变量”。例：

```
x = y
y = z
a := $($(x))
```

在这个例子中，$(x)的值是“y”，所以$($(x))就是$(y)，于是$(a)的值就是“z”。（注意，是“x=y”，而不是“x=$(y)”）

因此可以使用多个变量来组成一个变量的名字，然后再取其值：

```
first_second = Hello
a = first
b = second
all = $($a_$b)
```

这里的 `$a_$b` 组成了“first_second”，于是， `$(all)` 的值就是“Hello”。

变量值追加符+=

与命令包一样，变量也可以用define关键字定义出多行变量

### 环境变量

系统环境变量可以在make开始运行时被载入到Makefile文件中，但是如果Makefile中已定义了这个变量，或是这个变量由make命令行带入，那么系统的环境变量的值将被覆盖。（如果make指定了“-e”参数，那么，系统环境变量将覆盖Makefile中定义的变量）

因此，如果我们在环境变量中设置了 `CFLAGS` 环境变量，那么我们就可以在所有的Makefile中使用这个变量了。这对于我们使用统一的编译参数有比较大的好处。如果Makefile中定义了CFLAGS，那么则会使用Makefile中的这个变量，如果没有定义则使用系统环境变量的值，像“全局变量”和“局部变量”的特性。

当make嵌套调用时，上层Makefile中定义的变量会以系统环境变量的方式传递到下层的Makefile 中。只有通过命令行设置的变量会被传递，定义在文件中的变量，如果要向下层Makefile传递，则需要使用export关键字来声明。

当然，但不推荐把许多的变量都定义在系统环境中

### 目标（局部）变量

大多数在makefile中定义的变量都为全局变量，也可以为某个目标设置局部变量，它的作用范围只在这条规则及连带规则中，

其语法是：

```
<target ...> : <variable-assignment>;

<target ...> : override <variable-assignment>
```

<variable-assignment>;可以是前面讲过的各种赋值表达式，如 `=` 、 `:=` 、 `+=` 或是 `?=` 。第二个语法是针对于make命令行带入的变量，或是系统环境变量。

这个特性非常的有用，当我们设置了这样一个变量，这个变量会作用到由这个目标所引发的所有的规则中去。如：

```
prog : CFLAGS = -g
prog : prog.o foo.o bar.o
    $(CC) $(CFLAGS) prog.o foo.o bar.o

prog.o : prog.c
    $(CC) $(CFLAGS) prog.c

foo.o : foo.c
    $(CC) $(CFLAGS) foo.c

bar.o : bar.c
    $(CC) $(CFLAGS) bar.c
```

在这个示例中，不管上一级目录还是全局的 `$(CFLAGS)` 值，在prog目标，以及其所引发的所有规则中（prog.o foo.o bar.o的规则）， `$(CFLAGS)` 的值都是 `-g`

## 条件判断

```
libs_for_gcc = -lgnu
normal_libs =

foo: $(objects)
ifeq ($(CC),gcc)
    $(CC) -o foo $(objects) $(libs_for_gcc)
else
    $(CC) -o foo $(objects) $(normal_libs)
endif
```

在上面示例的这个规则中，目标 `foo` 可以根据变量 `$(CC)` 值（编译器的不同）来选取不同的函数库来编译程序。

我们可以从上面的示例中看到三个关键字： `ifeq` 、 `else` 和 `endif` 。 `ifeq` 的意思表示条件语句的开始，并指定一个条件表达式，表达式包含两个参数，以逗号分隔，表达式以圆括号括起。 `else` 表示条件表达式为假的情况。 `endif` 表示一个条件语句的结束，**任何一个条件表达式都应该以 `endif` 结束。**

条件式语法：

```
<conditional-directive>
<text-if-true>
else
<text-if-false>
endif
```

其中 `<conditional-directive>` 表示条件关键字，如 `ifeq` 。这个关键字有四个。

- 第一个`ifeq`，比较括号中两个数是否相等 ，相等为真

- 第二个 `ifneq`，比较两个数是否不相等，不相等为真 

- 第三个`ifdef`，变量的值非空为真，

```
ifdef <variable-name>
```

当然， `<variable-name>` 同样可以是一个函数的返回值。

注意这里`ifdef`只查看是否变量有值，不会去展开，如下：

示例一：

```
bar =
foo = $(bar)
ifdef foo
    frobozz = yes
else
    frobozz = no
endif
```

示例二：

```
foo =
ifdef foo
    frobozz = yes
else
    frobozz = no
endif
```

第一个例子中， `$(frobozz)` 值是 `yes` ，第二个则是 `no`。

- 第四个`ifndef`与第三个相反

特别注意的是，make是在读取Makefile时就计算条件表达式的值，并根据条件表达式的值来选择语句，所以，你最好不要把自动化变量（如 `$@` 等）放入条件表达式中，因为自动化变量是在运行时才有的。

## 函数（需要用時再來看）

函数调用，也是以 `$` 来标识的，其语法如下：

```
$(<function> <arguments>)
```

这里， `<function>` 就是函数名，make支持的函数不多。 `<arguments>` 为函数的参数，**参数间以逗号 `,` 分隔，**而**函数名和参数之间以“空格”分隔**。函数调用以 `$` 开头，以圆括号把函数名和参数括起。

示例：

```
comma:= ,
empty:=
space:= $(empty) $(empty)
foo:= a b c
bar:= $(subst $(space),$(comma),$(foo))
```

在这个示例中， `$(comma)` 的值是一个逗号。 `$(space)` 使用了 `$(empty)` 定义了一个空格， `$(foo)` 的值是 `a b c` ， `$(bar)` 的定义，调用了函数 `subst` ，这是一个替换函数，这个函数有三个参数，第一个参数是被替换字串，第二个参数是替换字串，第三个参数是替换操作作用的字串。这个函数也就是把 `$(foo)` 中的空格替换成逗号，所以 `$(bar)` 的值是 `a,b,c` 。

### 字符串处理函数（很多）

#### subst

```
$(subst <from>,<to>,<text>)
```

- 名称：字符串替换函数

- 功能：把字串 `<text>` 中的 `<from>` 字符串替换成 `<to>` 。

- 返回：函数返回被替换过后的字符串。

- 示例：

  > ```
  > $(subst ee,EE,feet on the street)
  > ```

把 `feet on the street` 中的 `ee` 替换成 `EE` ，返回结果是 `fEEt on the strEEt` 。

#### patsubst

```
$(patsubst <pattern>,<replacement>,<text>)
```

- 名称：模式字符串替换函数。

- 功能：查找 `<text>` 中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式 `<pattern>` ，如果匹配的话，则以 `<replacement>` 替换。

- 返回：函数返回被替换过后的字符串。

- 示例：

  > ```
  > $(patsubst %.c,%.o,x.c.c bar.c)
  > ```

把字串 `x.c.c bar.c` 符合模式 `%.c` 的单词替换成 `%.o` ，返回结果是 `x.c.o bar.o`

#### strip

- 名称：去空格函数。

- 功能：去掉 `<string>` 字串中开头和结尾的空字符。

- 返回：返回被去掉空格的字符串值。

- 示例：

  > ```
  > $(strip a b c )
  > ```

  把字串 `a b c     ` 去掉开头和结尾的空格，结果是 `a b c`。

#### findstring

```
$(findstring <find>,<in>)
```

- 名称：查找字符串函数

- 功能：在字串 `<in>` 中查找 `<find>` 字串。

- 返回：如果找到，那么返回 `<find>` ，否则返回空字符串。

- 示例：

  > ```
  > $(findstring a,a b c)
  > $(findstring a,b c)
  > ```

第一个函数返回 `a` 字符串，第二个返回空字符串

#### filter

```
$(filter <pattern...>,<text>)
```

- 名称：过滤函数

- 功能：以 `<pattern>` 模式过滤 `<text>` 字符串中的单词，保留符合模式 `<pattern>` 的单词。可以有多个模式。

- 返回：返回符合模式 `<pattern>` 的字串。

- 示例：

  > ```
  > sources := foo.c bar.c baz.s ugh.h
  > foo: $(sources)
  >     cc $(filter %.c %.s,$(sources)) -o foo
  > ```

  `$(filter %.c %.s,$(sources))` 返回的值是 `foo.c bar.c baz.s` 。

#### filter-out

```
$(filter-out <pattern...>,<text>)
```

- 名称：反过滤函数

- 功能：以 `<pattern>` 模式过滤 `<text>` 字符串中的单词，去除符合模式 `<pattern>` 的单词。可以有多个模式。

- 返回：返回不符合模式 `<pattern>` 的字串。

- 示例：

  > ```
  > objects=main1.o foo.o main2.o bar.o
  > mains=main1.o main2.o
  > ```

  `$(filter-out $(mains),$(objects))` 返回值是 `foo.o bar.o` 。

#### sort

```
$(sort <list>)
```

- 名称：排序函数
- 功能：给字符串 `<list>` 中的单词排序（升序）。
- 返回：返回排序后的字符串。
- 示例： `$(sort foo bar lose)` 返回 `bar foo lose` 。
- 备注： `sort` 函数会去掉 `<list>` 中相同的单词。

#### word

```
$(word <n>,<text>)
```

- 名称：取单词函数
- 功能：取字符串 `<text>` 中第 `<n>` 个单词。（从一开始）
- 返回：返回字符串 `<text>` 中第 `<n>` 个单词。如果 `<n>` 比 `<text>` 中的单词数要大，那么返回空字符串。
- 示例： `$(word 2, foo bar baz)` 返回值是 `bar` 。

#### wordlist

```
$(wordlist <ss>,<e>,<text>)
```

- 名称：取单词串函数
- 功能：从字符串 `<text>` 中取从 `<ss>` 开始到 `<e>` 的单词串。 `<ss>` 和 `<e>` 是一个数字。
- 返回：返回字符串 `<text>` 中从 `<ss>` 到 `<e>` 的单词字串。如果 `<ss>` 比 `<text>` 中的单词数要大，那么返回空字符串。如果 `<e>` 大于 `<text>` 的单词数，那么返回从 `<ss>` 开始，到 `<text>` 结束的单词串。
- 示例： `$(wordlist 2, 3, foo bar baz)` 返回值是 `bar baz` 。

#### words

```
$(words <text>)
```

- 名称：单词个数统计函数
- 功能：统计 `<text>` 中字符串中的单词个数。
- 返回：返回 `<text>` 中的单词数。
- 示例： `$(words, foo bar baz)` 返回值是 `3` 。
- 备注：如果我们要取 `<text>` 中最后的一个单词，我们可以这样： `$(word $(words <text>),<text>)` 。

#### firstword

```
$(firstword <text>)
```

- 名称：首单词函数——firstword。
- 功能：取字符串 `<text>` 中的第一个单词。
- 返回：返回字符串 `<text>` 的第一个单词。
- 示例： `$(firstword foo bar)` 返回值是 `foo`。
- 备注：这个函数可以用 `word` 函数来实现： `$(word 1,<text>)` 。

以上，是所有的字符串操作函数，如果搭配混合使用，可以完成比较复杂的功能。这里，举一个现实中应用的例子。我们知道，make使用 `VPATH` 变量来指定“依赖文件”的搜索路径。于是，我们可以利用这个搜索路径来指定编译器对头文件的搜索路径参数 `CFLAGS` ，如：

```
override CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))
```

如果我们的 `$(VPATH)` 值是 `src:../headers` ，那么 `$(patsubst %,-I%,$(subst :, ,$(VPATH)))` 将返回 `-Isrc -I../headers` ，这正是cc或gcc搜索头文件路径的参数。

### 文件名操作函数

下面我们要介绍的函数主要是处理文件名的。每个函数的参数字符串都会被当做一个或是一系列的文件名来对待。

#### dir

```
$(dir <names...>)
```

- 名称：取目录函数——dir。
- 功能：从文件名序列 `<names>` 中取出目录部分。目录部分是指最后一个反斜杠（ `/` ）之前的部分。如果没有反斜杠，那么返回 `./` 。
- 返回：返回文件名序列 `<names>` 的目录部分。
- 示例： `$(dir src/foo.c hacks)` 返回值是 `src/ ./` 。

#### notdir

```
$(notdir <names...>)
```

- 名称：取文件函数——notdir。
- 功能：从文件名序列 `<names>` 中取出非目录部分。非目录部分是指最後一个反斜杠（ `/` ）之后的部分。
- 返回：返回文件名序列 `<names>` 的非目录部分。
- 示例: `$(notdir src/foo.c hacks)` 返回值是 `foo.c hacks` 。

#### suffix

```
$(suffix <names...>)
```

- 名称：取後缀函数——suffix。
- 功能：从文件名序列 `<names>` 中取出各个文件名的后缀。
- 返回：返回文件名序列 `<names>` 的后缀序列，如果文件没有后缀，则返回空字串。
- 示例： `$(suffix src/foo.c src-1.0/bar.c hacks)` 返回值是 `.c .c`。

#### basename

```
$(basename <names...>)
```

- 名称：取前缀函数——basename。
- 功能：从文件名序列 `<names>` 中取出各个文件名的前缀部分。
- 返回：返回文件名序列 `<names>` 的前缀序列，如果文件没有前缀，则返回空字串。
- 示例： `$(basename src/foo.c src-1.0/bar.c hacks)` 返回值是 `src/foo src-1.0/bar hacks` 。

#### addsuffix

```
$(addsuffix <suffix>,<names...>)
```

- 名称：加后缀函数——addsuffix。
- 功能：把后缀 `<suffix>` 加到 `<names>` 中的每个单词后面。
- 返回：返回加过后缀的文件名序列。
- 示例： `$(addsuffix .c,foo bar)` 返回值是 `foo.c bar.c` 。

#### addprefix

```
$(addprefix <prefix>,<names...>)
```

- 名称：加前缀函数——addprefix。
- 功能：把前缀 `<prefix>` 加到 `<names>` 中的每个单词前面。
- 返回：返回加过前缀的文件名序列。
- 示例： `$(addprefix src/,foo bar)` 返回值是 `src/foo src/bar` 。

#### join

```
$(join <list1>,<list2>)
```

- 名称：连接函数——join。

- 功能：把 `<list2>` 中的单词对应地加到 `<list1>` 的单词后面。如果 `<list1>` 的单词个数要比 `<list2>` 的多，那么， `<list1>` 中的多出来的单词将保持原样。如果 `<list2>` 的单词个数要比 `<list1>` 多，那么， `<list2>` 多出来的单词将被复制到 `<list1>` 中。

- 返回：返回连接过后的字符串。

- 示例： `$(join aaa bbb , 111 222 333)` 返回值是 `aaa111 bbb222 333` 

  #### foreach函数

foreach函数和别的函数非常的不一样。因为这个函数是用来做循环用的，Makefile中的foreach函数几乎是仿照于Unix标准Shell（/bin/sh）中的for语句，或是C-Shell（/bin/csh）中的foreach语句而构建的。它的语法是：

```
$(foreach <var>,<list>,<text>)
```

这个函数的意思是，把参数 `<list>` 中的单词逐一取出放到参数 `<var>` 所指定的变量中，然后再执行 `<text>` 所包含的表达式。每一次 `<text>` 会返回一个字符串，循环过程中， `<text>` 的所返回的每个字符串会以空格分隔，最后当整个循环结束时， `<text>` 所返回的每个字符串所组成的整个字符串（以空格分隔）将会是foreach函数的返回值。

所以， `<var>` 最好是一个变量名， `<list>` 可以是一个表达式，而 `<text>` 中一般会使用 `<var>` 这个参数来依次枚举 `<list>` 中的单词。举个例子：

```
names := a b c d

files := $(foreach n,$(names),$(n).o)
```

上面的例子中， `$(name)` 中的单词会被挨个取出，并存到变量 `n` 中， `$(n).o` 每次根据 `$(n)` 计算出一个值，这些值以空格分隔，最后作为foreach函数的返回，所以， `$(files)` 的值是 `a.o b.o c.o d.o` 。

注意，foreach中的 `<var>` 参数是一个临时的局部变量，foreach函数执行完后，参数 `<var>` 的变量将不在作用，其作用域只在foreach函数当中。

### if 函数

if函数很像GNU的make所支持的条件语句——ifeq（参见前面所述的章节），if函数的语法是：

```
$(if <condition>,<then-part>)
```

或是

```
$(if <condition>,<then-part>,<else-part>)
```

可见，if函数可以包含“else”部分，或是不含。即if函数的参数可以是两个，也可以是三个。 `<condition>` 参数是if的表达式，如果其返回的为非空字符串，那么这个表达式就相当于返回真，于是， `<then-part>` 会被计算，否则 `<else-part>` 会被计算。

而if函数的返回值是，如果 `<condition>` 为真（非空字符串），那个 `<then-part>` 会是整个函数的返回值，如果 `<condition>` 为假（空字符串），那么 `<else-part>` 会是整个函数的返回值，此时如果 `<else-part>` 没有被定义，那么，整个函数返回空字串。

所以， `<then-part>` 和 `<else-part>` 只会有一个被计算。

### call函数

call函数是唯一一个可以用来创建新的参数化的函数。你可以写一个非常复杂的表达式，这个表达式中，你可以定义许多参数，然后你可以call函数来向这个表达式传递参数。其语法是：

```
$(call <expression>,<parm1>,<parm2>,...,<parmn>)
```

当make执行这个函数时， `<expression>` 参数中的变量，如 `$(1)` 、 `$(2)` 等，会被参数 `<parm1>` 、 `<parm2>` 、 `<parm3>` 依次取代。而 `<expression>` 的返回值就是 call 函数的返回值。例如：

```
reverse =  $(1) $(2)

foo = $(call reverse,a,b)
```

那么， `foo` 的值就是 `a b` 。当然，参数的次序是可以自定义的，不一定是顺序的，如：

```
reverse =  $(2) $(1)

foo = $(call reverse,a,b)
```

此时的 `foo` 的值就是 `b a` 。

需要注意：在向 call 函数传递参数时要尤其注意空格的使用。call 函数在处理参数时，第2个及其之后的参数中的空格会被保留，因而可能造成一些奇怪的效果。因而在向call函数提供参数时，最安全的做法是去除所有多余的空格。

### origin函数

origin函数不像其它的函数，他并不操作变量的值，他只是告诉你你的这个变量是哪里来的？其语法是：

```
$(origin <variable>)
```

- 注意， `<variable>` 是变量的名字，不应该是引用。所以你最好不要在 `<variable>` 中使用

  `$` 字符。Origin函数会以其返回值来告诉你这个变量的“出生情况”，下面，是origin函数的返回值:

- `undefined`

  如果 `<variable>` 从来没有定义过，origin函数返回这个值 `undefined`

- `default`

  如果 `<variable>` 是一个默认的定义，比如“CC”这个变量，这种变量我们将在后面讲述。

- `environment`

  如果 `<variable>` 是一个环境变量，并且当Makefile被执行时， `-e` 参数没有被打开。

- `file`

  如果 `<variable>` 这个变量被定义在Makefile中。

- `command line`

  如果 `<variable>` 这个变量是被命令行定义的。

- `override`

  如果 `<variable>` 是被override指示符重新定义的。

- `automatic`

  如果 `<variable>` 是一个命令运行中的自动化变量。关于自动化变量将在后面讲述。

这些信息对于我们编写Makefile是非常有用的，例如，假设我们有一个Makefile其包了一个定义文件 Make.def，在 Make.def中定义了一个变量“bletch”，而我们的环境中也有一个环境变量“bletch”，此时，我们想判断一下，如果变量来源于环境，那么我们就把之重定义了，如果来源于Make.def或是命令行等非环境的，那么我们就不重新定义它。于是，在我们的Makefile中，我们可以这样写：

```
ifdef bletch
    ifeq "$(origin bletch)" "environment"
        bletch = barf, gag, etc.
    endif
endif
```

当然，你也许会说，使用 `override` 关键字不就可以重新定义环境中的变量了吗？为什么需要使用这样的步骤？是的，我们用 `override` 是可以达到这样的效果，可是 `override` 过于粗暴，它同时会把从命令行定义的变量也覆盖了，而我们只想重新定义环境传来的，而不想重新定义命令行传来的。

### shell函数

shell函数也不像其它的函数。顾名思义，它的参数应该就是操作系统Shell的命令。它和反引号“`”是相同的功能。这就是说，shell函数把执行操作系统命令后的输出作为函数返回。于是，我们可以用操作系统命令以及字符串处理命令awk，sed等等命令来生成一个变量，如：

```
contents := $(shell cat foo)
files := $(shell echo *.c)
```

注意，这个函数会新生成一个Shell程序来执行命令，所以你要注意其运行性能，如果你的Makefile中有一些比较复杂的规则，并大量使用了这个函数，那么对于你的系统性能是有害的。特别是Makefile的隐式规则可能会让你的shell函数执行的次数比你想像的多得多。

### 控制make的函数

make提供了一些函数来控制make的运行。通常，你需要检测一些运行Makefile时的运行时信息，并且根据这些信息来决定，你是让make继续执行，还是停止。

```
$(error <text ...>)
```

产生一个致命的错误， `<text ...>` 是错误信息。注意，error函数不会在一被使用就会产生错误信息，所以如果你把其定义在某个变量中，并在后续的脚本中使用这个变量，那么也是可以的。例如：

示例一：

```
ifdef ERROR_001
    $(error error is $(ERROR_001))
endif
```

示例二：

```
ERR = $(error found an error!)

.PHONY: err

err: $(ERR)
```

示例一会在变量ERROR_001定义了后执行时产生error调用，而示例二则在目录err被执行时才发生error调用。

```
$(warning <text ...>)
```

这个函数很像error函数，只是它并不会让make退出，只是输出一段警告信息，而make继续执行。

## make运行

make的一个环境变量叫 `MAKECMDGOALS` ，这个变量中存放了指定的终极目标的列表，如果在命令行上，你没有指定目标，那么，这个变量是空值。这个变量可以让你使用在一些比较特殊的情形下。比如下面的例子：

```
sources = foo.c bar.c
ifneq ( $(MAKECMDGOALS),clean)
    include $(sources:.c=.d)
endif
```

基于上面的这个例子，只要我们输入的命令不是“make clean”，那么makefile会自动包含“foo.d”和“bar.d”这两个makefile。

makefile一般都包含了编译、安装、打包等功能。我们可以参照这种规则来书写我们的makefile中的目标。

- all:这个伪目标是所有目标的目标，其功能一般是编译所有的目标。
- clean:这个伪目标功能是删除所有被make创建的文件。
- install:这个伪目标功能是安装已编译好的程序，其实就是把目标执行文件拷贝到指定的目标中去。
- print:这个伪目标的功能是例出改变过的源文件。
- tar:这个伪目标功能是把源程序打包备份。也就是一个tar文件。
- dist:这个伪目标功能是创建一个压缩文件，一般是把tar文件压成Z文件。或是gz文件。
- TAGS:这个伪目标功能是更新所有的目标，以备完整地重编译使用。
- check和test:这两个伪目标一般用来测试makefile的流程。

这些一般是我们makefile中的基础伪目标及其功能

### 检查makefile正确进行

可以使用make命令的下述参数：

- `-n`, `--just-print`, `--dry-run`, `--recon`

  不执行参数，这些参数只是打印命令，不管目标是否更新，把规则和连带规则下的命令打印出来，但不执行，这些参数对于我们调试makefile很有用处。

- `-t`, `--touch`

  这个参数的意思就是把目标文件的时间更新，但不更改目标文件。也就是说，make假装编译目标，但不是真正的编译目标，只是把目标变成已编译过的状态。

- `-q`, `--question`

  这个参数的行为是找目标的意思，也就是说，如果目标存在，那么其什么也不会输出，当然也不会执行编译，如果目标不存在，其会打印出一条出错信息。

- `-W <file>`, `--what-if=<file>`, `--assume-new=<file>`, `--new-file=<file>`

  这个参数需要指定一个文件。一般是是源文件（或依赖文件），Make会根据规则推导来运行依赖于这个文件的命令，一般来说，可以和“-n”参数一同使用，来查看这个依赖文件所发生的规则命令。

另外一个很有意思的用法是结合 `-p` 和 `-v` 来输出makefile被执行时的信息。在参数部分会进行介绍

### make参数

`-b`, `-m`

这两个参数的作用是忽略和其它版本make的兼容性。

`-B`, `--always-make`

认为所有的目标都需要更新（重编译）。

`-C` *<dir>*, `--directory`=*<dir>*

指定读取makefile的目录。如果有多个“-C”参数，make的解释是后面的路径以前面的作为相对路径，并以最后的目录作为被指定目录。如：“make -C ~hchen/test -C prog”等价于“make -C ~hchen/test/prog”。

****

`-debug`[=*<options>*]

输出make的调试信息。它有几种不同的级别可供选择，如果没有参数，那就是输出最简单的调试信息。下面是<options>的取值：

- a: 也就是all，输出所有的调试信息。（会非常的多）

- b: 也就是basic，只输出简单的调试信息。即输出不需要重编译的目标。

- v: 也就是verbose，在b选项的级别之上。输出的信息包括哪个makefile被解析，不需要被重编译的依赖文件（或是依赖目标）等。

- i: 也就是implicit，输出所有的隐含规则。

- j: 也就是jobs，输出执行规则中命令的详细信息，如命令的PID、返回码等。

- m: 也就是makefile，输出make读取makefile，更新makefile，执行makefile的信息。

  ****

`-d`

相当于“–debug=a”。

`-e`, `--environment-overrides`

指明环境变量的值覆盖makefile中定义的变量的值。

`-f`=*<file>*, `--file`=*<file>*, `--makefile`=*<file>*

指定需要执行的makefile。

`-h`, `--help`

显示帮助信息。

`-i` , `--ignore-errors`

在执行时忽略所有的错误。

`-I` *<dir>*, `--include-dir`=*<dir>*

指定一个被包含makefile的搜索目标。可以使用多个“-I”参数来指定多个目录。

`-j` [*<jobsnum>*], `--jobs`[=*<jobsnum>*]

指同时运行命令的个数。如果没有这个参数，make运行命令时能运行多少就运行多少。如果有一个以上的“-j”参数，那么仅最后一个“-j”才是有效的。（注意这个参数在MS-DOS中是无用的）

`-k`, `--keep-going`

出错也不停止运行。而是跳过该出错命令，如果生成一个目标失败了，那么依赖于其上的目标就不会被执行了。

`-l` *<load>*, `--load-average`[=*<load>*], `-max-load`[=*<load>*]

指定make运行命令的负载。

`-n`, `--just-print`, `--dry-run`, `--recon`

仅输出执行过程中的命令序列，但并不执行。

`-o` *<file>*, `--old-file`=*<file>*, `--assume-old`=*<file>*

不重新生成的指定的<file>，即使这个目标的依赖文件新于它。

```
-p`, `--print-data-base
```

输出makefile中的所有数据，包括所有的规则和变量。这个参数会让一个简单的makefile都会输出一堆信息。

如果你只是想输出信息而不想执行makefile，你可以使用“make -qp”命令。

如果你想查看执行makefile前的预设变量和规则，你可以使用 “make –p –f /dev/null”。

这个参数输出的信息会包含着你的makefile文件的文件名和行号，所以，用这个参数来调试你的 makefile会是很有用的，特别是当你的环境变量很复杂的时候。

`-q`, `--question`

不运行命令，也不输出。仅仅是检查所指定的目标是否需要更新。如果是0则说明要更新，如果是2则说明有错误发生。

`-r`, `--no-builtin-rules`

禁止make使用任何隐含规则。

```
-R`, `--no-builtin-variabes
```

禁止make使用任何作用于变量上的隐含规则。

```
-s`, `--silent`, `--quiet
```

在命令运行时不输出命令的输出。

```
-S`, `--no-keep-going`, `--stop
```

取消“-k”选项的作用。因为有些时候，make的选项是从环境变量“MAKEFLAGS”中继承下来的。所以你可以在命令行中使用这个参数来让环境变量中的“-k”选项失效。

```
-t`, `--touch
```

相当于UNIX的touch命令，只是把目标的修改日期变成最新的，也就是阻止生成目标的命令运行。

```
-v`, `--version
```

输出make程序的版本、版权等关于make的信息。

```
-w`, `--print-directory
```

输出运行makefile之前和之后的信息。这个参数对于跟踪嵌套式调用make时很有用。

```
--no-print-directory
```

禁止“-w”选项。

`-W` *<file>*, `--what-if`=*<file>*, `--new-file`=*<file>*, `--assume-file`=*<file>*

假定目标<file>;需要更新，如果和“-n”选项使用，那么这个参数会输出该目标更新时的运行动作。如果没有“-n”那么就像运行UNIX的“touch”命令一样，使得<file>;的修改时间为当前时间。

```
--warn-undefined-variables
```

只要make发现有未定义的变量，那么就输出警告信息

## 隐含规则

在你的makefile中改变这些变量的值，或是在make的命令行中传入这些值，或是在你的环境变量中设置这些值，无论怎么样，只要设置了这些特定的变量，那么其就会对隐含规则起作用。

makefile执行过程中涉及到隐含规则生产的中间文件会被rm删除

我们可以把隐含规则中使用的变量分成两种：一种是命令相关的，如 `CC` ；一种是参数相关，如 `CFLAGS` 。下面是所有隐含规则中会用到的变量：

### 关于命令的变量

- `AR` : 函数库打包程序。默认命令是 `ar`
- `AS` : 汇编语言编译程序。默认命令是 `as`
- `CC` : C语言编译程序。默认命令是 `cc`
- `CXX` : C++语言编译程序。默认命令是 `g++`
- `CO` : 从 RCS文件中扩展文件程序。默认命令是 `co`
- `CPP` : C程序的预处理器（输出是标准输出设备）。默认命令是 `$(CC) –E`
- `FC` : Fortran 和 Ratfor 的编译器和预处理程序。默认命令是 `f77`
- `GET` : 从SCCS文件中扩展文件的程序。默认命令是 `get`
- `LEX` : Lex方法分析器程序（针对于C或Ratfor）。默认命令是 `lex`
- `PC` : Pascal语言编译程序。默认命令是 `pc`
- `YACC` : Yacc文法分析器（针对于C程序）。默认命令是 `yacc`
- `YACCR` : Yacc文法分析器（针对于Ratfor程序）。默认命令是 `yacc –r`
- `MAKEINFO` : 转换Texinfo源文件（.texi）到Info文件程序。默认命令是 `makeinfo`
- `TEX` : 从TeX源文件创建TeX DVI文件的程序。默认命令是 `tex`
- `TEXI2DVI` : 从Texinfo源文件创建军TeX DVI 文件的程序。默认命令是 `texi2dvi`
- `WEAVE` : 转换Web到TeX的程序。默认命令是 `weave`
- `CWEAVE` : 转换C Web 到 TeX的程序。默认命令是 `cweave`
- `TANGLE` : 转换Web到Pascal语言的程序。默认命令是 `tangle`
- `CTANGLE` : 转换C Web 到 C。默认命令是 `ctangle`
- `RM` : 删除文件命令。默认命令是 `rm –f`

### 关于命令参数的变量

下面的这些变量都是相关上面的命令的参数。如果没有指明其默认值，那么其默认值都是空。

- `ARFLAGS` : 函数库打包程序AR命令的参数。默认值是 `rv`
- `ASFLAGS` : 汇编语言编译器参数。（当明显地调用 `.s` 或 `.S` 文件时）
- `CFLAGS` : C语言编译器参数。
- `CXXFLAGS` : C++语言编译器参数。
- `COFLAGS` : RCS命令参数。
- `CPPFLAGS` : C预处理器参数。（ C 和 Fortran 编译器也会用到）。
- `FFLAGS` : Fortran语言编译器参数。
- `GFLAGS` : SCCS “get”程序参数。
- `LDFLAGS` : 链接器参数。（如： `ld` ）
- `LFLAGS` : Lex文法分析器参数。
- `PFLAGS` : Pascal语言编译器参数。
- `RFLAGS` : Ratfor 程序的Fortran 编译器参数。
- `YFLAGS` : Yacc文法分析器参数。

### 自动化变量

- `$@` : 表示规则中的目标文件集。在模式规则（带有“%”）中，如果有多个目标，那么， `$@` 就是匹配于目标中模式定义的集合。
- `$%` : 仅当目标是函数库文件中，表示规则中的目标成员名。例如，如果一个目标是 `foo.a(bar.o)` ，那么， `$%` 就是 `bar.o` ， `$@` 就是 `foo.a` 。如果目标不是函数库文件（Unix下是 `.a` ，Windows下是 `.lib` ），那么，其值为空。
- `$<` : 依赖目标中的第一个目标名字。如果依赖目标是以模式（即 `%` ）定义的，那么 `$<` 将是符合模式的一系列的文件集。注意，其是一个一个取出来的。
- `$?` : 所有比目标新的依赖目标的集合。以空格分隔。
- `$^` : 所有的依赖目标的集合。以空格分隔。如果在依赖目标中有多个重复的，那么这个变量会去除重复的依赖目标，只保留一份。
- `$+` : 这个变量很像 `$^` ，也是所有依赖目标的集合。只是它不去除重复的依赖目标。
- `$*` : 这个变量表示目标模式中 `%` 及其之前的部分。如果目标是 `dir/a.foo.b` ，并且目标的模式是 `a.%.b` ，那么， `$*` 的值就是 `dir/foo` 。这个变量对于构造有关联的文件名是比较有效。如果目标中没有模式的定义，那么 `$*` 也就不能被推导出，但是，如果目标文件的后缀是make所识别的，那么 `$*` 就是除了后缀的那一部分。例如：如果目标是 `foo.c` ，因为 `.c` 是make所能识别的后缀名，所以， `$*` 的值就是 `foo` 。这个特性是GNU make的，很有可能不兼容于其它版本的make，所以，你应该尽量避免使用 `$*` ，除非是在隐含规则或是静态模式中。如果目标中的后缀是make所不能识别的，那么 `$*` 就是空值。

![image-20231206173341161](https://o5orde-oss.oss-cn-beijing.aliyuncs.com/image-20231206173341161.png)

加D或F区别在于目录还是文件

### 隐含规则搜索算法

一个目标叫 T。下面是搜索目标T的规则的算法。注意：所有的后缀规则在Makefile被载入内存时，会被转换成模式规则。如果目标是 `archive(member)` 的函数库文件模式，那么这个算法会被运行两次，第一次是找目标T，如果没有找到的话，那么进入第二次，第二次会把 `member` 当作T来搜索。

1. 把T的目录部分分离出来。叫D，而剩余部分叫N。（如：如果T是 `src/foo.o` ，那么，D就是 `src/` ，N就是 `foo.o` ）
2. 创建所有匹配于T或是N的模式规则列表。
3. 如果在模式规则列表中有匹配所有文件的模式，如 `%` ，那么从列表中移除其它的模式。
4. 移除列表中没有命令的规则。
5. 对于第一个在列表中的模式规则：
   1. 推导其“茎”S，S应该是T或是N匹配于模式中 `%` 非空的部分。
   2. 计算依赖文件。把依赖文件中的 `%` 都替换成“茎”S。如果目标模式中没有包含斜框字符，而把D加在第一个依赖文件的开头。
   3. 测试是否所有的依赖文件都存在或是理当存在。（如果有一个文件被定义成另外一个规则的目标文件，或者是一个显式规则的依赖文件，那么这个文件就叫“理当存在”）
   4. 如果所有的依赖文件存在或是理当存在，或是就没有依赖文件。那么这条规则将被采用，退出该算法。
6. 如果经过第5步，没有模式规则被找到，那么就做更进一步的搜索。对于存在于列表中的第一个模式规则：
   1. 如果规则是终止规则，那就忽略它，继续下一条模式规则。
   2. 计算依赖文件。（同第5步）
   3. 测试所有的依赖文件是否存在或是理当存在。
   4. 对于不存在的依赖文件，递归调用这个算法查找他是否可以被隐含规则找到。
   5. 如果所有的依赖文件存在或是理当存在，或是就根本没有依赖文件。那么这条规则被采用，退出该算法。
   6. 如果没有隐含规则可以使用，查看 `.DEFAULT` 规则，如果有，采用，把 `.DEFAULT` 的命令给T使用。

一旦规则被找到，就会执行其相当的命令，而此时，我们的自动化变量的值才会生成。