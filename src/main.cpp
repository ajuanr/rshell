//
//  main.cpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "Parse.hpp"
#include "Commands.hpp"
#include "Connectors.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

bool isConnector(char *c, char *connector) {
    bool ret = false;
    while (connector++ != NULL) {
            if (connector == c)
                return true;
    }
    return ret;
}

void userInfo();

vector<char> getConnectors(char *);

int main(int argc, const char * argv[]) {
    
    const int BUFFER = 100; // large enough to hold a reasonable length command
    char input[BUFFER]; // the input from the user
    cout << "$: ";
    cin.getline(input, BUFFER);
    
    const char* delimit = ";&|";
    
    // make a vector of connectors
    vector<char> connectList = getConnectors(input);
    
    // parse the input, based on connectors
    Parse *p = new Parse(input, delimit);

    // further parse the input based on whitespace
    // vector mem will hold all the commands
    vector<Command*> mem;
    for (int i = 0; i != p->size(); ++i) {
    Command *cmd = new Cmd(p->parse(p->at(i), " "), BUFFER);
        mem.push_back(cmd);
    }
    
    // more connectors than commands and last connector is not ;
    // exit  due to wrong input
    if (connectList.size() > mem.size() &&
        connectList.at(connectList.size()-1) != ';') {
        cout << "error\n";
        return 9;
    }
    
    vector<Command*> done;
    int index = 0;
    for (int i = 0; i != mem.size(); ++i) {
        //mem.at(index)->execute();
        // for commands after the first one
        // add it to the vector, using a connector
        if (i != 0) {
            // check for the ; connector
            if ( connectList.at(i-1) == ';') {
                done.push_back(new Semi(done.at(index-1), mem.at(index)));
            }
            // check for &
            if (connectList.at(i-1) == '&') {
                done.push_back(new And(done.at(index-1), mem.at(index)));
            }
            // check for |
            if (connectList.at(i-1) == '|') {
                done.push_back(new Or(done.at(index-1), mem.at(index)));
            }
            index++;
        }
        // always push back the first command
        else {
            done.push_back(mem.at(index++));
        }
    } // end for loop

    // the last element will hold the complete tree
    if (!done.empty())
        done.at(done.size()-1)->execute();
    
    return 0;
}

vector<char> getConnectors(char * input) {
    vector<char> ret;
    // ignores ; connect since those always get executed
    for(int i = 0; input[i] !='\0'; ++i) {
        // check for ';'
        if (input[i] == ';')
            ret.push_back(input[i]);
        // check for &, or |
        if (input[i] == '&' || input[i] == '|') {
            //check for the second & or |
            if (input[i+1] != '\0' && input[i+1] == input[i]) {
                ret.push_back(input[i]);
            }
        }
    }
    return ret;
}

void userInfo() {
    ;
}
