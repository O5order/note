#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    int i, j, counter[6] = {0};
    srand(time(0));
    for (i=1;i<=6000;i++){
        int dice = rand() % 6;
        counter[dice]++;
    }
    for(j=1;j<=6;j++){
        printf("%d: %d\n", j, counter[j-1]);
    }
    return 0;
}
