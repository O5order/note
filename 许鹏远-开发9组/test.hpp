#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int test(){
	srand(time(0));
	char code[16];
	char real_code[16];
	int i;              // a lot of things that need to depend
	int k=0,o, ans, answer;
	char j;
	for(i=0; i<10; i++){
        	int num=rand()%95+32;      //验证码生成
       		j=num;
        	code[i]= j;
        	code[i+1]= '\0';
	}                       //验证码
	printf("%s\n", code);
	for(i=0;i<10;i++){
		if((code[i]>='0' && code[i]<='9') || (code[i]>='a' && code[i]<='z') || (code[i]>='A' && code[i]<= 'Z')){
           		 real_code[k]=code[i];
           		 real_code[k+1]='\0';
           		 k=k+1;
        	}
	}                           //应该输入的验证码
	char enter_code[11];
	i=0;
	while(1){
		scanf(" %s", enter_code);            //输入
		getchar();
		if (strcmp(enter_code,real_code)!=0){
			i=i+1;
			printf("Verify failed\n");
	     		if(i==3){                       //三次失败退出
		  		printf("register fail\n");
				return 1;
			}
		}else{
			printf("first Verify success\n");        //improve the verify
			printf("Second: what`s the answer: ");
			k=rand()%30+32;
			o=rand()%40+38;
			ans=k+o;
			i=0;
			while(1){
			i=i+1;
			printf("%d+%d=", k, o);
			scanf("%d", &answer);
			getchar();
			if(answer==ans){
				printf("Verify success\n");
				return 0;
			}else printf("Verify fail");     //wei wan
			if(i==3){return 1;}
			}
	     	}
	}
}
