#include <stdio.h>

int main(int argc, char *argv[])
{
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char initial = '65';
    int bajinzhi = 65;
    int shijinzhi = 65;

    printf("You are %d miles away.\n", distance);
    printf("float %f .\n", power);
    printf("double %lf.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("ba %o.\n", bajinzhi);
    printf("shi %x.\n", shijinzhi);
    printf("    ");
    return 0;     /*printf打印空字符时，不会有任何输出。空字符是指ASCII码为0的字符，也称为'\0'。在C语言中，字符串以空字符作为结尾标志，因此在使用printf打印字符串时，空字符不会被打印出来。如果想要打印空字符，*/
}
