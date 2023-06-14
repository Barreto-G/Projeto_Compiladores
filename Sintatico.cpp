#include <iostream>
#include <fstream>
#include <string>
#include "Sintatico.h"

bool ehEspacoEmBranco(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

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
        ConsomeEspacoEmBranco();
    }

    while(ehDefinicaoDeFuncao()) {
        if(posicao >= entrada.length())
            return true;
    }

    if(posicao >= entrada.length())
            return true;
    
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

        if(!ehListaDeParametros()) {
            return false;
        }
    }

    if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        return false;
    }

    posicao += 20;
    ConsomeEspacoEmBranco();

    if(!ehDeclaracaoComposta()) {
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
                posicao ++;
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

bool ehEspecificadorDeTipo() {
    std::string tipos[] = {"<TokInt>", "<TokFloat>", "<TokChar>", "<TokBool>"};

    for (const std::string& tipo : tipos) {
        if (entrada.substr(posicao, tipo.length()) == tipo) {
            posicao += tipo.length();
            ConsomeEspacoEmBranco();
            return true;
        }
    }

    return false;
}

bool ehListaDeParametros() {
    
    if(!ehParametro()) {
        return false;
    }

    if(entrada.substr(posicao, 6) != "<TokV>") {
        return true;
    }

    posicao += 6;
    ConsomeEspacoEmBranco();

    if(!ehListaDeParametros()) {
        return false;
    }

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
    ConsomeEspacoEmBranco();

    return true;
}

bool ehDeclaracaoComposta() {

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokAbreChaves>") {
        return false;
    }

    posicao += 15;
    ConsomeEspacoEmBranco();

    if(!ehListaDeDeclaracao()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 16) != "<TokFechaChaves>") {
        return false;
    }

    posicao += 16;
    ConsomeEspacoEmBranco();

    return true;
}

bool ehListaDeDeclaracao(){

    if(!ehDeclaracao()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(!ehListaDeDeclaracao() && entrada[posicao] != '<')
        return false;

    ConsomeEspacoEmBranco();

    return true;
}

bool ehDeclaracao() {

    if(!ehDeclaracaoDeExpressao() && !ehDeclaracaoComposta() && !ehDeclaracaoDeSelecao() && 
    !ehDeclaracaoDeIteracao() && !ehDeclaracaoDeRetorno()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 7) == "<TokPv>") {
        posicao += 7;
        ConsomeEspacoEmBranco();
    }

    return true;
}

bool ehDeclaracaoDeExpressao() {

    aux = posicao;
    ConsomeEspacoEmBranco();

    if(!ehEspecificadorDeTipo()) {
        posicao = aux;
        ConsomeEspacoEmBranco();
    }

    if(!ehExpressaoDeAtribuicao()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 7) != "<TokPv>") {
        return false;
    }

    ConsomeEspacoEmBranco();

    return true;
}

bool ehDeclaracaoDeSelecao() {

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 7) == "<TokIf>") {

        posicao += 7;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            return false;
        }

        posicao += 19;
        ConsomeEspacoEmBranco();

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            return false;
        }

        posicao += 20;
        ConsomeEspacoEmBranco();

        if (!ehDeclaracao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 9) == "<TokElse>") {

            posicao += 9;
            ConsomeEspacoEmBranco();

            if (!ehDeclaracao()) {
                return false;
            }
        }

        ConsomeEspacoEmBranco();

        return true;
    }

    return false;
}

bool ehDeclaracaoDeIteracao() {

    if (entrada.substr(posicao, 11) == "<TokWhile>") {
        
        posicao += 11;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            return false;
        }

        posicao += 19;

        ConsomeEspacoEmBranco();

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            return false;
        }

        posicao+= 20;

        ConsomeEspacoEmBranco();

        if (!ehDeclaracao()) {
            return false;
        }

        return true;
    }

    else if (entrada.substr(posicao, 8) == "<TokFor>") {

        posicao += 8;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            return false;
        }

        posicao += 19;
        ConsomeEspacoEmBranco();

        if (!ehDeclaracaoDeExpressao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 7) != "<TokPv>") {
            return false;
        }

        posicao += 7;
        ConsomeEspacoEmBranco();

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

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

    return false;
}

bool ehDeclaracaoDeRetorno() {

    if(entrada.substr(posicao, 11) != "<TokReturn>") {
        return false;
    }
    
    posicao += 11;
    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 7) != "<TokPv>") {

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    if (entrada.substr(posicao, 7) != "<TokPv>") {
        return false;
    }

    posicao+= 7;
    ConsomeEspacoEmBranco();

    return true;
}

bool ehExpressaoDeAtribuicao() {

    ConsomeEspacoEmBranco();
    int aux2;
    aux = aux2 = posicao;

    if(!ehExpressaoPosFixa()) {
        posicao = aux;
        if(ehExpressaoLogicaOU()) {
            return true;
        }
    }
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokAtribuicao>") {
        posicao = aux2;
        if(ehExpressaoLogicaOU()) {
            return true;
        }
        return false;
    }

    posicao += 15;
    ConsomeEspacoEmBranco();

    if(!ehExpressaoDeAtribuicao()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    return true;
}

