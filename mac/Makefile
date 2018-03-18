tempPath = ./temp/

objPath = ./temp/obj/
objects = $(objPath)main.o $(objPath)dllog.o $(objPath)dlcpfunc.o $(objPath)dlcpstring.o $(objPath)cJSON.o $(objPath)DLObject.o $(objPath)dlcpNet.o $(objPath)DLSqlite.o $(objPath)DLADTBase.o $(objPath)DLStack.o $(objPath)dl_generic_chain_list.o $(objPath)DLGenericChainList.o $(objPath)DLGenericStack.o $(objPath)DLGenericSingleChainList.o $(objPath)DLQueue.o $(objPath)DLList.o $(objPath)DLDict.o $(objPath)dlsort.o

testObjPath = ./temp/testObj/
testObjects = $(testObjPath)testcpdlc.o $(testObjPath)testdllog.o $(testObjPath)testcjson.o $(testObjPath)testdlobject.o $(testObjPath)testdlcpNet.o $(testObjPath)testdlsqlite.o $(testObjPath)testdl_generic_chain_list.o $(testObjPath)testDLGenericChainList.o $(testObjPath)testDLGenericStack.o $(testObjPath)testDLGenericSingleChainList.o $(testObjPath)testDLQueue.o $(testObjPath)testDLStack.o $(testObjPath)testDLList.o $(testObjPath)testDLDict.o $(testObjPath)testdlsort.o


basePath = ../cpdlc/
testPath = ../testcpdlc/
runPath = ./

CC = gcc
CPPFLAGS = -g -o
CFLAGS = -g -c
LIBS    = -lsqlite3

APP_NAME = cpdlc.exe

checkDir: clear checkTempDir checkObjDir checkTestDir $(APP_NAME)
$(APP_NAME): $(objects) $(testObjects)
	$(CC) $(CPPFLAGS) $(tempPath)$@ $^ -lm $(LIBS)

checkTempDir:
	test -d $(tempPath)|| mkdir -p $(tempPath)
checkObjDir:
	test -d $(objPath)|| mkdir -p $(objPath)
checkTestDir:
	test -d $(testObjPath)|| mkdir -p $(testObjPath)

$(objPath)main.o:$(runPath)main.c
	$(CC) $(CFLAGS) $^ -o $@

$(objPath)%.o:$(basePath)*/%.c
	$(CC) $(CFLAGS) $^ -o $@

$(objPath)%.o:$(basePath)dlsqlite/%.c
	$(CC) $(CFLAGS) $^ -o $@

$(objPath)%.o:$(basePath)dlADTBase/%.c
	$(CC) $(CFLAGS) $^ -o $@


$(testObjPath)%.o:$(testPath)%.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm $(objects) $(testObjects) $(tempPath)$(APP_NAME)
clear:
	rm -rf $(tempPath)


