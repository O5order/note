#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void umbrella(int ID){
	FILE *fp;
 	int um_id[20];
	int id[20];        
	int set[20];
	int i;
	char r;
	if((fp=fopen("umbrella", "r+"))==NULL){
		fp=fopen("umbrella", "w");
		for(i=0;i<20;i++){             //initalize
			um_id[i]=i;
			id[i]=0;
			set[i]=0;
			fwrite(um_id+i,sizeof(int),1,fp);
			fwrite(id+i,sizeof(int),1,fp);
			fwrite(set+i,sizeof(int),1,fp);
			fflush(fp);
    		}
    	}else{
    	rewind(fp);
    	for(i=0;i<20;i++){				//load umbrella datas
    			fread(um_id+i,sizeof(int),1,fp);
    			fread(id+i,sizeof(int),1,fp);
    			fread(set+i,sizeof(int),1,fp);
    	}
    	rewind(fp);
    	for(i=0;i<20;i++){                 //return the umbrella
		if(id[i]==ID){
    			printf("\nplease return the umbrella!\n");
    			printf("enter 'r' to return,else not to return\n");
    			scanf(" %c", &r);
    			if(r=='r'){
    				set[i]=0;
    				id[i]=0;
        		}else{
        		printf("remember to return umbrella!\n");
        		goto choose;
  			}
        	}	
        	fwrite(um_id+i,sizeof(int),1,fp);
        	fwrite(id+i,sizeof(int),1,fp);
        	fwrite(set+i,sizeof(int),1,fp);
        }
        }	
    choose:
    printf("which umbrella you want to borrow?enter the id.(these um_id still remain): \n");
    for(i=0;i<20;i++){
        if(set[i]==0)           //print umbrella remain
            printf("%d ", 1+um_id[i]);
    }
    int bor;
    scanf("%d", &bor);
    if(set[bor-1]==0){         //correct the umbrella status
            set[bor-1]=1;
            id[bor-1]=ID;
    }else{
        printf("wrong umbrella id");
        goto choose;
    }
    rewind(fp);
    for(i=0;i<20;i++){
            fwrite(um_id+i,sizeof(int),1,fp);
            fwrite(id+i,sizeof(int),1,fp);
            fwrite(set+i,sizeof(int),1,fp);
        }
    for(i=0;i<20;i++){
  	    fread(um_id+i,sizeof(int),1,fp);
    	    fread(id+i,sizeof(int),1,fp);
            fread(set+i,sizeof(int),1,fp);
    }
    fclose(fp);
}
