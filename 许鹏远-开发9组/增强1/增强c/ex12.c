#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = 4;
    while(i < argc) {
        printf("arg %d: %s\n", i, argv[i-4]);
        i++;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 0;
    i = 3;  // watch for this
    while(i > num_states) {
        printf("state %d: %s\n", i, states[i]);
        i--;
    }
    i=0;
    while(i<3){
	states[i]=argv[i];
	printf("state %d: %s\n", i, states[i]);
	i++;
    }

    return 0;
}
