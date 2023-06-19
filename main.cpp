#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "TabelaDeSimbolos.cpp"
#include "Tabela_palavras_chave.cpp"
#include "Lexico.cpp"
#include "Sintatico.cpp"

using namespace std;

int main(){
    TabelaChave *reservadas = new TabelaChave();
    TabelaDeSimbolos *table = new TabelaDeSimbolos(1000);
    bool programa_valido = true;

    programa_valido = analisarLexico(table, reservadas);
    if (programa_valido == false) {
        remove("teste2.txt");
        return 0;
    }
    cout << "\n\n Analise lexica concluida com sucesso.\n\n";

    if(AnalisarSintatico("teste2.txt", table)) {
        cout << "\nAnalise sintatica concluida com sucesso.\n";
    }

    else {
        cout << "\nAnalise sintatica mal-sucedida.\n";
    }
    
    delete(reservadas);
    delete(table);
    //remove("teste2.txt");
    
    return 0;
}