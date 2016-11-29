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

CD::CD() {
    oldPath = newPath = std::getenv("PWD");
}

// sets the new path and updates the old path
CD::CD(char * newPath) {
    this->newPath = oldPath = newPath;
    setPath(newPath);
}

void CD::setPath(char * newPath) {
    Test *pathCheck = new Test(newPath);
    // path exists
    if (!pathCheck->execute()) {
        // try to set the new path
        int test = setenv("PWD", newPath, 1);
        // the new environment variable was set,
        // update the PWD and OLDPWD path 
        if (!test) {
            // update the old path;
            oldPath = this->newPath;
            setenv("OLDPWD", oldPath, 1);
            // update the newPath;
            this->newPath = newPath;
        }
    }
    else
        perror("path does not exist");
}

// swap to char*, for the goBack() function
void charSwap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// go back to the previous path, e.g 'cd -'
void CD::goBack() {
    setPath(getenv("OLDPWD"));
}

// sets the PWD to the current path
void CD::home() {
    setPath(getenv("HOME"));
}

// execute changes the directory
int CD::execute() {
    return chdir(newPath);
}
