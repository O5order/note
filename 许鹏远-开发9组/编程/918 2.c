#include<stdio.h>
void main()
{   int i, m, k = 0, j;
    for(j=100;j<200;j++)
    {
        for(m=2;m<j;m++)
        {
            if(j % m == 0)
                break;
            else if(m>=j-1)
            {
                printf("%d ", j);
                k++;
            }
        }
    }
    printf("\n%d", k);
}
