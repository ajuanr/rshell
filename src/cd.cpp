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
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string.h>

/************** User Libraries *************/
#include "../header/cd.hpp"

using namespace std;

// default constructor
CD::CD() {
    history.push(NULL); // no previous path set
    history.push(getenv("PWD")); // current directory
}

void CD::setPath(char * newPath) {
    // remmove any blank spaces that might show up when using multiple commands
    char *path = strtok(newPath, " ");
    char * real=path;
    if (path[0] != '/') {
        real = realpath(path, NULL);
    }
    // path evaluates to a real path
    if (real) {
        Test *pathCheck = new Test(real,'d');
        // path exists
        if (!pathCheck->execute()) {
            history.pop(); // remove oldest entry
            history.push(deepCopy(real)); // add the new path
            setenv("PWD", deepCopy(real), 1); // update PWD variable
        }
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
        setenv("OLDPWD", history.front(), 1);
        setPath(history.front());
    }
}

// sets the PWD to the current path
void CD::home() {
    setPath(getenv("HOME"));
}

// execute changes the directory
int CD::execute() {
    int ret = chdir(getenv("PWD"));
    // ret is -1 on failure, we need 1
    return (ret==0)? 0:1;
}
