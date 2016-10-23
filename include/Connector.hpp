//
//  Connectors.hpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#ifndef Connectors_hpp
#define Connectors_hpp

#include "../include/Command.hpp"


class Connector {
public:
    Connector(Command*, Command*);
    Command* getLeft() {return left;}
    Command* getRight() {return right;}
    
    
private:
    Command *left;
    Command *right;
};



//
//class Or: public Command {
//public:
//    Or();
//    virtual void exec() { left->exec(); right->exec();};
//private:
//    Command *left;
//    Command *right;
//};
//
//class And: public Command {
//public:
//    And();
//    virtual void exec() { left->exec(); right->exec();};
//private:
//    Command *left;
//    Command *right;
//};

class Semi: public Command {
public:
    Semi(Connector* con):c(con) {};
    virtual void exec() { c->getLeft()->exec(); c->getRight->exec();};
private:
    Connector *c;
    Command *left;
    Command *right;
};

#endif /* Connectors_hpp */
