#ifndef _DLCPSTRING_H
#define _DLCPSTRING_H

char* mallocFormatString(char *str,...);
char * mallocBuffer(int size);
char * DLMallocStringStrip(char *pStr);
int URLDecode(const char* str,
            const int strSize,
            char* result,
            const int resultSize);
//int u2g(char *inbuf,int inlen,char *outbuf,int outlen);

//int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen);

char *
mallocCopyString(char * str);

#endif
