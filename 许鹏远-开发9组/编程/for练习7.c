#include<stdio.h>
int main(){
    int n;
    printf("please enter: ");
    scanf("%d", &n);
    int i,j;
    printf("*\n");
    for (i = 0; i<= n - 3; i++){
        printf("*");
        for(j = 1;j <= i; j++){
            printf(" ");
        }
        printf("*\n");
    }
    printf("*****\n");
    return 0;
}
£¨¿ÉÄÜÓÐÎó£©
