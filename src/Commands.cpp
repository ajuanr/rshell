//
//  Commands.cpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#include "../header/Commands.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

Cmd::Cmd(char **cmd, int size) {
    int i = 0;
    this->cmd = new char*[size];
    // temp points to the beginning of the command
    char ** temp = new char*[size];
    temp = this->cmd;
    while(*cmd != NULL) {
        *this->cmd++ = *cmd++;
        ++i;
    }
    this->cmd = temp;
    temp = 0;
    delete[] temp;
}

// returns 0 on successful execute
int Cmd::execute() {
    pid_t pid;
    // initialize to failure
    int status=1;
    
    // for the child process
    if ((pid = fork()) < 0) {
        cout << "forking child process failed\n";
        exit(1);
    }
    
    else if (pid == 0) {
        // execute the command and check if it exectuded
        if (execvp(*cmd, cmd) < 0) {
            exit(1);
        }
    }
    else {
        while (wait(&status) != pid)
            ;
    }
    return status;
}

// Constructor where user does not input a flag, -e is the default flag
Test::Test(char* file): filePath(file), flag('e') {
    buffer = new struct stat[sizeof(struct stat)];
}

// Constructor whhere user specifies a flag
Test::Test(char *file, char f): filePath(file), flag(f)  {
    buffer = new struct stat[sizeof(struct stat)];
}

// returns 0 upon succesful execution
// returns 1 upon failure
int Test::execute() {
    // remmove any blank spaces that might show up when using multiple commands
    int i=0;
    while (filePath[i] != '\0') {
        ++i;
    }
    if (filePath[i-1] == ' ') filePath[i-1] = '\0';
    
    char * real=filePath;
    if (filePath[0] != '/') {
        real = realpath(filePath, NULL);
    }
    bool ret = 1; // assume function call fails and return that
    
    // check to make sure that real now points to the real path after
    // the function realpath resolves to an actual directory
    if (real) {
    // file exists
        if(stat(real, buffer) == 0) {
            // check if file or directory
            if (flag == 'e') {
                if (S_ISREG(buffer->st_mode) || S_ISDIR(buffer->st_mode)) {
                    cout << "(True)\n";
                    return 0;
                }
            }
            if (flag == 'f') {
                if (S_ISREG(buffer->st_mode)) {
                    cout << "(True)\n";
                    return 0;
                }
            }
            if (flag == 'd') {
                if (S_ISDIR(buffer->st_mode)) {
                    cout << "(True)\n";
                    return 0;
                }
            }
        }
        // file does not exist
        else
        {
            perror(filePath);
        }
    }
    // check if memory was allocated
    // free the memory that realpath() reserves
    if (filePath[0] != '/') {
        free(real);
    }

    if (ret == 1) cout << "(False)\n"; // path doesn't exist
    
    return ret;
}
