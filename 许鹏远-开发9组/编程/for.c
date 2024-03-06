#include<stdio.h>
int main(){
    int m, n;
    printf("please enter the M: \n");
    scanf("%d", &m);
    printf("please enter the N: \n");
    scanf("%d", &n);
    int count;
    for (count = m; count<= n; count++) {
        printf("%d", count);
    }
    return 0;
}
