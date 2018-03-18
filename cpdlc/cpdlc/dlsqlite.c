/////////////////////////////////////
// File name : dlsqlite.c
// Create date : 2017-11-29 05:09
// Modified date : 2017-11-29 05:33
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>



int
main(void){
    sqlite3 *db=NULL;
     char *zErrMsg = 0;
     int rc;

     //打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
     rc = sqlite3_open("./mysqlite.db", &db);
     if( rc ){
        printf("这是大开啦额吗");
      //fprintf(stderr, "Can't open database: %s/n", sqlite3_errmsg(db));
      //sqlite3_close(db);
      //exit(1);
     }
     else printf("You have opened a sqlite3 database named zieckey.db successfully!/nCongratulations! Have fun !  ^-^ /n");
     //sqlite3_close(db); //关闭数据库
     return 0;
}
