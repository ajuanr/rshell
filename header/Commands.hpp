//
//  Commands.hpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#ifndef Commands_hpp
#define Commands_hpp

#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// ABC for holding individual commands
// as well as commands composed with connectors
class Command {
public:
    virtual int execute() = 0;
};

// this is the base class that will be executed
class Cmd: public Command {
public:
    Cmd(char**, int);
    virtual int execute();
private:
    char** cmd;
};

class Test: public Command {
public:
    Test(char*, char);
    Test(char*);
    virtual int execute();
private:
    char *filePath;
    char flag;
    struct stat *buffer;
};

#endif /* Commands_hpp */
