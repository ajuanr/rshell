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

CD::CD() {
    oldPath = newPath = std::getenv("PWD");
}

//char* CD::getPath() {
//    return std::getenv("PWD");
//}

// sets the new path and updates the old path
int CD::setPath(char * newPath) {
    // try to set the new path
    int test = setenv("PWD", newPath, 1);
    // the new environment variable was set,
    // update the PWD and OLDPWD path 
    if (test) {
        // update the old path;
        oldPath = this->newPath;
        setenv("OLDPWD", oldPath, 1);
        // update the newPath;
        this->newPath = newPath;
    }
    
    return test;
}

// go back to the previous path
int CD::goBack() {
    // try to set the new path
    int test = setenv("PWD", oldPath, 1);
    // the new environment variable was set,
    // swap the oldPath and newPath
    if (test) {
        setenv("OLDPWD", newPath, 1);
        // swap the paths
        char *temp = oldPath;
        oldPath = newPath;
        newPath = temp;
    }
    
    return test;
}

// sets the PWD to the current path
int CD::home() {
    newPath = getenv("HOME");
    return setPath(newPath);
    
}

// execute changes the directory
int CD::execute() {
    return chdir(newPath);
}
