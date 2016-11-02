//
//  main.cpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

/********* System Libraries ********/
#include <iostream>


/********** User Libraries ********/
#include "../header/Command.hpp"
#include "../header/Cmd.hpp"
#include "../header/Connector.hpp"
#include "../header/Parse.hpp"

using namespace std;


int main(int argc, const char * argv[]) {
    /***** user info ********/
    Cmd *user = new Cmd("whoami");
    string loggedIn = user->exec();
    loggedIn = string(loggedIn.begin(), loggedIn.end()-1); // remove newline
    Cmd *host = new Cmd("hostName");
    string hostName=host->exec();
    hostName = string(hostName.begin(), hostName.end()-1);
    string input =  loggedIn + "@" + hostName + "$ ";
    
    cout << input;
    /******** input *********/
    string s;
    getline(cin, s);
    while (s!="exit") {
        Parse *p = new Parse(s);
        p->exec();
        cout << input;
        getline(cin, s);
    }
    
    return 0;
}
