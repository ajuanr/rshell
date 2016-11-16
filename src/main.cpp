//
//  main.cpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

/******* System headers ********/
#include <iostream>
#include <unistd.h>
#include <stdio.h>

/******* User headers ********/
#include "../header/Parse.hpp"
#include "../header/Commands.hpp"
#include "../header/Connectors.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

bool isConnector(char *, char *);
bool closedProperly(char*, char, char);
bool hasPrnth(char*);
vector<char*> parse(char*, const char*);
Command* parseTest(char*);
Command* parseSymbolic(char*);
Command* parseCommand(char*, int);

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
    while(strcmp(input, "exit") != 0) {
    // make a vector of the connectors
    vector<char> connectList = getConnectors(input);
    
    vector<char*> mem;
    const char* delim = "&|;";
//    cout << "input is: " << input << endl;
    
    // parse input by closing parenthesis
    mem = parse(input, delim);
    
    // cmds will hold the individual commands
    vector<Command*> cmds;
    for (int i = 0; i != mem.size(); ++i) {
        Parse p;
        char **temp = p.parse(mem.at(i), "()"); // parse on whitespace
        // test if command is 'test' or using the bracket '['
        // uses keyword test
        if ( strncmp(*temp, "test", 4) == 0 ){
            Command *testCmd = parseTest(*temp);
            cmds.push_back(testCmd);
        }
        else if (**temp == '[') {
            /****** DELETE ******/
            Command *testCmd = parseSymbolic(*temp);
            cmds.push_back(testCmd);
            /********************/
        }
        else {
            Command *cmd = parseCommand(*temp, 100); // 100 is the buffer size
            cmds.push_back(cmd);
        }
    }

    // more connectors than commands and last connector is not ;
    // exit due to invalid input
    if (connectList.size() >= cmds.size() &&
        connectList.at(connectList.size()-1) != ';') {
        cout << "Invalid input\n";
        return 9;
    }
    // done will hold the vector with the command tree
    // which will be executed
    vector<Command*> done;
    
    for (int i = 0, index = 0; i != mem.size(); ++i) {
        // skip the first command as it's always pushed onto the vector
        // add the following commands to the vector, using a connector
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
        
        // get input for the next command
        cout << "$: ";
        cin.getline(input, BUFFER);
//
    } // end input
    return 0;
}

/******************************************************/
/***************** Function definitions ***************/
/******************************************************/
// check if a char* has an ( or ) parenthesis
// return true if it does
bool hasPrnth(char *line) {
    bool hasP = false;
    
    for ( int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == '(' || line[i] == ')')
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

// finds the connectors(&, |, and ;) in a line
// puts them into a vector
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

// parses a line using the delimiter and places the output in a vector
vector<char*> parse(char *line, const char *delim) {
    vector<char*> ret;
    Parse *p = new Parse();
    char **parseResult = p->parse(line, delim);
    for (int i = 0; i != p->getSize(); ++i) {
        ret.push_back(*parseResult++);
    }
    return ret;
}

bool isConnector(char *c, char *connector) {
    bool ret = false;
    while (connector++ != NULL) {
        if (connector == c)
            return true;
    }
    return ret;
}

Command* parseTest(char * test) {
    const int BUFFER = 100;
    char **ret = new char* [BUFFER];
    char **temp = new char* [BUFFER]; // points to the beginning
    temp = ret;
    char *token = strtok(test, " ");
    *ret++ = token;
    // only one blank left to get the token for
    token = strtok(NULL, " ");
    
    // the user omitted the flag
    if (*token != '-') {
        cout << token << endl;
        Command *result = new Test(token);
        return result;
    }
    // flag was included, continue processing
    *ret++ = token;
    token = strtok(NULL, "^");
    *ret++=token;
    
    // point temp back to beginning
    ret = temp;
    // clean-up
    temp = 0;
    delete[] temp;

    Command *result = new Test(ret[2], ret[1][1]);
    
    return result;
}

// this function parses the symbolic version of test
Command* parseSymbolic(char * line) {
    Parse p;
    char **parsedLine = p.parse(line, "[]");
    
    const int BUFFER = 100;
    char **ret = new char* [BUFFER];
    char **temp = new char* [BUFFER]; // points to the beginning
    temp = ret;
    char *token = strtok(*parsedLine, " ");
    
    if (*token != '-') {
        cout << token << endl;
        Command *result = new Test(token);
        return result;
    }
    // flag was included, continue processing
    *ret++ = token;
    token = strtok(NULL, "^");
    *ret++=token;
    
    // point temp back to beginning
    ret = temp;
    // clean-up
    temp = 0;
    delete[] temp;
    
    Command *result = new Test(ret[1], ret[0][1]);
    
    *ret++ = token;
    // only one blank left to get the token for
    token = strtok(NULL, " ");
    
    return result;
}

Command* parseCommand(char *cmd, int size) {
    Parse p;
    // parse on blank space;
    Command *result = new Cmd(p.parse(cmd, " "), size);
    return result;
}
