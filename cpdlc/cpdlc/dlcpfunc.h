/////////////////////////////////////
// File name : dlcpfunc.h
// Create date : 2016-05-23 09:58
// Modified date : 2018-01-25 23:58
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _dlcpfunc_H
#define _dlcpfunc_H

typedef enum
{
    dl_plat_unknow = 0,
    dl_plat_windows = 1,
    dl_plat_linux,
    dl_plat_mac,
    dl_plat_iphone,
    dl_plat_iphone_simulator,
} dl_plat;

int getDLPlat();
int dlcpMkdir(const char* filePath);
int isPlatWindows();
int isPlatLinux();
int isPlatMac();
int isPlatIphone();
int isPlatIphoneSimulator();

#endif

