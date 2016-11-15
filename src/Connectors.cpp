//
//  Connectors.cpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#include "../header/Connectors.hpp"

#include <iostream>

Connector::Connector(Command* left, Command *right) {
    this->left = left;
    this->right = right;
}

int Semi::execute() {
    getLeft()->execute();
    if (getRight())
        getRight()->execute();
    return 0; // next command always executes when using semi-colon
}

int And::execute() {
    int ret = getLeft()->execute();

    // execute failed
    if (ret != 0) {
        return ret;
    }
    // execute was succesful, test next command
    else
        ret = getRight()->execute();
    // return result of second command
    return ret;
}

// if left command is succesful, return 0, indicating succes and exit
// otherwise, return result of second command
int Or::execute() {
    int ret = getLeft()->execute();
    // execute failed
    if (ret==0) {
        return ret;
    }
    // execute was succesful, test next command
    else
        ret = getRight()->execute();
    // return result of second command
    return ret;
}
