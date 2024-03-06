#include<stdio.h>
int main(){
    int min, max;
    printf("please enter the min: ");
    scanf("%d", &min);
    printf("please enter the max: ");
    scanf("%d", &max);
    int number,count = 0;
    for(number = min;number <= max; number++){
        if(number % 3 == 2 && number % 5 == 3 && number % 7 == 2){
            count++;
            if (count <= 3){
                printf("%d ", number);
            }
        }
    }
    return 0;
}
