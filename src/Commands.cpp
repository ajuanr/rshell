//
//  Commands.cpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#include "../header/Commands.hpp"
#include <stdio.h>
#include <unistd.h>
#include <iostream>

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
            cout << "exec failed\n";
            exit(1);
        }
    }
    else {                                  /* for the parent:      */
        while (wait(&status) != pid)       /* wait for completion  */
            ;
    }
    return status;
}
