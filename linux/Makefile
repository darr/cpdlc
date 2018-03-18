tempPath = ./temp/

objPath = ./temp/obj/
objects = $(objPath)main.o $(objPath)dllog.o $(objPath)dlcpfunc.o $(objPath)dlcpstring.o $(objPath)cJSON.o $(objPath)DLObject.o $(objPath)DLPerson.o $(objPath)dlcpNet.o

testObjPath = ./temp/testObj/
testObjects = $(testObjPath)testcpdlc.o $(testObjPath)testdllog.o $(testObjPath)testcjson.o $(testObjPath)testdlobject.o $(testObjPath)testdlcpNet.o

basePath = ../cpdlc/
testPath = ../testcpdlc/
runPath = ./

cpdlc.exe: checkTempDir checkObjDir checkTestDir $(objects) $(testObjects)
	gcc -g -o $(tempPath)cpdlc.exe $(objects) $(testObjects) -lmysqlclient 
checkTempDir:
	test -d $(tempPath)|| mkdir -p $(tempPath)
checkObjDir:
	test -d $(objPath)|| mkdir -p $(objPath)
checkTestDir:
	test -d $(testObjPath)|| mkdir -p $(testObjPath)

$(objPath)main.o:$(runPath)main.c $(basePath)cpdlc/dllog.h
	gcc -g -c main.c -o $(objPath)main.o
$(objPath)dllog.o:$(basePath)cpdlc/dllog.c $(basePath)cpdlc/dllog.h
	gcc -g -c $(basePath)cpdlc/dllog.c -o $(objPath)dllog.o
$(objPath)dlcpNet.o:$(basePath)cpdlc/dlcpNet.c $(basePath)cpdlc/dlcpNet.h
	gcc -g -c $(basePath)cpdlc/dlcpNet.c -o $(objPath)dlcpNet.o
$(objPath)dlcpfunc.o:$(basePath)cpdlc/dlcpfunc.c $(basePath)cpdlc/dlcpfunc.h
	gcc -g -c $(basePath)cpdlc/dlcpfunc.c -o $(objPath)dlcpfunc.o
$(objPath)cJSON.o:$(basePath)cJSON/cJSON.c $(basePath)cJSON/cJSON.h
	gcc -g -c $(basePath)cJSON/cJSON.c -o $(objPath)cJSON.o
$(objPath)DLObject.o:$(basePath)dlobject/DLObject.c $(basePath)dlobject/DLObject.h
	gcc -g -c $(basePath)dlobject/DLObject.c -o $(objPath)DLObject.o
$(objPath)DLPerson.o:$(basePath)dlperson/DLPerson.c $(basePath)dlperson/DLPerson.h
	gcc -g -c $(basePath)dlperson/DLPerson.c -o $(objPath)DLPerson.o
#$(objPath)DLClient.o:$(basePath)dlclient/DLClient.c $(basePath)dlclient/DLClient.h
#	gcc -g -c $(basePath)dlclient/DLClient.c -o $(objPath)DLClient.o
$(objPath)dlcpstring.o:$(basePath)cpdlc/dlcpstring.c $(basePath)cpdlc/dlcpstring.h
	gcc -g -c $(basePath)cpdlc/dlcpstring.c -o $(objPath)dlcpstring.o



$(testObjPath)testcpdlc.o:$(testPath)testcpdlc.c $(testPath)testcpdlc.h
	gcc -g -c $(testPath)testcpdlc.c -o $(testObjPath)testcpdlc.o
$(testObjPath)testdllog.o:$(testPath)testdllog.c $(testPath)testdllog.h
	gcc -g -c $(testPath)testdllog.c -o $(testObjPath)testdllog.o
$(testObjPath)testcjson.o:$(testPath)testcjson.c $(testPath)testcjson.h
	gcc -g -c $(testPath)testcjson.c -o $(testObjPath)testcjson.o
$(testObjPath)testdlcpNet.o:$(testPath)testdlcpNet.c $(testPath)testdlcpNet.h
	gcc -g -c $(testPath)testdlcpNet.c -o $(testObjPath)testdlcpNet.o
$(testObjPath)testdlobject.o:$(testPath)testdlobject.c $(testPath)testdlobject.h
	gcc -g -c $(testPath)testdlobject.c -o $(testObjPath)testdlobject.o
#$(testObjPath)testDLClient.o:$(testPath)testDLClient.c $(testPath)testDLClient.h
#	gcc -g -c $(testPath)testDLClient.c -o $(testObjPath)testDLClient.o

clean:
	rm $(objects) $(testObjects) $(tempPath)cpdlc.exe

