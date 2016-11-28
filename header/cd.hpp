//
//  CD.hpp
//  CD class
//
//  Created by Juan Ruiz on 11/26/16.
//  Copyright © 2016 Juan Ruiz. All rights reserved.
//

#ifndef CD_hpp
#define CD_hpp

#include "Commands.hpp"

class CD: public Command {
public:
    CD();
//    char* getPath();
    int setPath(char*);
    int goBack();
    int home();
    virtual int execute();
private:
    char *newPath; // the current path
    char *oldPath; // the old path;
};

#endif /* CD_hpp */
