#include<stdio.h>
int main(){
    int num1, num2, num3, t;
    printf("Please enter the longth: ");
    scanf("%d%d%d", &num1, &num2, &num3);
    if (num1 > num2){t = num1; num1 = num2; num2 = t;}
    if (num1 > num3){t = num2; num1 = num3; num3 = t;}
    if (num2 > num3){t = num3; num2 = num3; num3 = t;}
    if (num1 == num3)
        printf("recular trinagle\n");
    if (num1 == num2 || num2 == num3)
        printf("isosceles trinagle\n");
    if (num1 * num1 + num2 * num2 == num3 * num3)
        printf("rectangular tringle\n");
    return 0;
}
