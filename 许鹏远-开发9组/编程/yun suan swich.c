#include<stdio.h>
int main(){
    int num1, num2;
    char op;
    double answer;
    scanf("%d%c%d", &num1, &op, &num2);
    switch (op) {
        case '+':
            answer = num1 + num2;
            break;
        case '/':
            answer = num1 / num2;
            break;
        case '-':
            answer = num1 - num2;
            break;
        case '*':
            answer = num1 * num2;
            break;
            }
    printf("ans is %f", answer);
    return 0;
}
