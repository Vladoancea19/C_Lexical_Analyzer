#ifndef ANALIZATOR_LEXICAL_C_TRANSITION_H
#define ANALIZATOR_LEXICAL_C_TRANSITION_H

#include <string>

using namespace std;

class Transition {

    int currentState, nextState;
    string inputSymbol;

public:
    Transition(int currentState, int nextState, string inputSymbol);

    [[nodiscard]] int getCurrentState() const;

    void setCurrentState(int currentState);

    [[nodiscard]] int getNextState() const;

    void setNextState(int nextState);

    [[nodiscard]] const string &getInputSymbol() const;

    void setInputSymbol(const string &inputSymbol);
};

#endif
