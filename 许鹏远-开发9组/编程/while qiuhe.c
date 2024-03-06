#include<stdio.h>
int main(){
    int num;
    int sum = 0;
    int count = 0;
    float average;
    printf("please enter the number: (0: quit)\n");
    scanf("%d", &num);
    if (num == 0){
        printf("average is N/A");
    }else{
        while (num != 0){
            sum = sum + num;
            count++;
            scanf("%d", &num);
        }
        average = (float) sum / count;
        printf("average is %f\n", average);
    }
    return 0;
}
