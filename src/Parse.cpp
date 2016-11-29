//
//  Parse.cpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "../header/Parse.hpp"
#include "../header/Commands.hpp"
#include "../header/cd.hpp"

// parses the input and return a char** that can be used with execvp
char** Parse::parse(char* line, const char* delim) {
    char **ret = new char* [BUFFER];
    char **temp = new char* [BUFFER]; // points to the beginning
    temp = ret;
    char *token = strtok(line, delim);
    // reset the size on every parse
    size = 0;
    while (token != NULL) {
        *ret++ = token;
        ++size;
        token = strtok(NULL, delim);
    }
    // so we know where the end is
    *ret = NULL; // end with NULL
    
    // point temp back to beginning
    ret = temp;
    // clean-up
    temp = 0;
    delete[] temp;
    
    return ret;
}
// this functions parses commands that utilize the 'test' command
Command* Parse::parseTest(char * test) {
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
Command* Parse::parseSymbolic(char * line) {
    Parse p;
    char **parsedLine = p.parse(line, "[]");
    
    const int BUFFER = 100;
    char **ret = new char* [BUFFER];
    char **temp = new char* [BUFFER]; // points to the beginning
    temp = ret;
    char *token = strtok(*parsedLine, " ");
    
    if (*token != '-') {
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

Command* Parse::parseCommand(char *cmd, int size) {
    Parse p;
    // parse on blank space;
    Command *result = new Cmd(p.parse(cmd, " "), size);
    return result;
}

Command* Parse::parseCD(char *line) {
    CD *result = new CD();
    char *token = strtok(line, " ");
    token = strtok(NULL, " "); // ignore the first token, it's the cd command
    // if token is  not null, you have a dash or a path
    if (token != NULL) {
        if (*token == '-')
            result->goBack();
        else
            result->setPath(token);

    }
    else
        result->home();
    
    return result;
}
