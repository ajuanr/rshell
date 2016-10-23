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

using namespace std;

int main(int argc, const char * argv[]) {
    Command *a = new Cmd("ls");
    Command *b = new Cmd("echo");
    Command *c = new Cmd("cat");
    
    Connector* s = new Connector(a,b);
    Command *d = new Semi(s);
    
    d->exec();
    cout << endl;
    
    return 0;
}
