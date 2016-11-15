//
//  Connectors.hpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#ifndef Connectors_hpp
#define Connectors_hpp

#include "../header/Commands.hpp"

#include <stdio.h> // for NULL

// ABC representing a connector
class Connector: public Command {
public:
    Connector():left(NULL), right(NULL){ };
    // default parameter because semicolons don't need right argument
    Connector(Command* l, Command *r=0);
    Command* getLeft() {return left;};
    Command* getRight() {return right;};
    virtual int execute() = 0; // leave it up to the connectors to implement
private:
    Command *left;
    Command *right;
};

// class implements the semicolon(;) connector
class Semi: public Connector{
public:
    Semi(): Connector() { };
    Semi(Command *l, Command *r): Connector(l,r) { };
    virtual int execute();
};

// class implements the And(&&) connector
class And: public Connector {
public:
    And(): Connector() { };
    And(Command *l, Command *r): Connector(l, r) { };
    virtual int execute();
};

// class implements the Or (||) connector
class Or: public Connector {
public:
    Or(): Connector() { };
    Or(Command *l, Command *r): Connector(l, r) { };
    virtual int execute();
};

#endif /* Connectors_hpp */
