/////////////////////////////////////
// File name : dlsort.c
// Create date : 2018-02-01 17:11
// Modified date : 2018-02-06 18:12
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "dllog.h"
#include "dlsort.h"

#define LeftChild(i) ( 2 * ( i ) + 1)

void
Swap(int* a,int* b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void
MaoPaoSort(int r[], int n){
    int low = 0;
    int high = n - 1;
    int tmp,j;
    while (low < high){
        for (j = low; j < high; ++j){
            if (r[j] > r[j+1]){
                tmp = r[j];
                r[j] = r[j+1];
                r[j+1] = tmp;
            }
        }
        --high;
        for (j = high; j > low; --j){
            if (r[j] < r[j-1]){
                tmp = r[j];
                r[j] = r[j-1];
                r[j-1] = tmp;
            }
        }
        ++low;
    }
}

void
SelectSort(int a[],int n){
    int i;
    for (i = 0;i<n-1;i++){
        int k = i;
        int j;
        for (j = i + 1; j < n; j++){
            if (a[j] < a[k]){
                k = j;
            }
        }
        if (k!=i){
            int t = a[i];
            a[i] = a[k];
            a[k] = t;
        }
    }
}

void
PercDown( int A[],int i, int A_size){
    int Child;
    int tmp;
    for (tmp = A[i]; LeftChild(i) < A_size; i = Child){
        Child = LeftChild(i);
        if (Child != A_size - 1 && A[Child + 1] > A[Child]){
            Child++;
        }
        if(tmp < A[Child]){
            A[i] = A[Child];
        }else{
            break;
        }
    }
    A[i] = tmp;
}

void
HeapSort(int A[],int A_size){
    int i;
    for (i = A_size / 2; i >= 0; i--)
        PercDown(A,i,A_size);
    for (i = A_size - 1; i > 0; i--){
        Swap(&A[0],&A[i]);
        PercDown(A,0,i);
    }
}

void
InsertSort(int A[], int A_size){
    int j;
    int m;
    int tmp;

    for (m = 1; m < A_size; m++){
        tmp = A[m];
        for (j=m; j>0 && A[j-1] > tmp; j--){
            A[j] = A[j-1];
        }
        A[j] = tmp;
    }
}

void
InsertSort2(int A[],int n){
    int i;
    for (i = 1; i < n; i++){
        if (A[i] < A[i-1]){
            int j = i - 1;
            int x = A[i];
            A[i] = A[i-1];
            while (j >=0 && x < A[j]){
                A[j+1] = A[j];
                j--;
            }
            A[j+1] =x;
        }
    }
}

void
BInsertSort(int a[], int n){
    int i;
    for (i = 1; i < n; i++){
        int low = 0;
        int high = i;
        if (a[i] < a[i-1]){
            int x = a [i];
            a[i] = a[i - 1];
            while (low<=high){
                int m = (low+high)/2;
                if(x<a[m])  high = m - 1;
                else low = m + 1;
            }
            int j;
            for (j = i - 1;j >= high + 1;j--){
                a[j+1] = a[j];
            }
            a[j+1] = x;
        }
    }
}

void
InsertionSort(int A[],int A_size){
    InsertSort2(A,A_size);
}

void
ShellSort(int A[],int A_size){
    int i;
    int j;
    int Increment;
    int tmp;
    for (Increment = A_size / 2; Increment > 0; Increment /=2){
        for (i = Increment; i < A_size; i++){
            tmp = A[i];
            for (j = i; j >= Increment; j -= Increment){
                if (tmp < A[j - Increment]){
                    A[j] = A[j - Increment];
                }else{
                    break;
                }
            }
            A[j] = tmp;
        }
    }
}

int
_Median3(int A[], int Left, int Right){
    int Center = (Left + Right)/2;
    if (A[Left] > A[Center])
        Swap(&A[Left],&A[Center]);
    if (A[Left] > A[Right])
        Swap(&A[Left],&A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center],&A[Right]);

    Swap(&A[Center],&A[Right - 1]);
    return A[Right - 1];
}

#define Cutoff (3)

void
_Qsort(int A[],int Left, int Right){
    int i;
    int j;
    int Pivot;

    if (Left + Cutoff <=Right){
        Pivot = _Median3(A,Left,Right);
        i = Left;
        j = Right - 1;
        for(;;){
            while (A[++i] < Pivot){}
            while (A[--j] > Pivot){}
            if (i < j)
                Swap(&A[i],&A[j]);
            else
                break;
        }
        Swap(&A[i],&A[Right - 1]);
        _Qsort(A,Left,i-1);
        _Qsort(A,i+1,Right);
    } else
        InsertionSort(A+Left,Right-Left+1);
}

void
Qsort(int A[],int N){
    _Qsort(A,0,N-1);
}

void
_QuickSort(int A[],int Left,int Right){
    int i,j;
    int pivot;
    if (Left < Right){
        i = Left - 1;
        j = Right;
        pivot = A[Right];
        for (;;){
            while(A[++i] < pivot){}
            while(A[--j] > pivot){}
            if(i<j)
                Swap(&A[i],&A[j]);
            else
                break;
        }
        Swap(&A[i],&A[Right]);
            _QuickSort(A,Left,i-1);
            _QuickSort(A,i+1,Right);
    }
}

void
QuickSort(int A[],int N){
    _QuickSort(A,0,N-1);
}


