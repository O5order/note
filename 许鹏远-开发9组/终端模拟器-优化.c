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
	char exit[5]="exit";   //�����������
	int j=0;
	char do_[3]="do";
	return_function:
	while(1){
		printf("\n(xpy69) > ");
		scanf("%s", &i);
		if(strcmp(i,do_)==0){			//���ñȽϺ����ͼ�ӱ���jȷ��������
			j+=1;
		}else if(strcmp(i,list)==0){
			j+=2;
		}else if(strcmp(i,help)==0){
			j+=3;
		}else if(strcmp(i,exit)==0){
    		j+=4;
		}else {printf("ָ�����");break;}
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
		j=0;    // �ط���������Ϊ0��ʵ��ѭ��
	}
	do_program:
		scanf("%s", &i);  //����ʵ���ĸ���Ŀ
		int number;
		number=i[strlen(i)-1]-48;   //����ASCII�뽫���һ�����ֻش����Ӷ�ʵ��switch���
	switch(number){
		case 1:program1();break;
		case 2:program2();break;
		case 3:program3();break;
		case 4:program4();break;
	}
	j=0;      // �ط���������Ϊ0��ʵ��ѭ��
	goto return_function;      //�ط�ѭ��
	exit:
	return 0;
}

//������1 �žų˷���
void program1(){
	int i,j;
	for(i=1;i<=9;i++){
		for(j=i;j<=9;j++){
			printf("%d*%d=%2d  ", i, j, i*j);
		}
		printf("\n");
	}
}
//������2�����ж�
void program2(){
	int year;
	scanf("%d", &year);
	if(year%4==0)
		printf("%d������", year);
	else printf("%d��������", year);
}
//������3 ����
int program3() {
	printf("enter your number");
	int num[128];
	int i, t, j;
	int new_add=0;
	for(i=0;i<10;i++)
	scanf("%d", &num[i]);     //����
    circle:
	for(i=0;i<10+new_add;i++){
		for(j=1;j<10-i+new_add;j++){				//ð������
			if(num[j]%2==1 && num[j-1]%2==0){			//ʵ��������ǰ
				t=num[j];
				num[j]=num[j-1];
				num[j-1]=t;
			}
			if(num[j]<num[j-1] && num[j]%2==1 && num[j-1]%2==1){			//������С����
				t=num[j];
				num[j]=num[j-1];
				num[j-1]=t;
			}
			if(num[j]<num[j-1] && num[j]%2==0 && num[j-1]%2==0){			//ż����С����
				t=num[j];
				num[j]=num[j-1];
				num[j-1]=t;
			}
		}
	}
	for(i=0;i<10+new_add;i++)			//������
	printf("%d ", num[i]);
	printf("\nnow you are adding nums,enter 0 to break: ");
	for(i=10;i<128;i++){       //�������
        if(scanf("%d", &num[i])==0)
            return 0;
        new_add++;       //���ø�������ʵ��α��̬����
        if(num[i]==0){
            new_add--;
            break;
        }
    }
    goto circle;      //ѭ��
}
//������4  �����ϰ�
struct huowu      //�ṹ���������
{	char food[20];
	float once_money;
	int number;
}all[64]={{"ţ��",3,0},{"���",2,0},{"������",5,0},{"��Ȫˮ",1,0},{"���ȳ�",1.5,0},{"����÷",5,0},{"������",10,0},{"������",1,0},{"����",0.5,0},{"ֽ��",1,0}};
void program4(){
	int i,num;
	float total_money=0;
	char buy[40];
	printf("please enter what you want to buy and the amount(enter over to break)\nif you want to add huowo,please enter root\n");
	circle:     //ѭ����ʼ
	while(1){
		scanf("%s", &buy);
		if(strcmp(buy,"root")==0)
			goto root;  //����Աֱ�ӻص�root״̬
		if(strcmp(buy,"over")!=0){
			scanf("%d", &num);    //����
		}
		for(i=0;i<64;i++){
			if(strcmp(buy,all[i].food)==0){
				if(all[i].number==0){
				all[i].number=num;			//������Ʒ����
				printf("���ۣ�%.2f\n", all[i].once_money);
			}else all[i].number+=num;
				total_money=all[i].once_money*num+total_money;   //�����ܼ�
			}
		}
		if(strcmp(buy,"over")==0){
			break;             //����ѭ��
		}
	}
	root:    								//����Աģʽ��ӻ���
	if(strcmp(buy,"root")==0){
		printf("enter over to break\n");
		int j=0;    //������������ȷ��������Ļ���
		for(i=10+j;i<64;i++){
			printf("please enter the name: ");
			scanf("%s", &all[i].food);
			if(strcmp(all[i].food,"over")==0)
				break;
			printf("please enter the money: ");
			scanf("%f", &all[i].once_money);
			j++;
		}
		goto circle;   //�ص�ѭ��
	}
	printf("��Ʒ�� ���� ����\n");
	for(i=0;i<64;i++){
		if(all[i].number!=0)
		printf("%s   %.1f %d\n", all[i].food, all[i].once_money, all[i].number);//�������СƱ
	}
	printf("�ܼ�   %.1f",total_money);
}
