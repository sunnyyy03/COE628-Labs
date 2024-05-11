/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: s25das
 *
 * Created on February 5, 2024, 5:25 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv) {
    pid_t pid;
    int status;
    char line[101];  
    char *my_argv[50];  
    int argCount = 0;  

    while (1) {
        printf("Your Command>\n");
        memset(line, 0, sizeof(line));
        argCount = 0;
        char ch;
        int charIndex = 0;
        
        while ((ch = getchar()) != '\n') {
            if (ch == '&') {
                break;
            }

            line[charIndex++] = ch;

            if (charIndex >= 100) {
                fprintf(stderr, "Error: Maximum line length exceeded.\n");
                exit(EXIT_FAILURE);
            }
        }

        my_argv[argCount++] = strtok(line, " ");
        while (argCount < 50 && (my_argv[argCount++] = strtok(NULL, " ")) != NULL);

        if (line[charIndex - 1] == '&') {
            line[charIndex - 1] = '\0';  
        } else {
            line[charIndex] = '\0'; 
        }

        if ((pid = fork()) == 0) {
            execvp(my_argv[0], my_argv);
            perror("Error in execvp");
            exit(EXIT_FAILURE);
        }

        waitpid(pid, &status, 0);

        printf("Hello from parent with child %d\n", pid);
    }

    return EXIT_SUCCESS;
}



