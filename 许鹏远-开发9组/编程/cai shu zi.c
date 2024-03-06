#include<stdio.h>
int main(){
    int answer = 6;
    int guess;
    printf("please enter your guess: ");
    scanf("%d", &guess);
    if (guess > answer){
        printf("too large!");
    }else if (guess < answer){
        printf("too small!");
    }else printf("correct!");
    return 0;
}
