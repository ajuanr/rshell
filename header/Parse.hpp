//
//  Parse.hpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#ifndef Parse_hpp
#define Parse_hpp

#include <vector>

// forward declaration
class Command;
class CD;

class Parse {
public:
    Parse():size(0) { };
    char** parse(char*, const char*);
    Command* parseTest(char*);
    Command* parseSymbolic(char*);
    Command* parseCommand(char*, int);
    void parseCD(char *, CD*);
    void print() const;
    int getSize() const {return size;}
private:
    int size;
    static const unsigned int BUFFER = 100; //max number of commands
};

#endif /* Parse_hpp */
