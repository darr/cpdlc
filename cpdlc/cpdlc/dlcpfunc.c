/////////////////////////////////////
// File name : dlcpfunc.c
// Create date : 2016-05-23 09:57
// Modified date : 2018-01-25 04:50
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
#include "dlcpfunc.h"
#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

int getDLPlat(){
    #ifdef __WIN32
        return dl_plat_windows;
    #endif

    #ifdef __linux__
        return dl_plat_linux;
    #endif

    #ifdef TARGET_OS_MAC
        return dl_plat_mac;
    #endif

    #ifdef __APPLE__
        return dl_plat_mac;
    #endif

    #ifdef TARGET_OS_IPHONE
        return dl_plat_iphone;
    #endif

    #ifdef TARGET_IPHONE_SIMULATOR
        return dl_plat_iphone_simulator;
    #endif

    return dl_plat_unknow;
}

int
isPlatWindows(){
    int p = getDLPlat();
    if (p == dl_plat_windows)
        return 0;
    return -1;
}

int
isPlatLinux(){
    int p = getDLPlat();
    if (p == dl_plat_linux)
        return 0;
    return -1;
}

int
isPlatMac(){
    int p = getDLPlat();
    if (p == dl_plat_mac)
        return 0;
    return -1;
}

int
isPlatIphone(){
    int p = getDLPlat();
    if (p == dl_plat_iphone)
        return 0;
    return -1;
}

int
isPlatIphoneSimulator(){
    int p = getDLPlat();
    if (p == dl_plat_iphone_simulator)
        return 0;
    return -1;
}

void
dealPlat(){
    #ifdef WIN32
    printf("windows\n");
    #endif

	#ifdef __linux__
	printf("linux\n");
	#endif

	#if TARGET_OS_IPHONE
		printf("iphone os");
	#elif TARGET_OS_MAC
		printf("mac os");
	#endif

	#ifdef __llvm__
	printf("llvm-gcc The Mac OS X \n");
	#endif

    #ifdef __ppc__
    printf("32 bit PowerPC\n");
    #endif

    #ifdef __ppc64__
    printf("64 bit PowerPC\n");
    #endif

    #ifdef __i386__
    printf("32 bit x86\n");
    #endif

    #ifdef __x86_64__
    printf("64 bit x86\n");
    #endif

    #ifdef __arm__
    printf("32 bit arm AArch32\n");
    #endif

    #ifdef __arm64__
    printf("64 bit arm64 AArch64\n");
    #endif

    #ifdef __ARM_VFPV4__
    printf("VFPv4 ARM\n");
    #endif

    #ifdef __FMA__
    printf("Hardware FMA\n");
    #endif

    #ifdef __LP64__
    printf("Point Address 64 bit\n");
    #endif
}

int
dlcpMkdir(const char* filePath){
    //windows
    #ifdef __WIN32
        int status = mkdir(filePath);
        return status;
    #endif

    //linux
    #ifdef __linux__
        int status = mkdir(filePath,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
        return status;
    #endif

    //mac

    #ifdef __APPLE__
        int status = mkdir(filePath,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
        return status;
    #endif
    //#ifdef __llvm__
}

