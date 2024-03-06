#include<stdio.h>
int main(){
	printf("(xpy69) > ");
	char i[20];
	while(1){
	scanf("%s", &i);
	if(i==doprogram || i==runprogram){
		printf("程序正在执行。。。\n");
		printf("程序执行结束。");
	}else if(i==exit){
		break;
	}
	else printf("指令错误！");
	}
	return 0;
}
