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
    return 0;     /*printf��ӡ���ַ�ʱ���������κ���������ַ���ָASCII��Ϊ0���ַ���Ҳ��Ϊ'\0'����C�����У��ַ����Կ��ַ���Ϊ��β��־�������ʹ��printf��ӡ�ַ���ʱ�����ַ����ᱻ��ӡ�����������Ҫ��ӡ���ַ���*/
}
