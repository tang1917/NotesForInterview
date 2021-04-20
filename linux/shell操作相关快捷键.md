# shell操作相关快捷键
* **shell概念**：
命令解释器，用于用户和操作系统之间的交互
运行过程：
1. 解析输入的命令
2. 搜索环境变量的路径
3. 找到了输入的命令，运行这个程序

* **快捷键**：
**遍历历史记录**：history
向上：ctrl+p
向下：ctrl+n

**删除**：
删除光标前边字符：backspace,ctrl+h
删除光标后边字符：ctrl+d
删除光标前面的字符串：ctrl+u
删除光标后边的字符串：ctrl+k

**移动**
向前：ctrl+b
向后：ctrl+f
光标移动到头部：ctrl+a
光标移动到尾部：ctrl+e

**补全**
ctrl+tab
# linux目录结构
树结构
根目录用 / 表示，后面有子目录
- /bin:binary,二进制文件，可执行程序，也就是一些常见shell命令
- /dev:device,在linux下一切皆文件
* 硬盘，显卡，显示器
- /lib：linux运行的时候需要加载的一些动态库
- /mnt:手动的挂载目录
- /media:自动挂载目录
- /root:linux的超级用户的家目录
- /usr:unix system resource
* 头文件
* 游戏
* 用户安装的程序 /usr/local
- /etc:存放配置文件
* /etc/passwd
* /etc/group
* man 5 passwd
- /opt: 安装第三方应用程序
- /home: linux操作系统所有用户的家目录
    *用户家目录：（）/home/kevin
- /tmp: 存放临时文件

# 绝对路径和相对路径
1. 相对路径：从当前的目录开始表示
2. 绝对路径：从根目录下开始表示
3.  .和..
    * .当前目录
    * .. 当前目录的上一级目录
4.  ~：表示用户家目录
5.  pwd ： 显示当前的绝对路径
6. $：表示当前用户是普通用户；#：当前用户是超级用户


# 文件目录相关命令
1. tree
    * 查看目录内容
    * tree 查看当前目录
    * tree dir 查看指定目录
    * 需要安装： sudo apt-get install tree
    * 
2. ls
    * 功能：查看文件或目录
    * 语法：
    * 参数
        * -a 显示所有文件
            * 会显示隐藏文件
        * -l 显示文件类型
            -rwxr-xr-x 1 root root 149688 7月 28 2020 kmod
            * 第一个字符：文件的类型
                * 7种
                * 普通文件：-
                    * .txt 压缩包 可执行程序
                * 目录：d
                * 符号链接：l
                * 管道：p
                * 套接字：s
                * 字符设备：c
                    * 键盘，鼠标
                * 块设备：b
                    * u盘，硬盘
           * rwxr：文件所有者权限
           * xr: 文件所属组用户的权限
           * x:其他人对文件的操作权限
           * 1：硬链接技术
           * root :文件所有者
           * root:文件所属组
           * 149688：文件大小
               * 如果是目录，看到的大小永远是4k，表示的是目录存储空间，而不是里面的内容
           * 日期
           * 文件名
       * ll = ls -alF
三种类型的用户：
文件所有者：user
文件所属组用户：group
其他人：other
3. cd 切换目录
    a. cd目录
    b. 如何进入到家目录：
        * cd绝对路径
        * cd ~
        * cd
    c. 在临近的两个目录直接切换
        * 最后两个相邻的
        * cd -
        * 目录很长的情况
