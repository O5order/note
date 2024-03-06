#include <stdio.h>
#include <stdlib.h>

void student(int ID){
	FILE *fp;
	printf("============================================");
	printf("\nyou have went to the interface of the student\n");
	printf("enter 'm' to look at the message\nenter 'g' to look at test grade\nenter 'r' to borrow umbrella\nenter 'a' to answer the question from teacher\nenter 'q' to quit register");
	printf("\n===========================================\n");
	printf("#");
	char word;
	if((scanf("%c", &word))==0) {
		printf("please enter right word");
		exit(0);
	}
	char i[200];
	int j=0, l=0;       //just something need to use
	char m;
	char answer;
	switch(word){
	case 'm':
		if((fp=fopen("message","r"))==NULL){
			printf("there is no more message");
			exit(0);
		}
		printf("you have received new message from teacher!");
		printf("\n==============================\n");
		fread(i,sizeof(char)*200,1,fp);
		printf("%s", i);
		printf("\n==============================\n");
		fclose(fp);
		fp=fopen("message", "w");
		fclose(fp);
		break;
	case 'g':
		if((fp=fopen("grade","r"))==NULL){
			printf("there is no your score");
			exit(0);
		}
		printf("you have received new score from teacher!");
		printf("\n==============================\n");
		fread(i,sizeof(char)*200,1,fp);
		printf("%s", i);
		printf("\n==============================\n");
		fclose(fp);
		break;
	case 'a':
		if((fp=fopen("question","r+"))==NULL){
			printf("there is no question from teacher");
			exit(0);
		}
		printf("you have received new questions from teacher!");
		printf("\n==============================\n");
		fread(i,sizeof(char)*200,1,fp);
		for(j=0;j<200;j++){
			m=i[j];
			if(m=='?'){				//?to answer the question
				l=l+1;
				an:
				printf("\nyour answer(only yes or no): ");
				answer=getchar();
				getchar();
				fprintf(fp,"\nanswer%d: ", l);
					if(answer=='y'){
						fputc(answer,fp);
						answer=getchar();   	//yes or no
						getchar();
						if(answer=='e'){
							fputc(answer,fp);
							answer=getchar();
							getchar();
							if(answer=='s'){
								fputc(answer,fp);
								}else {
							printf("only yes or no!");
							goto an;
							}
						}else {
						printf("only yes or no!");
						goto an;
						}
					}else if(answer=='n'){
						fputc(answer,fp);
						answer=getchar();   	//no
						getchar();
						if(answer=='o'){
							fputc(answer,fp);
						}else {
						printf("only yes or no!");
						goto an;
						}
					}else{
						printf("only yes or no!");
						goto an;
					}
			continue;
			}
			if(i[j]==0)break;
			printf("%c", m);		//print word of txt
		}
		printf("\n==============================\n");
		fclose(fp);
		break;
	case 'r':
		umbrella(ID);
		printf("remember to return!");
		break;
	case 'q':
		printf("\nsafely quit");
		exit(0);
	}
}
