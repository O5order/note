#include<stdio.h>
int main(){
	char string[128];
	gets(string);       //输入
	int i,j,t;
	for(i=0;i<128;i++){
		if (string[i]==' ') {
			printf("&nbsp");       //替换
			for(j=i;j<128;j++){
				t=string[j];
				string[j]=string[j+1];
				string[j+1]=string[j];       //原位数组元素推移
				if(string[j]=='\0')
					break;       //检测是否读取结束
			}
		}
		if(string[i]=='\0'){
            break;      //检测是否读取结束
        }
		printf("%c", string[i]);    //打印数组
	}
	return 0;
}
