#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    srand(time (0));
    int car_hour=rand()%3+9;
    int car_minture=rand()%60;
    printf("������ʼ����%d.%d\n", car_hour, car_minture);
    printf("����ʱ���Ϊ9.00-12.00���벻Ҫ���Ŷ\n������С����ʼ��ʱ����վ̨\n");//����ʱ�� 
    printf("�û����룺");
    int human_hour, human_minture;
    int zhantai;      //������վ̨��ʱ�� 
    scanf("%d.%d %d", &human_hour ,&human_minture, &zhantai);
    int x=0;           //��Ŀǰ����վ̨ 
    int answer;
    if(60*car_hour+car_minture>60*human_hour+human_minture){          //���ȵ��ٷ��� 
    	answer=zhantai*20+60*car_hour+car_minture-60*human_hour-human_minture;
	}
	if(60*car_hour+car_minture<60*human_hour+human_minture){       //�ȷ������ٵ�
		while(1){
       		car_minture+=20;
       		x++;
        	if(x==3){
           		x=0;
           		car_minture+=10;                  /*ÿ������վ��תһȦ����10����*/ 
        	}                                    
        	if(car_minture>=60){
            	car_minture-=60;
            	car_hour++;            //ÿ60���ӽ�һСʱ 
        	}
        	if(60*car_hour+car_minture>60*human_hour+human_minture){          
            	break;
        	}
    	}         
		if(x<zhantai){
    	    answer=(zhantai-x)*20+car_minture-human_minture;    //�����˺���������һվ 
    	}
    	if(x==zhantai){
        	answer=car_minture-human_minture;       //����վ����վ�����
   	 	}
    	if(x>zhantai){
        	answer=50+car_minture-human_minture;     //���մ����ڵ�վ�뿪 
    	}
	}
    printf("�ȴ�ʱ����%d", answer);
    return 0;
}

