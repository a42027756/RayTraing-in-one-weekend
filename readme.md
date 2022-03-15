# Ray Tracing in one weekend

跟着Github上面RayTracing one one weekend的教程学习了一段时间，虽然说确实不止用了one weekend，但也算是成功地构建出了这个简单的光线追踪器。下面先放一下我渲染出来的最终效果图：

[![bjXtfI.png](https://s1.ax1x.com/2022/03/15/bjXtfI.png)](https://imgtu.com/i/bjXtfI)

没有想到这张图渲染了可能有8个小时（等不下去上床睡觉了），总体来说令人满意！

本垃圾电脑配置：i5-9300H GTX1660ti 感觉只能摸到图形学入门门槛

下面总结一下在学习过程中踩过的坑：

## PPM

从这个项目一开始就遇到了一个大问题：跟着教程的第一步所生成的ppm文件，所有下载的图片软件都打不开。于是到网上搜寻解法，最后终于找到了一个情况相同的老哥，他提供了另一种方法解决了这个ppm打不开的问题，就是svpng，用来将2进制rgb数据直接转换成png格式文件。这样经过了一点点改变之后，整个项目总算是跑了起来。。

当然，后来遇到别的问题，在官方的Github Issue页面浏览的时候，发现了有人遇到了和我一样的问题，有人回答了是输出的数据编码是UTF-16，所以无法识别，只要转换成UTF-8就好。后来我也自己测试了一下，确实是这样，原因在于我使用了windows powershell而不是cmd，powershell默认使用UTF-16输出数据（太坑了），所以我输出的所有ppm都无法直接查看。

## Dielectrics

看教程的时候参考了中文翻译，许多代码在中英文版本中有不同，很多都是混着用。其中sphere类中的hit函数判定光线和球相交的方法我有一些疑惑，但是也没有深究，没想到后来还是要尝苦果。在电解质章节涉及到的折射的实现中，因为hit判定的问题，导致光线进入到球体内部之后，无论如何都无法从球体中穿出，造成了光线一直在球体中弹射，直到达到最大递归深度50，然后自动返回黑色。于是就出现了这样的效果：

[![bxKwy6.png](https://s1.ax1x.com/2022/03/15/bxKwy6.png)](https://imgtu.com/i/bxKwy6)

整个电解质材质都显示黑色。

在github大佬的指点之下，终于发现了我的hit函数方法有问题，重写了hit后终于实现了折射效果：

[![bxK5m8.png](https://s1.ax1x.com/2022/03/15/bxK5m8.png)](https://imgtu.com/i/bxK5m8)

## Stack overflow

整个项目两次遇到了stack overflow问题

- 第一次是没有弄明白svpng的运行机制，unsigned char数组超出下标导致溢出；

  解决方法：数组适配图片分辨率大小

- 第二次是unsigned char数组过大导致溢出,报错chkstk.asm

  解决方法：扩大栈内存  #pragma comment(linker, "/STACK:102400000,102400000")

