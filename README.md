# Socket-2021
计算机网络课设，Socket编程。

**实现简述：**  
客户端进行渲染，服务端计算每个客户端对应盒子的位置变化。  
服务端使用多线程，可与多个客户端通信，每连接一个新客户端，将创建与该客户端的专属线程进行通信。  
客户端同时进行渲染和通信。

需要来自我另一个项目的库文件(**CardRenderer.lib**)(承担渲染工作)，可在当前项目 **./lib** 找到对应库文件。  
（渲染项目：
[Khasehemwy/SoftwareRenderer](https://github.com/Khasehemwy/SoftwareRenderer)）

# 展示
<image src="https://user-images.githubusercontent.com/57032017/119599919-884a5f00-be18-11eb-8040-960b88b63b3e.png" width=80%>
<image src="https://user-images.githubusercontent.com/57032017/119606460-39ef8d00-be25-11eb-8856-c412f892b283.gif" width=80%>
  
# 使用
  进入 **./Debug** 目录,先启动 **Server.exe** ,再按顺序启动 **Client0.exe** 和 **Client1.exe** 。
