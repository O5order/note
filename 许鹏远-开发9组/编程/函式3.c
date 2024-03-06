#include<stdio.h>
void max(int);
int main(){
    max(1);
    return 0;
}
void max(int i){
    if (i<=9){
        max(i+1);
        printf("%d\n", i);
    }
}
