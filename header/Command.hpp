//
//  Command.hpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp

#include<iostream>
#include<string>

class Command {
public:
    Command() { }
    virtual std::string exec() = 0;
private:
};

#endif /* Command_hpp */
