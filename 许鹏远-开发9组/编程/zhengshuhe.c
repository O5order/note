#include<stdio.h>
int main(){
    int n, m, total;
    printf("please enter your number: \n");
    scanf("%d%d", &n, &m);
    for (total = n;n <=m;n++){
        total = n + total;
    }
    printf("total is %d", total);
    return 0;
}
