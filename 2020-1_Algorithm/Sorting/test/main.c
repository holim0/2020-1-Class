#include "ds.h"
#include <string.h>

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

int main(int argc, char *argv[])
{
	printf("Algorithm - Homework # 2 - <Student ID>\n");	
	
	char *filename, *buf;
	int n, m;
	
	for (n=200; x<1001; x+=200)
		for (m=0; y<10; y++)
		{
			//read the file input_x_y.txt into a buffer
			read_input(filename, buf);
			//convert the buffer to data structure
			//get the current time (time.h)
			//sort the data with sorting functions
			//get the current time (time.h)
		}     
	return 0;
}

void read_input(char *filename, char *buf)
{
	FILE *ptr_file;
	ptr_file = fopen(filename, buf);
	if (ptr_file==NULL)
	{
		printf("File is not exist.\n");
		exit(1);
	}
         
} 

void convert_PARRAY(char *buf, PARRAY parray)
{
       
}  

void convert_STACK(char *buf, STACK stack)
{
       
} 

void convert_QUEUE(char *buf, QUEUE queue)
{
       
} 

void convert_HEAP(char *buf, HEAP heap)
{
       
} 