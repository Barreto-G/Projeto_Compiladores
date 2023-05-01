#include<iostream>
#include<vector>


#ifndef TOKEN
#define TOKEN

class Token{
    friend class TabelaDeSimbolos;
    public:

    Token(std::string type, std::string identificador, std::string value, int linha, int coluna);
    void nova_ocorrencia(int linha, int coluna, std::string value);


    private:
        std::string id;
        int contador_posicoes = 0;  //variavel auxiliar para contar as ocorrencias da variavel
        std::string tipo;   //Tipo da variavel fica armazenado aqui
        std::string valor;  //Valor da variavel armazenado no formato de string, depois deve ser convertido para o tipo especificado na variavel tipo
        std::vector<std::vector<int>> posicoes; //vetor que contem outro vetor com os valores das posicoes de coluna e linha onde houve a ocorrencia desse token
        Token* prox = NULL;

};


    Token::Token(std::string type, std::string identificador, std::string value, int linha, int coluna){
        valor = value;
        id = identificador;
        tipo = type;
        std::vector<int> aux;
        aux.push_back(coluna);
        aux.push_back(linha);
        posicoes.push_back(aux);
        contador_posicoes++;
    }

    void Token::nova_ocorrencia(int linha, int coluna, std::string value){
        valor = value;
        std::vector<int> aux;
        aux.push_back(coluna);
        aux.push_back(linha);
        posicoes.push_back(aux);
        contador_posicoes++;
    }

#endif