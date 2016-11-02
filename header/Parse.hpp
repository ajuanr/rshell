//
//  Parse.hpp
//  Assignment 2
//
//  Created by Juan Ruiz on 10/29/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#ifndef Parse_hpp
#define Parse_hpp

#include <iostream>
#include <string>
#include <vector>

#include "Command.hpp"
#include "Connector.hpp"

class Parse{//: public Command {
public:
    Parse(std::string);
    void parse(std::string);
    char* parse2(char *s);
    void exec();
    
    typedef std::string::const_iterator cIter;
    
    /*********** Utility Functions ************/
    cIter findBeg(cIter, cIter);
    cIter findConnector(cIter, cIter);
    bool isConnector(char);
    Command* createConnector(char c, Connector *);
    
private:
    std::vector<Command*> mem;
    std::string input;
};

#endif /* Parse_hpp */
