Windows 10屏幕会自动刷新的问题终于解决了。
=====

#### 问题：
每隔20~30秒，系统都会刷新一次桌面和最下边的状态栏，导致只要开着"文件夹"(folder)，所有的文件夹都会自动关闭，而且，只要在做全屏的工作，一定会被弹出到桌面。但是只有文件夹会自动关闭而其他应用不会关闭。（我拔掉网线后就一切正常，插上网线后就会出现前面的问题，此外，新建一个Windows用户，进去之后也是一切正常的，怀疑是网卡驱动问题，卸载重装之后未解决）

#### 原因：
由于一些软件的.dll文件的原因，使得文件夹（也就是Windows资源管理器停止工作）停止工作。这一点可以在控制面板中搜索“查看可靠性历史记录”来确认，发现发生错误的程序是: **C:\Windows\explore.exe**

#### 解决方法：
基本原理是使用Windows Debug Tool分析crash的文件即可，具体做法是（**可以先看step i**）：

a). 在C盘新建一个文件夹，命名为"dumps"

b). 在桌面上新建一个文本文件，拷贝如下内容并保存，命名为：`explorercrashdumps-to-C.reg`
```text
Windows Registry Editor Version 5.00

[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps\explorer.exe]
"DumpFolder"=hex(2):63,00,3a,00,5c,00,64,00,75,00,6d,00,70,00,73,00,00,00
"DumpCount"=dword:00000002
"DumpType"=dword:00000002
```
c). 运行该注册表文件，使得下次文件夹crash的时候，crash的内容会自动写入`c:\dumps`文件夹

d). 在微软官网下载Debugging tools for Windows (WinDbg)，链接：https://developer.microsoft.com/en-us/windows/hardware/windows-driver-kit .下载好下载器之后，选择Download the windows software development kit.并在后边的选择框中**只选** Debugging tools for Windows.下载好后安装。

e). 此时，前面的“桌面自动刷新，文件夹自动关闭”的问题肯定已经出现过了，因此，`c:\dumps`文件夹中一定有crash file。在C盘中新建一个文件夹命名为`localsymbols`。

f). 打开刚刚安装的Windbg.选择：`File -> Symbol file path`，写入：`SRV*c:\localsymbols*http://msdl.microsoft.com/download/symbols`，点击Ok。选择: `File -> Open crash dump`，选择c:\dumps文件夹中的任意一个crash file。

g). 此时会出现一大堆和微软相关的信息，在最下边的命令行里输入：`!analyze -v` 并回车，就会自动下载相关的.pdb文件至c:\localsymbols文件夹，之后会自动分析出导致问题的文件，这个过程由网速觉得，大概10分钟。

h). 一般而言，出问题的那个文件是：`FAILURE_IMAGE_NAM`E 所对应的文件，点开下边的`browse full module list`，可以查看该文件的路径。删除之即可。

i). **备注：**只要系统产生了crash文件，那么如果自己的电脑还是一直闪屏（这可能会导致WinDbg运行自动出错），那么可以把crash文件拷贝到正常的电脑上，执行step d~h 即可。

上边内容参考了：http://www.tenforums.com/general-support/23377-taskbar-desktop-randomly-refreshes-after-upgrading-ten.html