4. pwd 输出当前的路径
5. mkdir 创建目录
        * mkdir 目录名
        * 创建多级目录 -p
 6. touch 创建文件
        * touch 文件名
            * 如果不存在，创建文件
            * 文件存在：更新创建文件的时间
     
 7. rmdir 只能删除空目录
 8. rm
     *  目录
         *  rm 目录名 -r
             *  -r递归的方式处理
         *  注意问题
             *  删除之后很难恢复
             *  rm -a -i :给出删除的信息提示
    * 文件
        * rm 文件名 -i
 9. cp -- 拷贝
    * cp 要拷贝的文件（file1）  file(不存在)
        * 创建file，将file1中的内容拷贝到file
    * cp file1 file(存在)
        * file1覆盖file
    * cp file dir(存在)
        * 拷贝file到dir目录
    * cp dir(存在） dir1(存在)
        * 将dir目录拷贝到dir1目录中 ，包括dir目录
    * cp dir(存在) dir1(不存在)
        * 创建dir1
        * 将dir中的内容拷贝到dir1中，不包括dir目录
 10. mv - 改名或者移动

    * 用法：mv file1 file2
    * 改名
        * mv file(存在) file1(不存在) 
        * mv dir(存在) dir1(不存在)
    * 移动
        * mv file(文件) dir（存在目录）
        * mv dir(目录存在) dir1(目录存在)
    * mv file(存在) file2(存在)
        * file文件覆盖file2文件
11. 查看文件内容 --了解内容
    * cat
        * cat filename
            * 使用于文件比较小的情况
    * more
        * more filename
            * 回车：向下浏览一行
            * 空格：翻页，向下
            * 退出：q
    * less 
        * less filename
        * 向下滚动一行：
            * 回车，ctrl+n
        * 向上滚动一行：ctrl+p
        * 向下翻页：pagedown,空格
        * 向上翻页：pageup
        * 退出：q
    * head
        * 显示文件头部的内容，默认10行 
        * head -n filename, n为显示的行数
    * tail
        * 显示尾部内容，操作类似head
    
 12. 软硬链接 ln
     
     * 链接简单来说是一种文件共享方式，可以简单理解为Windows中常见的快捷方式。
     
     *  软链接 -- 快捷方式
         *  保存了其代表文件的绝对路径，在访问时替换自身的路径
     *  ln -s 文件名 快捷方式的名字 
    *  文件名使用绝对路径
     *  目录也可以创建软链接
     
     *  硬链接
         *  与普通文件没什么不同，inode都指向同一个文件在硬盘中的区块。
         *  ln 文件名 硬链接的名字
           ![image-20210420101048424](C:\Users\86156\AppData\Roaming\Typora\typora-user-images\image-20210420101048424.png)
# 用户权限，用户和用户组
1. 修改文件或目录的权限
    *   文字设定法
        *   chmod who[+|-|=]mode 文件名
            *   who:
                *   u-user,文件所有者
                *   g-group,文件所属组
                *   o-other,其他人
            *   +|-|=
            *   mode
                *   r:读
                *   w:写
                *   x:执行
                *   -：没有任何权限
    *   数字设定法
        *   chmod [+|-|=]mode 文件名
            *   mode:
                *   r:4
                *   w:2
                *   x:1
                *   -:0
            *  文件权限：777给所有者和所属组减去r
                *  chmod -440 file
2. 修改文件所有者或所属组 -chown
     * chown 新的所有者 文件名
     * chown 新的所有者：新的组 文件名
 # 文件的查找和检索
 1. 根据文件属性查找
     *  文件名
         *  find 查找的目录 -name "查找的文件名"
     *  文件类型
         *  find 查找目录 -type 文件类型
             *  普通文件 ：f
             *  目录： d
             *  符号链接：l
             *  管道：p
             *  套接字：s
             *  字符设备：c
             *  块设备：b
     *  文件大小
         *  find 查找目录 -size +10M
         *  find . -size +10k -size -100k
     *  日期
         *  创建的日期： -ctime -n/+n
             *  -n:n天以内
             *  +n:n天以外
         *  修改的日期:  -mtime
         *  访问日期： -atime
     *  深度
         *  -maxdepth n(层数)
         *  -mindepth n(层数）n层以上的)
         *  find 目录 -maxdepth n -name "name" 
     *  高级查找
         *  例：查找指定目录并列出该目录中的指定信息
         *  find ./ -type d -exec shell 命令（ls -l）{} \;
 2. 根据文件的内容查找
    *  grep  -r (有目录) “查找的内容” 搜索的路径 -n(显示行号)
 3.  总结
    * find 搜索的路径 参数 搜索的内容
    * grep 搜索的内容 参数 搜索的路径
 # 压缩包管理
 1. linux小常见的压缩格式
     *  .gz - gzip
     *  .bz2 - bzip2
 2.  常用压缩命令：
     *  tar - 打包
         *  参数：
             *  c - 创建压缩文件
             *  x - 释放压缩文件
             *  v - 打印提示信息(可不写)
             *  f - 指定压缩包的名字
             *  z - 使用gzip压缩文件 - xxx.tar.gz
             *  j - 使用bzip2的方式压缩文件 --xxx.tar.bz2
         *  压缩
             *  tar参数 压缩包的名字 原材料 --gz
                 *  tar zcvf test.tar.gz file dir
         *  解压缩
             *  tar zxvf test.tar.gz 
             *  tar zxvf test.tar.gz -C 指定路径
     *  rar
         *  rar需要安装
             *  sudo apt-get install rar
         *  压缩
             *  rar a 压缩包名（不用指定后缀） 压缩内容
         *  解压缩
             *  rar x 压缩包名 解压目录
     *  zip/unzip
             *  压缩
                 *  zip 参数 压缩包名 原材料
                     *  如果有目录：-r
                 *  解压缩
                     *  unzip 压缩包名字 -d 解压目录
 3. 总结
     *  压缩：
         *  tar/rar/zip 参数 压缩包名 原材料
     *  解压
         *  tar/rar/unzip 参数 压缩包名 参数 解压路径
             *  rar解压到指定目录不需要指定参数
             *  unzip不需要解压参数，解压到指定目录需要参数 d
# 软件的安装和卸载
1. 在线安装 --ubuntu apt-get
    * 安装：sudo apt-get(apt) install 安装包的名字
    * 卸载：sudo apt-get(apt) remove 软件的名字
    * 软件列表的更新：sudo apt-get(apt) update
    * 清空缓存：sudo apt-get(apt) clean
        * /var/cache/apt/archives
            * xxx.deb
   2. 软件包安装（ubuntu下deb格式）
       1. 安装：sudo dpkg -i  xxx.deb
       2. 卸载：sudo dpkg -r 软件的名字