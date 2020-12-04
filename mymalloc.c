#include<stdio.h>
#include "mymalloc.h"

Block *locate=(void*)myMemory;

void *MyMalloc(size_t NoOfsize){
	Block *ptr,*preptr,*result;
	if(locate->next==NULL){     //first start of memory
	    printf("\n\n\n            Memory Operation!\n\n\n");
		locate->size=SIZE-sizeof(Block);
		locate->flag='F';
		locate->next=NULL;
		locate->prev=NULL;
		printf("\n  Initialize of the memory!\n\n\n");
	}
	ptr=locate;
	//traverse through the memory array to find the relavent memory Block
	while(((ptr->flag=='A')||(ptr->size<=NoOfsize))&&(ptr->next!=NULL)){
		preptr=ptr;
		ptr=ptr->next;
		ptr->prev=preptr;
	}
	if(ptr->size==NoOfsize){     //find exactly same size memory Block
		ptr->flag='A';
		
		printf("\n Allocated memory block size  |   %d  |\n",ptr->size);
		result= (void*)(++ptr);
		return result;
	}
	else if(ptr->size >(NoOfsize+sizeof(Block))){   // split the current memory Block
		Block *temp=(void*)((void*)ptr+NoOfsize+sizeof(Block));
		temp->flag='F';
		temp->next=ptr->next;
		temp->prev=ptr;
		temp->size=ptr->size-(NoOfsize+sizeof(Block));
		ptr->flag='A';
		ptr->size=NoOfsize;
		ptr->next=temp;
		
		printf(" Allocated memory block size  |   %d  |  %c  |\n\n",ptr->size,ptr->flag);
		result= (void*)(++ptr);
		return result;
	}
	else{    //can't find  suitable memory Block
		printf("\n  Not Allocated!\n");
		return 0;
	}
}

void MyFree(void *newptr){
	Block *ptr=newptr-sizeof(Block);
	if((void*)locate<=newptr && newptr<=(void*)(locate+SIZE)){ //check the given pointer is in the range or not
		ptr->flag='F';
		printf(" \n\nFree memory blocked size |   %d   |   %c  |\n",ptr->size,ptr->flag);
		printf("The Block size is: %d\n",sizeof(Block));
		ptr=locate;
		while(/*ptr &&*/ ptr->next!=NULL)    //merge the consecative two free memory Block
		{
			if(ptr->flag=='F' && ptr->next->flag=='F')      // ex:- A | F | F
			{
				ptr->size=ptr->size+ptr->next->size+sizeof(Block);
				ptr->next=ptr->next->next;
				printf("\n  Merge succesfully!");
			}                                                         
			ptr=ptr->next;
				
		}
			
		}
		else{
		printf("\n  Suitable pointer not found!\n");
		
	}
}
	
void PrintMemory(){
	Block *ptr=locate;
	printf("\n\n\n       Current Memory  \n\n");
	printf("\n\n |   Flag    |    Size of Block  |\n\n");
	while(ptr!=NULL){
		printf(" |   %c      |     %d            \n",ptr->flag,ptr->size);
		ptr=ptr->next;
	}
	
}


