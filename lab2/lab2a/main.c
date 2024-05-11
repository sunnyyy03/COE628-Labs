#include <stdio.h>  //printf, fprintf
#include <stdlib.h> //EXIT_SUCCESS
#include <string.h> //strlen, strcmp
#define TOO_MANY_ARGS 2
#define TOO_FEW_ARGS 1

int main(int argc, char* argv[]) {
    //Default values:
    int exit_code = EXIT_SUCCESS;
    char * greeting = "Hello";
    char * person = "person";
    
    //Add code to change the exit_code depending on argc
    int arg = argc;
    char* name;
    
    //Add code to change 'person' if one is given on command line
    int len = strlen(argv[0]);
    char * last3 = argv[0] + len - 3; //last3 points to last 3 chars   
    if(strcmp(last3,"bye") == 0)
        greeting = "Bye";
    
    //Add code to change 'greeting' if last 3 chars of command are 'bye'
    if(arg == 1){
        exit_code = 1;
        person = "UNKNOWN";
    }
    if(arg == 2){
        exit_code = 0;
        person = argv[1];
    }
    if(arg >= 3){
        exit_code = 2; 
        person = argv[1];
    }
    
    printf("%s %s\n", greeting, person);
    
    fprintf(stderr, "exit_code: %d\n", exit_code);
    
    return exit_code; //Could also say exit(exit_code)
}