/*Èí¼ş2310°àĞíÅôÔ¶-2023005269*/ 
#include<stdio.h>
#include<math.h>
int main(){
	double PI=0;
	int i, j=2;
	for(i=1;i<2000;i+=2){
		PI+=pow(-1,j)*(1.0/i);
		j++;
		if(fabs(1.0/i)<pow(10,-6)){
			break;
		}
	}PI*=4;
	printf("%lf", PI);
	return 0;
}
