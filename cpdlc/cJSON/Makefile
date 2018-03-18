test.exe:test.o cJSON.o
	gcc -g -o test.exe test.o cJSON.o -lm
test.o:test.c cJSON.h
	gcc -g -c test.c
cJSON.o:cJSON.c cJSON.h
	gcc -g -c cJSON.c 
