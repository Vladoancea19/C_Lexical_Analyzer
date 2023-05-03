#ifndef ANALIZATOR_LEXICAL_C_LEXICALANALYZER_H
#define ANALIZATOR_LEXICAL_C_LEXICALANALYZER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TokenValueMap.h"
#include "Transition.h"
#include "Token.h"

class LexicalAnalyzer {
    const vector<Transition> transitions = {
            {0, 1, "ch"},
            {0, 2, "0-9"},
            {0, 3, "."},
            {0, 4, "\""},
            {0, 7, ";"},
            {0, 8, " "},
            {0, 8, "\n"},
            {0, 9, "/"},
            {0, 15, "+"},
            {0, 18, "-"},
            {0, 21, "!%*^"},
            {0, 23, "="},
            {0, 29, "<"},
            {0, 25, ">"},
            {0, 33, "&"},
            {0, 36, "|"},
            {0, 38, ":"},
            {0, 39, "~"},
            {0, 41, "#{[()]}"},
            {1, 1, "ch"},
            {1, 1, "0-9"},
            {2, 2, "0-9"},
            {2, 3, "."},
            {3, 3, "0-9"},
            {4, 4, "//"},
            {4, 5, "\\"},
            {4, 6, "\""},
            {5, 4, "..."},
            {7, 7, ";"},
            {8, 8, " "},
            {8, 8, "\n"},
            {9, 10, "/"},
            {9, 12, "*"},
            {9, 40, "="},
            {10, 10, "!\n"},
            {10, 11, "\n"},
            {12, 12, "!*"},
            {12, 13, "*"},
            {13, 12, "!/"},
            {13, 14, "/"},
            {15, 16, "+"},
            {15, 17, "="},
            {18, 19, "-"},
            {18, 19, "="},
            {21, 22, "="},
            {23, 24, "="},
            {25, 26, "="},
            {25, 27, ">"},
            {27, 28, "="},
            {29, 30, "="},
            {29, 31, "<"},
            {31, 32, "="},
            {33, 34, "&"},
            {33, 35, "="},
            {36, 37, "|"},
            {36, 38, "="}
    };

    const string KEYWORDS[32] = {
            "auto", "double", "int", "struct",
            "break", "else", "long", "switch",
            "case", "enum", "register", "typedef",
            "char", "extern", "return", "union",
            "continue", "for", "signed", "void",
            "do", "if", "static", "while",
            "default", "goto", "sizeof", "volatile",
            "const", "float", "short", "unsigned"
    };

    TokenValueMap tokenValueMap;

    int positionInFile;

    ifstream &fin;

public:
    explicit LexicalAnalyzer(ifstream &fin);

    [[nodiscard]] const vector<Transition> &getTransitions() const;

    [[nodiscard]] const string *getKeywords() const;

    [[nodiscard]] const TokenValueMap &getTokenValueMap() const;

    void setTokenValueMap(const TokenValueMap &tokenValueMap);

    [[nodiscard]] int getPositionInFile() const;

    void setPositionInFile(int positionInFile);

    Token getToken();

private:

    Token getState(int position, const string& sequence);
};

#endif
