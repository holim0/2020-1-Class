#include <stdio.h>
#include <stdlib.h>
 

void Print(int *a, int n)
{
    int i;
     
    for( i=0 ; i<n ; i++ )
        printf("%d ", a[i]);
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
 
#ifdef SHOWPASS
    printf("\nPASS  : ");
    Print(a, n);
 
#endif
}



int main() {
    int *arr=malloc(sizeof(int)*1000005);
    char *buf=malloc(sizeof(char) * 1000001);
    FILE *fp= fopen("input_200000_0.txt", "r");
    
    int idx=0;
    while (!feof(fp)) {
			fscanf(fp, "%s", buf);
			int num = atoi(buf);
            //printf("%d\n", num);
			arr[idx]=num;
			idx++;
		}

    int arr2[6]={1,2,3,100,4,3};
    int size = 200000;//sizeof(arr) / sizeof(int);

    //Print(&arr[0], size); 
    RadixSort(&arr[0], size);
    Print(&arr[0], size);

    fclose(fp);

    return 0;
}