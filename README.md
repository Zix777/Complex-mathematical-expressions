#复杂数学表达式
本项目为一个利用C++对常用复杂数学表达式进行求值的算法类。附带一个利用这个算法类写的计算器，通过Qt实现界面。

#支持的运算符
支持常见的运算符,加减乘除(`+-*/`)，开方(`#`)，乘方(`^`)，模(`%`)，百分比(`%`)，度(`` ` ``反引号) ，阶乘(`!`)，三角函数(`sin, cos, tan, arcsin, arccos, arctan`)，对数(`log，ln，lg`)等。其中开平方支持省略根指数2。
括号内为代码中使用的运算符符号，输入表达式时需要将表达式内对应符号转为括号内对应符号。即`√` `°` `×` `÷`等符号是非法的,需转换为`#` `` ` `` `*` `/`

#运算优先级
1. 如果有括号就先算括号内后算括号外，同一级运算顺序是从左到右，不区分大中小括号；
2. 百分号和角度符号优先级最高；
3. 三角函数和对数运算优先级相同，小于上一条；
4. 阶乘和开平方优先级相同，小于上一条；
5. 乘方和开多次方优先级相同，小于上一条；
6. 模运算与乘除优先级相同，小于上一条；
7. 负号,加减运算优先级最低；

推荐多使用括号，避免因运算符优先级导致的问题

##例1
表达式 | 计算步骤
------------------------|--------------------
`` 8+5*sin90`!*2^#4``|先将角度转为弧度
`=8+5*sin1.57076!*2^#4`|计算sin
`=8+5*1!*2^#4`|计算阶乘
`=8+5*1*2^#4`|计算开方
`=8+5*1*2^2`|计算乘方
`=8+5*1*4`|计算第一个乘法
`=8+5*4`|计算第二个乘法
`=8+20`|计算加法
`=28`|

##例2
表达式 | 计算步骤
------------------------|--------------------
`-lg10+lg1000%*#4!`|百分数化为小数
`=-lg10+lg10*#4!`|计算lg
`=-1+1*#4!`|计算开平方
`=-1+1*2!`|计算乘方
`=-1+1*2`|计算乘法
`=-1+2`|计算负号
`=-1+2`|计算加法
`=1`|                              
![计算结果](https://github.com/Zix777/Complex-mathematical-expressions/blob/master/screenshot/sp20161010_214714.png)

#USAGE
[数学表达式求值算法类的使用](https://github.com/Zix777/Complex-mathematical-expressions/tree/master/%E5%9B%9B%E5%88%99%E8%BF%90%E7%AE%97)

[计算器的介绍和使用](https://github.com/Zix777/Complex-mathematical-expressions/tree/master/Calculator)
