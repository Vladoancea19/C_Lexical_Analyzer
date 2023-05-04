#include "Transition.h"

#include <utility>

Transition::Transition(int currentState, int nextState, string inputSymbol) : currentState(currentState), nextState(nextState), inputSymbol(move(inputSymbol)) {}

int Transition::getCurrentState() const {
    return currentState;
}

void Transition::setCurrentState(int currentState) {
    Transition::currentState = currentState;
}

int Transition::getNextState() const {
    return nextState;
}

void Transition::setNextState(int nextState) {
    Transition::nextState = nextState;
}

const string &Transition::getInputSymbol() const {
    return inputSymbol;
}

void Transition::setInputSymbol(const string &inputSymbol) {
    Transition::inputSymbol = inputSymbol;
}
