#include<stdio.h>
#include<stdlib.h>
int main(){
    char english_words[5][6]={"just","see","her","your","come"};
    int i, j;
    for(i=0;i<5;i++){
    	for(j=0;j<10;j++){
    		if(english_words[i][j]=='\0')
				break;
    		printf("%c", english_words[i][j]);
	 	}
	}
	return 0;
}
