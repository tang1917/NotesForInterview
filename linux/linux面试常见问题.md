# 查看进程状态

ps aux: 查询内存中进程信息

ps aux | grep 进程ID

* STAT:该进程的状态，linux的进程有五种状态：
  * D不可中断
  * R 运行
  * S 中断
  * T停止
  * Z僵死



# 系统检测工具

## tcpdump

* 网络抓包工具

## lsof

* 当前系统打开的文件描述符工具

## nc

* 用来快速构建网络连接工具

## strace

* 跟踪程序执行过程中执行的系统调用和接收到的信号

## netstat

* 网络信息统计工具

## vmstat

* 实时输出系统各资源的使用情况

## mpstat

实时检测多处理器系统上每个资源的使用情况
