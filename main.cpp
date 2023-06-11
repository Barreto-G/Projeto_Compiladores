#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include "TabelaDeSimbolos.cpp"
#include "Tabela_palavras_chave.cpp"
#include "Lexico.cpp"

using namespace std;

int main(){
    TabelaChave *reservadas = new TabelaChave();
    TabelaDeSimbolos *table = new TabelaDeSimbolos(1000);
    bool programa_valido = true;

    programa_valido = analisarLexico(table, reservadas);
    if (programa_valido == false) return 0;
    cout << "\n\n ANALISE LEXICA CONCLUIDA: NENHUM ERRO ENCONTRADO\n\n";

    
    delete(reservadas);
    delete(table);
    //remove("teste2.txt");
    
    return 0;
}