# make

* gcc - 编译器
* make - linux自带的构建器，是一个命令工具，解释makefile中的规则，构建我们的项目
  * 构建的规则在makefile中

# makefile文件的命名

- makefile
- Makefile

# makefile中的规则

gcc a.c b.c c.c -o app

- 三部分：**目标，依赖，命令**

**目标：依赖**

**（tab）命令**

eg:

app:a.c b.c c.c

​	gcc a.c b.c c.c -o app

- makefile由一条或多条规则组成

# makefile的编写

- **第一个版本**

  - app:a.c b.c c.c

    ​	gcc a.c b.c c.c -o app

  * 缺点：效率低，修改一个文件，所有文件会被全部重新编译

- **第二个版本**

  app:main.o add.o sub.o mul.o

  ​	gcc main.o add.o sub.o mul.o -o app

  main.o:main.c

  ​	gcc main.c -c 

  add.o:add.c

  ​	gcc add.c -c

  sub.o:sub.c

  ​	gcc sub.c -c

  mul .o:mul.c

  ​	gcc mul.c -c

  -  **工作原理：**
    - 检测依赖是否存在：
      - 向下搜索下边的规则，如果有规则是用来生成查找依赖的，执行规则中的命令
    - 依赖存在，判断是否需要更新：
      - 原则：目标时间》依赖时间
  - **缺点：**冗余

  

- **第三个版本**

  * 自定义变量

    object = a.o b.o c.o

    变量的取值：aa = $(obj)

  *  makefile自带的变量：大写
    * CPPFLAGS
    * CC
  * 自动变量：
    * $@:规则中的目标
    * $<:规则中的第一个依赖
    * $^：规则中的所有依赖
    * 只能在规则的命令中使用

  `obj = main.o add.o sub.o mul.o`

  `target = app`

  `$(target):$(obj)`

  ​	`gcc $(obj) -o $(target)`

  `%.o:%.c`

  ​	**gcc -c $< -o $@**

  模式匹配：

  %.o:%.c

  第一次：main.o没有

  main.o:main.c

  ​	gcc -c main.c -o main.o
  - 缺点：可移植性比较差

- **第四个版本**

  - makefile所有的函数都有返回值

  - 查找指定目录下指定类型的文件

    - src = $(wildcard ./*.c)
    - 匹配替换
      - obj = $(patsubst %.c,%.o,$(src))

  - src = $(wildcard ./*.c)

    obj = $(patsubst %.c,%.o,$(src))

    target = app

    $(target):$(obj)

    ​	gcc $^ -o $@

    %.o:%.c

    ​	gcc -c $< -o $@

  * **缺点**：不能清理项目

- **第五个版本**

  - 让make生成不是终极目标的目标

    - make 目标名

  - 编写一个清理项目的规划

    clean:

    ​	rm *.o app

  * 声明伪目标：

    .PHONY:clean

  * -f:强制执行

  * 命令前加-

    * 忽略执行失败的命令，继续向下执行其余命令