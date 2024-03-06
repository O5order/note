/*Èí¼ş2310°àĞíÅôÔ¶-2023005269*/ 
#include<stdio.h>
int main(){
	float r, h, c, s, s1, s2, v;
	scanf("%f %f", &r, &h);
	c=3.141*r*2;
	s=r*r*3.141;
	s1=c*h;
	s2=s+s1;
	v=1/3.0*s*h;
	printf("c=%f,s=%f7,s1=%f,s2=%f,v=%f", c, s, s1, s2, v);
	return 0;
}
