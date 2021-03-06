# Linux网络编程基础API

## socket地址API

* 主机字节序和网络字节序
  * 字节序
    * **在内存中的排列顺序会影响它被累加器装载成的整数的值**
  * 大端字节序
    * 一个整数的高位字节存储在内存的低地址处
  * 小端字节序
    * **一个整数的高位字节存储在内存中的高地址处**
  * 主机字节序
    * 现代pc大多采用小端字节序，因此小端字节序又被称为主机字节序
  * 网络字节序
    * **发送端总是把要发送的数据转化成大端字节序后发送，大端字节序又成为网络字节序**

* 通用socket地址
  * socket网络编程接口中表示socket地址的是结构体sockaddr
    * 结构体成员
      * 地址族类型
        * AF_UNIX
        * AF_INET
        * AF_INET6
      * sa_data成员
        * 用于存放socket地址值
* 各个协议族专用socket地址
  * AF_UNIX
    * sockaddr_un
  * IPV4
    * sockaddr_in
      * 地址族
      * 端口号
      * IPV4结构体
  * IPV6
    * sockaddr_in6
      * 地址族
      * 端口号
      * 流信息
      * IPV6结构体
      * scope ID(实验阶段)
* IP地址转换函数
  * int inet_pton(int af,const char* src,void* dst)
  * const char* inet_ntop(int af,const void* src, char* dst,socklen_t cnt)

## 创建socket

* int socket(int domain,int type,int protocol)
  * 底层协议族（PF_INET6,PF_INET4)
  * type参数指定服务类型
  * 默认
* 返回一个socket文件描述符

## 命名socket

创建socket时指定了地址族但未指定使用该地址族中哪个具体socket地址，将一个socket文件与socket地址绑定成为给socket命名，在服务器程序中，我们通常要命名socket，只有命名后客户端才知道如何连接它，客户端采用匿名方式，自动分配socket地址。

* int bind(int sockfd,const struct sockaddr* my_addr,socklent_t addrlen)

## 监听socket

socket被命名后，还不能马上接受客户连接，需要通过系统调用创建一个监听队列以存放待处理客户连接

* int listen(int sockfd,int backlog)

## 接受连接

* int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen)

sockfd参数是执行过listen系统调用的监听socket。addr参数用来获取被接受连接的远端socket地址，该socket的地址的长度由addrlen参数指出

## 发起连接

* int connect(int sockfd,const struct sockaddr *serv_addr,socklen_t addrlen)

sockfd参数由socket系统调用返回一个socket，serv_addr参数是服务器监听的socket地址，addrlen参数则指定了这个地址的长度，成功时返回0，失败时返回-1，并设置ERRNO

## 关闭连接

* int close(int fd)

fd参数是待关闭的socket，不过close系统调用并非总是立即关闭一个连接，而是将fd的引用计数减一，只有当fd的引用计数为0时才真正关闭连接。

* int shutdown(int sockfd,int howto)

立即关闭连接

## 数据读写

### TCP数据读写

* 对文件的读写操作read和write同样适用于socket。还有专门的系统调用

ssize_t recv(int sockfd,void *buf,size_t len,int flags);

ssize_t send(int sockfd,const void* buf,size_t len,int flags);

* flags参数为数据收发提供了额外的控制
  * MSG__OOB:发送或接收紧急数据
  * MSG_NOSIGNAL:往读端关闭的管道或者socket连接中写数据不引发SIGPIPE信号

### UDP数据读写

socket编程接口中用于UDP数据读写的系统调用时：

* ssize_t recvfrom(int sockfd,void* buf,size_t len,int flags,struct sockaddr* src_addr,socklen_t* addrlen);
* ssize_t sendto(int sockfd,const void* buf,size_t len,int flags,const struct sockaddr* dest_addr,socklent_t addrlen);

### 通用数据读写函数

* ssize_t recvmsg(int sockfd,struct msghdr* msg,int flags);
* ssize_t sendmsg(int sockfd,struct msghdr* msg,int flags);

## 带外数据

linux内核检测到TCP紧急标志时，将通知应用程序有带外数据需要接收。

内核通知应用程序带外数据到达的两种方式是：

* I/O复用产生的异常事件
* SIGURG信号

应用程序得到了有带外数据需要接收的通知，通过下面函数确定带外数据在数据流中的位置

* int sockatmark(int sockfd)

如果是，sockatmark返回1，此时利用带MSG_OOB标志的recv调用来接收带外数据

## 地址信息函数

* getsockname():获取本端socket地址
* getpeername():获取远端socket地址

## socket选项

