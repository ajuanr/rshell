//
//  main.cpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#include <iostream>

#include "../include/Command.hpp"
#include "../include/Cmd.hpp"
#include "../include/Connector.hpp"
#include "../include/Parse.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
//    Command *a = new Cmd("ls");
//    Command *b = new Cmd("echo");
//    Command *c = new Cmd("pwd");
//    c->exec();
//    Connector* e = new Connector(c);
//    Command *d = new Semi(e);
//    c->exec();
//    d->exec();
//    cout << endl;
    
    string s = "ls -l; pwd";
    
    Parse *p = new Parse(s);
    p->exec();
    
//    cout << *p->findConnector(s.begin()+5,s.end() ) << endl;
//    cout << *p->findBeg(s.begin()+6, s.end()) << endl;
    
    
    
    return 0;
}
