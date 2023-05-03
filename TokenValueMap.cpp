#include "TokenValueMap.h"

TokenValueMap::TokenValueMap() {}

const vector<bool> &TokenValueMap::getIsDistinct() const {
    return isDistinct;
}

void TokenValueMap::setIsDistinct(bool isDistinct) {
    TokenValueMap::isDistinct.push_back(isDistinct);
}

void TokenValueMap::modifyIsDistinct(int position, bool isDistinct) {
    TokenValueMap::isDistinct[position] = isDistinct;
}

const map<int, string> &TokenValueMap::getValuesToStrings() const {
    return valuesToStrings;
}

void TokenValueMap::setValuesToStrings() {
    TokenValueMap::valuesToStrings = map<int, string>();
}

void TokenValueMap::insertValuesToStrings(int key, string val) {
    TokenValueMap::valuesToStrings.insert({key, val});
}