读取和设置socket文件描述符属性的方法：

* getsockopt()
* setsockopt()

### SO_RCVLOWAT和SO_SNDLOWAT选项

一般被用来被I/O复用系统调用来判断socket是否可读或可写

## 网络信息API

* 根据主机名称/ip地址获取主机的完整信息
* 根据端口号/服务名称获取服务信息

# 高级I/o函数

## pipe函数

* int pipe(int fd[2])

  创建管道实现进程间的通信

  * fd[1]:写端口
  * fd[0]:读端口

## dup函数和dup2函数

创建一个新的函数描述符，与原有描述符指向相同的文件、管道或者网络连接

## readv函数和writev函数

* 从文件描述符读到分散的内存块中
* 将分散的内存数据一并写入文件描述符中

# sendfile函数

在两个文件描述符之间直接传递数据，从而避免了内核缓冲区和用户缓冲区之间的数据拷贝

## mmap函数和munmap函数

申请一块内存作为进程间通信的共享内存

## splice函数

在两个文件中移动数据

## tee函数

在两个管道文件符中复制数据

## fcntl函数

对文件描述符进行各种控制操作

# Linux服务器程序规范

## 日志

### Linux系统日志

* rsyslogd守护进程在接收到用户进程或内核输入的日志后，会把他们输出到某些特定的日志文件
* syslog函数
  * 应用进程使用syslog函数与rsyslogd守护进程通信。

## 用户信息

### UID\EUID\GID\EGID

* EUID存放的目的是方便资源访问：它使得运行程序的用户拥有该程序的有效用户权限

### 切换用户

## 进程间关系

* 进程组
* 会话
  * 一些有关联的进程组将形成一个会话
* 用ps命令查看进程关系

## 系统资源限制

Linux系统资源限制可以通过一对函数来读取和设置

* getrlimit()
* setrlimit()

## 改变工作目录和根目录

* chdir
* chroot

## 服务器程序后台化

后台进程又称守护进程，没有控制终端，因而不会意外接收到用户输入

1. **创建子进程，关闭父进程**
2. 设置文件权限
3. **创建新的会话，设置本进程为进程组首领**
4. 切换工作目录
5. 关闭标准输入设备、标准输出设备和标准错误输出设备
6. **关闭其他已经打开的文件描述符**
7. 将标准输入、标准输出和标准错误输出都定向到/dev/null文件

# 高性能服务器程序框架

## 服务器模型

* C/S模型
* P2P模型

## 服务器编程框架

* C/S模型
* P2P模型

## 服务器编程框架

* I/O处理单元
  * 等待并接受新的客户连接，接收客户数据，并将服务器响应数据返回给客户端
* 逻辑单元
  * 通常是一个进程或线程，它分析并处理客户数据，然后将结果传递给I/O处理单元或者直接发送给客户端
* 网络存储单元
  * 可以是数据库、缓存和文件，甚至是一台服务器
* 请求队列是各单元之间通信方式的抽象，I/O处理单元接受到客户请求时，需要以某种方式通知一个逻辑单元来处理该请求

## I/O模型

### 用户进程和系统进程（用户态和内核态）

在内核态可以访问系统资源，比如：处理器、输入输出IO、进程管理、内存、设备、计时器

进程间通信IPC、网络通信

* 同步IO

  要求用户代码自行执行I/O操作，将数据从内核缓存区读入用户缓存区或者将数据从用户缓存区写入内核缓存区（内核向应用程序通知的是就绪事件还是完成事件）

  * 阻塞I/O
  * 非阻塞I/O
  * I/O复用
    * 应用程序通过I/O复用函数向内核注册一组事件，内核通过I/O复用函数把其中的就绪事件通知给应用程序
  * 信号驱动IO
    * 为文件描述符指定宿主进程，当文件描述符上有事件发生，信号处理函数将被触发

* 异步IO

  **由内核来执行I/O操作，数据在内核缓存区和用户缓存区之间的移动由内核在“后台”完成**

## 两种高效的事件处理模式

* Reactor模式
  * **它要求主线程（I/O处理单元）只负责监听文件描述符上是否有事件发生，有的话就立即将该事件通知工作线程；数据的读写，接受新连接以及处理客户请求均在工作线程中完成**
* Proactor模式
  * **所有的I/O操作都交给主线程和内核来处理，工作线程仅仅负责业务逻辑**

## 两种高效的并发模式

由于I/O操作的速度远没有CPU的计算速度快，所以让程序阻塞于I/O操作将浪费大量时间，如果程序有多个执行线程，则当前被I/O操作所阻塞的执行线程可主动放弃CPU，将执行权转移到其他线程。

