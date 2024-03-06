#include<stdio.h>
int main(){
    int num1, num2;
    char op;
    double answer;
    scanf("%d%c%d", &num1, &op, &num2);
    if (op == '+'){
        answer = num1 + num2;
    }else if (op == '*'){
        answer = num1 * num2;
    }else if (op == '-'){
        answer = num1 - num2;
    }else {
        answer = (double) num1 / num2;
    }
    printf("ans is %f", answer);
    return 0;
}
