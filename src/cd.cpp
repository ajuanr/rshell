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
    currentPath = getenv("PWD");
    oldPath = NULL;
}

// sets the new path and updates the old path
CD::CD(char * newPath) {
    currentPath = oldPath = newPath;
    setPath(newPath);
}

// swap to char*, for the goBack() function
void charSwap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void CD::setPath(char * newPath) {
//    cout << "OLD       " << oldPath
//    << "\nthis->new " << currentPath
//    << "\nnewPath   " << newPath << endl;
    Test *pathCheck = new Test(newPath);
    // path exists
    if (!pathCheck->execute()) {
        // test if the new PWD variable is set
        // update the PWD and OLDPWD path 
        if (!setenv("PWD", newPath, 1)) {
            // update the old path;
            this->oldPath = currentPath;
            setenv("OLDPWD", newPath, 1);
            //charSwap(&oldPath, &(this->newPath));
            // update the newPath;
            currentPath = newPath;
//            this->newPath = getenv("PWD");
//            charSwap(&(this->newPath), &newPath);
        }
//        cout << "\t\tOLD       " << oldPath
//        << "\n\t\tthis->new " << currentPath
//        << "\n\t\tnewPath   " << newPath << endl;
    }
    else
        perror("path does not exist");
}

// go back to the previous path, e.g 'cd -'
void CD::goBack() {
//    charSwap(&oldPath, &newPath)
    if (oldPath==NULL) {
        cout<< "previous directory not set\n";
    }
    else
    setPath(oldPath);
}

// sets the PWD to the current path
void CD::home() {
    setPath(getenv("HOME"));
}

// execute changes the directory
int CD::execute() {
    return chdir(currentPath);
}
