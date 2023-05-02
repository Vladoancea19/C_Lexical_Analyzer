#include "TokenValueMap.h"

TokenValueMap::TokenValueMap() {}

int TokenValueMap::getNoTokenValues() const {
    return noTokenValues;
}

void TokenValueMap::setNoTokenValues(int noTokenValues) {
    TokenValueMap::noTokenValues = noTokenValues;
}

const vector<int> &TokenValueMap::getValues() const {
    return values;
}

void TokenValueMap::setValues(int values) {
    TokenValueMap::values.push_back(values);
}

const vector <string> &TokenValueMap::getStringValues() const {
    return stringValues;
}

void TokenValueMap::setStringValues(string stringValues) {
    TokenValueMap::stringValues.push_back(stringValues);
}

const vector<bool> &TokenValueMap::getIsDistinct() const {
    return isDistinct;
}

void TokenValueMap::setIsDistinct(bool isDistinct) {
    TokenValueMap::isDistinct.push_back(isDistinct);
}

void TokenValueMap::modifyIsDistinct(int position, bool isDistinct) {
    TokenValueMap::isDistinct[position] = isDistinct;
}