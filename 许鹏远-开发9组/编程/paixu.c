#include<stdio.h>
int main(){
    int a, b, c, t;
    printf("please enter the three number: ");
    scanf("%d%d%d", &a, &b, &c);
    if(a >= b && b >= c){
        t = a; a = c; c = t;
    }
    if(a >= c && c >= b){
        t = a; a = b; b = c; c = t;
    }
    if(b >= c && c >= a){
        t = c; c = b; b = t;
    }
    if(b >= a && a >= c){
        t = a; a = c; c = b; b = t;}
    if(c >= a && a >= b){
        t = a; a = b; b = t;}
    printf("%d,%d,%d", a, b, c);
    return 0;
}
