# MarkDown（标题一）
## 一：MarkDown简介（标题二）
&emsp;&emsp;Markdown是一种可以使用普通文本编辑器编写的标记语言，通过简单的标记语法，它可以使普通文本内容具有一定的格式。</br>
&emsp;&emsp;Markdown具有一系列衍生版本，用于扩展Markdown的功能（如表格、脚注、内嵌HTML等等），这些功能原初的Markdown尚不具备，它们能让Markdown转换成更多的格式，例如LaTeX，Docbook。Markdown增强版中比较有名的有Markdown Extra、MultiMarkdown、 Maruku等。这些衍生版本要么基于工具，如Pandoc；要么基于网站，如GitHub和Wikipedia，在语法上基本兼容，但在一些语法和渲染效果上有改动</br>
&emsp;&emsp;Markdown在线编程工具：http://www.ctrlshift.net/project/markdowneditor/ </br>

半方大的空白:&ensp;或:&#8194;；</br>
全方大的空白:&emsp;或:&#8195;；</br>
不断行的空白格:&nbsp;或:&#160;；</br>

### （1）MarkDown教程
- **<a href="http://www.jianshu.com/p/7bd23251da0a" target="_blank">Markdown在线教程</a>**
- **欢迎大家访问<a href="https://github.com/" target="_blank">我的Github</a>**
### （2）常用的MarkDown工具
- **[VSCode](https://code.visualstudio.com/)**
- **[Byword](https://bywordapp.com/)**
- **[MacDown](http://macdown.uranusjr.com/)**
### （3）特殊文本格式：
> cmake_minimum_required(VERSION 3.4.1)</br>
> #设置OpenCV的路径</br>
> set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/../OpenCV-android-sdk/sdk/native/jni)</br>
> find_package(OpenCV REQUIRED)</br>
> include_directories(${CMAKE_SOURCE_DIR}/../OpenCV-android-sdk/sdk/native/jni/include)</br>
### （4）代码块
``` C++
#include <stdio> 
int main() //C语言是从main()函数开始的
{
  printf("Hello world!\n"); 
  return 0; 
}
```

### （5）显示图片
<img src="http://ww1.sinaimg.cn/large/005Xtdi2jw1f9k7b8a6vmj312w0rg143.jpg" width="300"/>

> **注意：** 虽然浏览器存储大部分时候都比较可靠，但为了您的数据安全，在联网后，**请务必及时发表或者保存到服务器草稿箱**。
