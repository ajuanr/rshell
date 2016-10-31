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
    virtual std::string exec();
private:
    Connector *c;
};

class And: public Command {
public:
    And(Connector* con):c(con) {};
    virtual std::string exec();
private:
    Connector *c;
};


class Semi: public Command {
public:
    Semi(Connector* con):c(con) {};
    virtual std::string exec();
private:
    Connector *c;
};

#endif /* Connectors_hpp */
