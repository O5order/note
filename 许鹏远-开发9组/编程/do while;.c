#include<stdio.h>
int main(){
    int guess, answer = 4;
    do {
        printf("please enter the guess");
        scanf("%d", &guess);
        if(guess > answer){
            printf ("too large\n");
        }else if (guess < answer){
            printf ("too small\n");
        }else {
            printf ("correct\n");
        }
    }while (guess != answer);
    return 0;
}
