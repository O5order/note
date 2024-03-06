#include<stdio.h>
int main(){
    int a, b, c, mid;
    printf("please enter the three integer: ");
    scanf("%d%d%d", &a, &b, &c);
    mid = a;
    if (b > a && b < c || b > a && b < c){
        mid = b;
    }
    if (c > a && c < b || c > b && c < a){
        mid = c;
    }
    printf("midum is %d", mid);
    return 0;
}
