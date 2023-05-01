#include<iostream>
#include "TabelaDeSimbolos.cpp"

using namespace std;

int main(){
    TabelaDeSimbolos *table = new TabelaDeSimbolos(10);


    table->insere("FLOAT", "c", "10",1,10);

    table->insere("INTEIRO", "caraca", "11",1,10);

    table->insere("INTEIRO", "Burrito", "59",1,10);


    table->percorre();

    delete(table);
}