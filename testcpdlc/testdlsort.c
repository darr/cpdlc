/////////////////////////////////////
// File name : testdlsort.c
// Create date : 2016-06-05 03:39
// Modified date : 2018-02-06 18:18
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../cpdlc/cpdlc/dllog.h"
#include "../cpdlc/cpdlc/dlsort.h"

unsigned long int next = 1;
unsigned long int count_size = 500;
//unsigned long int count_size = 2000000;

int rand(void){
    next = next * 1103515245 + 12345;
    //return (unsigned int)(next/65536) % 32768;
//    return (unsigned int)(next/65536) % 52768;
    return (unsigned int)(next/65536) % 100;
}

static
void
_testMaoPaoSortCorrect(int Array[], int N){
    int N_size = sizeof(int)*N;
    int *A = malloc(N_size);
    memcpy(A,Array,N_size);
    MaoPaoSort(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testInsertSortCorrect(int Array[], int N){
    int N_size = sizeof(int)*N;
    int *A = malloc(N_size);
    memcpy(A,Array,N_size);
    InsertSort(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testSelectSortCorrect(int Array[], int N){
    int N_size = sizeof(int)*N;
    int *A = malloc(N_size);
    memcpy(A,Array,N_size);
    SelectSort(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testInsertSort2Correct(int Array[], int N){
    int N_size = sizeof(int)*N;
    int *A = malloc(N_size);
    memcpy(A,Array,N_size);
    InsertSort2(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testBInsertSortCorrect(int Array[], int N){
    int N_size = sizeof(int)*N;
    int *A = malloc(N_size);
    memcpy(A,Array,N_size);
    BInsertSort(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testShellSortCorrect(int Array[], int N){
    int N_size = sizeof(int)*N;
    int *A = malloc(N_size);
    memcpy(A,Array,N_size);
    ShellSort(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testHeapSortCorrect(int Array[], int N){
    int N_size = sizeof(int)*N;
    int *A = malloc(N_size);
    memcpy(A,Array,N_size);
    HeapSort(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testQsortCorrect(int Array[], int N){
    int N_size = sizeof(int)*N;
    int *A = malloc(N_size);
    memcpy(A,Array,N_size);
    Qsort(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testQuickSortCorrect(int Array[], int N){
    int *A = malloc(sizeof(int)*N);
    memcpy(A,Array,N*4);
    QuickSort(A,N);
    int i;
    for (i =0; i< N; i++){
        int cur = A[i];
        DL_TEST_COMPARE_VALUE_INT(cur,i)
    }
    free(A);
}

static
void
_testInsertionSort(void){

    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i < A_size; i++){
        A[i] = rand();
    }
    clock_t begin_t = clock();
    InsertionSort(A,A_size);
    clock_t end_t = clock();
    printf("InsertionSort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testMaoPaoSort(void){
    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }
    clock_t begin_t = clock();
    SelectSort(A,A_size);
    clock_t end_t = clock();
    printf("MaoPaoSort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testSelectSort(void){
    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }
    clock_t begin_t = clock();
    SelectSort(A,A_size);
    clock_t end_t = clock();
    printf("SelectSort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testInsertSort(void){

    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }
    clock_t begin_t = clock();
    InsertSort(A,A_size);
    clock_t end_t = clock();
    printf("InsertSort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testInsertSort2(void){

    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }
    clock_t begin_t = clock();
    InsertSort2(A,A_size);
    clock_t end_t = clock();
    printf("InsertSort2:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testBInsertSort(void){

    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }
    clock_t begin_t = clock();
    BInsertSort(A,A_size);
    clock_t end_t = clock();
    printf("BInsertSort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testShellSort(void){

    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }

    clock_t begin_t = clock();
    ShellSort(A,A_size);
    clock_t end_t = clock();
    printf("ShellSort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testHeapSort(void){

    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }

    clock_t begin_t = clock();
    HeapSort(A,A_size);
    clock_t end_t = clock();
    printf("HeapSort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testQsort(void){

    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }

    clock_t begin_t = clock();
    Qsort(A,A_size);
    clock_t end_t = clock();
    printf("Qsort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testQuickSort(void){

    int A_size = count_size;
    int A[A_size];
    int i;
    for (i =0; i<A_size; i++){
        A[i] = rand();
    }

    clock_t begin_t = clock();
    QuickSort(A,A_size);
    clock_t end_t = clock();
    printf("QuickSort:%f 秒\n", (double)(end_t - begin_t)/ CLOCKS_PER_SEC);
}

static
void
_testSortCorrect(void){
    _testMaoPaoSort();
    _testSelectSort();
    _testInsertSort();
    _testInsertSort2();
    _testBInsertSort();
    _testShellSort();
    _testHeapSort();
    _testQsort();
    _testQuickSort();
}

static
void
_common_use_test(void){
    int N = 10;
    int Array[10] = { 6, 2, 3, 1, 9, 8, 0, 7, 4, 5, };
    _testMaoPaoSortCorrect(Array,N);
    _testInsertSortCorrect(Array,N);
    _testSelectSortCorrect(Array,N);
    _testInsertSort2Correct(Array,N);
    _testBInsertSortCorrect(Array,N);
    _testShellSortCorrect(Array,N);
    _testHeapSortCorrect(Array,N);
    _testQsortCorrect(Array,N);
    _testQuickSortCorrect(Array,N);
}

static
void
_marginal_test(void){
    _testSortCorrect();
}

static
void
_runtest(void){
    _common_use_test();
    if (1 == DL_MARGINAL_TEST)
        _marginal_test();
//    _marginal_test();
}

void testdlsort(void){
    _runtest();
}
