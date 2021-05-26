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
    
  
# 记录
  
  * socket()命名冲突时,使用::socket().
    ```cpp
    this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP
    ```  
  
  * 若创建了一个int buffer[512],在recv()和send()中要使用buffer时,可以直接用(char*)buffer.
    ```cpp
    recv(client, (char*)keyBuffer, sizeof(keyBuffer), 0);
    send(client, (char*)positions, sizeof(positions), 0);
    ```
  
  * 当传输的数据本身定义时是一个指针时,发送的大小不能用sizeof(),因为这样sizeof()仅仅是指针的大小.
    ```cpp
    send(client.serverSocket, (char*)window.screen_keys, 512, 0);//这里得用具体大小512
    ```
  
  * 将客户端的渲染和通信放在同一个while循环里,而不是分两个线程,可以避免多线程访问冲突的问题.  
  
  
  * 使用多线程时,注意数据的变化.
    如,当在t线程中使用threadCnt时,其实是使用的变化后的值:
    ```cpp
  	t.detach();
		threadCnt++; threadCnt %= 2;
    ```
    把threadCnt在线程调用时当作参数传入,可正确使用其变化前的值:
    ```cpp
    std::thread t(this->ServiceClient, clientAddr, client, threadCnt);
    ```
