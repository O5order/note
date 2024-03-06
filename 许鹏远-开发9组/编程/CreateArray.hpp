#include<stdlib.h>
#include<stdio.h>
int* CreateArray(int size){
	int *p=(int* )malloc(sizeof(int)*size);
	if(p==NULL){
        printf("malloc failed");
	}
	return p;
}



