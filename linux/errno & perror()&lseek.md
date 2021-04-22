# errno & perror()

系统函数库 open,read,write,lseek等如果返回错误信息会修改全局变量errno的值，不同的值，对应不同的错误信息，使用perror()打印不同的错误信息。

# lseek

* 函数原型：off_t lseek(int fd,off_t offset,int whence)

  * SEEK_SET
  * SEEK_CUR
  * SEEK_END

* 使用

  * 文件指针移动到头部

    ​	lseek(fd,0,SEEK_SET)

  * 获取文件指针当前的位置

    int len = lseek(fd,0,SEEK_CUR)

  * 获取文件长度

    int len = lseek(fd,0,SEEK_END)

* 文件扩展

  * 文件原大小100k，扩展为1100k

    ​	lseek(fd,1000,SEEK_END)

  * 最后做一次写操作

    write(fd,"a",1);