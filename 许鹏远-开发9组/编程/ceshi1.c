#include<stdio.h>
int main(){
	char string[128];
	gets(string);       //����
	int i,j,t;
	for(i=0;i<128;i++){
		if (string[i]==' ') {
			printf("&nbsp");       //�滻
			for(j=i;j<128;j++){
				t=string[j];
				string[j]=string[j+1];
				string[j+1]=string[j];       //ԭλ����Ԫ������
				if(string[j]=='\0')
					break;       //����Ƿ��ȡ����
			}
		}
		if(string[i]=='\0'){
            break;      //����Ƿ��ȡ����
        }
		printf("%c", string[i]);    //��ӡ����
	}
	return 0;
}
