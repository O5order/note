#include<stdlib.h>
#include<stdio.h>
void AddNumber(int *array,int number){
    array=(int* )realloc(array, sizeof(int)*number);
	if (array==NULL)
		printf("Warning:array adding failed");
}
