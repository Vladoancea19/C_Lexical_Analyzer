#ifndef ANALIZATOR_LEXICAL_C_TOKENVALUEMAP_H
#define ANALIZATOR_LEXICAL_C_TOKENVALUEMAP_H

#include <vector>
#include <string>

using namespace std;

class TokenValueMap {
    int noTokenValues;
    vector<int> values;
    vector<string> stringValues;
    vector<bool> isDistinct;

public:
    TokenValueMap();

    [[nodiscard]] int getNoTokenValues() const;

    void setNoTokenValues(int noTokenValues);

    [[nodiscard]] const vector<int> &getValues() const;

    void setValues(int values);

    [[nodiscard]] const vector <string> &getStringValues() const;

    void setStringValues(string stringValues);

    [[nodiscard]] const vector<bool> &getIsDistinct() const;

    void setIsDistinct(bool isDistinct);

    void modifyIsDistinct(int position, bool isDistinct);
};

#endif
