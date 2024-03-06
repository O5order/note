#include<stdio.h>
	int main(void)
	{  
	int i, j, total=0, m;
    for(i=1;i<1000;i++)
    {
        total=0;
        for(j=1;j<i;j++){
            if(i%j==0)
                total=total+j;
        }
        if(i==total){
            printf("%d its factors is ", i);  //right
          for(j=1;j<i/2;j++){
              if(i%j==0)
              	printf("%d ", j);
      		}
      		printf("\n");
	  	}
	}
      
       return 0;
}
