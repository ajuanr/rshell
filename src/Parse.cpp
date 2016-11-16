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
