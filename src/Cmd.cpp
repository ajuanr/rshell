//
//  Cmd.cpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

/***** System Libraries *****/
#include<iostream>


/***** User Libraries *****/
#include "../include/Cmd.hpp"

using namespace std;

Cmd::Cmd(string s, vector<string> f)
:cmd(s), flags(f)
{
}

void Cmd::exec() {
    cout << cmd << " ";
}
