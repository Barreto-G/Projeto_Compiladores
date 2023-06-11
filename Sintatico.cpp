#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Sintatico.h"

// Função para verificar se um caractere é um espaço em branco
bool ehEspacoEmBranco(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

// Função para consumir espaços em branco
void ConsomeEspacoEmBranco() {
    while (posicao < entrada.length() && ehEspacoEmBranco(entrada[posicao])) {
        posicao++;
    }
}

bool ehPrograma() {

    int aux = posicao;

    while(!ehPrincipal()) {
        posicao = aux;
        if(!ehDefinicaoDeFuncao())
            return false;
        if(posicao >= entrada.length())
            return false;
        posicao++;
        ConsomeEspacoEmBranco();
    }

    while(ehDefinicaoDeFuncao()) {
        if(posicao >= entrada.length())
            return true;
    }
    
    return false;
}

bool ehPrincipal() {

    if(entrada.substr(posicao, 8) != "<TokInt>") {
        return false;
    }

    posicao+= 8;
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 9) != "<TokMain>") {
        return false;
    }

    posicao+= 9;
    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            return false;
    }

    posicao+= 19;
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        while(true) {

            if(!ehListaDeParametros()) {
                break;
            }
        }
    }

    if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        return false;
    }

    posicao += 20;
    ConsomeEspacoEmBranco();

    if(!ehDeclaracaoComposta) {
        return false;
    }

    ConsomeEspacoEmBranco();
    
    return true;
}

bool ehDefinicaoDeFuncao() {

    ConsomeEspacoEmBranco();

    if (!ehEspecificadorDeTipo()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if (!ehIdentificador()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            return false;
    }

    posicao+= 19;
    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        // Reconhecer lista de parâmetros
        while (true) {
            if (!ehEspecificadorDeTipo()) {
                return false;
            }

            ConsomeEspacoEmBranco();

            if (!ehIdentificador()) {
                return false;
            }

            ConsomeEspacoEmBranco();

            if (entrada.substr(posicao, 6) != "<TokV>") {
                posicao += 6;
                ConsomeEspacoEmBranco();
                break;
            }

            posicao++;
            ConsomeEspacoEmBranco();
        }
    }

    if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        return false;
    }

    posicao += 20;
    ConsomeEspacoEmBranco();

    if (!ehDeclaracao()) {
        return false;
    }

    return true;
}

bool ehListaDeParametros() {
    
    if(!ehParametro) {
        return false;
    }

    if(entrada.substr(posicao, 6) != "<TokV>") {
        return true;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    if(!ehListaDeParametros) {
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    return true;
}

bool ehParametro() {

    ConsomeEspacoEmBranco();

    if(!ehEspecificadorDeTipo()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(!ehIdentificador()) {
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    return true;
}

bool ehDeclaracaoComposta() {

    ConsomeEspacoEmBranco();

    if(entrada[posicao] != '{') {
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    if(!ehListaDeDeclaracao()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada[posicao] != '}') {
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    return true;
}

bool ehListaDeDeclaracao(){

    if(!ehDeclaracao()) {
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    if(!ehListaDeDeclaracao && entrada[posicao] != '}')
        return false;

    posicao++;
    ConsomeEspacoEmBranco();

    return true;
}


bool ehDeclaracao() {

    return true;
}

// Função para reconhecer um tipo especificador
bool ehEspecificadorDeTipo() {
    std::string tipos[] = {"INTEIRO", "FLUTUANTE", "CARACTERE", "SIMOUNAO", "VAZIO"};

    for (const std::string& tipo : tipos) {
        if (entrada.substr(posicao, tipo.length()) == tipo) {
            posicao += tipo.length();
            return true;
        }
    }

    return false;
}

// Função para reconhecer uma expressão
bool ReconheceExpressao();

// Função para reconhecer um statement
bool ReconheceDeclaracao() {
    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 2) == "SE") {
        posicao += 2;

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != '(') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (!ReconheceExpressao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != ')') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (!ReconheceDeclaracao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 5) == "SENAO") {
            posicao += 5;

            ConsomeEspacoEmBranco();

            if (!ReconheceDeclaracao()) {
                return false;
            }
        }

        return true;
    }
    else if (entrada.substr(posicao, 8) == "ENQUANTO") {
        posicao += 8;

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != '(') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (!ReconheceExpressao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != ')') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (!ReconheceDeclaracao()) {
            return false;
        }

        return true;
    }
    else if (entrada.substr(posicao, 4) == "PARA") {
        posicao += 4;

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != '(') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (!ReconheceDeclaracao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (!ReconheceExpressao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != ';') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (!ReconheceExpressao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != ')') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (!ReconheceDeclaracao()) {
            return false;
        }

        return true;
    }
    else if (entrada.substr(posicao, 7) == "RETORNA") {
        posicao += 7;

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != ';') {
            if (!ReconheceExpressao()) {
                return false;
            }

            ConsomeEspacoEmBranco();
        }

        if (entrada[posicao] != ';') {
            return false;
        }

        posicao++;

        return true;
    }
    else if (entrada.substr(posicao, 4) == "FACA") {
        posicao += 4;

        ConsomeEspacoEmBranco();

        if (!ReconheceDeclaracao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 7) != "ENQUANTO") {
            return false;
        }

        posicao += 7;

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != '(') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (!ReconheceExpressao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != ')') {
            return false;
        }

        posicao++;

        ConsomeEspacoEmBranco();

        if (entrada[posicao] != ';') {
            return false;
        }

        posicao++;

        return true;
    }
    else {
        // Reconhecer statement como uma expressão seguida de ponto e vírgula
        return ReconheceExpressao();
    }

    return false;
}

