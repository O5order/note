#include<stdio.h>
int main(){
    int max;
    printf("enter your max: ");
    scanf("%d", &max);
    int i;
    for(i =1;i <= max;i++){
        if (i%3 ==2 && i%5==3 && i%7==2){
            printf("%d ", i);
        }
    }
    return 0;
}
