#include "ds.h"
#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

# ifdef sun
# define const
# endif

extern const char *
okfail(int val)
{
	return val ? "[ OK ]" : "[FAIL]";
}

//prototype
void read_input(char *, char *);
void convert_PARRAY(char *, PARRAY);
void convert_STACK(char *, STACK);
void convert_QUEUE(char *, QUEUE);
void convert_HEAP(char *, HEAP);


//sorting function 


HEAP Heap_h(HEAP);
int qdata[1000005];
int arr[1000005]; int arr2[1000005];
int rdata[1000005];
int hdata[1000005];
int idx = 0;

void RadixSort(int *a, int n);
void swap(int *a, int *b);
void heapify(int arr[], int here, int size);
void buildHeap(int arr[], int size);
void heapSort(int arr[],int size);
void merge(int left, int right);
void partition(int left,int right);
void quick_sort(int *data, int start, int end);


int main(int argc, char *argv[])
{
	printf("Algorithm - Homework # 3 - <2015310578>\n");

	char *filename, *buf, *filename2;
	int n, m;
	char a[50] = "input_";
	char b[10] = "_";
	char c[10] = ".txt";
	char c2[10]=".out";
	char k[30] = "";
	char k2[30]="";

	char val[10]; char val2[10];

	for (n = 200000; n < 1000001; n += 200000) {
		for (m = 0; m < 10; m++)
		{
			k[0] = '\0'; k2[0]='\0'; val[0] = '\0'; val2[0] = '\0';
			sprintf(val, "%d", n);
			strcat(k, a); strcat(k, val); strcat(k, b); strcat(k2, a); strcat(k2, val); strcat(k2, b);
			sprintf(val2, "%d", m); strcat(k, val2); strcat(k2, val2); strcat(k, c); strcat(k2, c2);
			filename = k; filename2=k2;
			read_input(filename, buf);
			clock_t start, end;
			
			FILE * writef= fopen(filename2, "w");
			

			start=clock();
			quick_sort(qdata, 0, n);
			end=clock();
			double result=(double)(end-start)/CLOCKS_PER_SEC;
			printf("%.3f\n", result);
			RadixSort(rdata, n);
			partition(0, n);
			heapSort(hdata, n);
			
			for (int i = 0; i < n; i++)
			{
				fprintf(writef, "%d\n", qdata[i]);
			}
		}
		
		
		
	}
	return 0;
}


void RadixSort(int *a, int n)
{
    int *b=malloc(sizeof(int)*1000005);
    int i, m=0, exp=1;
 
    for( i=0 ; i<n ; i++ )
    {
        if( a[i] > m )
            m = a[i];
    }
 
    while( m/exp > 0 )
    {
        int bucket[10] = {0};
         
        for( i=0 ; i<n ; i++ )
            bucket[a[i]/exp%10]++;
 
        for( i=1 ; i<10 ; i++ )
            bucket[i] += bucket[i-1];
 
        for( i=n-1 ; i>=0 ; i-- )
            b[--bucket[a[i]/exp%10]] = a[i];
 
        for( i=0 ; i<n ; i++ )
            a[i] = b[i];
 
        exp *= 10;
	}	
}



void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int arr[], int here, int size) {
    int left = here * 2 + 1;
    int right = here * 2 + 2;
    int max=here;
    if (left < size&&arr[left]>arr[max])
        max = left;
    if (right < size&&arr[right]>arr[max])
        max = right;
 
    if (max != here) {
        swap(&arr[here], &arr[max]);
        heapify(arr, max, size);
    }
}
 
void buildHeap(int arr[], int size) {
    int i,j;
    for (i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, i, size);
    }
}
 
void heapSort(int arr[],int size) {
    int treeSize;
    buildHeap(arr, size);
    for (treeSize = size - 1; treeSize >= 0; treeSize--) {
        swap(&arr[0], &arr[treeSize]);
        heapify(arr, 0,treeSize);
    }
}




void merge(int left, int right)
{
	int mid = (left + right) / 2;

	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j]) 
			arr2[k++] = arr[i++]; 
		else
			arr2[k++] = arr[j++];
	}

	int tmp = i>mid ? j : i;
	
	while(k<=right) arr2[k++] = arr[tmp++];

	for (int i=left;i<=right;i++) arr[i] = arr2[i];
}

void partition(int left,int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2; 
		partition(left, mid);
		partition(mid + 1, right);
		merge(left, right);
	}
}

void quick_sort(int *data, int start, int end){ 
	if(start >= end){ 
		return; 
	} 
	int pivot = start; int i = pivot + 1; 
	int j = end; 
	int temp; 
	while(i <= j){ 
		
		while(i <= end && data[i] <= data[pivot]){ 
			i++; 
		} 
		while(j > start && data[j] >= data[pivot]){ 
			j--; 
		} 
		
		if(i > j){  
			temp = data[j]; 
			data[j] = data[pivot]; 
			data[pivot] = temp; 
		}else{  
			temp = data[i]; 
			data[i] = data[j]; 
			data[j] = temp; } 
			
	}  
	quick_sort(data, start, j - 1); 
	quick_sort(data, j + 1, end);


}

void read_input(char *filename, char *buf)
{
	FILE *ptr_file;
	ptr_file = fopen(filename, "r");
	if (ptr_file == NULL)
	{
		printf("File is not exist.\n");
		exit(1);
	}
	else {
		buf = malloc(sizeof(char) * 1000001);
		idx=0;
		while (!feof(ptr_file)) {
			fscanf(ptr_file, "%s", buf);
			int num = atoi(buf);
			qdata[idx] = num;  arr[idx]=num; rdata[idx]=num; hdata[idx]=num;
			idx++;
		}
		
		return;
	}
}

// void convert_PARRAY(char *buf, PARRAY parray)
// {

// }

// void convert_STACK(char *buf, STACK stack)
// {

// }

// void convert_QUEUE(char *buf, QUEUE queue)
// {

// }

// void convert_HEAP(char *buf, HEAP heap)
// {

// }

