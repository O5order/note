#include<stdio.h>
	int main(void)
	{
	  /*********Begin*********/
	 char c;
      int j=0, k=0, l=0, o=0 ;
      while((c=getchar())!='\n'){
          if((c>='a' && c<='z') || (c>='A' && c<='Z'))
          j++;
          else if(c>='0' && c<='9')
          k++;
          else if(c==' ')
          o++;
          else l++;
      }
      printf("%d %d %d %d", j , k ,o , l);
	  /*********End**********/
       return 0;
	}
