#include<stdio.h>
int sum(int);

int main(){
    int n;
    printf("please enter the num: ");
    scanf("%d", &n);
    printf("ans is %d", sum(n));
    return 0;
}

int sum(int n){
    if (n == 1){
        return 1;
    }
    return sum(n-1) + n;
    }
