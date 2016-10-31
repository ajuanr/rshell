//
//  Cmd.cpp
//  Assignment 2
//
//  Created by Juan on 10/20/16.
//  Copyright © 2016 Juan. All rights reserved.
//

/***** System Libraries *****/
#include <iostream>
#include <string>
#include <stdexcept>
#include <stdio.h>

/***** User Libraries *****/
#include "../include/Cmd.hpp"

using namespace std;

Cmd::Cmd(string s, vector<string> f)
:cmd(s), flags(f)
{
}

string Cmd::exec() {
        char buffer[128];
        std::string result = "";
    FILE* pipe = popen(cmd.c_str(), "r");
        if (!pipe) throw std::runtime_error("popen() failed!");
        try {
            while (!feof(pipe)) {
                if (fgets(buffer, 128, pipe) != NULL)
                    result += buffer;
            }
        } catch (...) {
            pclose(pipe);
            throw;
        }
        pclose(pipe);
//        return result;
    return result;
//    }
}
