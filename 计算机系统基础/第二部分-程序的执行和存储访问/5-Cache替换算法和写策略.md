# Cache 替换算法和写策略

**概览：**

**[:question: Cache 替换算法](#cache-替换算法)**  
**[:question: Cache 写策略](#cache-写策略)**  
**[:question: Cache 实现的几个因素](#cache-实现的几个因素)**

_本章只做简单介绍，具体应看“操作系统”的课程内容_

## Cache 替换算法

问题引入：组相联映射时，假定第 0 组的两行分别被主存第 0 和 8 块占满，此时若需调入主存第 16 块，根据映射关系，它只能放到 cache 第 0 组，因此第 0 组中必须有一块被调出，那么调出哪一块呢？  
这就是淘汰策略问题，也称替换算法

常见的替换算法有：

- 先进先出 FIFO（first-in-first-out）
- 最近最少用 LRU（least-recently uesd）
- 最不经常用 LFU（least-frequently uese）
- 随机替换（random）

### 先进先出

总是把最先进入的那一块淘汰掉

### 最近最少用

总是把最近最少用的那一块淘汰掉

- LRU 是一种栈算法，它的命中率随组的增大而提高
- 当分块局部化范围（即：某段时间集中访问的存储区）超过了 cache 存储容量时，命中率变得很低。极端情况下，假设地址留是 1,2,3,4,1,2,3,4,1......,而 cache 每组只有三行，那么不管是 FIFO 还是 LRU，其命中率都为 0，这种现象称为颠簸（Thrashing/PingPong）
- LRU 具体实现时，并不是通过移动块来实现的，而是通过给每个 cache 行设定一个计数器，根据计数指来记录这些主存块的使用情况，这个计数值称为 LRU 位

## Cache 写策略

这是 cache 的一致性问题

- 为何要保持 cache 和主存中数据的一致？  
  因为 cache 中的内容是主存块的副本，当 cache 中的内容进行更新时，就存在 cache 和主存如何保持一致性的问题  
  以下情况也会出现“cache 一致性问题”
  - 当多个设备允许访问主存时  
    例如：I/O 设备可直接读写内存时，如果 cache 中的内容被修改，则 I/O 设备读出的对应主存单元的内容无效；若 I/O 设备修改了主存单元的内容，则 cache 中对应的内容无效
  - 当多个 cpu 都带有各自的 cache 而共享主存时  
    某个 cpu 修改了自身 cache 中的内容，则对应的主存单元和其它 cpu 中对应的内容都变为无效
- 写操作有两种情况
  - 写命中（Write Hit）：要写的单元已经在 cache 中
  - 写不命中（Write Miss）：要写的单元不在 cache 中

### 写命中

对于写命中有两种处理方式

- Write Through（通过式写、写直达、直写）
  - 同时写 cache 和主存单元
  - 使用写缓冲（Write Buffer）
- Write Back（一次性写、写回、回写）
  - 只写 cache 不写主存，缺失时一次写回，每行有个修改位（dirty bit - 脏位），大大降低主存带宽需求，控制可能复杂

Write Buffer

- 在 cache 和 memory 之间增加一个 write buffer
  - cpu 同时写数据到 cache 和 write buffer
  - memory controller（存控）将缓冲内容写主存
- write buffer 是一个 FIFO 队列
  - 在存数频率不高时效果好
- 问题
  - 当频繁写时，易使写缓存饱和，发生阻塞
- 如何解决写缓冲饱和
  - 加一个二级 cache
  - 使用 write back 方式的 cache

### 写不命中

对于写不命中有两种处理方式

- Write Allocate（写分配）
  - 将主存块装入 cache，然后更新相应单元
  - 试图利用空间局部性，但每次都要从主存读一个块
- Not Write Allocate（写不分配）
  - 直接写主存单元，不把主存块装入 cache

## Cache 实现的几个因素

- Cache 性能由缺失率确定，而缺失率与 cache 大小、block 大小等有关
  - cache 大小：cache 越大，缺失率越低，但成本越高
  - block 大小：block 大小与 cache 大小有关，且不能太大，也不能太小

### 系统中 cache 数目

- 刚引入 cache 时只有一个 cache。近年来多 cache 系统成为主流
- 多 cache 系统中，需要考虑两方面：
  - 单级/多级  
    外部（Off-chip）cache：不做在 cpu 内而是独立设置的一个 cache  
    片内（On-chip）cache：将 cache 和 cpu 做在一个芯片上  
    单级 cache：只用一个片内 cache  
    多级 cache：同时使用 L1 cache 和 L2 cache，甚至 L3 cache，L1 cache 更靠近 cpu，其速度比 L2 快，容量比 L2 小
  - 联合/分立  
    分立：指数据和指令分开存放在各自的数据和指令 cache 中  
    一般 L1 cache 都是分立 cache  
    L1 cache 的命中时间比命中率更重要  
    联合：指数据和指令都放在一个 cache 中  
    一般 L2 cache 都是联合 cache  
    L2 cache 的命中率比命中时间更重要
