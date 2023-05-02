#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

int main() {
    ifstream fin("D:\\CLion\\C_Lexical_Analyzer\\input.txt", ifstream::in);
    ofstream fout("D:\\CLion\\C_Lexical_Analyzer\\output.txt", ofstream::out);

    LexicalAnalyzer lexicalAnalyzer = LexicalAnalyzer(fin);
    Token token;

    if (!fout.is_open()) {
        std::cerr << "Could not open OUTPUT file" << endl;
        return 1;
    }

    do {
        token = lexicalAnalyzer.getToken();

        if(token.getType() != -1)
            token.writeToken(lexicalAnalyzer.getTokenValueMap(), fout);
        else {
            fout << "eroare lexicala" << " - " << lexicalAnalyzer.getPositionInFile();
            break;
        }

    } while(token.getType() > 0);

    fout.close();

    return 0;
}