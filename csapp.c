计算机系统是由硬件和系统软件组成的，它们共同工作来运行应用程序。虽然系统的
具体实现方式随着时间不断变化，但是系统内在的概念却没有改变。所有计算机系统都有
相似的硬件和软件组件，它们又执行着相似的功能。一些程序员希望深入了解这些组件是
如何工作的以及这些组件是如何影响程序的正确性和性能的，以此来提高自身的技能。本
书便是为这些读者而写的。
现在就要开始一次有趣的漫游历程了。如果你全力投身学习本书中的概念，完全理解底
层计算机系统以及它对应用程序的影响，那么你会步上成为为数不多的“大牛”的道路。
你将会学习一些实践技巧，比如如何避免由计算机表示数字的方式引起的奇怪的数字
错误。你将学会怎样通过一些小窍门来优化自己的 C 代码，以充分利用现代处理器和存储
器系统的设计。你将了解编译器是如何实现过程调用的，以及如何利用这些知识来避免缓
冲区溢出错误带来的安全漏洞，这些弱点给网络和因特网软件带来了巨大的麻烦。你将学
会如何识别和避免链接时那些令人讨厌的错误，它们困扰着普通的程序员。你将学会如何
编写自己的 Unix shell� 自己的动态存储分配包，甚至于自己的 Web 服务器。你会认识并发
带来的希望和陷阱，这个主题随着单个芯片上集成了多个处理器核变得越来越重要。
在 Kernighan 和 Ritchie 的关于 C 编程语言的经典教材[61]中，他们通过图 1-1 中所
示的 hello 程序来向读者介绍 C�尽管 hello 程序非常简单，但是为了让它实现运行，系
统的每个主要组成部分都需要协调工作。从某种意义上来说，本书的目的就是要帮助你了
解当你在系统上执行 hello 程序时，系统发生了什么以及为什么会这样。

#include <stdio.h>
int main(){
	printf("hello world"\n)
}

我们通过跟踪 hello 程序的生命周期来开始对系统的学习棗 从它被程序员创建开始，
到在系统上运行，输出简单的消息，然后终止。我们将沿着这个程序的生命周期，简要地介
绍一些逐步出现的关键概念、专业术语和组成部分。后面的章节将围绕这些内容展开。
1.1 信息就是位+ 上下文
hello程序的生命周期是从一个源程序(或者说源 文件)开始的，即程序员通过编辑器创
建并保存的文本文件，文件名是 hello.c� 源程序实际上就是一个由值 〇 和 1 组成的位(又称
为比特)序列，8 个位被组织成一组，称为字节。每个字节表示程序中的某些文本字符。

大部分的现代计算机系统都使用 ASCII 标准来表示文本字符，这种方式实际上就是用
一个唯一的单字节大小的整数值@来表示每个字符。比如，图 1-2 中给出了 hello.c 程序
的 ASCII 码表示。

hello.c 程序是以字节序列的方式储存在文件中的。每个字节都有一个整数值，对应
于某些字符。例如，第一个字节的整数值是 35,它对应的就是字符“# ”。第二个字节舍
整数值为 105,它对应的字符是 依此类推。注意，每个文本行都是以一个看不见的
换行符 ‘W 来结束的，它所对应的整数值为 10。像 hello.c 这样只由 ASCII 字符构成
的文件称为文本文件，所有其他文件都称为二进制文件。
hello.c 的表示方法说明了一个基本思想：系统中所有的信息棗 包括磁盘文件、内
存中的程序、内存中存放的用户数据以及网络上传送的数据，都是由一串比特表示的。区
分不同数据对象的唯一方法是我们读到这些数据对象时的上下文。比如，在不同的上下文
中，一个同样的字节序列可能表示一个整数、浮点数、字符串或者机器指令。
作为程序员，我们需要了解数字的机器表示方式，因为它们与实际的整数和实数是不
同的。它们是对真值的有限近似值，有时候会有意想不到的行为表现。这方面的基本原理
将在第 2 章中详细描述。

1.2 程序被其他程序翻译成不同的格式
hello 程序的生命周期是从一个高级 C 语言程序开始的，因为这种形式能够被人读
懂。然而，为了在系统上运行 hello.c 程序，每条 C 语句都必须被其他程序转化为一系
列的低级机器语言指令。然后这些指令按照一种称为可执行目标程序的格式打好包，并以
二进制磁盘文件的形式存放起来。目标程序也称为可执行目标文件。
在 Unix 系统上，从源文件到目标文件的转化是由编译器驱动程序完成的：

linux>gcc -o hello hello.c

在这里，GCC 编译器驱动程序读取源程序文件 hello.c�并把它翻译成一个可执行
目标文件 hello�这个翻译过程可分为四个阶段完成，如图 1-3 所示。执行这四个阶段的
程序（预处理器、编译器、汇编 器和链接器）一起构成了编译系统（compilation system)�

1.4. 2 运行 hello 程序
前面简单描述了系统的硬件组成和操作，现在开始介绍当我们运行示例程序时到底发
生了些什么。在这里必须省略很多细节，稍后会做补充，但是现在我们将很满意于这种整
体上的描述。
初始时，shell 程序执行它的指令，等待我们输人一个命令。当我们在键盘上输人字符串
�/hello�后，shell 程序将字符逐一读人寄存器，再把它存放到内存中，如图 1-5 所示。

当我们在键盘上敲回车键时，shell 程序就知道我们已经结束了命令的输人。然后
shell 执行一系列指令来加载可执行的 hello 文件，这些指令将 hello 目标文件中的代码
和数据从磁盘复制到主存。数据包括最终会被输出的字符串揾ello,worldW�
利用直接存储 器存取（DMA,将在第 6 章中讨论）技术，数据可以不通过处理器而直
接从磁盘到达主存。这个步骤如图 1-6 所示。


