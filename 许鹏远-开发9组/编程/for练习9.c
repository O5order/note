#include <stdio.h>
#include <ctype.h>
#include <string.h>
// forward declarations
void print_letters(char arg[],int n);

void print_arguments(int argc, char *argv[])
{
    int i = 0;
    int n = 0;
    for(i = 0; i < argc; i++) {
	n=strlen(argv[i]);
        print_letters(argv[i], n);
    }
}

void print_letters(char arg[],int n)
{
    int i = 0;

    for(i = 0;i < n; i++) {
        char ch = arg[i];

        if((ch>'a' && ch<'z') || (ch>'A' && ch<'Z')) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
