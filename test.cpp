//#pragma once
//#include<WinSock2.h>
//#include<socketapi.h>
//#include"graphBasic.h"
//#include<fstream>
//using namespace std;
//void ha()
//{
//	sockaddr_in addr;
//	addr.sin_family = AF_INET;
//	addr.sin_addr.S_un.S_addr = inet_addr("102.12.12.12");//字符串转化为二进制
//	addr.sin_port = htons(80);
//	debug(inet_ntoa(addr.sin_addr));//二进制转化为字符串
//	WORD word = MAKEWORD(2, 0);//设置主版本号和副版本号2.0
//	WSAData data;
//	WSAStartup(word, &data);//成功返回0
//	//debug(data.szDescription);//版本信息
//	//debug(data.szSystemStatus);//套接字状态，Running
//	//debug(data.iMaxSockets);//单进程最大套接字数
//	char c[20];
//	gethostname(c, 20);//取得当前主机的名字，weies？？
//	hostent* p = gethostbyname("baidu.com");
//
//	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	//参数1： 设置协议：v4 AF_INET，v6 AF_INET6
//	//参数2： 设置传输方式：流式 SOCK_STREAM,数据报：SOCK_DGRAM
//	//参数3： 设置传输协议：IPPROTO_TCP,IPPROTO_UDP
//	//closesocket(sock);//关闭套接字
//
//	SOCKADDR addr0 = sockaddr();
//	addr0.sa_data;
//	bind(sock, &addr0, 15);
//	listen(sock, 10);//第二个参数是排队的长度
//	connect(sock, &addr0, 15);//返回枚举值，错误时SOCK_ERROR
//	int* pp;
//	int ret0 = getsockname(sock, &addr0, pp);//函数获取已绑定（可能是未调用bind的系统自动绑定）的套接口本地协议地址（sockaddr=IP:PORT）
//	int ret1 = getpeername(sock, &addr0, pp);
//	//getpeername函数获得与指定套接口连接的远程地址信息
//
//	SOCKET S = accept(sock, &addr0, pp);
//
//	//根据域名获取ip
//	struct hostent* pHostBaiDu = gethostbyname("www.baidu.com");
//	printf("Host name: %s/n", pHostBaiDu->h_name);
//	printf("IP Address: %s/n", inet_ntoa(*((struct in_addr*)pHostBaiDu->h_addr)));
//
//	//发送数据
//	int ret2 = send(sock, c, 10, 0);
//	int ret3 = sendto(sock, c, 10, 0, &addr0, 15);//主要用于面向无连接的UDP
//
//	int ret4 = recv(sock, c, 10, 0);
//	int ret5 = recvfrom(sock, c, 10, 0, &addr0, pp);
//
//	int ret6 = shutdown(sock, SD_BOTH);//第二个参数:SD_RECIEVE关闭接受,SD_SEND关闭接受。
//										//SD_BOTH关闭双向
//	int err = WSAGetLastError();//获取上一个错误
//	setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, c, 20);
//	closesocket(sock);//关闭套接字
//}
//int main()
//{
//
//	WORD word = MAKEWORD(2, 0);//设置主版本号和副版本号2.0
//	WSAData data;
//	int ret = WSAStartup(word, &data);//成功返回0
//	if (ret!=0)
//	{
//		debug("wrong when start up");
//		exit(0);
//	}
//	sockaddr_in svraddr;
//	memset(&svraddr, 0, 16);
//	svraddr.sin_port = htons(8080);
//	svraddr.sin_family = AF_INET;
//	svraddr.sin_addr.S_un.S_addr = INADDR_ANY;
//	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	_WINSOCK2API_::bind(server, (sockaddr*)&svraddr, sizeof(svraddr));
//	if (listen(server, 10)!=0)
//	{
//		debug("wrong when listen");
//		debug(GetLastError());
//		exit(0);
//	}
//	sockaddr_in inaddr;
//	int len = 0;
//	int length = 0;
//	while (true)
//	{
//		len = sizeof(inaddr);
//		SOCKET so = accept(server, (sockaddr*)&inaddr, &len);
//		if (so==INVALID_SOCKET)continue;
//		char c[100];
//		if ((length=recv(so, c, 100, 0))<=0)//<0出错，=0关闭，>0表示接受的字节数
//		{
//			debug("wrong when receieve");
//			debug(WSAGetLastError());
//			exit(0);
//		}i
//		else {
//			debugAll(c,length);
//			send(so, "success", 8, 0);
//		}
//		shutdown(so, SD_BOTH);
//		closesocket(so);
//	}
//
//	shutdown(server, SD_BOTH);
//	closesocket(server);
//	WSACleanup();
//}