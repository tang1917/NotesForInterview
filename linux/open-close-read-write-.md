1. pcb:结构体

   一个进程有一个文件描述符表：1024

   - 前三个被占用
   - 文件描述符符作用：寻找磁盘文件

2. open函数的使用

   * 函数原型：

     * int open(const char *pathname,int flags);
     * int open(const char *pathname,int flags,mode_t mode);

   * 参数

     * flags

       * 必选项 O_RDONLY,O_WRONLY,O_RDWR

       * 可选项

         * 创建文件：O_CREAT

         * 追加文件：O_APPEND
         * 文件截断：O_TRUNC
         * 设置非阻塞：O_NONBLOCK

       * mode

         * mode&~umask

3. read

   * 函数原型：ssize_t read(int fd,void *buf,size_t count)

4. write

   * 函数原型：ssize_t write(int fd,const void *buf.size_t count);