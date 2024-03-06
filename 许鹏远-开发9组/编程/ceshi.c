#include<stdio.h>
int main(void)
{
    FILE *p;
    p = fopen("open.txt", "r");
    getc(p);
    if (feof(p))
    {
        printf("文件为空。");
    }
    else
    {
        rewind(p);//将光标跳回到文件开头
        int a=10;
        fscanf(p,"%d",&a);
        printf("%d", a);
    }
    return 0;
 }
