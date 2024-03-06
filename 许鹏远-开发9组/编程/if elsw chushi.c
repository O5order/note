#include<stdio.h>
int main(){
    int grade;
    printf("please enter the two numbers: ");
    scanf("%d", &grade);
    if (grade < 60){
        printf("fail");
    }else {
        printf("pass");
    }
    return 0;
}
