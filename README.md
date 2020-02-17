### 简单存储工具

#### 背景

此项目是为了学习`lsm树`的原理以及有关存储的知识.支持持久化存储等功能

#### 特性

- 使用`布隆过滤器`加快从磁盘中读取的速度
- 设计`lru`进行键的淘汰
- 使用`Varint`编码进行数字压缩
- 使用`snappy`对于文件内容压缩
- 通过日志进行数据恢复
- 使用`mmap`来进行文件的写入
- 对于文件建立相关索引加速查找
- ....

#### 核心思路

顺序写的IO速率是比随机写快的,尽可能把随机写转化为顺序写,将写性能放大,尽可能减少读性能的损失

##### 为了查找数据库的特定键的值,索引如何建立?

- 我理解的索引是保存一些额外的数据作为指引,找到磁盘中数据的位置.

- 一开始的想法是建立哈希映射,在内存中建立哈希映射,其中键会对应数据文件中的字节偏移量,更新文件,同时也需要更新内存中的映射,使用哈希映射来查找数据文件的偏移量,读取该值.但是所有键都必须存入可用内存之中，这种情况适合于不同的键并不多的情况,而且它需要大量随机访问磁盘I/O.

- 我们可以通过保证存入文件的数据有序,不可更改,在每一块数据之后写入键的偏移量和所有键的个数,将布隆过滤器的值进行存入,并且记录文件中的每一块数据和每一块布隆过滤器的偏移量

  

 ![image](https://github.com/LhdDream/kiosk_key_value/blob/master/img/a.png)

  

- 其中数据块,我们可以这样组织

  

```
 \r | key | \r | value
 
 \r | key | \r | value
 
 key_offest| key_offest | key_offest_size
```



##### 如何应对进程突然退出?

- 使用`mmap`作为写缓冲区,mmap通过创建虚拟区间完成文件物理地址和进程虚拟地址的映射,引发缺页异常,磁盘装入内存,如果进程对于主存有写操作,系统一段时间之后会自动回写磁盘地址
- 我们可以利用这一点来保证kill -9之后数据的一致性.
- 每次写入数据之前,首先写入到日志之中,启动的时候通过日志来进行恢复.

##### 写入的流程是什么?

- 检查hashset 中是不是存在相应的键,存在则进行删除

- `memtable`中有n个map存在,每一时刻只有一个map启动,如果当前map没满,直接进行插入.当前map达到限制,生成新的map.
- 当n个map达到一致容量进行合并,转化为不可修改的unmemtable,执行写入磁盘的格式化处理
- ...

##### 读取的流程是什么?

- 在`lru`中寻找键,找到返回,找不到去`memtable`寻找
- 遍历所有的memtable中找不到,从磁盘中寻找

- ....

##### 删除的流程是什么?

- 在memtable中的hash set中添加相应的值
- ...



#### 不足之处

- 在磁盘中并没有进行文件的合并
- 程序只是单进程
- ....

#### 安装和使用:

* 您需要确认您的计算机上安装了cmake ,并且cmake 版本>= 3.15。
* 您在使用的时候包含 src/core/db.h 和 base/dict_buider.h 即可( 可参照 main.cpp ) 

#### 性能测试:

测试环境:

​	Device Model:     TOSHIBA MQ01ABF050(5400转/秒)

​	CPU:  Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz

​	磁盘写性能:  	

  ![image](https://github.com/LhdDream/kiosk_key_value/blob/master/img/b.png)

测试代码:

```
#include <iostream>
#include "../src/core/db.h"
#include "../base/dict_builder.h"
#include <memory>
#include <chrono>
using namespace std;

char* randomstr()
{
    static char buf[1024];
    int len = rand() % 768 + 255;
    for (int i = 0; i < len; ++i) {
        buf[i] = 'A' + rand() % 26;
    }
    buf[len] = '\0';
    return buf;
}


int main(){


    std::unique_ptr<db> m_db= dict::Init("1.log","red");
    long long l = 0;
    std::string k[100000]{} ;
    for(int i = 0 ; i < 100000 ;i++){
        k[i] = randomstr();
        l += k[i].size();
    }
    std::string v = "123456789";
    l += 900000;

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    /*代码段*/
    for(int i = 0 ; i< 100000 ; i++){
         m_db->Set(k[i],v);
    }

    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
    std::cout << "time used ：" << time_used.count() << "seconds." << std::endl;
    std::cout << "data " << l/1024/1024  << " MB"<< std::endl;
    return 0;
}
```

测试数据: 随机插入10w条数据

测试性能:	

![image](https://github.com/LhdDream/kiosk_key_value/blob/master/img/c.png)

#### 总结和收获:

- 对于底层的知识知道的太少,经过遇到卡壳的情况,没有相应的知识存储.有一段时间,经常对着屏幕发呆,不知道如何去写,想过放弃过这个东西.尝试慢慢的鼓励自己,硬着头皮一点一点去学,慢慢从最简单的想法一点一点去做,也算是给自己的一个交代吧,
- 在日常的学习中忽视了底层的知识,现在才知道底层的知识特别重要,才能去更好的了解事物的运行.







