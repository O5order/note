#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void teacher(int ID){
	FILE *fp;
	printf("============================================");
	printf("\nyou have went to the interface of the teacher\n");
	printf("enter 'm' to send message to the all of student\nenter 'g' to give out test grade\nenter 'r' to borrow umbrella\nenter 'a' to distribute questionnaire\nenter 'q' to quit register");
	printf("\n===========================================\n");
	printf("$");
	char word;
	int i=0, j=0;
	char ch;			// just something need last
	char m;
	char k[800];
	int num;
	scanf(" %c", &word);
	switch(word){
	case 'm':
		printf("what message you want to send:(less than 200)\n");
		printf("enter @ to over");
		printf("\n========================================\n");
		if((fp=fopen("message", "a+"))==NULL)     //make sure send a lot of message
			fp=fopen("message", "w");	//if student not look at message
		ch=getchar();
		i=0;
		while (1){
			if(ch=='@')break;
			fputc(ch,fp);
			ch=getchar();
			i=i+1;
			if(i==200){
				printf("too many words");
				break;
			}
		}
		fclose(fp);
		break;
	case 'g':
		if((fp=fopen("grade", "a+"))==NULL)
		fp=fopen("grade", "w");
		printf("ID you want to send grade:\n ");
		fprintf(fp,"grade id: ");
		ch=getchar();			//printf who`s grade
		while(1){
			fputc(ch,fp);
			if((ch=getchar())=='\n')
				break;
		}
		printf("grade you want to save:(less than 100)\n");
		printf("enter . to over\n");
		printf("========================================\n");
		ch=getchar();
		i=0;
		while (1){
			if(ch=='.')break;
			fputc(ch,fp);
			ch=getchar();
			i=i+1;
			if(i==100){
				printf("too many words");
				break;
			}
		}
		fclose(fp);
		break;
	case 'a':
			if((fp=fopen("question", "a+"))==NULL){
				fp=fopen("question", "w");         //have no question yet
				printf("how many question you want to make?\n");
				scanf(" %d", &num);
			}else { 
				printf("new answer receive: \n");
				fread(k,sizeof(char)*800,1,fp);
				for(j=0;j<800;j++){
					m=k[j];
					if(m==0)break;		//printf new answer from student
					printf("%c", m);
				}
				fclose(fp);			// make sure txt have nothing
				fp=fopen("question", "w");	//return to question
				printf("how many question you want to make?\n");
				scanf(" %d", &num);
			}
			while(num>j){
			j++;
			printf("question you want to sand:(less than 200)\n");
			printf("enter ? to over\n");
			printf("========================================\n");
			ch=getchar();
			while (1){
				fputc(ch,fp);
				if(ch=='?')break;
				ch=getchar();
				i=i+1;
				if(i==200){
					printf("too many words");
					break;
				}
			}
		}
		fclose(fp);
		printf("\nover");
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
