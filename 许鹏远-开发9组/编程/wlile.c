#include<stdio.h>
int main(){
    int guess;
    int answer = 4;
    int count = 1;
    printf("please enter the guess: ");
    scanf("%d", &guess);
    while(guess != answer) {
         if(guess <= answer){
            printf("too small\n");
        }else{
            printf("too large\n");
        }
            printf("please enter the guess: \n");
            scanf("%d", &guess);
            count++;
    }
    printf("correct (%d)", count);
    return 0;
}
