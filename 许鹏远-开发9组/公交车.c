#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    srand(time (0));
    int car_hour=rand()%3+9;
    int car_minture=rand()%60;
    printf("公交车始发于%d.%d\n", car_hour, car_minture);
    printf("发车时间段为9.00-12.00，请不要输错哦\n请输入小明开始的时刻与站台\n");//发车时间 
    printf("用户输入：");
    int human_hour, human_minture;
    int zhantai;      //人所在站台及时间 
    scanf("%d.%d %d", &human_hour ,&human_minture, &zhantai);
    int x=0;           //车目前所在站台 
    int answer;
    if(60*car_hour+car_minture>60*human_hour+human_minture){          //人先到再发车 
    	answer=zhantai*20+60*car_hour+car_minture-60*human_hour-human_minture;
	}
	if(60*car_hour+car_minture<60*human_hour+human_minture){       //先发车人再到
		while(1){
       		car_minture+=20;
       		x++;
        	if(x==3){
           		x=0;
           		car_minture+=10;                  /*每走三个站就转一圈，等10分钟*/ 
        	}                                    
        	if(car_minture>=60){
            	car_minture-=60;
            	car_hour++;            //每60分钟进一小时 
        	}
        	if(60*car_hour+car_minture>60*human_hour+human_minture){          
            	break;
        	}
    	}         
		if(x<zhantai){
    	    answer=(zhantai-x)*20+car_minture-human_minture;    //车在人后，至少再走一站 
    	}
    	if(x==zhantai){
        	answer=car_minture-human_minture;       //车离站，到站后接人
   	 	}
    	if(x>zhantai){
        	answer=50+car_minture-human_minture;     //车刚从人在的站离开 
    	}
	}
    printf("等待时间是%d", answer);
    return 0;
}

