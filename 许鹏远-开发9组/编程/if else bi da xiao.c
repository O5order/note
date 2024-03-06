#include<stdio.h>
int main(){
    int a, b;
    printf("please enter the two number: ");
    scanf("%d%d", &a, &b);
    if (a > b){
        printf("a > b");
    }else {
        if (a < b){
            printf("a < b");
            }else {
            printf("a = b");
        }
    }
    return 0;
}
