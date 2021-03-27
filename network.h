#pragma once
#include<WinSock2.h>
#include"graphBasic.h"
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<queue>
using namespace std;
function<void(void)> hander = 0;
bool SocketInited = false;
int NumOfSocks = 0;
mutex mu;
condition_variable cond;
unique_lock<mutex> locker(mu);
void initAPI()
{
	WORD word = MAKEWORD(2, 0);//设置主版本号和副版本号2.0
	WSAData data;
	if (WSAStartup(word, &data)!=0)//成功返回0
		debug("Wrong when start up socket APIs,last error"+WSAGetLastError());
	SocketInited = true;
}
string getHostByName(string s)
{
	if (!SocketInited)
		initAPI();
	return inet_ntoa(*((struct in_addr*)gethostbyname(s.c_str())->h_addr));
}
string getIP(string s)
{
	if (!SocketInited)
		initAPI();
	return inet_ntoa(*((struct in_addr*)gethostbyname(s.c_str())->h_addr));
}

class userInfo {
public:
	userInfo(string ipp, unsigned short portt) {
		ip = ipp;
		port = portt;
	}
	string toString()
	{
		return " ip: "+ip+", port: "+itos(port);
	}
	string ip;
	unsigned short port;
};

class AbstractSocket {
public:
	AbstractSocket() {
		if (!SocketInited)
			initAPI();
		NumOfSocks++;
	}
	void setPort(unsigned short port)
	{
		addr.sin_port = htons(port);
		if (needbind&&_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16)<0)//=0成功，<0失败
			debug("Wrong when bind socket and address,last error"+WSAGetLastError());
	}

	void setIPAddress(const char* IPAddress = "ANY")
	{
		if (IPAddress=="ANY")
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
		else addr.sin_addr.S_un.S_addr = inet_addr(IPAddress);
		if (needbind&&_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16)<0)//=0成功，<0失败
			debug("Wrong when bind socket and address,last error"+WSAGetLastError());
	}

	userInfo getUserInfo(sockaddr_in in)
	{
		auto port = ntohs(in.sin_port);
		auto ip = inet_ntoa(in.sin_addr);
		return userInfo(ip, port);
	}

	~AbstractSocket() {
		NumOfSocks--;
		shutdown(sock, SD_BOTH);
		closesocket(sock);
		if (NumOfSocks==0)
		{
			WSACleanup();
			SocketInited = false;
		}
	}
	bool needbind = false;
	sockaddr_in addr;
	SOCKET sock;
};

class SVRSocket :public AbstractSocket {//服务端套接字
public:
	SVRSocket(unsigned short port, string IPAddress = "ANY")
	{
		needbind = true;
		memset(&addr, 0, 16);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		if (IPAddress=="ANY")
			addr.sin_addr.S_un.S_addr = INADDR_ANY;
		else addr.sin_addr.S_un.S_addr = inet_addr(IPAddress.c_str());
		if (_WINSOCK2API_::bind(sock, (sockaddr*)&addr, 16)<0)//=0成功，<0失败
			debug("Wrong when bind socket and address,last error"+WSAGetLastError());
	}

	void listen()
	{
		if (_WINSOCK2API_::listen(sock, 50)<0)
		{
			debug("Wrong when start listen,last error: "+WSAGetLastError());
		}
		else
		//创建线程一直查询是否有新的连接
			if (!queryCreated)
			{
				createQuery();
				queryCreated = true;
			}

	}

	void createQuery()
	{
		fu = async([=]() {
			int len = 16;
			while (true)
			{
				len = 16;
				SOCKET so = accept(sock, (sockaddr*)&addr, &len);
				//send(so, "You connet success", 19, 0);
				if (so==INVALID_SOCKET)continue;
				else
				{
					debug("accepted a new client, "+getUserInfo(addr).toString());
					list.push_back(so);
					buffer.push_back(string());
					users.push_back(getUserInfo(addr));
					threadlist.push_back(thread([=](int i) {
						char c[500];
						while (true)
						{
							memset(c, 0, 500);
							int ret = recv(list[i], c, 500, 0);
							if (ret<=0)
							{
								shutdown(so, SD_BOTH);
								closesocket(so);
								debug("client shut down: "+itos(i));
								erase(i);
								break;
							}
							else
							{
								buffer[i] += c;
								debug(c);
							}
						}
					}, list.size()-1));
					threadlist[threadlist.size()-1].detach();
				}
			}
		});
	}
	void erase(int i)
	{
		list.erase(list.begin()+i);
		TerminateThread(threadlist[i].native_handle(), 0);
		threadlist.erase(threadlist.begin()+i);
		buffer.erase(buffer.begin()+i);
		users.erase(users.begin()+i);
	}

	bool queryCreated = false;
	future<void> fu;
	vector<SOCKET> list;
	vector<thread> threadlist;
	vector<string> buffer;
	vector<userInfo> users;
};

class Socket :public AbstractSocket {//客户端套接字
public:
	Socket() {}

	Socket(string ip, unsigned short port)
	{
		memset(&addr, 0, 16);
		addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	void connect()
	{
		if (thd)TerminateThread(thd->native_handle(), 0);
		if (_WINSOCK2API_::connect(sock, (sockaddr*)&addr, 16)<0)
		{
			debug("Wrong when connect to host: "+getUserInfo(addr).toString());
		}
		else {
			debug("connect succesfully");
			static future<void> fu=async([=]() {
				char c[500] = {};
				while (true)
					if (recv(sock, c, 500, 0)<=0)
					{
						debug("connect closed");
						break;
					}
					else {
						string s = c;
						debug(s);
						while(true)
						{
							auto pos = s.find('\n');
							if (pos!=string::npos)
							{
								msg.push(string(s.begin(), s.begin()+pos));
								s = s.substr(pos+1);
							}
							else break;
						}
						newMsg = true;
						if (hander)hander();
						memset(c, 0, 500);
					}
			});
		}
	}

	void send(string s)
	{
		if (_WINSOCK2API_::send(sock, s.c_str(), s.length(), 0)<0)
		{
			debug("Wrong when send MSG to host: "+getUserInfo(addr).toString());
		}
	}
	string getMessage()
	{
		if (newMsg)
		{
			return msg.front();
		}
		else {
			return "";
		}
	}
	thread* thd = 0;
	bool newMsg = false;
	queue<string> msg;

};

class UDPSocket :public AbstractSocket {//客户端套接字
public:
	UDPSocket() {}

	UDPSocket(string ip, unsigned short port)
	{
		memset(&addr, 0, 16);
		addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
		addr.sin_port = htons(port);
		addr.sin_family = AF_INET;
		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}

	void connect()
	{
		if (_WINSOCK2API_::connect(sock, (sockaddr*)&addr, 16)<0)
		{
			debug("Wrong when connect to host: "+getUserInfo(addr).toString());
		}
		else {
			static thread query([=]() {
				char c[500] = {};
				while (true)
					if (recv(sock, c, 500, 0)<=0)
					{
						debug("connect closed");
						break;
					}
					else {
						msg += c; newMsg = true;
					}
			});
			query.detach();
		}
	}

	void send(string s)
	{
		if (_WINSOCK2API_::send(sock, s.c_str(), s.length(), 0)<0)
		{
			debug("Wrong when send MSG to host: "+getUserInfo(addr).toString());
		}
	}

	string getMessage()
	{
		if (newMsg)
		{
			newMsg = false;
			return msg;
		}
		else {
			return "";
		}
	}

	bool newMsg = false;
	string msg;
};