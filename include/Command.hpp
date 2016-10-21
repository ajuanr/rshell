//
//  Command.hpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp

class Command {
public:
    Command() { }
    virtual void exec() = 0;
private:
};

#endif /* Command_hpp */
