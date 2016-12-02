//
//  CD.hpp
//  CD class
//
//  Created by Juan Ruiz on 11/26/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#ifndef CD_hpp
#define CD_hpp

#include <queue>

#include "Commands.hpp"

class CD: public Command {
public:
    CD();
    void setPath(char*);
    void goBack();
    void home();
    virtual int execute();
private:
    std::queue<char*> history;
    char *currentPath; // the current path
    char *oldPath; // the old path;
};

#endif /* CD_hpp */
