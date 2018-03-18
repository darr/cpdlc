/////////////////////////////////////
// File name : dllog.c
// Create date : 2016-04-24 11:11
// Modified date : 2016-06-01 10:48
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "dllog.h"
#include "dlcpfunc.h"

//DLlog default config begin
#define IS_SHOW_LOG 1
#define DL_LOG_MODE log_mode_develop
#define LOG_FILE_PATH "./dllog/"
#define LOG_FILE_NAME "dllog"
#define LOG_PRINT_LEVEL log_level_debug
#define IS_PRINT_LINE_BREAK 0
//DLlog default config end

#define DL_LOG(str) printf("LEVEL:error     FILE:%s     FUNC:%s     LINE:%d     DESCRIPTION:%s", __FILE__,__FUNCTION__,__LINE__,str)


static int globalIsShowLog = IS_SHOW_LOG;
static log_mode_type globalLogMode = DL_LOG_MODE;
static char * globalLogFilePath = LOG_FILE_PATH;
static char * globalLogFileName = LOG_FILE_NAME;
static log_level_type globalLogPrintLevel = LOG_PRINT_LEVEL;
static int globalIsPrintLineBreak = IS_PRINT_LINE_BREAK;

static void
_FreeMemory(void *ptr){
    if(ptr == NULL){
        return;
    }else{
        free(ptr);
        ptr = NULL;
    }
}

void
setIsShowLog(int isShowLog)
{
    globalIsShowLog = isShowLog;
}

static
int
_getIsShowLog()
{
    return globalIsShowLog;
}

void
setLogPrintLevel(log_level_type logPrintLevel)
{
    globalLogPrintLevel = logPrintLevel;
}

static
log_level_type
_getLogPrintLevel()
{
    return globalLogPrintLevel;
}

void
setLogFilePath(char * logFilePath)
{
    globalLogFilePath = logFilePath;
}

static
char *
_getLogFilePath()
{
    return globalLogFilePath;
}

void
setLogMode(log_mode_type logMode)
{
    globalLogMode = logMode;
}

static
log_mode_type
_getLogMode()
{
    return globalLogMode;
}

void
setLogFileName(char *logFileName)
{
    globalLogFileName = logFileName;
}

static
char *
_getLogFileName()
{
    return globalLogFileName;
}

void
setIsPrintLineBreak(int isPrintLineBreak)
{
    globalIsPrintLineBreak = isPrintLineBreak;
}

static
int
_getIsPrintLineBreak()
{
    return globalIsPrintLineBreak;
}

static
char *
_getLogLevelStr(int log_level)
{
    char * log_level_str;
    switch(log_level){
        case log_level_debug:
            log_level_str = "debug";
            break;
        case log_level_info:
            log_level_str = "info";
            break;
        case log_level_warning:
            log_level_str = "warning";
            break;
        case log_level_null:
            log_level_str = "null";
            break;
        case log_level_error:
            log_level_str = "error";
            break;
        case log_level_syserror:
            log_level_str = "syserror";
            break;
        case log_level_fatal:
            log_level_str = "fatal";
            break;
        default:
            log_level_str = "unknown";
            DL_LOG("undifined log_level");
            }
    return log_level_str;
}

static
char*
_mallocBuffer(int size)
{
    char* bufferPointer = (char *) malloc (size);
    if (bufferPointer == NULL)
        DL_LOG("malloc fail\n");
    return bufferPointer;
}

