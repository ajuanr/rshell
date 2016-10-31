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
    Connector(Command*, Command* c=0);
    Command* getLeft() {return left;}
    Command* getRight() {return right;}
    void setRight(Command* Right) { this->right = Right; }
    
private:
    Command *left;
    Command *right;
};

class Or: public Command {
public:
    Or(Connector* con):c(con) {};
    virtual void exec();
private:
    Connector *c;
};

class And: public Command {
public:
    And(Connector* con):c(con) {};
    virtual void exec();
private:
    Connector *c;
};

//
//class Or: public Command {
//public:
//    Or();
//    virtual void exec();
//private:
//    Command *left;
//    Command *right;
//};

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
    virtual void exec(); 
private:
    Connector *c;
};

#endif /* Connectors_hpp */
