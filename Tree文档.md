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

##### 9. int CVICALLBACK M7_5Kw_Callback
当按下TAB2的先导泵(7.5Kw)时，指示灯状态反转。

##### 10. int CVICALLBACK M1_1Kw_Callback
当按下TAB2的回油泵(1.1Kw)时，指示灯状态反转。

##### 11. int CVICALLBACK MSTEPSTART_Callback
当按下TAB2的最后一个标签`步进电机控制`时，指示灯状态反转。

##### 12. int CVICALLBACK MSTEPDIR_Callback
当调节`步进电机控制`标签中的_缩与伸_ 按钮时，调用该回调函数来读取这个按钮的值。

##### 13. int CVICALLBACK M9START_Callback
TAB2的`变频电机控制`中变频电机M9 的启停控制。

当启动按钮按下时，指示灯状态反转，读取旁边的`速度调节`中的速度值，并把值在DA输出的1号通道输出(借助于函数`OutputExpandDA1`来输出)。
此外，同时启动风机(mWindTH)。

##### 14. int CVICALLBACK  M9SPD_Callback
TAB2中变频电机M9 的速度控制。

通过在`速度调节`的设置按钮中设置速度值之后，调用本回调函数来在DA输出的1号通道输出(借助于函数`OutputExpandDA1`来输出)速度值。

##### 15. int CVICALLBACK MainPumpRampCallback
TAB2的`变频电机控制`中_调速选择_下拉菜单的回调函数。当选择不同的速度时，调节上边的_主泵比例溢流阀_ 的增加按钮时，每次增加的量会根据下来菜单的快慢来变化。_调速选择_ 越慢，每次增加的越少。

##### 16. int CVICALLBACK V65Callback
TAB2的`油源比例阀`标签中，_副泵比例溢流阀_的回调函数，读取该溢流阀的设定值，并在DA输出的2号通道输出(借助于函数`OutputExpandDA2`来输出)。

##### 17. int CVICALLBACK SecondPumpRampCallback2
TAB2的副泵比例溢流阀所对应的_速度选择_下拉菜单回调函数，根据不同的速度来设定增加溢流阀值时每次增加的步长。

##### 18. int CVICALLBACK Slot5Callback
TAB2的`油源比例阀`标签中，除了副泵比例溢流阀之外的3个阀门的回调函数，通过句柄`v_Slot5`读取这3个阀的设定值到程序中。

##### 19. int CVICALLBACK Slot6Callback
读取TAB2的`比例溢流阀加载`标签下的_A4,B4_以及TAB2的`力士乐比例溢流阀加载`标签下的_A1,B1_的值，通过句柄`v_Slot6`读取到程序中。

##### 20. int CVICALLBACK Slot7Callback
读取TAB2的`比例溢流阀加载`标签下的_A3,B3_以及TAB2的`力士乐比例溢流阀加载`标签下的_A2,B2_的值，通过句柄`v_Slot7`读取到程序中。



