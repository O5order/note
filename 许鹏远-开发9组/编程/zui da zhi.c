#include<stdio.h>
int main(){
    int a, b ,c, max;
    printf("please enter the three number: ");
    scanf("%d%d%d", &a, &b, &c);
    max = a;
    if (c >= a && c >= b){
        max = c;
    }else if (b >= a && b >= c)
    max = b;
    printf("the maximum is %d", max);
    return 0;
}
