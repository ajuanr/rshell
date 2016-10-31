//
//  Connectors.cpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#include "../include/Connector.hpp"

// Connector Constructor
Connector::Connector(Command* l, Command* r):left(l), right(r) { }

void Semi::exec() {
    c->getLeft()->exec();
    if (c->getRight()) {
        c->getRight()->exec();
    }
}

void And::exec() {
    c->getLeft()->exec();
    if (c->getRight()) {
        c->getRight()->exec();
    }
}

void Or::exec() {
    c->getLeft()->exec();
    if (c->getRight()) {
        c->getRight()->exec();
    }
}
