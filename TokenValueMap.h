#ifndef ANALIZATOR_LEXICAL_C_TOKENVALUEMAP_H
#define ANALIZATOR_LEXICAL_C_TOKENVALUEMAP_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class TokenValueMap {
    map<int, string> valuesToStrings;
    vector<bool> isDistinct;

public:
    TokenValueMap();

    [[nodiscard]] const map<int, string> &getValuesToStrings() const;

    void setValuesToStrings();

    void insertValuesToStrings(int key, string val);

    [[nodiscard]] const vector<bool> &getIsDistinct() const;

    void setIsDistinct(bool isDistinct);

    void modifyIsDistinct(int position, bool isDistinct);
};

#endif
