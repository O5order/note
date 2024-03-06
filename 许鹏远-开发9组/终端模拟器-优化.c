#include<stdio.h>
#include<string.h>
void program2();
void program1();
int program3();
void program4();
int main(){
	char i[20];
	char list[5]="list";
	char help[5]="help";
	char exit[5]="exit";   //基础命令参数
	int j=0;
	char do_[3]="do";
	return_function:
	while(1){
		printf("\n(xpy69) > ");
		scanf("%s", &i);
		if(strcmp(i,do_)==0){			//利用比较函数和间接变量j确定输入结果
			j+=1;
		}else if(strcmp(i,list)==0){
			j+=2;
		}else if(strcmp(i,help)==0){
			j+=3;
		}else if(strcmp(i,exit)==0){
    		j+=4;
		}else {printf("指令错误");break;}
		switch (j){
			case 1:
				printf("(do the program what you enter)\n");
				goto do_program;
			case 2:
				printf("(all program you can do)");
				printf("\n do\n list\n help\n exit");
				break;
			case 3:
				printf("(search how to go on the order)");
				printf("\n do:(do the program what you enter)\n list:(all program you can do)\n exit:(exit the terminal)\n help:(search how to go on the order)");
				break;
			case 4:
				printf("(exit the terminal)");goto exit;
		}
		j=0;    // 重返辅助变量为0，实现循环
	}
	do_program:
		scanf("%s", &i);  //具体实现哪个项目
		int number;
		number=i[strlen(i)-1]-48;   //利用ASCII码将最后一个数字回传，从而实现switch语句
	switch(number){
		case 1:program1();break;
		case 2:program2();break;
		case 3:program3();break;
		case 4:program4();break;
	}
	j=0;      // 重返辅助变量为0，实现循环
	goto return_function;      //重返循环
	exit:
	return 0;
}

//副函数1 九九乘法表
void program1(){
	int i,j;
	for(i=1;i<=9;i++){
		for(j=i;j<=9;j++){
			printf("%d*%d=%2d  ", i, j, i*j);
		}
		printf("\n");
	}
}
//副函数2闰年判断
void program2(){
	int year;
	scanf("%d", &year);
	if(year%4==0)
		printf("%d是闰年", year);
	else printf("%d不是闰年", year);
}
//副函数3 排序
int program3() {
	printf("enter your number");
	int num[128];
	int i, t, j;
	int new_add=0;
	for(i=0;i<10;i++)
	scanf("%d", &num[i]);     //输入
    circle:
	for(i=0;i<10+new_add;i++){
		for(j=1;j<10-i+new_add;j++){				//冒泡排序
			if(num[j]%2==1 && num[j-1]%2==0){			//实现奇数在前
				t=num[j];
				num[j]=num[j-1];
				num[j-1]=t;
			}
			if(num[j]<num[j-1] && num[j]%2==1 && num[j-1]%2==1){			//奇数大小排序
				t=num[j];
				num[j]=num[j-1];
				num[j-1]=t;
			}
			if(num[j]<num[j-1] && num[j]%2==0 && num[j-1]%2==0){			//偶数大小排序
				t=num[j];
				num[j]=num[j-1];
				num[j-1]=t;
			}
		}
	}
	for(i=0;i<10+new_add;i++)			//结果输出
	printf("%d ", num[i]);
	printf("\nnow you are adding nums,enter 0 to break: ");
	for(i=10;i<128;i++){       //持续输出
        if(scanf("%d", &num[i])==0)
            return 0;
        new_add++;       //利用辅助变量实现伪动态数组
        if(num[i]==0){
            new_add--;
            break;
        }
    }
    goto circle;      //循环
}
//副函数4  超市老板
struct huowu      //结构体基础货物
{	char food[20];
	float once_money;
	int number;
}all[64]={{"牛奶",3,0},{"面包",2,0},{"方便面",5,0},{"矿泉水",1,0},{"火腿肠",1.5,0},{"溜溜梅",5,0},{"薄荷糖",10,0},{"豆腐干",1,0},{"辣条",0.5,0},{"纸巾",1,0}};
void program4(){
	int i,num;
	float total_money=0;
	char buy[40];
	printf("please enter what you want to buy and the amount(enter over to break)\nif you want to add huowo,please enter root\n");
	circle:     //循环开始
	while(1){
		scanf("%s", &buy);
		if(strcmp(buy,"root")==0)
			goto root;  //管理员直接回到root状态
		if(strcmp(buy,"over")!=0){
			scanf("%d", &num);    //输入
		}
		for(i=0;i<64;i++){
			if(strcmp(buy,all[i].food)==0){
				if(all[i].number==0){
				all[i].number=num;			//计算商品数量
				printf("单价：%.2f\n", all[i].once_money);
			}else all[i].number+=num;
				total_money=all[i].once_money*num+total_money;   //计算总价
			}
		}
		if(strcmp(buy,"over")==0){
			break;             //跳出循环
		}
	}
	root:    								//管理员模式添加货物
	if(strcmp(buy,"root")==0){
		printf("enter over to break\n");
		int j=0;    //借助辅助变量确定多输入的货物
		for(i=10+j;i<64;i++){
			printf("please enter the name: ");
			scanf("%s", &all[i].food);
			if(strcmp(all[i].food,"over")==0)
				break;
			printf("please enter the money: ");
			scanf("%f", &all[i].once_money);
			j++;
		}
		goto circle;   //回到循环
	}
	printf("商品名 单价 数量\n");
	for(i=0;i<64;i++){
		if(all[i].number!=0)
		printf("%s   %.1f %d\n", all[i].food, all[i].once_money, all[i].number);//最终输出小票
	}
	printf("总价   %.1f",total_money);
}
