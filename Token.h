#ifndef ANALIZATOR_LEXICAL_C_TOKEN_H
#define ANALIZATOR_LEXICAL_C_TOKEN_H

#include <iostream>
#include <fstream>
#include "TokenValueMap.h"

using namespace std;

class Token {
    int type, value;

public:
    Token();

    int getType() const;

    void setType(int type);

    int getValue() const;

    void setValue(int value);

    void writeToken(TokenValueMap tokenValueMap, ofstream &fout) const;
};

#endif