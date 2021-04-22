# 目录遍历相关函数

1. 打开一个目录

   * DIR *opendir(const char* * name)
   * 返回值：指向目录的指针

2. 读目录

   struct dirent * readdir(DIR *dirp)

   * 参数：opendir的返回值
   * 返回值：目录项结构体

3. 关闭目录

   * int  closedir(DIR * dirp)

   struct dirent

   {

   }

4. 独立完成递归操作读目录中指定类型文件个数的操作；

# dup-dup2

1. 复制文件描述符
   * int dup(int oldfd);
     * oldfd 要复制的文件描述符
     * 返回值：新的文件描述符
     * dup调用成功：
       * 有两个文件描述符指向同一个文件
     * 返回值：取最小的且没被占用的文件描述符
   * int dup2(int oldfd,int newfd);
     * oldfd->>hello
     * newfd->>world
       * 假设newfd已经指向了一个文件，首先断开与那个文件的链接，newfd指向oldfd指向的文件
       * newfd没有被占用，newfd指向oldfd指向的文件

# 改变已经打开的文件的属性：fcntl

* 变参函数
* 复制一个已有的文件描述符
  * int ret = fcntl(fd,F_DUPFD);
* 获取/设置文件状态标志
  * open的flags函数
  * 

