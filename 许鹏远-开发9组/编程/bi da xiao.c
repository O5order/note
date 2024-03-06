#include<stdio.h>
int main(){
    int a, b, c, d, min;
    printf("Please enter the four number: ");
    scanf("%d%d%d%d", &a, &b, &c, &d);
    min = a;
    if (b < min){
        min = b;
    }
    if (c < min){
        min = c;
    }
    if (d < min){
        min = d;
    }
    printf("mainmum is %d", min);
    return 0;
}
