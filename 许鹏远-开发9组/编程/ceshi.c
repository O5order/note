#include<stdio.h>
int main(void)
{
    FILE *p;
    p = fopen("open.txt", "r");
    getc(p);
    if (feof(p))
    {
        printf("�ļ�Ϊ�ա�");
    }
    else
    {
        rewind(p);//��������ص��ļ���ͷ
        int a=10;
        fscanf(p,"%d",&a);
        printf("%d", a);
    }
    return 0;
 }