bool ehExpressaoPosFixa() {

    if(!ehExpressaoPrimaria()) {
        return false;
    }

    if(entrada.substr(posicao, 18) != "<TokAbreColchetes>" && entrada.substr(posicao, 18) != "<TokAbreColchetes>") {
        return false;
    }
}

bool ehListaDeExpressaoDeArgumento() {

    if(!ehExpressaoDeAtribuicao()) {
        return false;
    }

    if(entrada.substr(posicao, 6) != "<TokV>") {
        return true;
    }

    posicao += 6;
    ConsomeEspacoEmBranco();

    if(!ehListaDeExpressaoDeArgumento()) {
        return false;
    }
    
    return true;
}

bool ehExpressaoPrimaria() {
    
    if(!ehIdentificador() && !ehConstante() && entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
        return false;
    }

    if(entrada.substr(posicao, 19) != "<TokAbreParenteses>") {

        posicao += 19;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoDeAtribuicao()) {
            return false;
        }

        if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            return false;
        }

        posicao += 20;
        ConsomeEspacoEmBranco();
    }

    return true;
}

bool ehConstante() {

    if(!ehInteiro() && !ehFlutuante() && !ehCaractere()) {
        return false;
    }

    return true;
}

bool ehIdentificador() {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 5) != "TokID") {
        return false;
    }

    posicao += 5;
    ConsomeEspacoEmBranco();

    while(entrada[posicao] != '>') {
        posicao++;
        ConsomeEspacoEmBranco();
    }

    posicao++;
    ConsomeEspacoEmBranco();

    return true;
}

bool ehInteiro() {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 9) != "TokNumint") {
        posicao--;
        return false;
    }

    posicao += 9;
    ConsomeEspacoEmBranco();

    while(entrada[posicao] != '>') {
        posicao++;
        ConsomeEspacoEmBranco();
    }

    posicao++;
    ConsomeEspacoEmBranco();

    return true;
}

bool ehFlutuante() {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 11) != "TokNumfloat") {
        posicao--;
        return false;
    }

    posicao += 11;
    ConsomeEspacoEmBranco();

    while(entrada[posicao] != '>') {
        posicao++;
        ConsomeEspacoEmBranco();
    }

    posicao++;
    ConsomeEspacoEmBranco();

    return true;
}

bool ehCaractere() {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 12) != "TokCaractere") {
        posicao--;
        return false;
    }

    posicao += 12;
    ConsomeEspacoEmBranco();

    while(entrada[posicao] != '>') {
        posicao++;
        ConsomeEspacoEmBranco();
    }

    posicao++;
    ConsomeEspacoEmBranco();

    return true;
}


int main() {

    std::ifstream arquivo("teste2.txt"); // Abre o arquivo para leitura

    if (arquivo.is_open()) { // Verifica se o arquivo foi aberto com sucesso
        std::string conteudo((std::istreambuf_iterator<char>(arquivo)), std::istreambuf_iterator<char>());

        // Processa o conteúdo do arquivo
        entrada = conteudo;

        if(ehIdentificador()) {
            std::cout << "Analise bem-sucedida";
        }

        else {
            std::cout << "Analise mal-sucedida";
        }

        arquivo.close(); // Fecha o arquivo
    } 
    else {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
    }

    return 0;
}