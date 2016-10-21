//
//  Cmd.hpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#ifndef Cmd_hpp
#define Cmd_hpp

/****** System Libraries ******/
#include <string>
#include <vector>

/******* User Libraries ******/
#include "../include/Command.hpp"

class Cmd: public Command {
public:
    Cmd();
    Cmd(std::string, std::vector<std::string> = std::vector<std::string>() );
    virtual void exec();
    virtual std::string getCmd() const {return cmd;};
    virtual std::vector<std::string> getFlags() const {return flags;};
    
private:
    std::string cmd;
    std::vector<std::string> flags;
};

#endif /* Cmd_hpp */
