Tree.c 的说明文档
=====
这里按照程序里的函数从上到下的位置，对每一个函数做了说明。

##### 1. int __stdcall WinMain
程序的主函数，内容是`初始化DAQmxTask`，`初始化UI界面`，`初始化保存缓冲区`，`隐藏任务栏`，`初始化滤波器`，以及等待用户在UI中的操作。

##### 2. int CVICALLBACK ExitPanel
这是程序退出时所执行的一些控制量清零操作

##### 3. int CVICALLBACK TxtTest
鼠标左键点击UI右上角的帮助符号（问号）时，让那个符号变亮（即设置`ATTR_DIMMED = 0`）

##### 4. int CVICALLBACK P6_Test
鼠标从UI右上角的帮助符号划过时，让符号变亮（即设置`ATTR_DIMMED = 0`）

##### 5. int CVICALLBACK P6_TestHide
鼠标从UI右上角的帮助符号划过时，让符号变暗（即设置`ATTR_DIMMED = 1`）

##### 6. int CVICALLBACK M55Kw_Callback
当按下TAB2（上边的TAB）的副泵(55Kw)时，运行指示灯状态反转，并且读取TAB2的`变频电机控制`中的_主泵比例溢流阀_(NUM_V14_1)，
TAB2的`油源比例阀`中的_控制压力比例阀(NUM_V72)，副泵比例节流阀(NUM_V67)和先导比例节流阀(NUM_V59)_，显示到`Slot5中`。

其中`ValveArray5 = valueof {NUM_V14_1, NUM_V72, NUM_V67, NUM_V59}`

##### 7. int CVICALLBACK M30Kw_Callback
当按下TAB2的循环泵(30Kw)时，指示灯状态反转。

##### 8. int CVICALLBACK M15Kw_Callback
当按下TAB2的控制泵(15Kw)时，指示灯状态反转。