bool ehExpressaoLogicaOU() {

    if(!ehExpressaoLogicaE()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 7) != "<TokOr>") {
        return true;
    }

    else if(entrada.substr(posicao, 7) == "<TokOr>") {

        posicao += 7;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoLogicaOU()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    return true;
}

bool ehExpressaoLogicaE() {

    if(!ehExpressaoDeIgualdade()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 8) != "<TokAnd>") {
        return true;
    }

    else if(entrada.substr(posicao, 8) == "<TokAnd>") {

        posicao += 8;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoLogicaE()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    return true;
}

bool ehExpressaoDeIgualdade() {

    if(!ehExpressaoRelacional()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 16) != "<TokComparacao>" && entrada.substr(posicao, 15) != "<TokDiferente>") {
        return true;
    }

    else if(entrada.substr(posicao, 16) == "<TokComparacao>") {

        posicao += 16;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoDeIgualdade()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    else if(entrada.substr(posicao, 15) == "<TokDiferente>") {

        posicao += 15;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoDeIgualdade()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    return true;
}

bool ehExpressaoRelacional() {

    if(!ehExpressaoAditiva()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 10) != "<TokMaior>" && entrada.substr(posicao, 10) != "<TokMenor>" &&
    entrada.substr(posicao, 15) != "<TokMaiorIgual>" && entrada.substr(posicao, 15) != "<TokMenorIgual>") {
        return true;
    }

    else if(entrada.substr(posicao, 10) == "<TokMaior>") {

        posicao += 10;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoRelacional()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    else if(entrada.substr(posicao, 10) == "<TokMenor>") {

        posicao += 10;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoRelacional()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    else if(entrada.substr(posicao, 15) == "<TokMaiorIgual>") {

        posicao += 15;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoRelacional()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    else if(entrada.substr(posicao, 15) == "<TokMenorIgual>") {

        posicao += 15;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoRelacional()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    return true;
}

bool ehExpressaoAditiva() {

    if(!ehExpressaoMultiplicativa()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 9) != "<TokMais>" && entrada.substr(posicao, 10) != "<TokMenos>") {
        return true;
    }

    else if(entrada.substr(posicao, 9) == "<TokMais>") {

        posicao += 9;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoAditiva()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    else if(entrada.substr(posicao, 10) == "<TokMenos>") {

        posicao += 10;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoAditiva()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    return true;
}

bool ehExpressaoMultiplicativa() {

    if(!ehExpressaoPosFixa()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 10) != "<TokVezes>" && entrada.substr(posicao, 8) != "<TokDiv>") {
        return true;
    }

    else if(entrada.substr(posicao, 10) == "<TokVezes>") {

        posicao += 10;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoMultiplicativa()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    else if(entrada.substr(posicao, 8) == "<TokDiv>") {

        posicao += 8;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoMultiplicativa()) {
            return false;
        }

        ConsomeEspacoEmBranco();
    }

    return true;
}

bool ehExpressaoPosFixa() {

    if(!ehExpressaoPrimaria()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 18) != "<TokAbreColchetes>" && entrada.substr(posicao, 19) != "<TokAbreParenteses>" && 
    entrada.substr(posicao, 6) != "<TokP>") {
        return true;
    }

    while(entrada.substr(posicao, 18) == "<TokAbreColchetes>" || entrada.substr(posicao, 19) == "<TokAbreParenteses>" || 
    entrada.substr(posicao, 6) == "<TokP>") {

        if(entrada.substr(posicao, 18) == "<TokAbreColchetes>") {

            posicao += 18;
            ConsomeEspacoEmBranco();

            if(!ehExpressaoDeAtribuicao()) {
                return false;
            }

            if(entrada.substr(posicao, 19) != "<TokFechaColchetes>") {
                return false;
            }

            posicao += 19;
            ConsomeEspacoEmBranco();
        }

        else if(entrada.substr(posicao, 19) == "<TokAbreParenteses>") {

            posicao += 19;
            ConsomeEspacoEmBranco();

            if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {

                if(!ehListaDeExpressaoDeArgumento()) {
                    return false;
                }

                ConsomeEspacoEmBranco();
            }

            if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
                return false;
            }

            posicao += 20;
            ConsomeEspacoEmBranco();
        }

        else if(entrada.substr(posicao, 6) == "<TokP>") {

            posicao += 6;
            ConsomeEspacoEmBranco();

            if(!ehIdentificador()) {
                return false;
            }

            ConsomeEspacoEmBranco();
            
        }
    }

    return true;

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

    ConsomeEspacoEmBranco();
    
    if(!ehIdentificador() && !ehConstante() && entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
        return false;
    }

    if(entrada.substr(posicao, 19) == "<TokAbreParenteses>") {

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
        posicao--;
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

bool AnalisarSintatico(string nomedoarquivo) {

    std::ifstream arquivo(nomedoarquivo); // Abre o arquivo para leitura

    if (arquivo.is_open()) { // Verifica se o arquivo foi aberto com sucesso
        std::string conteudo((std::istreambuf_iterator<char>(arquivo)), std::istreambuf_iterator<char>());

        // Processa o conteúdo do arquivo
        entrada = conteudo;

        if(ehPrograma()) {
            return true;
        }

        else {
            return false;
        }

        arquivo.close(); // Fecha o arquivo
    } 
    else {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
    }

    return false;
}