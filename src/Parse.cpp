//
//  Parse.cpp
//  Assignment 2
//
//  Created by Juan Ruiz on 10/29/16.
//  Copyright © 2016 Juan. All rights reserved.
//

#include "Parse.hpp"

using namespace std;

Parse::Parse(string s) {
    cmd = parse(s);
    
}

vector<Command*> Parse::parse(string s) {
    vector<Command*> ret;
    
    for(string::const_iterator i = s.begin(); i != s.end(); ++i) {
        //ignore empty white space at the beginning
//        i = find_if(s.begin()), s.end(), isspace);
    }
    
    return ret;
}
