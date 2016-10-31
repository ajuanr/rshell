//
//  main.cpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

/********* System Libraries ********/
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

/********** User Libraries ********/
#include "../include/Command.hpp"
#include "../include/Cmd.hpp"
#include "../include/Connector.hpp"
#include "../include/Parse.hpp"

using namespace std;

//void my_handler(sig_t s){
//    if (s==SIGINT) {
//    printf("Caught signal %d\n",s);
//    exit(1);
//    }
//}

int main(int argc, const char * argv[]) {

    cout << ">> ";
    string s;
    getline(cin, s);
    //sig_t exit;
    while (s!="exit") {
        Parse *p = new Parse(s);
        p->exec();
        cout << " >> ";
        getline(cin, s);
        //my_handler(exit);
    }

    
    //     s = "ls -a; echo hello && mkdir test || echo world; git status";
    //    string s = "ls -a";
    
    return 0;
}
