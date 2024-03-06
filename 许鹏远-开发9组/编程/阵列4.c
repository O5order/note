#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    int prices[5]={34, 64, 98, 65, 26};
    int i, total;
    do{
        printf("num: ", i);
        scanf("%d", &i);
        total += prices[i-1];
        }while(i != 0);
    printf("total is %d", total);
    return 0;
}
