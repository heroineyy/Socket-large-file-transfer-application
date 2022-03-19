#pragma once
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<stdbool.h>
#define SPORT 8888
#define err(errMsg) printf("[line:%d]%s failed code %d" ,__LINE__,errMsg, WSAGetLastError());

enum MSGTAG
{
	MSG_FILENAME = 1,
	MSG_FILESIZE = 2,
	MSG_READY_READ = 3,
	MSG_SENDFILE = 4,
	MSG_SUCCESSED = 5,
	MSG_OPENFILE_FAILD = 6,//告诉客户端文件找不到
	ENDSEND = 7,
	//CHAT_REQUSET = 8,//聊天请求
	//CHAT_START = 9,//聊天开始，告诉客户端可以进行聊天啦
	CHAT_END = 10,//关闭聊天室
	CHAT_ING=11//聊天进行时
};


#pragma pack(1)//设置结构体字节对齐
#define PACKET_SIZE (10240 -sizeof(int)*3)//！！！
struct MsgHeader
{
	enum MSGTAG msgID;//当前消息标记
	union MyUnion
	{
		struct
		{
			char fileName[256];
			int fileSize;
		}fileInfo; //260
		struct
		{
			int nStart;
			int nsize;//该包的数据大小
			char buf[PACKET_SIZE];
		}packet;
		struct
		{
			char chatbuf[PACKET_SIZE];//聊天信息缓存
		}CHAT;
	};
};
#pragma pack()
	

//初始化socket库
bool initSocket();
//关闭socket库
bool closeSocket();
//监听客户端连接
void listenToClient();
//处理消息
bool processMsg(SOCKET);
//读取文件，获得文件大小
bool readFile(SOCKET, struct MsgHeader*);
//发送文件
bool sendFile(SOCKET, struct MsgHeader*);
//多线程发送函数
unsigned __stdcall p_send(void*);
//多线程接受函数
unsigned __stdcall p_recv(void*);
