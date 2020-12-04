#include<stdio.h>
#include<stddef.h>
#define MYMALLOC

#define SIZE 25000

char myMemory[SIZE];

typedef struct descriptionBlock{
	size_t size;       //size of Block 
	char flag;         // 'F'=free Block  'A'=allocate Block
	struct descriptionBlock *next;
	struct descriptionBlock *prev;
}Block;

void *MyMalloc(size_t NoOfsize);
void MyFree(void *newptr );
void PrintMemory();