static
char*
_mallocStrFormat(char *str,...)
{
    va_list argptr;
    int needreadcount;
    int strbuffersize = 1024;
    char* strbuffer = _mallocBuffer(strbuffersize);
    va_start(argptr, str);
    needreadcount = vsnprintf(strbuffer,strbuffersize,str, argptr);
    va_end(argptr);

    if(needreadcount >= strbuffersize) {
        DL_LOG("re malloc");
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

static
char*
_getCurrentDay()
{
    time_t timeStamp;
    time ( &timeStamp);
    int dayFormatSize = 11;
    struct tm * timeInfo= localtime ( &timeStamp);
    int currentYear = timeInfo->tm_year + 1900;
    int currentMon = timeInfo->tm_mon + 1;
    char* dayFormat = _mallocStrFormat("%d-%d-%d",currentYear,currentMon,timeInfo->tm_mday);
    return dayFormat;
}

static
void
_createFilePath(char* filePath)
{
    DIR *dirptr = NULL;
    struct dirent *entry;
    dirptr = opendir(filePath);
    if (dirptr == NULL){
        //int status = mkdir(filePath,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
        int status = dlcpMkdir(filePath);
        if (status == -1) {
            DL_LOG("");
            printf("dir:%s create dir fail errno:%d errordesc:%s \n", filePath,errno,strerror(errno));
        }
    }else{
        closedir(dirptr);
    }
}

static
char*
_getLogFileFullPath()
{
    char * dayFormat = _getCurrentDay();
    char* filePath = _getLogFilePath();
    char* fileName = _getLogFileName();
    _createFilePath(filePath);
    char *logFileFullPath = _mallocStrFormat("./%s%s%s.dllog",filePath,fileName,dayFormat);
    _FreeMemory(dayFormat);
    return logFileFullPath;
}

static
void
_writeToFile(char* text)
{
    FILE *filePointer;
    char *logFileFullPath = _getLogFileFullPath();
    char *openStyle = "a";
    filePointer= fopen(logFileFullPath,openStyle);
    fputs(text,filePointer);
    fclose(filePointer);
    _FreeMemory(logFileFullPath);
}

static
void
_writeLogToFile(int log_level, char *str, int line, const char *func, const char *file, char *log_level_str)
{
    char *fileCache = _mallocStrFormat("LEVEL:%-10sLINE:%-10dFILE:%s   FUNC:%s   DESCRIPTION:%s\n",log_level_str, line, file, func, str);
    if(isPlatIphone()!= 0 && isPlatIphoneSimulator() !=0){
        _writeToFile(fileCache);
    }

    _FreeMemory(fileCache);
}

static
void
_dealLogModeRelease(int log_level, char *str, int line, const char *func, const char *file, char *log_level_str)
{
    printf("%s\n",str);
    _writeLogToFile(log_level,str,line,func,file,log_level_str);
}

static
void
_dealLogModeDevelop(int log_level, char *str, int line, const char *func, const char *file, char *log_level_str)
{
    if (_getIsPrintLineBreak()){
        printf("LEVEL:%s\nFILE:%s\nFUNC:%s\nLINE:%d\nDESCRIPTION:%s\n",log_level_str, file,func,line,str);
    }else {
        printf("LEVEL:%-10sFILE:%s   FUNC:%s     LINE:%d     DESCRIPTION:%s\n",log_level_str, file,func,line,str);
    }
    _writeLogToFile(log_level,str,line,func,file,log_level_str);
}

static
void
_dealLogModeDebug(int log_level, char *str, int line, const char *func, const char *file, char *log_level_str)
{
    if (log_level > log_level_warning){
        _dealLogModeDevelop(log_level, str, line, func, file, log_level_str);
    }
    else {
        _dealLogModeRelease(log_level, str, line, func, file, log_level_str);
    }
}

static
void
_checkLogMode(int log_level, char *str, int line, const char *func, const char *file, char *log_level_str)
{
    int log_mode = _getLogMode();
    switch(log_mode){
        case log_mode_release:
            _dealLogModeRelease(log_level, str, line, func, file, log_level_str);
            break;
        case log_mode_debug:
            _dealLogModeDebug(log_level, str, line, func, file, log_level_str);
            break;
        case log_mode_develop:
            _dealLogModeDevelop(log_level, str, line, func, file, log_level_str);
            break;
        default:
            DL_LOG("unkown log mode");
        }
}

static
int
_checkIsSystemError(log_level_type log_level, char **str)
{
    int isSysError = 0;
    if(log_level == log_level_syserror) {
        char * syserrorStr = _mallocStrFormat("%s   system errno:%d system error description:%s",*str,errno,strerror(errno));
        *str = syserrorStr;
        isSysError = 1;
    }
    return isSysError;
}

static
void
__FreeMemorySysErrorStr(char *str, int isSysError)
{
    if (isSysError)
        _FreeMemory(str);
}

static
void
_checkLogLevelShowBell(int log_level)
{
    if(log_level > log_level_warning)
        printf("\007\007\007\007\007\007");
}

static
void
_DLlog(log_level_type log_level, int line, const char *func, const char *file,char* str)
{
    if(_getIsShowLog()) {
        if (log_level >= _getLogPrintLevel()){
            char *log_level_str = _getLogLevelStr(log_level);
            int isSysError = _checkIsSystemError(log_level, &str);

            _checkLogLevelShowBell(log_level);
            _checkLogMode(log_level, str, line, func, file, log_level_str);
            __FreeMemorySysErrorStr(str,isSysError);
        }
    }
}

void
DLlogFormat(log_level_type log_level, int line, const char *func, const char *file,char* str,...)
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
        str = strbufferNeed;
    }
    else {
        str = strbuffer;
    }

    _DLlog(log_level, line,func,file,str);
    _FreeMemory(str);
}
