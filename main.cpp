/**
 * Implementarea unui analizor lexical pentru un limbaj de programare uzual (Pascal, C, etc., la alegerea studentului).
 * Conventii:
 * 1 = identificator
 * 2 = cuvant cheie
 * 3 = constanta intreaga
 * 4 = constanta in virgula mobila
 * 5 = constanta caracter/sir de caractere
 * 6 = separator
 * 7 = spatiu
 * 8 = comentariu
 * 9 = operator
 * 10 = caracter special
 */

#include <iostream>
#include <string>
#include <fstream>
#include "LexicalAnalyzer.h"

int main() {
    ifstream fin("C:\\Z\\CLion\\C_Lexical_Analyzer\\input.txt", ifstream::in);
    ofstream fout("C:\\Z\\CLion\\C_Lexical_Analyzer\\output.txt", ofstream::out);

    LexicalAnalyzer lexicalAnalyzer = LexicalAnalyzer(fin);
    Token token;

    if (!fout.is_open()) {
        std::cerr << "Could not open OUTPUT file" << endl;
        return 1;
    }

    do {
        token = lexicalAnalyzer.getToken();

        if(token.getType() != -1)
            token.writeToken(const_cast<TokenValueMap &>(lexicalAnalyzer.getTokenValueMap()), fout);
        else {
            fout << "eroare lexicala" << " - " << lexicalAnalyzer.getPositionInFile();
            break;
        }

    } while(token.getType() > 0);

    fout.close();

    return 0;
}