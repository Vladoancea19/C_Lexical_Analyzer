#include <map>
#include "Token.h"

Token::Token() {
    this->type = -1;
    this->value = -1;
}

int Token::getType() const {
    return type;
}

void Token::setType(int type) {
    Token::type = type;
}

int Token::getValue() const {
    return value;
}

void Token::setValue(int value) {
    Token::value = value;
}

void Token::writeToken(TokenValueMap &tokenValueMap, ofstream &fout) const {
    string tokenType, tokenValue;
    int i = 0;

    for (auto const& [key, val] : tokenValueMap.getValuesToStrings()) {
        if(key == this->value) {
            if(tokenValueMap.getIsDistinct()[i])
                return;
            else {
                tokenValue = val;
                tokenValueMap.modifyIsDistinct(i, true);
            }
        }
        i++;
    }

    switch (this->type) {
        case 1:
            tokenType = "identifier";
            break;
        case 2:
            tokenType = "keyword";
            break;
        case 3:
            tokenType = "integer constant";
            break;
        case 4:
            tokenType = "Floating-point constant";
            break;
        case 5:
            tokenType = "string literal";
            break;
        case 6:
            tokenType = "punctuator";
            break;
        case 9:
            tokenType = "operator";
            break;
        case 10:
            tokenType = "special character";
            break;
        default:
            return;
    }

    fout << tokenType << " - " << tokenValue << endl;
}