//
//  CD.cpp
//  CD class
//
//  Created by Juan Ruiz on 11/26/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

/************** System Libraries *************/
#include <iostream>
#include <cstdlib>
#include <unistd.h>

/************** User Libraries *************/
#include "cd.hpp"


using namespace std;

// perform a deep copy of a char* array
char* deepCopy(char* input) {
    char *ret = new char [100];
    int i;
    for (i=0; input[i] != '\0'; ++i)
    {
        ret[i] = input[i];
    }
    ret[++i] = '\0'; // add the null character
    return ret;
}

// default constructor
CD::CD() {
    history.push(NULL); // no previous path set
    history.push(getenv("PWD")); // current directory
}

// swap to char*, for the goBack() function
void charSwap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void CD::setPath(char * newPath) {
    char *testPath = deepCopy(newPath);
    Test *pathCheck = new Test(testPath,'d');
    // path exists
    if (!pathCheck->execute()) {
        history.pop(); // remove oldest entry
        history.push(deepCopy(newPath)); // add the new path
        setenv("PWD", deepCopy(newPath), 1); // update PWD variable
    }
    else
        perror("path does not exist");
}

// go back to the previous path, e.g 'cd -'
void CD::goBack() {
    if (history.front()==NULL) {
        perror("previous directory not set");
    }
    else {
        setPath(history.front());
    }
}

// sets the PWD to the current path
void CD::home() {
    setPath(getenv("HOME"));
}

// execute changes the directory
int CD::execute() {
    return chdir(getenv("PWD"));
}

