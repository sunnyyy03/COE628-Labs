/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: s25das
 *
 * Created on February 12, 2024, 8:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void parseInput(char *input, char *cmd1, char *cmd2) {
    
    char *pipe_pos = strchr(input, '|');
    
    if (pipe_pos == NULL) {
        strcpy(cmd1, input);
        cmd2[0] = '\0';
    }
    
    else {
        *pipe_pos = '\0';
        strcpy(cmd1, input);
        strcpy(cmd2, pipe_pos + 1);
    }
}

int main(int argc, char** argv) {
    
    char input[100];
    char cmd1[50];
    char cmd2[50];
    printf("Enter your command: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; 
    parseInput(input, cmd1, cmd2);
    int fd[2];
    pipe(fd);
    pid_t pID = fork();
    
    if (pID == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pID == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        system(cmd1);
        exit(EXIT_SUCCESS);
    }
    
    else {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        system(cmd2);
        exit(EXIT_SUCCESS);
    }
    
    return EXIT_SUCCESS;
}