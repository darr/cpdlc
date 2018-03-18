/////////////////////////////////////
// File name : dllog.h
// Create date : 2016-04-24 16:23
// Modified date : 2016-05-22 03:37
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLlog_H
#define _DLlog_H

#define DEBUG_LOG(str,...) DLlogFormat(log_level_debug,__LINE__,__FUNCTION__,__FILE__,str,##__VA_ARGS__)
#define INFO_LOG(str,...) DLlogFormat(log_level_info,__LINE__,__FUNCTION__,__FILE__,str,##__VA_ARGS__)
#define WARNING_LOG(str,...) DLlogFormat(log_level_warning,__LINE__,__FUNCTION__,__FILE__,str,##__VA_ARGS__)
#define CONDITION_VALUE_IS_NULL DLlogFormat(log_level_null,__LINE__,__FUNCTION__,__FILE__,"condition value is null")
#define ERROR_LOG(str,...) DLlogFormat(log_level_error,__LINE__,__FUNCTION__,__FILE__,str,##__VA_ARGS__)
#define SYSERROR_LOG(str,...) DLlogFormat(log_level_syserror,__LINE__,__FUNCTION__,__FILE__,str,##__VA_ARGS__)
#define FATAL_LOG(str,...) DLlogFormat(log_level_fatal,__LINE__,__FUNCTION__,__FILE__,str,##__VA_ARGS__)

typedef enum
{
    log_level_debug = 1,
    log_level_info,
    log_level_warning,
    log_level_null,
    log_level_error,
    log_level_syserror, //sys calls error,show system error description
    log_level_fatal,
} log_level_type;

typedef enum
{
    log_mode_release = 1,   //show run step log
    log_mode_debug,         //show log description info. log_level > warning then show detail
    log_mode_develop,       //show detail of the log info
}log_mode_type;

void DLlogFormat(log_level_type log_level, int line, const char *func, const char *file, char* str,...);

void setIsShowLog(int isShowLog);
void setLogPrintLevel(log_level_type logPrintLevel);
void setLogFilePath(char * logFilePath);
void setLogMode(log_mode_type logMode);
void setLogFileName(char *logFileName);
void setIsPrintLineBreak(int isPrintLineBreak);
#endif

