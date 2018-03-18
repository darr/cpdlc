/////////////////////////////////////
// File name : dlcpNet.c
// Create date : 2016-07-12 04:59
// Modified date : 2018-01-26 00:30
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifdef __WIN32
    #include <winsock2.h>
#endif

#ifdef __linux__
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <stdarg.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include "../cpdlc/dllog.h"
    #include "../cpdlc/dlcpstring.h"
    #include "../cJSON/cJSON.h"
#endif

#ifdef __APPLE__
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <stdarg.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include "../cpdlc/dllog.h"
    #include "../cpdlc/dlcpstring.h"
    #include "../cJSON/cJSON.h"
#endif

#include <stdio.h>
#include "dllog.h"
#define BUFFER_SIZE 1024

typedef struct sockaddr_in sockaddr_in;
typedef struct in_addr in_addr;
typedef struct sockaddr sockaddr;

#ifdef __WIN32
void
WSAStartInit(WSADATA* wsaData){
    WORD wVersionRequested;
    wVersionRequested = MAKEWORD(2, 2);
    int ret;
    ret = WSAStartup(wVersionRequested, wsaData);
    if (ret!=0){
        SYSERROR_LOG("WSAStartup() failed!");
        exit(1);
    }
    if (LOBYTE(wsaData->wVersion)!=2 || HIBYTE(wsaData->wVersion)!=2){
        WSACleanup();
        ERROR_LOG("Invalid WinSock version!");
        exit(1);
        //return;
    }
    return;
}
#endif

static
int
_createSocket()
{
    #ifdef __WIN32
        int sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    #endif

    #ifdef __linux__
        int sockClient = socket(AF_INET, SOCK_STREAM,0);
    #endif

    #ifdef __APPLE__
        int sockClient = socket(AF_INET, SOCK_STREAM,0);
    #endif
        if (sockClient == -1){
        #ifdef __WIN32
            WSACleanup();
        #endif
            ERROR_LOG("create socket failed!");
            exit(1) ;
        }
        return sockClient;
}

static
void
_initServerAddr(sockaddr_in* serverAddr,int server_port,const char* server_ip){
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(server_port);
    #ifdef __WIN32
       serverAddr->sin_addr.S_un.S_addr = inet_addr(server_ip);
    #endif

    #ifdef __linux__
        serverAddr->sin_addr.s_addr = inet_addr(server_ip);
    #endif

    #ifdef __APPLE__
        serverAddr->sin_addr.s_addr = inet_addr(server_ip);
    #endif

    return;
}

static
void
_connectServerAddr(int sockClient, sockaddr_in* serverAddr){
    int sockaddr_in_length = sizeof(sockaddr_in);
    DEBUG_LOG("will connect to the server");

    while (1){
        DEBUG_LOG("connectting to the server");
        #ifdef __WIN32
        int errConnect = connect(sockClient, serverAddr, sockaddr_in_length);
        #endif
        #ifdef __linux__
        int errConnect = connect(sockClient, (sockaddr*)serverAddr, sockaddr_in_length);
        #endif
        #ifdef __APPLE__
        int errConnect = connect(sockClient, (sockaddr*)serverAddr, sockaddr_in_length);
        #endif

        if (-1 == errConnect){
            ERROR_LOG("connect failed !!!");
            //continue;
            #ifdef __WIN32
            closesocket(sockClient);
            WSACleanup();
            #endif
            #ifdef __linux__
            close(sockClient);
            #endif
            #ifdef __APPLE__
            close(sockClient);
            #endif
            break;
        }else{
            INFO_LOG("connnect sucess,prepare to send message");
            break;
        }
    }
    return;
}

static
void
_sendDataServerAddr(int sockClient, const char* content){
    int errSend =  send(sockClient, content, strlen(content), 0);
    if (-1 == errSend){
        ERROR_LOG("send data error!");
        exit(1);
    }else{
        INFO_LOG("data has been sent to server");
    }
    return;
}

static
char*
_recvDataServerAddr(int sockClient){
    char dataBuffer[BUFFER_SIZE + 1];
    bzero(dataBuffer, BUFFER_SIZE);
    int recv_bytes = recv(sockClient, dataBuffer, BUFFER_SIZE,0);
    if (recv_bytes < 0){
        ERROR_LOG("receive data error!");
        exit(1);
    }else{
        dataBuffer[recv_bytes] = 0x00;
        INFO_LOG("receive from server:\n%s\n", dataBuffer);
    }
    char* ret_content = mallocFormatString(dataBuffer);
    return ret_content;
}

char*
blockTcpRequest(const char* content,const char* server_ip,int server_port){
    #ifdef __WIN32
       SOCKET sockClient;
       WSADATA wsaData;
       WSAStartInit(&wsaData);
       sockClient = createSocket();
    #endif

    #ifdef __linux__
    int sockClient = _createSocket();
    #endif
    #ifdef __APPLE__
    int sockClient = _createSocket();
    #endif
    sockaddr_in serverAddr;
    _initServerAddr(&serverAddr,server_port,server_ip);
    _connectServerAddr(sockClient,&serverAddr);
    _sendDataServerAddr(sockClient,content);
    char* ret_content = _recvDataServerAddr(sockClient);
    #ifdef __WIN32
        closesocket(sockClient);
        WSACleanup();
    #endif
    #ifdef __linux__
    close(sockClient);
    #endif
    #ifdef __APPLE__
    close(sockClient);
    #endif
    return ret_content;
}
