//
//  Parse.cpp
//  Assignment 2
//
//  Created by Juan Ruiz on 10/29/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#include "Parse.hpp"
#include "Connector.hpp"
#include "Cmd.hpp"

using namespace std;

Parse::Parse(string s):input(s) {
    parse(s);
}

void Parse::parse(string s) {
    
    string::const_iterator beg = s.begin(), end = s.end(), i=beg;
    
    while (i != end) {
        while (!isConnector(*i) && i != end) {++i;}
        if (isspace(*(i-1))) mem.push_back(new Cmd(string(beg, i-1)));
        else mem.push_back(new Cmd(string(beg, i)));
        //mem.push_back(new Cmd(string(i, i+1)));
        while (isConnector(*i) && i != end){++i; beg = i+1;} // go past connectors
    } 
}

// check if the input is a conector
bool Parse::isConnector(char c) {
    const int numConnectors = 3;
    static const char connector[numConnectors] = {';', '&', '|'};
    
    for (int i = 0; i != numConnectors; ++i) {
        if (connector[i] == c)
            return true;
    }
    return false;
    
}

Command* Parse::createConnector(char c, Connector *connector) {
    switch (c) {
        case ';': return new Semi(connector); break;
        case '&': return new Or(connector); break;
        case '|': return new And(connector); break;
        default: return new Semi(connector); break;
    }
}

void Parse::exec() {
    for(int i = 0; i != mem.size(); ++i) {
        mem.at(i)->exec();
    }
}
