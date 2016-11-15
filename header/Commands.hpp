//
//  Commands.hpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#ifndef Commands_hpp
#define Commands_hpp

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

#endif /* Commands_hpp */
