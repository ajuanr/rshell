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

bool closedProperly(char*, char, char);
bool hasPrnth(char*);
vector<char*> parse(char*, const char*);

void userInfo();

vector<char> getConnectors(char *);

/**************** FOR TESTING *******************/
template<class T>
void print(vector<T> vec) {
    for (typename vector<T>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
        cout << *i << endl;
    }
}
/**************** FOR TESTING *******************/

void completeParse();

int main(int argc, const char * argv[]) {
    
    const int BUFFER = 100; // large enough to hold a reasonable length command
    char input[BUFFER]; // the input from the user
    cout << "$: ";
    cin.getline(input, BUFFER);
    
    // make a vector of the connectors
    vector<char> connectList = getConnectors(input);
    
    char **parseResult;
    vector<char*> mem;
    const char* delim = "&|;";
    cout << "input is: " << input << endl;

//        parseResult = p->parse(input, );
    
    // parse input by closing parenthesis
    mem = parse(input, delim);
    
//    int size = mem.size();
//    for (int i = 0; i != size; ++i) {
//        mem.push_back(parse(mem.at(i)), "(");
//        
//    }
    
    //print(mem);
    
    // cmds will hold the individual commands
    vector<Command*> cmds;
    for (int i = 0; i != mem.size(); ++i) {
        Parse p;
        char **temp = p.parse(mem.at(i), "() "); // parse on whitespace
        if (*temp == "test" || **temp=='[')
            cout << "testing 1,2, 3\n";
        else {
            Command *cmd = new Cmd(temp, 100); // 100 is the buffer size
            cmds.push_back(cmd);
        }
    }
    
//    for (int i =0; i != cmds.size(); ++i) {
//        cmds.at(i)->execute();
//    }

    
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
                done.push_back(new Semi(done.at(index-1), cmds.at(index)));
            }
            // check for &
            if (connectList.at(i-1) == '&') {
                done.push_back(new And(done.at(index-1), cmds.at(index)));
            }
            // check for |
            if (connectList.at(i-1) == '|') {
                done.push_back(new Or(done.at(index-1), cmds.at(index)));
            }
            index++;
        }
        // always push back the first command
        else {
            done.push_back(cmds.at(index++));
        }
    } // end for loop

    // the last element will hold the complete tree
    if (!done.empty())
        done.at(done.size()-1)->execute();
//
    return 0;
}

// check if a char* has an ( or ) parenthesis
// return true if it does
bool hasPrnth(char *line) {
    bool hasP = false;
    
    for ( ; *line != '\0'; *line++) {
        if (*line == '(' || *line == ')')
            hasP = true;
    }
    return hasP;
}

// returns true if all opening parenthesis have a closing parenthesis
bool closedProperly(char* line, char open, char close) {
    // check if every opening parentheis is closed;
    int opening = 0;
    int closing = 0;
    
    while (*line != '\0') {
        // opening parenthesis
        if (*line == open)
            ++opening;
        // closing parenthesis
        if (*line == close)
            ++closing;
        ++line;
    }
    return (opening == closing);
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

// parses the line using the delimiter and places the output in a vector
vector<char*> parse(char *line, const char *delim) {
    vector<char*> ret;
    Parse *p = new Parse();
    char **parseResult = p->parse(line, delim);
    for (int i = 0; i != p->getSize(); ++i) {
        ret.push_back(*parseResult++);
    }
    return ret;
}
