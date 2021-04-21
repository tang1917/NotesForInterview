1. gcc工作流程
   * 预处理   -E
     * 宏替换
     * 头文件展开
     * 注释去掉
     * xxx.c->xxx.i
   * 编译--S
     * xxx.i->xxx.s
     * 汇编文件
   * 汇编 -c
     * xxx.s->xxx.o
     * 二进制文件
   * 链接
     * xxx.o->xxx(可执行)

2. gcc常用参数

   * -v/--version

   * -I  重新指定头文件的路径

     * gcc sum.c -I ./include/ -o sum

   * -c ：将汇编文件生成二进制文件，得到了一个.o文件

   * -o:指定生成的文件的名字

   * -g:

     gdb调试的时候需要添加

   * -D

     在编译的时候指定一个宏

   * -Wall 

     添加警告信息

   * -On
     * 优化代码，n是优化级别：1，2，3