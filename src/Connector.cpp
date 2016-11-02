//
//  Connectors.cpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#include "../header/Connector.hpp"

Connector::Connector(Command* l, Command* r):left(l), right(r) { }

std::string Semi::exec() {
    c->getLeft()->exec();
    if (c->getRight()) {
        c->getRight()->exec();
        return c->getLeft()->exec() + c->getRight()->exec();
    }
    return c->getLeft()->exec();
}

std::string And::exec() {
    if (c->getLeft()->exec().size()>0 && c->getRight()->exec().size()>0) {
        return c->getLeft()->exec() + c->getRight()->exec();
    }
    return "";
}

std::string Or::exec() {
    if (c->getLeft()->exec().size()>0 || c->getLeft()->exec().size()>0) {
        return c->getLeft()->exec() + c->getRight()->exec();
    }
    return "";
}
