#include<iostream>
#include "TabelaDeSimbolos.cpp"
#include "Tabela_palavras_chave.cpp"

using namespace std;

int main(){
    /*TabelaDeSimbolos *table = new TabelaDeSimbolos(10);
    table->insere("FLOAT", "c", "10",1,10);
    table->insere("INTEIRO", "caraca", "11",1,10);
    table->insere("INTEIRO", "Burrito", "59",1,10);
    table->percorre();
    delete(table);*/

    TabelaChave *reservadas = new TabelaChave(10);
    reservadas->insere("ENQUANTO", "TokEnquanto", "PALAVRA_RESERVADA");
    reservadas->insere("PARA", "TokPara", "PALAVRA_RESERVADA");
    reservadas->insere("MAIS", "TokMais", "OPERADOR");
    reservadas->insere("MENOS", "TokMenos", "OPERADOR");
    reservadas->percorre();
    delete(reservadas);

}