* 半同步/半异步模式
  * 同步异步指是否按照代码序列的顺序执行
  * 同步线程用于处理客户逻辑，异步线程用于处理I/O事件
* 领导者/追随者模式
  * 多个工作线程轮流获得事件源集合，轮流监听，分发并处理事件的一种模式
    * 句柄集：I/O资源
    * 线程集
    * 事件处理器和具体事件处理器
* 有限状态机

## 提高服务器性能的其他建议

* 池
  * 内存池
  * 进程池
  * 线程池

池是一组资源的集合，这组资源在服务器之初就被完全创建好并初始化，这称为静态资源分配，之后服务器运行中需要相关资源，无须动态分配，直接获取。这是一种利用服务器硬件资源，以换取运行效率的做法。

* 数据复制
* 上下文切换和锁

# IO复用

## select系统调用

* 用途：在一段指定的时间内，监听用户感兴趣的文件描述符上的可读，可写和异常等事件
* select API
  * int select(int nfds,fd_set* readfds,fd_set* writefds,fd_set* exceptfds,struct timeval* timeout);
* 文件描述符就绪条件
  * 可读
    * 内核接收缓冲区中的字节数大于或等于其低水位标记
    * socket通信的对方关闭连接，此时对该socket的读操作将返回0
    * 监听socket上有新的连接请求
    * socket上有未处理的错误
  * 可写
    * 发送缓存区可用字节数大于或等于其低水位标记
    * socket的写操作被关闭
    * socket使用非阻塞connect连接成功或者失败（超时）之后
    * socket上有未处理的错误

## poll系统调用

用途：在指定时间内轮询一定数量的文件描述符，以测试其中是否有就绪者

int poll(struct pollfd* fds,nfds_t nfds,int timeout);

## epoll系列系统调用

* epoll使用一组函数来完成任务，而不是单个函数
* epoll把用户关心的文件描述符上的事件放在内核里的一个事件表中，从而无须像select和poll那样每次调用都重复传入文件描述符集或事件集
* int epoll_create(int size)
* int epoll_ctl(int epfd,int op,int fd,struct epoll_event *event)
* int epoll_wait(int epfd,struct epoll_event* events,int maxevents,int timeout);
* LT和ET模式
  * epoll对文件符的操作有两种模式：LT(电平触发)和ET(边沿触发)
    * LT:
      * 将此事件通知应用程序后，应用程序可以不立即处理该事件，下一次调用epoll_wait时,还会再此像应用程序通知该事件
    * ET：
      * 应用程序必须立即处理该事件，因为后续的epoll_wait不会再向应用程序通知这一事件。可以降低epoll事件被触发的次数
      * 

* 阻塞IO和非阻塞IO的理解
  * 阻塞和非阻塞是应用程序对设备文件访问的两种方式，阻塞方式下，设备文件不可访问，进程就休眠，当设备文件可访问时，唤醒进程；非阻塞方式下，设备文件不可访问时，进程可以继续执行

* EPOLLONESHOT事件
  * 在使用ET模式时，在读取完某个socket上的数据后开始处理这些数据，而在处理该数据过程中该socket上又有新数据可读，此时另外一个线程被唤醒来读取这些新的数据，于是就出现了两个线程同时操作一个socket的局面。
  * 注册EPOLLONESHOT事件后当一个线程在处理某个socket时不允许别的线程有机会操作该socket，处理完成之后重置这个事件，别的socket才有机会处理这个socket
* select、poll和epoll区别
  * 事件集合
    * select：用户通过三个参数分别传入感兴趣的可读、可写以及异常等事件
    * poll：统一处理所有事件类型
    * epoLL:统一处理所有事件类型，通过一个事件表直接管理用户感兴趣的所有事件。
  * 索引就绪文件描述符的时间复杂度
    * o(n),o(n),o(1)
  * 最大支持文件描述符
    * 一般有最大限制	65535	65535
  * 工作模式
    * LT	LT 支持ET高效模式

## I/O复用的高级应用一：非阻塞connect

对非阻塞的socket调用connect,而连接又没有立即建立，可以使用I/O复用函数监听这个可写事件，当socket、poll返回后，在利用getsockopt来读取错误码，并清除该socket上的错误，如果错误码是0，表示连接成功建立，否则连接失败。可以同时发起多个连接，并一起等待。

## I/O复用的高级应用二：聊天室程序

* 客户端：同时处理网络连接和用户输入
* 服务器端：同时管理监听socket和连接socket

## I/O的高级应用三： 同时处理TCP和UDP服务

