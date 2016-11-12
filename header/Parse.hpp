//
//  Parse.hpp
//  Assignment 3
//
//  Created by Juan Ruiz on 11/7/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#ifndef Parse_hpp
#define Parse_hpp

#include <vector>

class Parse {
public:
    Parse(char*, const char*);
    char** parse(char*, const char*);
    char* at(int i) { return mem.at(i); }
    std::vector<char*> getVector(){return mem;}
    void print() const;
    unsigned long size() const { return mem.size(); }
private:
    std::vector<char*> mem;
    static const int BUFFER = 100; // maybe have this passed in at a later point
};

#endif /* Parse_hpp */
