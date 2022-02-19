#pragma once
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<stdbool.h>
#define SPORT 8888
#define err(errMsg) printf("[line:%d]%s failed code %d" ,__LINE__,errMsg, WSAGetLastError());

//包标志位
enum MSGTAG
{
	MSG_FILENAME = 1,
	MSG_FILESIZE = 2,
	MSG_READY_READ = 3,
	MSG_SENDFILE = 4,
	MSG_SUCCESSED = 5,
	MSG_OPENFILE_FAILD = 6,
	ENDSEND=7,
	//CHAT_REQUSET = 8,
	//CHAT_START = 9,
	CHAT_END = 10,
	CHAT_ING=11
};

//包结构
#pragma pack(1)
#define PACKET_SIZE (102400-sizeof(int)*3)//!!!!
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
			char chatbuf[PACKET_SIZE];
		}CHAT;
	};
};
#pragma pack()


//初始化socket库
bool initSocket();
//关闭socket库
bool closeSocket();
//监听客户端连接
void connectToHost();
//处理消息
bool processMsg(SOCKET);
//获取文件名
void downloadFileName(SOCKET serfd);
//根据返回的文件大小分配内存空间
void readyread(SOCKET serfd, struct MsgHeader*);
//写文件
bool writeFile(SOCKET serfd, struct MsgHeader*);
//聊天室
bool chatroom(SOCKET);
//多线程发送函数
unsigned __stdcall p_send(void*);
//多线程接受函数
unsigned __stdcall p_recv(void*);