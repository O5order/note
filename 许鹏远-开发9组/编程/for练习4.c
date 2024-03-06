#include<stdio.h>
int main(){
    int N;
    printf("please enter: ");
    scanf("%d", &N);
    int number, m = 0;
    for(number = 2;number < N;number++){
        if (N % number == 0){
            m++;
        }
    }
    if (m == 0){
        printf("yes");
    }
    if (m != 0){
        printf("no");
    }
    return 0;
}
