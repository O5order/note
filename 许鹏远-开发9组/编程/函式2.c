#include<stdio.h>
int max2(int, int);
int max3(int, int, int);
int main(){
    int i, j, k;
    printf("please enter the num: ");
    scanf("%d%d%d", &i, &j, &k);
    printf("%d", max3(i, j, k));
    return 0;
}
int max2(int i, int j){
    if (i>=j){
        return i;
    }else {
        return j;
    }
}
int max3(int k, int i,int j){
    return max2(max2(i,j), k);
}