* 服务器监听多个端口
* 同一个端口同时处理该服务器上的TCP和UDP请求

## 超级服务xinetd

* xinetd配置文件
  * 主配置文件
  * 子配置文件
* xinetd工作流程

# 信号

* 信号产生的条件
  * 对于前台进程，用户可以通过输入特殊的终端字符来给它发送信号
  * 系统异常，比如浮点异常和非法内存段访问
  * 系统状态变化，比如alarm定时器到期
  * 运行kill命令或者调用kill函数

## Linux信号概述

* 发送信号
  * int kill(pid_t pid,int sig)
* 信号处理函数原型
  * typedef void(*__sighandler_t)(int)

* Linux信号
  * * SIGHUP 控制终端被挂起
    * SIGABRT 进程调用abort函数生成该信号
    * SIGURG socket连接上接收到紧急数据

* 终端系统调用
  * 程序在执行处于阻塞状态的系统调用信号，并且我们为该信号设置了信号处理函数，则默认情况下系统调用将被中断。

## 信号函数

* signal系统调用

  * _sighandler_t signal(int sig,sighandler_t  _handler)
    * sig是参数要捕获的信号类型,_handler是指定信号sig的处理函数，返回一个函数指针，前一次调用的，或者默认处理函数

* sigaction系统调用

  指定新的信号处理方式，返回之前信号的处理方式

## 信号集

* 信号集函数
* 进程信号掩码
* 进程信号掩码
  * sigprocmask
* 被挂起信号
  * 如果给进程发送一个被屏蔽的信号，则操作系统将该信号设置为进程的一个被挂起的信号

## 统一事件源

信号是一种异步事件：信号处理函数和程序的主循环是两条不同的执行路线。信号处理函数需要尽可能快的执行，以确保该信号不被屏蔽太久。

一种典型的解决方案是：把信号的主要处理逻辑放到程序的主循环中，当信号处理函数被触发时，它只是简单的通知主循环程序接收到信号，并把信号值传递给主循环，主循环再根据接收到的信号值执行目标信号对应的逻辑代码。信号处理函数使用管道来将信号“传递给主循环”：信号处理函数往管道的写端写入信号值，主循环则从管道的读端读出信号值。通过IO复用来监听管道的读端。

## 网络编程相关信号

* SIFHUP

  * 触发条件：当挂起信号的控制终端时，SIGHUB信号将被触发
  * lsof命令： 用于查看你进程开打的文件，打开文件的进程，进程打开的端口(TCP、UDP)，找回/恢复删除的文件。是十分方便的系统监视工具，因为lsof命令需要访问核心内存和各种文件，所以需要root用户执行

* SIGPIPE

  * 往一个读端关闭的管道或socket连接中写数据将引发SIGPIPE信号，程序收到SIGPIPE信号的默认行为是结束进程。
  * send函数返回的errno或者监听文件描述符上的POLLRDHUB事件

* SIGURG

  * 内核通知应用程序带外数据的两种方式
    * I/O复用技术：select系统调用再接收到带外数据时将返回，并向应用程序报告socket上的异常事件
    * 使用SIGURG信号

* 带外数据总结

  * 带外数据：用于迅速通告对方本端发生的重要事件，**带外数据比普通数据有更高的优先**级，它应该立即被发送，而不论发送缓冲区中是否有排队等待发送的普通数据。

  * TCP/UDP
    * **UDP没有实现带外数据传输，TCP利用其头部的紧急指针标志和紧急指针两个字段来提供一种紧急方式**
    * 发送多字节的带外数据，只有最后一个字节被当作带外数据
  * 检测带外数据是否到达的两种方法
    * I/O复用系统调用报告的异常事件
    * SIGURG信号
  * 应用程序发送接收带外程序
    * recv/send 标志 MSG_OOB

# 定时器

* 概述
  * 定时是指在一段时间后触发某段代码的机制，将每个定时事件封装成定时器，并使用某种容器类数据结构，比如链表，排序链表和事件轮将所有的定时器封串联起来，以实现对定时事件的统一管理。
  * LINUX提供了三种定时方法：
    * socket选项SO_RCVTIMEO和SO_SNDTIMEO
    * SIGALRM信号
    * I/O复用系统调用的超时参数

## SIGALRM信号

* **基于升序链表的定时器**
  * 超时时间
  * 任务回调函数
* 处理非活动连接

## I/O复用系统调用的超时函数

* 带有超时参数，需要不断更新定时参数反应剩余时间

## 高性能定时器

