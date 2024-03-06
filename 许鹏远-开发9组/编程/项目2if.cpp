/*Èí¼ş2310°àĞíÅôÔ¶-2023005269*/ 
#include<stdio.h>
int main(){
	int number;
	scanf("%d", &number);
	if(number>=90 && number<=100)
		printf("A");
		else if(number<90 && number >= 80)
			printf("B");
			else if(number<80 && number >= 70)
				printf("C");
				else if(number<70 && number >= 60)
						printf("D");
					else if(number<60)
							printf("E");
							else
								printf("Error");
	return 0;
}

