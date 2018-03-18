# crossPlatDLC
## 项目介绍
这个项目是一个跨平台的C基础工具包。初衷是用C实现一个webserver.余有时而尽力。

#### 关于代码结构
1. _

    | 文件加       | 描述 |作用|
    | :-------- | -----    |----|
    | cpdlc      | 跨平台C包的代码||
    | android      |android demo     ||
    | ios      | ios demo    ||
    | linux    | linux demo    ||
    | mac      | mac demo   ||
    | win32      | windows demo    ||
    | testcpdlc     | 自动化测试代码    |先编写的测试驱动代码|
    | cpdlc/dlobject     | 面向对象C基类    ||
    | cpdlc/dlADTbase     | 基础的抽象数据类型类    ||
    | cpdlc/cpdlc/dllog     | 基础设施日志兼自动化测试代码    ||
    | cpdlc/dlsqlite     | sqlite数据库接口类    ||



#### 一个日志打印系统 dllog

1. 支持格式化输出日志的行／函数／文件／内容
1. 支持快速日志嵌入 FUNC_RUN_LOG
1. 支持常用的判断日志 CONDITION_VALUE_IS_NULL
1. 支持日志的分级别打印 日志级别 debug info warning error fatal
1. 支持在运行期间修改级别
1. 支持不同模式的打印 日志模式 release debug develop 默认是develop
1. 支持在运行期间修改模式
1. 支持设置错误断言级别 默认是warning
1. 支持设置是否打开断言 默认是关闭的
1. 支持持久化日志到文件 默认级别warning
1. 支持日志文件夹比较大时自动删除
1. 支持持久化日志到数据库 鉴于这个日志系统是基础设施 所以并没有实现。
1. 支持自动化测试
1. 支持跨平台 mac win linux

具体代码可以参见 testcpdlc/testdllog.c

#### 用C实现的一个小型的精简的面向对象系统 DLObject
1. 支持了面向对象的封装
2. 支持了面向对象的继承
3. 支持了面向对象的多态

设计这个小系统的目的是用面向对象的思想写C，并不是为了实现一个大而全的面向对象语言。
所以实现中没有可以去实现过于复杂的面向对象性质
这个系统追求代码上的精简和创建新类时的精简。
当然随着抽象度的提高，希望这个对象自治的时候，自然会想到要用引用计数，垃圾回收这些高级的面向对象功能。
但是尽量不与c思想违背。
DLObject使用了比较多的宏来使代码精简和自动化生成代码。
具体代码可以参见 testcpdlc/testdlobject.c

以面向对象系统，自动化测试，和日志分级打印为基础，实现了基础的抽象数据结构。
#### 泛型链表类
1. 可以存入任何类型的泛型单链表类
1. 可以存入任何类型的泛型双链表类

创建的泛型链表类，可以存入任何类型的数据

#### 泛型单链表类 DLGenericSingleChainList
以泛型单链表为基础
1. 泛型栈  DLStack testcpdlc/testDLStack.c
1. 泛型队列 DLQueue testcpdlc/testDLQueue.c
1. 泛型列表 DLList testcpdlc/testDLList.c
1. 泛型字典 DLDict testcpdlc/testDLDict.c

泛型栈和泛型队列的实现应该已经足够，只是未做限制。泛型字典在查询效率还有提升空间，字典未加入散列，然余感觉够用。
不够用的时候再重构它。


运行系统在mac 文件夹下，当然其它的demo也可以。
``` shell
make
```


然后运行生成的temp文件夹下的cpdlc.exe
``` shell
./cpdlc.exe
```
这时候就会运行testcpdlc文件夹下所有的自动化测试代码。
有问题就会打印出来，或者设置了断言级别的打印的话，程序就会中断。
程序默认高级别的日志会写入数据库中，当然也可以自己设置级别。写入数据库中的日志可以以后或者做远程分析。
例如可以将数据库中级别比较高的日志上传到其他的日志服务器做集中分析。
当然数据库中也可以存储所有的日志，只不过数据库没有自动删除功能。适合放置级别比较高的日志。方便日后分析。
当然使用数据库需要需要依赖sqlite或者mysql等数据库。

每次修改程序，然后运行下程序，自动化测试代码不报错的话，可以认为自己的修改对以前的代码没有产生影响。


