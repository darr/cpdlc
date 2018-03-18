/////////////////////////////////////
// File name : testdlcpNet.c
// Create date : 2016-05-22 05:18
// Modified date : 2016-10-22 15:28
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include "testdlcpNet.h"
#include "../cpdlc/cpdlc/dlcpNet.h"
#include "../cpdlc/cpdlc/dllog.h"


////// test code //////////////////////////////////////////
void
testdlcpNetClient(){
    int serverPort = 7589;
    char *sendContent = "send this message from a client\n";
    char *serverIP = "106.187.39.151";
    //char *serverIP = "127.0.0.1";
    char* ret_content = blockTcpRequest(sendContent,serverIP,serverPort);
    INFO_LOG(ret_content);
}

void
testdlcpNetServer(){
    int serverPort = 7589;
    char *sendContent = "send this message from a client \n";
    char *serverIP = "127.0.0.1";
    char* ret_content = blockTcpRequest(sendContent,serverIP,serverPort);
    INFO_LOG(ret_content);
}

void
testdlcpNet(){
    testdlcpNetClient();
}


