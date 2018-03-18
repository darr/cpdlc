#include <stdio.h>
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
#include "DLClient.h"

#define PROT_NUMBER 8183
#define BUFFER_SIZE 255

typedef struct sockaddr_in sockaddr_in;
typedef struct in_addr in_addr;
typedef struct sockaddr sockaddr;

int createSocket()
{
    int sockClient = socket(AF_INET, SOCK_STREAM,0);
    if(-1 == sockClient)
    {
        SYSERROR_LOG("Error socket create!");
        exit(1);
    }
    return sockClient;
}

void
initServerAddr(sockaddr_in* serverAddr)
{
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(PROT_NUMBER);

    char server_ip[20];
    bzero(server_ip, sizeof(server_ip));

    //DEBUG_LOG("请输入您所要连接的服务器IP地址:");
    //scanf("%s", server_ip);
    snprintf(server_ip,sizeof(server_ip),"106.187.39.151");
    DEBUG_LOG("您输入的IP地址为：%s\n",server_ip);

    serverAddr->sin_addr.s_addr = inet_addr(server_ip);
    bzero(&(serverAddr->sin_zero),8);
}

void
connectServerAddr(int sockClient, sockaddr_in* serverAddr)
{
    int sockaddr_in_length = sizeof(sockaddr_in);
    DEBUG_LOG("连接服务器中");
    while(1)
    {
        DEBUG_LOG("和服务器建立连接中。。。");
        int errConnect = connect(sockClient, (sockaddr*)serverAddr, sockaddr_in_length);
        if(-1 == errConnect)
        {
            SYSERROR_LOG("连接失败   ");
            sleep(10);
            continue;
        }
        else
            DEBUG_LOG("接收成功将要发送信息");
            break;
    }
    return;
}
char *
getSendData()
{
    cJSON *root,*fmt,*img,*thm,*fld;char *out;int i;	/* declare a few. */
	root=cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
	cJSON_AddStringToObject(fmt,"type",		"rect");
	cJSON_AddNumberToObject(fmt,"width",		1020);
	cJSON_AddNumberToObject(fmt,"height",		1080);
	cJSON_AddFalseToObject (fmt,"interlace");
	cJSON_AddNumberToObject(fmt,"frame rate",	24);
	
	out=cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n",out);
    //free(out);	/* Print to text, Delete the cJSON, print it, release the string. */
    return out;
}

char *
getDataBuffer(int contentLen)
{
    char* dataBuffer = mallocBuffer(contentLen);
    bzero(dataBuffer, contentLen);
    return dataBuffer;
}

void
sendDataServerAddr(int sockClient)
{
    char *sendData = getSendData();
    char response[1024];
    sprintf( response, "POST /furni/getcontent HTTP/1.1\r\nAccept: */*\r\nAccept-Language: zh-cn\r\nContent-Type: application/x-www-form-urlencoded\r\nAccept-Encoding: gzip, deflate\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; SV1; Maxthon; .NET CLR 1.1.4322)\r\nHost: 106.187.39.151:8183\r\n Content-Length: %d\r\nConnection: Keep-Alive\r\nCache-Control: no-cache\r\n\r\n%s", strlen( sendData), sendData);
    INFO_LOG("\n%s",response);
    //char *sendData = "hello world!";
    //char *dataBuffer = getDataBuffer(strlen(sendData)+1);
    //char *dataBuffer = getDataBuffer(strlen(response)+1);
    //strncpy(dataBuffer, "hello", strlen("hello"));
    //strncpy(dataBuffer, sendData, strlen(sendData));
    //strncpy(dataBuffer, sendData, strlen(response));
    //free(sendData);
    //int errSend = send(sockClient, dataBuffer, strlen(dataBuffer),0);
    int errSend = send(sockClient, response, strlen(response),0);
    if(-1 == errSend)
    {
        SYSERROR_LOG("send data error! ");
        exit(1);
    }
    return;
}

char *
getReturnContent(char * buffer)
{
    cJSON *objJSON = cJSON_Parse(buffer);
    char *out = cJSON_Print(objJSON);
    return out;
}

void
recvDataServerAddr(int sockClient)
{
    char dataBuffer[BUFFER_SIZE+1];
    bzero(dataBuffer, BUFFER_SIZE);
    int recv_bytes = recv(sockClient, dataBuffer, BUFFER_SIZE,0);
    if(recv_bytes < 0)
    {
        SYSERROR_LOG("receive data error! ");
        exit(1);
    }
    //char * recvContent = getReturnContent(dataBuffer);
   //DEBUG_LOG("收到从服务器返回的信息：\n%s\n", recvContent);
    //free(recvContent);
    DEBUG_LOG("收到从服务器返回的信息：\n%s\n", dataBuffer);
    return;
}

void runDLClient(){
    int sockClient = createSocket();
    sockaddr_in serverAddr;
    initServerAddr(&serverAddr);
    connectServerAddr(sockClient, &serverAddr);
    sendDataServerAddr(sockClient);
    recvDataServerAddr(sockClient);
    close(sockClient);
}

//  int main(int argc, int* argv[])
//  {
//      int sockClient = createSocket();
//      sockaddr_in serverAddr;
//      initServerAddr(&serverAddr);
//      connectServerAddr(sockClient, &serverAddr);
//      sendDataServerAddr(sockClient);
//      recvDataServerAddr(sockClient);
//      close(sockClient);
//      return 0;
//  }
