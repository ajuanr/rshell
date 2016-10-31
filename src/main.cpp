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

    
    string s = "ls -a; echo hello && mkdir test || echo world; git status";
//    string s = "ls -a";
    Parse *p = new Parse(s);
    p->exec();
    
    return 0;
}
