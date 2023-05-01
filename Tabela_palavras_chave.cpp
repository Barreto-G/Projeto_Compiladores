#include<iostream>
#include "palavra_reservada.cpp"

using namespace std;

#ifndef FUNCAOHASH
#define FUNCAOHASH


const int PRIMO = 37;


int funcaoHash(string s, int M){
    long h = 0;
    for(unsigned i = 0; i<s.length(); i++){
        h = (PRIMO * h + s[i]) % M;
    }
    return h;
}
#endif

#ifndef TABELACHAVES
#define TABELACHAVES

class TabelaChave{

    public:
        TabelaChave(int cap);
        ~TabelaChave();
        void insere(std::string cadeia, std::string categoria, std::string tipo);
        void remove(string cadeia);
        string recupera(string cadeia);
        void percorre();



    private:
        PalavraReservada** elementos; //Define um vetor de ponteiros para os elementos na tabela de simbolos
        int capacidade; //Vai ditar a capacidade da tabela de simbolos

};

TabelaChave::TabelaChave(int cap=100){
    capacidade = cap;
    elementos = new PalavraReservada*[cap];   //define elementos como um vetor de ponteiros de capacidade igual a passada no construtor

    for (int i = 0; i < cap; i++){  //Vai inicializar todas as posicoes da tabela como null
        elementos[i] = NULL;
    }
}

TabelaChave::~TabelaChave(){
     for (int i = 0; i < capacidade; ++i){  //Percorre toda a tabela hash
        PalavraReservada *atual = elementos[i];
        while(atual != NULL){
            PalavraReservada* aux = atual;
            atual = atual->prox;    //Percorre recursivamente todos os elementos da fila
            delete(aux);            //Deleta todos do ultimo ate o comeco
        }
     }
     delete[] elementos;            //libera a memoria do vetor de ponteiros da tabela
}

void TabelaChave::insere(std::string cadeia, std::string categoria, std::string tipo){
    string aux = cadeia;    //A funcao hash eh calculada pela cadeia da palavra chave
    int hash = funcaoHash(aux, capacidade);

    if(recupera(aux)=="NAO ENCONTRADO"){    //se nao encontra o id na tabela, insere um novo
        if(elementos[hash] == NULL){        //Se na posicao nao tiver nada, insere um novo
            elementos[hash] = new PalavraReservada(cadeia, categoria, tipo);
        }
        else{                               //Se ja houver um elemento naquela posicao, percorre toda a lista ligada para inserir o novo token no final dela
            cout<<"Colidiu: "<< aux << endl;
            PalavraReservada* atual = elementos[hash];
            while(atual->prox != NULL){
                atual = atual->prox;
            }
            PalavraReservada* novo = new PalavraReservada(cadeia, categoria, tipo);
            atual->prox = novo;
        }
    }
    else{
        cout<< "Item ja esta na tabela"<< endl;
    }

}

string TabelaChave::recupera(string cadeia){
    string aux = cadeia;
    int hash = funcaoHash(aux, capacidade);
    if (elementos[hash] != NULL && elementos[hash]->cadeia == cadeia){  //Se o id passado esta numa posicao na tabela no inicio da lista, retorna seu id
        return elementos[hash]->cadeia;
    }
    else{       //Senao percorre toda a lista ligada na posicao da hash para encontrar o id, caso a posicao esteja nula ou nao haja esse valor naquela posicao, retorna nao encontrado
        PalavraReservada* atual = elementos[hash];
        
        while (atual != NULL && atual->cadeia != cadeia){
            atual = atual->prox;
        }

        if (atual != NULL && atual->cadeia == cadeia){
            return atual->cadeia;
        }
        else{
            return "NAO ENCONTRADO";
        }
    }
}


void TabelaChave::remove(string cadeia){
    int hash = funcaoHash(cadeia, capacidade);
    if (elementos[hash] != NULL && elementos[hash]->cadeia == cadeia){
        PalavraReservada* aux = elementos[hash];
        elementos[hash] = elementos[hash]->prox;
        delete aux;
    } 
    else {
        PalavraReservada* atual = elementos[hash];
        PalavraReservada* anterior;
        while (atual != NULL && atual->cadeia != cadeia){
            anterior = atual;
            atual = atual->prox;
        }
        if (atual != NULL && atual->cadeia == cadeia){
            anterior->prox = atual->prox;
            delete atual;
        } 
        else {
            cout << "ERRO NA REMOÇÃO" << endl;  //Mais uma excessao a implementar
        }
    }
}

void TabelaChave::percorre(){  //Imprime a toda a tabela hash posicao por posicao, cada linha contendo toda a fila numa determinada posicao hash
    PalavraReservada* atual;
    cout<<"!------------------------!"<< endl;
    for(int i=0; i<capacidade; i++){
        cout<<i<<":";
        atual = elementos[i];
        while(atual!=NULL){
            cout<<"{CADEIA:["<< atual->cadeia<<"] CATEGORIA: ["<<atual->categoria<< "] TIPO:[" << atual->tipo<< "]} -->";
            atual = atual->prox;
        }
        cout<< "NULL"<< endl;
    }
    cout<<"!------------------------!"<< endl;
}

#endif