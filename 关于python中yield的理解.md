当我们阅读python代码时，经常会发现某个函数中带有`yield`关键字。上网Google之，发现有一大堆答案，但都无不包含 _iterable_, _iterator_, _generator_，
看的人真心眼花缭乱，尤其对于刚刚上手python的人，本想好好的学习下`yield`是干什么用的，结果越看越混乱。

仔细看了python官方的[文档](https://docs.python.org/3.5/glossary.html#term-generator)和Stack Overflow上众
大神的[回答](https://stackoverflow.com/questions/231767/what-does-the-yield-keyword-do-in-python)，根据一个小例子将`yield`与之相关
的各种“器”总结如下。

**yield的功能**\\
在python的函数中，`yield`与`return`的功能非常相似，都会返回
