#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(ifstream &fin) : fin(fin) {
    this->positionInFile = 0;

    if (!fin.is_open()) {
        cerr << "Could not open INPUT file" << endl;
    }

    this->tokenValueMap.setValuesToStrings();
}

const vector<Transition> &LexicalAnalyzer::getTransitions() const {
    return transitions;
}

const string *LexicalAnalyzer::getKeywords() const {
    return KEYWORDS;
}

const TokenValueMap &LexicalAnalyzer::getTokenValueMap() const {
    return tokenValueMap;
}

void LexicalAnalyzer::setTokenValueMap(const TokenValueMap &tokenValueMap) {
    LexicalAnalyzer::tokenValueMap = tokenValueMap;
}

int LexicalAnalyzer::getPositionInFile() const {
    return positionInFile;
}

void LexicalAnalyzer::setPositionInFile(int positionInFile) {
    LexicalAnalyzer::positionInFile = positionInFile;
}

Token LexicalAnalyzer::getToken() {
    string sequence;
    char character;
    int currentPosition = 0, nextPosition;

    fin.seekg(this->positionInFile);

    while(fin.get(character)) {
        this->positionInFile++;

        nextPosition = -1;

        for(int i = 0; i < 56; i++){
            if(currentPosition == transitions[i].getCurrentState()) {
                bool isValid = false;

                if(transitions[i].getInputSymbol() == "ch")
                    if(isalpha(character) || character == '_')
                        isValid = true;

                if(transitions[i].getInputSymbol() == "0-9")
                    if(isdigit(character))
                        isValid = true;

                if(transitions[i].getInputSymbol() == "//")
                    if(character != '\"' && character != '\\')
                        isValid = true;

                if(transitions[i].getInputSymbol() == "...")
                    isValid = true;

                if(transitions[i].getInputSymbol() == "!\n")
                    if(character != '\n')
                        isValid = true;

                if(transitions[i].getInputSymbol() == "!*")
                    if(character != '*')
                        isValid = true;

                if(transitions[i].getInputSymbol() == "!/")
                    if(character != '/')
                        isValid = true;

                if(transitions[i].getInputSymbol() == "!%*^")
                    if(character == '!' || character == '%' || character == '*' || character == '^')
                        isValid = true;

                if(transitions[i].getInputSymbol() == "#{[()]}")
                    if(character == '#' || character == '(' || character == ')' || character == '[' || character == ']' || character == '{' || character == '}')
                        isValid = true;

                if(transitions[i].getInputSymbol().length() == 1)
                    if(transitions[i].getInputSymbol()[0] == character)
                        isValid = true;

                if(isValid)
                    nextPosition = transitions[i].getNextState();
            }
        }

        if(nextPosition == -1) {
            Token token = getState(currentPosition, sequence);

            if(token.getType() == -1)
                return token;
            else {
                sequence = "";
                currentPosition = 0;
                this->positionInFile--;

                fin.seekg(this->positionInFile);

                if(token.getType() != 7 && token.getType() != 8)
                    return token;
            }
        }
        else {
            sequence.push_back(character);
            currentPosition = nextPosition;
        }
    }

    fin.close();

    Token token = getState(currentPosition, sequence);

    if(token.getType() == -1) {
        if(sequence.size() == 0) {
            token.setType(0);
            token.setValue(0);

            return token;
        }

        return token;
    }
    else {
        if(token.getType() != 7 && token.getType() != 8 && token.getType() != 10)
            return token;
        else {
            token.setType(0);
            token.setValue(0);

            return token;
        }
    }
}

Token LexicalAnalyzer::getState(int position, const string &sequence) {
    Token token = Token();

    if(position == 41) {
        token.setType(10);
        token.setValue(-1);
    }
    else {
        if(position >= 15) {
            token.setType(9);
            token.setValue(-1);
        }
        else {
            switch(position) {
                case 1: {
                    bool isKeyword = false;

                    for(const auto &keyword: KEYWORDS)
                        if(keyword == sequence)
                            isKeyword = true;

                    if(!isKeyword) {
                        token.setType(1);
                    }
                    else {
                        token.setType(2);
                    }
                    break;
                }
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
                case 14:
                    token.setType(8);
                    break;
                default:
                    token.setType(-1);
                    break;
            }
        }
    }

    bool isDistinct = true;

    for(auto const& [key, val] : tokenValueMap.getValuesToStrings()) {
        if(val == sequence) {
            token.setValue(key);
            isDistinct = false;
        }
    }

    if(isDistinct) {
        tokenValueMap.insertValuesToStrings(tokenValueMap.getValuesToStrings().size(), sequence);
        tokenValueMap.setIsDistinct(false);
        token.setValue(tokenValueMap.getValuesToStrings().size() - 1);
    }

    return token;
}