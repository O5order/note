#include <stdio.h>
int main() {
    int number1;
    int number2;
    int number3;
    int sum;
    printf("Please enter the first number: ");
    scanf("%d", &number1);
    printf("Please enter the second number: ");
    scanf("%d", &number2);
    printf("Please enter the three number: ");
    scanf("%d", &number3);
    sum = number1 + number2 + number3;
    printf("Sum is %d.\n", sum);
    return 0;
}
