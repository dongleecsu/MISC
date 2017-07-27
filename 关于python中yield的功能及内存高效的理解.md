当我们阅读python代码时，经常会发现某个函数中带有`yield`关键字。上网Google之，发现有一大堆答案，但都无不包含 _iterable_, _iterator_, _generator_，
看的人真心眼花缭乱，尤其对于刚刚上手python的人，本想好好的学习下`yield`是干什么用的，结果越看越混乱。

仔细看了python官方的[文档](https://docs.python.org/3.5/glossary.html#term-generator)和Stack Overflow上众大神的[回答](https://stackoverflow.com/questions/231767/what-does-the-yield-keyword-do-in-python)，根据一个小例子总结`yield`的用法。主要回答两个问题：
- yield的具体功能是什么？
- yield为什么能够做到内存高效使用？

### yield的功能

在python的函数中，`yield`与`return`的功能非常相似，都会从函数返回，但是二者又有重要区别，主要有2点不同：
- _返回值不同。_ `yield`返回一个generator，而`return`返回其后的表达式。
- _下一次函数调用时，行为不同。_`yield`返回后，其实程序并没有跳出该函数，只是把函数置于“悬挂”状态，程序会记录本次`yield`的位置，下次函数调用时，会直接从`yield`的下一条语句断点恢复。而`return`返回后，程序会跳出函数，`return`之后的语句永远都不会执行。

用一个小例子说明。
```python
# function 1
def createGen():
  print 'In function createGen msg'
  yield 1
  yield 3
  yield 5

# function 2
def func():
  print 'In function func msg'
  return 1
  print 'Never reached point'
```
```shell
>>> gen = createGen()
>>> type(gen)
<type 'generator'>
>>> fn = func()
In function func msg
>>> for i in gen:
      print i
In function createGen msg
1
3
5
```
首先，我们分别调用了函数`createGen()`和`func()`。先说说较为简单的`func()`，当我们调用该函数时，程序进入函数体，执行第一个`print`打印出相应的消息，之后遇到`return`后，会返回后面的1给变量`fn`，所以此时`fn`是一个整型数。`return`之后的第二个`print`永远也不会被执行。这与我们平常的理解都完全相同。

对于语句`gen = createGen()`，其调用函数的机制与函数`func()`大为不同。由于函数使用`yield`返回，因此其返回是一个generator（暂时只需要记住它可是可迭代的），在仅仅执行`gen = createGen()`时，函数并没有显式的执行，而仅仅返回了一个generator对象。由于generator遵从 *iterable protocol*， 即具有`__iter__()`和`next()`方法，可以**一次输出一个数据**，可以用于`for  in`语句中。因此，再后面的for循环中，其执行情况是：\
第一次执行for循环，程序会进入函数`createGen()`从头开始执行直到遇到`yield`，首先打印消息`print 'In function createGen msg'`，接着函数返回1给`i`，在for循环中，打印i的数值。由于`gen`的数据流还没有耗尽，`next()`没有扔出`StopIteration`异常，进行下一次循环；\
第二次执行for循环，程序会从函数`createGen()`断点恢复继续执行直至遇到下一个`yield 3`，回3给`i`，在for循环中，打印i的数值。由于`gen`的数据流还没有耗尽，`next()`没有扔出`StopIteration`异常，进行下一次循环；\
第三次执行for循环，程序会从函数`createGen()`断点恢复继续执行直至遇到下一个`yield 5`，回3给`i`，在for循环中，打印i的数值。由于`gen`的数据流还没有耗尽，`next()`没有扔出`StopIteration`异常，进行下一次循环；\
当下一次for循环时，由于`gen`的数据流已经耗尽，`next()`扔出`StopIteration`异常，循环跳出。

### yield与内存高效利用
可以经常看到`yield`与内存高效利用(memory efficient)的字眼相挂钩，但为什么使用`yield`能够做到内存高效呢？主要还是要从generator的特性说起。

我们经常会遇到这样的情况：有些数据我们只需要使用一次，但数据量却很大，例如在监督学习训练卷积神经网络时，需要用大量图片，但是每次数据预处理环节只对整个数据集处理一次（预处理中带有随机crop等，因此前后两次预处理是不同的），一次性返回整个预处理后的数据集会耗费大量内存。假设我们有5G的图片，如果预处理后直接将所有数据都返回，整个数据量会超过20G，内存会溢出。这时就是generator出场的时候了。

generator是可迭代的，针对于大数据量问题，可以将整个数据集划分为很多小子块，一次只输出一个小数据块，对于数据预处理的方法，可以在`next()`方法中实现，从而既做了数据预处理，也遍历了整个数据集。
