#include<stdio.h>
int main(void)
{
    int i=0, x=0, count=0;
    for(i=2;i<100;i++){
        for(x=2;x<=i;x++){
            if (i%x==0)
            break;
        }
        if(x==i){
            printf("%d ", i);
            count++;
        }
    }
    printf("\n%d", count);
}
