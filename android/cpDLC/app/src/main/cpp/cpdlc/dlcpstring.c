#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
//#include <iconv.h>
#include "dlcpstring.h"

#define NON_NUM '0'

static void
_FreeMemory(void *ptr){
    free(ptr);
    ptr = NULL;
}

static char *
_mallocBuffer(int size)
{
    char* bufferPointer = (char *) malloc (size);
    if (bufferPointer == NULL){

        printf("LEVEL:error\nFILE:%s\nFUNC:%s\nLINE:%d\nDESCRIPTION:%s\n", __FILE__,__FUNCTION__,__LINE__,"malloc fail");
    }
    else{
        memset(bufferPointer, 0, size);
    }
    return bufferPointer;
}

char *
mallocBuffer(int size)
{
    return _mallocBuffer(size);
}

char
_char2Num(char ch){
if(ch>='0' && ch<='9')return (char)(ch-'0');
if(ch>='a' && ch<='f')return (char)(ch-'a'+10);
if(ch>='A' && ch<='F')return (char)(ch-'A'+10);
return NON_NUM;
}

char *
mallocFormatString(char *str,...)
{
    va_list argptr;
    int needreadcount;
    int strbuffersize = 1024;
    char* strbuffer = _mallocBuffer(strbuffersize);
    va_start(argptr, str);
    needreadcount = vsnprintf(strbuffer,strbuffersize,str, argptr);
    va_end(argptr);

    if(needreadcount >= strbuffersize) {
        printf("re malloc Func:%s Line:%d\n",__FUNCTION__,__LINE__);
        _FreeMemory(strbuffer);
        int size = needreadcount + 1;
        char* strbufferNeed = _mallocBuffer(size);
        va_start(argptr, str);
        vsnprintf(strbufferNeed,size,str, argptr);
        va_end(argptr);
        return strbufferNeed;
    }
    return strbuffer;
}

char *
mallocCopyString(char * str){
    char * p = mallocBuffer(strlen(str)+1);
    strcpy(p,str);
    return p;

}


char *
_stripLeft(char *str){
    int l = strlen(str);
    int i;
    int j = 0;
    for(i = 0;i < l; i++)
    {
        if((str[i]==' ')
           ||
           (str[i]=='\r')
           ||
           (str[i]=='\n')
           ){
           j++;
        }else{
           break;
        }
    }
    int nl = l - j;
    char *nStr = mallocBuffer(nl+1);
    int k=j;
    for(k = j;k<l;k++){
        nStr[k-j] = str[k];
    }
    free(str);
    return nStr;
}

char *
_stripRight(char *str){
    int l = strlen(str);
    int i;
    int j = 0;
    for(i = l;i > 0; i--)
    {
        if((str[i]==' ')
           ||
           (str[i]=='\r')
           ||
           (str[i]=='\n')
           ){
           j++;
        }else{
           break;
        }
    }
    int nl = l - j;
    char *nStr = mallocBuffer(nl+1);
    int k;
    for(k = 0;k<l-j;k++){
        nStr[k] = str[k];
    }
    free(str);
    return nStr;
}

//  int
//  _codeConvert(char *from_charset,
//                  char *to_charset,
//                  char *inbuf,
//                  int inlen,
//                  char *outbuf,
//                  int outlen)
//  {
//      iconv_t cd;
//      int rc;
//      char **pin = &inbuf;
//      char **pout = &outbuf;

//      cd = iconv_open(to_charset,from_charset);
//      if (cd==0) return -1;
//      memset(outbuf,0,outlen);
//      if (iconv(cd,pin,(size_t *)&inlen,pout,(size_t *)&outlen)==-1) return -1;
//      iconv_close(cd);
//      return 0;
//  }

char *
DLMallocStringStrip(char *pStr){
    char *nStr = mallocBuffer(strlen(pStr));
    strcpy(nStr,pStr);
    char *leftStr = _stripLeft(nStr);
    char *rightStr = _stripRight(leftStr);
    return rightStr;
}


int
URLDecode(const char* str,
            const int strSize,
            char* result,
            const int resultSize)
{
    char ch, ch1, ch2;
    int i;
    int j = 0; /* for result index */

    if ((str == NULL)
        || (result == NULL)
        || (strSize <= 0)
        || (resultSize <= 0)
        ) {
    return 0;
    }

    for (i=0; (i<strSize) && (j<resultSize); i++) {
        ch = str[i];
        switch (ch) {
            case '+':
                result[j++] = ' ';
                break;
            case '%':
                if (i+2 < strSize) {
                ch1 = _char2Num(str[i+1]);
                ch2 = _char2Num(str[i+2]);
                    if ((ch1 != NON_NUM) && (ch2 != NON_NUM)) {
                        result[j++] = (char)((ch1<<4) | ch2);
                        i += 2;
                        break;
                        }
                }
            default:
                result[j++] = ch;
                break;
        }
    }

    result[j] = '\0';
    return j;
}


//  int
//  u2g(char *inbuf,int inlen,char *outbuf,int outlen) {
//      return _codeConvert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
//  }

//  int
//  g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen) {
//      return _codeConvert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
//  }

