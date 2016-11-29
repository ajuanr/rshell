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
    Test *pathCheck = new Test(newPath,'d');
    // path exists
    if (!pathCheck->execute()) {
        history.pop(); // remove oldest entry
        history.push(newPath); // add the new path
        setenv("PWD", newPath, 1); // update PWD variable
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
        cout << "At front: " << history.front() << endl;
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

//cout << "path exists\n";
//// update the old path
//charSwap(&oldPath, &currentPath);
//charSwap(&currentPath, &newPath);
//setenv("PWD", currentPath, 1);
////        setenv("PWD", newPath, 1);
////        cout << "currentPath: " << currentPath << endl;
////        charSwap(&oldPath, &currentPath);
////        char* temp = new char;
////        temp = newPath;
////        currentPath = temp;
//cout << "\t2OLD       " << oldPath << endl;
//cout << "\t2CURRENT   " << currentPath << endl;