* 时间轮
  * 指针指向轮子上的一个槽，它以恒定的速度转动，每转动异步就指向下一个槽，每个槽指向一个定时器链表，每条链表上的定时器具有相同的特征：他们的定时时间相差N*si的整数倍
* 时间堆
  * 将所有定时器中超时时间最小的一个定时器的超时值作为心搏间隔。通过最小堆实现

# 高性能I/O框架库Libevent

## 概述

* I/O框架库以库函数的形式，封装了较为底层的系统调用，给应用程序提供了一组更便于使用的接口。
* 各种I/O框架库的实现原理基本相似，要么以Reactor模式，要么以Proactor模式实现，要么同时以这两种模式实现。
* 基于Reactor模式的I/O框架库
  * 句柄
    * 当内核检测到就绪事件时，将通过句柄来通知这一事件。在Linux环境下，I/O事件对应的句柄是文件描述符，信号事件对应的句柄就是信号值
  * 事件多路分发器
    * I/O框架库一般将系统支持的各种I/O复用系统封装成统一的接口，成为事件的多路分发器。
    * 事件处理器和具体事件处理器
      * 事件处理器执行事件对应的业务逻辑，它通常包含一个或多个handle_event回调函数，这些回调函数在事件循环中被执行。I/O框架库提供的事件处理器通常是一个接口，用户需要继承它来实现自己的事件处理器，一般事件处理器被声明为虚函数，以支持用户扩展。
  * Reactor
    * Reactor是I/O框架库的核心。它提供的几个主要方法是：
      * handle_events
        * 等待事件，然后依次处理所有就绪事件对应的事件处理器
      * register_handler,该方法调用事件多路分发器的register_event方法来往事件多路分发器中注册个事件
      * remove_handler,该方法调用事件多路分发器的remove_event方法来删除事件多路分发器中的一个事件

## Libevent源码分析

略

#  多进程编程

## 进程间共享

* 代码段、数据段、栈、堆、标准I/O缓存
* 文件描述符
* 内存映射区
* 所有的环境变量
* UID/EUID/GID/EGID
  * 使得运行程序的用户拥有该程序的有效用户权限

## 线程间共享

* 堆
* 全局变量
* 地址空间

# 进程池和线程池

## 动态创建子进程（子线程）实现并发服务的缺点

* 动态创建进程（线程）是比较耗费时间的，这将导致较慢的客户响应
* 动态创建的子进程通常只用来为一个客户服务，这将导致系统上产生大量的细微进程。进程间的切换将消耗大量的cpu时间
* 动态创建的子进程是当前进程的完整映像。当前进程必须谨慎的管理其分配的文件描述符和堆内存等系统资源，否则子进程可能复制这些资源，从而使系统资源急剧下降，进而影响服务器性能。

## 进程池和线程池概述

进程池是由服务器预先创建一组子进程，所有子进程运行着相同的代码，并具有相同的属性。

当有新任务到来时，主进程选择进程池中的一个子线程为新任务服务，两种方式：

* 主进程使用某种算法来主动选择子进程
* 主进程和所有子进程通过一个共享队列来同步，子进程都睡眠在该工作队列上。当有新的任务到来时，主进程将任务添加到工作队列中。这将唤醒正在等待任务的子进程，不过只有子进程获得新任务的接管权。

当选择好子进程后，主进程还需要使用某种通知机制来告诉目标子进程有新任务需要处理，并传递必要的数据。

# 慢系统调用

指可能永久阻塞的系统调用。

## EINTR

进程在一个慢系统调用(slow system call)中阻塞时，当捕获到某个信号且相应信号处理函数返回时，这个系统调用被中断，调用返回错误，设置errno为EINTR（相应的错误描述为“Interrupted system call”）

## 如何处理被中断的系统调用

* 人为重启被中断的系统调用
* 安装信号时设置SA_RESTART属性
* 忽略信号



# 线程安全

* 线程安全函数

**任何未使用静态数据或其他共享资源的函数都是线程安全的。使用静态数据或其他共享资源的函数，必须通过加锁的方式来使函数实现线程安全**。

* 线程安全

如果一个函数在同一时刻可以被多个线程安全地调用，不发生竞态条件，就称该函数是线程安全的。

* 可重入

**可重入（Reentrant）函数可以由多于一个线程并发使用，而不必担心数据错误**。**可重入函数可以在任意时刻被中断，稍后再继续运行，不会丢失数据。可重入性解决函数运行结果的确定性和可重复性**。

 		*  一个函数对于多个线程是可重入的，则这个函数是线程安全的
 		*  一个函数是线程安全的，但并不一定是可重入的，比如使用互斥锁实现的线程安全
 		*  可重入性要强于线程安全性

