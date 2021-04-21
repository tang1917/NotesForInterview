1. gcc a.c b.c c.c -o app

   gcc a.c b.c c.c -o app -g

   -g: 会保留函数名和变量名

2. 启动gdp

   gdp 可执行程序的名字

   a. gdp app

   b. 给程序传参：set args xxx xxx

3. 查看代码

   * 当前文件
     * l
     * l 行号
     * l 函数名
   * 非当前文件：
     * l 文件名：行号
     * |文件名：函数名
   * 设置显示行数：
     * set listsize n
     * show listsize

4. 断点操作 - break / b

   * 设置断点

     * b 行号
     * b 函数名
     * b 文件名：行号
     * b文件名：函数名

   * 查看断点

     * info(i) b

   * 删除断点

     * d num(断点的编号)

     * 删除多个：

       d num1 num2

       d num1-num2

   * 设置断点无效

     * dis num(编号)

   * 断点生效

     * ena num(编号)

   * 设置条件断点

     * b行号 if 变量==var

5. 调试相关命令

   * 让gdb跑起来
     * 

   * 打印变量的值：
     * p 变量名
   * 打印变量的类型：
     * ptype 变量名
   * 向下单步调试：
     * next - n
       * 不会进入函数体
     * step - s
       * 会进入函数体内部
         * 跳出函数体：finish
   * 继续运行gdb，停在下一个断点的位置
     * continue - c
   * 退出gdb
     * quit -q
   * 变量的自动显示
     * display 变量名
     * 取消：undisplay 编号
       * 查看编号： i display
   * 从循环体直接跳出
     * until
       * 不能有断点
   * 直接设置变量等于某一个值
     * set var 变量名=value

