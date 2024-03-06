#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


#define MAX_DATA 100

int well_fgets(char *out_string,int num){
    for(int i=0;i<num;i++)
    {
    	out_string[i] = fgetc(stdin);
    	out_string[i+1] = '\0';
    	if(out_string[i] == '\n')
    	{
    		out_string[i] = '\0';
    		break;
    	}

    }
    return 1;


}

int read_string(char **out_string, int max_buffer)
{
    *out_string = calloc(1, max_buffer + 1);


    int result = well_fgets(*out_string, max_buffer);


    return 0;


}

int read_int(int *out_int)
{
    char *input = NULL;
    int rc = read_string(&input, MAX_DATA);


    *out_int = atoi(input);

    free(input);
    return 0;

}



int read_scan(const char *fmt, ...)
{
    int i = 0;
    int rc = 0;
    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    va_list argp;
    va_start(argp, fmt);

    for(i = 0; fmt[i] != '\0'; i++) {
        if(fmt[i] == '%') {
            i++;
            switch(fmt[i]) {
                case '\0':

                    break;

                case 'd':
                    out_int = va_arg(argp, int *);
                    rc = read_int(out_int);

                    break;

                case 'c':
                    out_char = va_arg(argp, char *);
                    *out_char = fgetc(stdin);
                    break;

                case 's':
                    max_buffer = va_arg(argp, int);
                    out_string = va_arg(argp, char **);
                    rc = read_string(out_string, max_buffer);

                    break;



            }
        } else {
            fgetc(stdin);
        }


    }

    va_end(argp);
    return 0;

}



int main(int argc, char *argv[])
{
    char *first_name = NULL;
    char initial = ' ';
    char *last_name = NULL;
    int age = 0;

    printf("What's your first name? ");
    int rc = read_scan("%s", MAX_DATA, &first_name);

    printf("What's your initial? ");
    rc = read_scan("%c\n", &initial);


    printf("What's your last name? ");
    rc = read_scan("%s", MAX_DATA, &last_name);


    printf("How old are you? ");
    rc = read_scan("%d", &age);

    printf("---- RESULTS ----\n");
    printf("First Name: %s", first_name);
    printf("Initial: '%c'\n", initial);
    printf("Last Name: %s", last_name);
    printf("Age: %d\n", age);

    free(first_name);
    free(last_name);
    return 0;

}
