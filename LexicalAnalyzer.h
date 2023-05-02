#ifndef ANALIZATOR_LEXICAL_C_LEXICALANALYZER_H
#define ANALIZATOR_LEXICAL_C_LEXICALANALYZER_H

#include <vector>
#include "TokenValueMap.h"
#include "Transition.h"
#include "Token.h"

using namespace std;

class LexicalAnalyzer {
    const vector<Transition> transitions = {
            {0, 1, "litera"},
            {1, 1, "litera"},
            {1, 1, "cifra"},
            {0, 2, "cifra"},
            {2, 2, "cifra"},
            {0, 3, "."},
            {2, 3, "."},
            {3, 3, "cifra"},
            {0, 4, "\""},
            {4, 4, "comentariu"},
            {4, 5, "\\"},
            {4, 6, "\""},
            {5, 4, "orice"},
            {0, 7, ";"},
            {7, 7, ";"},
            {0, 8, " "},
            {8, 8, " "},
            {0, 8, "\n"},
            {8, 8, "\n"},
            {0, 9, "/"},
            {9, 10, "/"},
            {10, 10, "neterminal"},
            {10, 11, "\n"},
            {9, 12, "*"},
            {12, 12, "notstar"},
            {12, 13, "*"},
            {13, 12, "notslash"},
            {13, 14, "/"},
            {0, 15, "+"}, // +
            {15, 16, "+"}, // ++
            {15, 17, "="}, // +=
            {0, 18, "-"}, // -
            {18, 19, "-"}, // --
            {18, 19, "="}, // -=
            {0, 21, "nerepetabil"}, // *
            {21, 22, "="}, // *=
            {0, 23, "="}, // =
            {23, 24, "="}, // ==
            {0, 25, ">"}, // >
            {25, 26, "="}, // >=
            {25, 27, ">"}, // >>
            {27, 28, "="}, // >>=
            {0, 29, "<"}, // <
            {29, 30, "="}, // <=
            {29, 31, "<"}, // <<
            {31, 32, "="}, // <<=
            {0, 33, "&"}, // &
            {33, 34, "&"}, // &&
            {33, 35, "="}, // &=
            {0, 36, "|"}, // |
            {36, 37, "|"}, // ||
            {36, 38, "="}, // |=
            {0, 39, "~"}, // ~
            {9, 40, "="}, // /
            {0, 41, "paranteza"}
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
    explicit LexicalAnalyzer(ifstream &fin) : fin(fin) {

        this->positionInFile = 0;

        if (!fin.is_open()) {
            cerr << "Could not open INPUT file" << endl;
        }

        this->tokenValueMap.setNoTokenValues(0);
    }

    TokenValueMap &getTokenValueMap() {
        return tokenValueMap;
    }

    [[nodiscard]] int getPositionInFile() const {
        return positionInFile;
    }

    Token getToken() {
        int poz_curenta = 0, poz_noua = 0;
        string sequence;
        char c;

        fin.seekg(this->positionInFile);

        while (fin.get(c)) {
            this->positionInFile += 1;
            poz_noua = getTransition(poz_curenta, c);
            if (poz_noua == -1) {
                Token token = procesareStareFinala(poz_curenta, sequence);
                if (token.getType() == -1) {
                    return token;
                } else {
                    poz_curenta = 0;
                    sequence = "";
                    this->positionInFile -= 1;
                    fin.seekg(this->positionInFile);
                    if (token.getType() != 7 && token.getType() != 8 && token.getType() != 10) {
                        return token;
                    }
                }
            } else {
                sequence += c;
                poz_curenta = poz_noua;
            }
        }

        fin.close();

        Token token = procesareStareFinala(poz_curenta, sequence);

        if (token.getType() == -1) {
            if(sequence.empty()){
                token.setType(0);
                token.setValue(0);

                return token;
            }
            return token;
        } else {
            if (token.getType() != 7 && token.getType() != 8 && token.getType() != 10) {
                return token;
            } else {
                token.setType(0);
                token.setValue(0);

                return token;
            }
        }
    }

private:

    static bool checkArgument(char argument_test, string argument_tranzitie) {
        if(argument_tranzitie == "litera"){
            if(isalpha(argument_test) || argument_test == '_'){
                return true;
            }
        }
        if(argument_tranzitie == "cifra"){
            if(isdigit(argument_test)){
                return true;
            }
        }
        if(argument_tranzitie == "comentariu"){
            if(argument_test != '\"' && argument_test != '\\'){
                return true;
            }
        }
        if(argument_tranzitie == "orice"){
            return true;
        }
        if(argument_tranzitie == "neterminal"){
            if(argument_test != '\n'){
                return true;
            }
        }
        if(argument_tranzitie == "notstar"){
            if(argument_test != '*'){
                return true;
            }
        }
        if(argument_tranzitie == "notslash"){
            if(argument_test != '/'){
                return true;
            }
        }
        if(argument_tranzitie == "nerepetabil"){
            if(argument_test == '*' || argument_test == '%'
               || argument_test == '!' || argument_test == '^'){
                return true;
            }
        }
        if(argument_tranzitie == "paranteza"){
            if(argument_test == '(' || argument_test == ')'
               || argument_test == '[' || argument_test == ']'
               || argument_test == '{' || argument_test == '}'){
                return true;
            }
        }
        if(argument_tranzitie.length() == 1){
            if(argument_tranzitie[0] == argument_test){
                return true;
            }
        }
        return false;
    }

    int getTransition(int poz_start, char argument){
        for(int i = 0; i < 55; i++){
            if(poz_start == transitions[i].getCurrentState()){
                if(checkArgument(argument, transitions[i].getInputSymbol())){
                    return transitions[i].getNextState();
                }
            }
        }
        return -1;
    }

    bool isKeyword(const string& sequence) {
        for(const auto& keyword : KEYWORDS)
            if(keyword == sequence)
                return true;

        return false;
    }

/*
         * 1 = identificator
         * 2 = keyword
         * 3 = constanta intreaga
         * 4 = constanta in virgula mobila
         * 5 = constanta literara
         * 6 = punctuator
         * 7 = spatiu/sfarsit de linie
         * 8 = comentariu
         * 9 = operator
         * 10 = paranteza
         */
    Token procesareStareFinala(int position, string sequence) {
        Token token = Token();

        if(position == 41) {
            token.setType(10);
            token.setValue(-1);
        }
        else {
            if (position >= 15) {
                token.setType(9);
                token.setValue(-1);
            } else {
                switch (position) {
                    case 1:
                        if (!isKeyword(sequence)) {
                            token.setType(1);
                        } else {
                            token.setType(2);
                        }
                        break;
                    case 2:
                        token.setType(3);
                        break;
                    case 3:
                        token.setType(4);
                        break;
                    case 6:
                        token.setType(5);
                        break;
                    case 7:
                        token.setType(6);
                        break;
                    case 8:
                        token.setType(7);
                        break;
                    case 9:
                        token.setType(9);
                        break;
                    case 11:
                        token.setType(8);
                        break;
                    case 14:
                        token.setType(8);
                        break;
                    default:
                        token.setType(-1);
                        break;
                }
            }
        }

        bool gasit = false;

        for(int i = 0; i < tokenValueMap.getNoTokenValues(); i++){
            if(tokenValueMap.getStringValues()[i] == sequence){
                token.setValue(tokenValueMap.getValues()[i]);
                gasit = true;
            }
        }
        if(!gasit){
            tokenValueMap.setValues(tokenValueMap.getNoTokenValues());
            tokenValueMap.setStringValues(sequence);
            tokenValueMap.setIsDistinct(false);
            token.setValue(tokenValueMap.getNoTokenValues());
            tokenValueMap.setNoTokenValues(tokenValueMap.getNoTokenValues() + 1);
        }

        return token;
    }
};

#endif
