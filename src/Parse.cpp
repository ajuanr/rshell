//
//  Parse.cpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#include "Parse.hpp"
//#include <iostream>

//using std::cout;    using std::endl;

// Parses the input based on the delimeter and add it to a vector containg
// the commands
Parse::Parse(char* input, const char* delimiter) {
    char* token = strtok(input, delimiter);
    while (token != NULL) {
        mem.push_back(token);
        token = strtok(NULL, delimiter);
    }
}

// further parses the input and return a char** that can be used with execvp
char** Parse::parse(char* line, const char* delimeter) {
    char **ret = new char* [BUFFER];
    char **temp = new char* [BUFFER]; // points to the beginning
    temp = ret;
    char *token = strtok(line, delimeter);
    int index = 0;
    while (token != NULL) {
        *ret++ = token;
        ++index;
        token = strtok(NULL, " ");
    }

    *ret = NULL; // end with NULL
    
    ret = temp;
    // clean-up
    temp = 0;
    delete[] temp;
    
    return ret;
}
