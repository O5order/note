#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }
    int i = 0;
    for(i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];
	if (letter>'A' && letter<'Z'){
		letter+=32;
		printf("%c", letter);
	}else printf(" ok  %c", letter);
     }
    return 0;
}
