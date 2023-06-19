#include "Sintatico.h"

bool ehEspacoEmBranco(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

void ConsomeEspacoEmBranco() {
    while (posicao < entrada.length() && ehEspacoEmBranco(entrada[posicao])) {
        posicao++;
    }
}

int AcharLinha(int pos) {

    int i = 0;
    int linha = 1;
    while (i <= pos) {
        if(entrada[i] == '\n') {
            linha++;
        }
        i++;
    }
    return linha;
}

bool ehPrograma() {

    while(true) {

        aux = posicao;
        int cont = 0;

        if(!ehDeclaracaoDeExpressao()) {
            break;
        }
    }

    posicao = aux;
    ConsomeEspacoEmBranco();

    while(true) {

        aux = posicao;
        int cont = 0;

        if(!ehDefinicaoDeFuncao()) {
            break;
        }
    }

    posicao = aux;
    ConsomeEspacoEmBranco();

    if(!ehPrincipal()) {
        cout << "Erro - nao ha funcao PRINCIPAL\n";
    }

    if(posicao >= entrada.length())
            return true;
    
    return false;
}

bool ehPrincipal() {

    ConsomeEspacoEmBranco();

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
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
    }

    else {
        posicao+= 19;
    }
    
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        ehListaDeParametros();
    }

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
    }

    else {
        posicao+= 20;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokAbreChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um {\n";
    }

    posicao += 15;

    if(!ehListaDeDeclaracao()) {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma declaracao\n";
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 16) != "<TokFechaChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um }\n";
    }

    else {
        posicao += 16;
    }
    
    return true;
}

bool ehDefinicaoDeFuncao() {

    if (!ehEspecificadorDeTipoDeFuncao()) {
        return false;
    }

    if (entrada.substr(posicao, 9) == "<TokMain>" || !ehIdentificador()) {
        return false;
    }

    ConsomeEspacoEmBranco();

   if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
    }

    else {
        posicao+= 19;
    }
    
    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        ehListaDeParametros();
    }

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
    }

    else {
        posicao+= 20;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokAbreChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um {\n";
    }

    posicao += 15;

    if(!ehListaDeDeclaracao()) {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma declaracao\n";
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 16) != "<TokFechaChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um }\n";
    }

    else {
        posicao += 16;
    }

    return true;
}

bool ehEspecificadorDeTipo() {

    ConsomeEspacoEmBranco();

    std::string tipos[] = {"<TokInt>", "<TokFloat>", "<TokChar>", "<TokBool>"};

    for (const std::string& tipo : tipos) {
        if (entrada.substr(posicao, tipo.length()) == tipo) {
            posicao += tipo.length();
            return true;
        }
    }

    return false;
}

bool ehEspecificadorDeTipoDeFuncao() {

    ConsomeEspacoEmBranco();

    std::string tipos[] = {"<TokInt>", "<TokFloat>", "<TokChar>", "<TokBool>", "<TokVoid>"};

    for (const std::string& tipo : tipos) {
        if (entrada.substr(posicao, tipo.length()) == tipo) {
            posicao += tipo.length();
            return true;
        }
    }

    return false;
}

bool ehListaDeParametros() {
    
    if(!ehParametro()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 20) == "<TokFechaParenteses>") {
        return true;
    }

    else if(entrada.substr(posicao, 6) != "<TokV>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma virgula separando os parametros\n";
    }

    else{
        posicao += 6;
    }

    if(!ehListaDeParametros()) {
        return false;
    }

    if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
    }

    return true;
}

bool ehParametro() {

    if(!ehEspecificadorDeTipo()) {
        return false;
    }

    if(!ehIdentificador()) {
        return false;
    }

    return true;
}

bool ehDeclaracaoComposta() {

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 15) != "<TokAbreChaves>") {
        return false;
    }

    else {
        posicao+= 15;
    }

    if(!ehListaDeDeclaracao()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 16) != "<TokFechaChaves>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um }\n";
    }

    else {
        posicao+= 16;
    }

    return true;
}

bool ehListaDeDeclaracao(){

    if(!ehDeclaracao()) {
        return false;
    }

    if(!ehListaDeDeclaracao() && entrada[posicao] != '<') {
        return false;
    }

    return true;
}

bool ehDeclaracao() {

    if(!ehDeclaracaoDeExpressao() && !ehDeclaracaoComposta() && !ehDeclaracaoDeSelecao() && 
    !ehDeclaracaoDeIteracao() && !ehDeclaracaoDeRetorno() && !ehDeclaracaoDeRegraDeTres()) {
        return false;
    }

    return true;
}

bool ehDeclaracaoDeExpressao() {

    aux = posicao;

    if(!ehEspecificadorDeTipo()) {
        posicao = aux;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 9) == "<TokMain>") {
        return false;
    }

    if(!ehExpressaoDeAtribuicao()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 7) != "<TokPv>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um ; antes da nova declaracao\n";
    }

    else {
        posicao += 7;
    }

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

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            return false;
        }

        posicao += 20;

        if (!ehDeclaracaoComposta()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 9) == "<TokElse>") {

            posicao += 9;

            if (!ehDeclaracaoComposta()) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool ehDeclaracaoDeIteracao() {

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 10) == "<TokWhile>") {
        
        posicao += 10;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
        }

        else {
            posicao+= 19;
        }

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
        }

        else {
            posicao+= 20;
        }

        if (!ehDeclaracaoComposta()) {
            return false;
        }

        return true;
    }

    else if (entrada.substr(posicao, 8) == "<TokFor>") {

        posicao += 8;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
        }

        else {
            posicao+= 19;
        }

        if (!ehDeclaracaoDeExpressao()) {
            return false;
        }

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 7) != "<TokPv>") {
            return false;
        }

        posicao += 7;

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
        }

        else {
            posicao+= 20;
        }

        if (!ehDeclaracaoComposta()) {
            return false;
        }

        return true;
    }

    return false;
}

bool ehDeclaracaoDeRetorno() {

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 11) != "<TokReturn>") {
        return false;
    }
    
    posicao += 11;
    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 7) != "<TokPv>") {

        if (!ehExpressaoDeAtribuicao()) {
            return false;
        }
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 7) != "<TokPv>") {
        cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um ;\n";
        return false;
    }

    else {
        posicao += 7;
    }

    return true;
}

bool ehDeclaracaoDeRegraDeTres() {

    ConsomeEspacoEmBranco();

    if (entrada.substr(posicao, 16) == "<TokRegraDeTres>") {

        posicao += 16;
        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 19) != "<TokAbreParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um (\n";
        }

        else {
            posicao+= 19;
        }

        if (!ehExpressaoPrimaria()) {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um identificador, constante ou expressao\n";
        }

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 6) != "<TokV>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma virgula separando os parametros\n";
        }

        else{
            posicao += 6;
        }

        if (!ehExpressaoPrimaria()) {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um identificador, constante ou expressao\n";
        }

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 6) != "<TokV>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado uma virgula separando os parametros\n";
        }

        else{
            posicao += 6;
        }

        if (!ehExpressaoPrimaria()) {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um identificador, constante ou expressao\n";
        }

        ConsomeEspacoEmBranco();

        if (entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
        }

        else {
            posicao+= 20;
        }

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 7) != "<TokPv>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um ;\n";
        }

        else{
            posicao += 7;
        }
    }

    else {
        return false;
    }

    return true;
}

bool ehExpressaoDeAtribuicao() {

    int aux2;
    aux = aux2 = posicao;

    if(!ehExpressaoPosFixa()) {

        posicao = aux;

        if(ehExpressaoLogicaOU()) {
            return true;
        }

        return false;
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

    if(!ehExpressaoDeAtribuicao()) {
        return false;
    }

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

        if(!ehExpressaoLogicaOU()) {
            return false;
        }
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

        if(!ehExpressaoLogicaE()) {
            return false;
        }
    }

    return true;
}

bool ehExpressaoDeIgualdade() {

    if(!ehExpressaoRelacional()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 15) != "<TokComparacao>" && entrada.substr(posicao, 14) != "<TokDiferente>") {
        return true;
    }

    else if(entrada.substr(posicao, 15) == "<TokComparacao>") {

        posicao += 15;
        ConsomeEspacoEmBranco();

        if(!ehExpressaoDeIgualdade()) {
            return false;
        }
    }

    else {

        posicao += 14;

        if(!ehExpressaoDeIgualdade()) {
            return false;
        }
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

        if(!ehExpressaoRelacional()) {
            return false;
        }
    }

    else if(entrada.substr(posicao, 10) == "<TokMenor>") {

        posicao += 10;

        if(!ehExpressaoRelacional()) {
            return false;
        }
    }

    else if(entrada.substr(posicao, 15) == "<TokMaiorIgual>") {

        posicao += 15;

        if(!ehExpressaoRelacional()) {
            return false;
        }
    }

    else {

        posicao += 15;

        if(!ehExpressaoRelacional()) {
            return false;
        }
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

        if(!ehExpressaoAditiva()) {
            return false;
        }
    }

    else {

        posicao += 10;

        if(!ehExpressaoAditiva()) {
            return false;
        }
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

        if(!ehExpressaoMultiplicativa()) {
            return false;
        }
    }

    else {

        posicao += 8;

        if(!ehExpressaoMultiplicativa()) {
            return false;
        }
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

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 18) == "<TokAbreColchetes>") {

            posicao += 18;

            if(!ehExpressaoDeAtribuicao()) {
                return false;
            }

            ConsomeEspacoEmBranco();

            if(entrada.substr(posicao, 19) != "<TokFechaColchetes>") {
                cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um ]\n";
            }

            else {
                posicao += 19;
            }
        }

        else if(entrada.substr(posicao, 19) == "<TokAbreParenteses>") {

            posicao += 19;
            ConsomeEspacoEmBranco();

            if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {

                if(!ehListaDeExpressaoDeArgumento()) {
                    return false;
                }
            }

            ConsomeEspacoEmBranco();

            if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
            }

            else {
                posicao += 20;
            }
        }

        else {

            posicao += 6;

            if(!ehIdentificador()) {
                return false;
            }
        }
    }

    return true;

}

bool ehListaDeExpressaoDeArgumento() {

    if(!ehExpressaoDeAtribuicao()) {
        return false;
    }

    ConsomeEspacoEmBranco();

    if(entrada.substr(posicao, 6) != "<TokV>") {
        return true;
    }

    posicao += 6;

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

        if(!ehExpressaoDeAtribuicao()) {
            return false;
        }

        ConsomeEspacoEmBranco();

        if(entrada.substr(posicao, 20) != "<TokFechaParenteses>") {
            cout << "Erro - linha " << AcharLinha(posicao) << ": esperado um )\n";
        }

        else {
            posicao += 20;
        }
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

    if(entrada.substr(posicao, 5) != "TokID") {
        posicao--;
        return false;
    }

    posicao += 5;

    while(entrada[posicao] != '>') {
        posicao++;
    }

    posicao++;

    return true;
}

bool ehInteiro() {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;

    if(entrada.substr(posicao, 9) != "TokNumint") {
        posicao--;
        return false;
    }

    posicao += 9;

    while(entrada[posicao] != '>') {
        posicao++;
    }

    posicao++;

    return true;
}

bool ehFlutuante() {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;

    if(entrada.substr(posicao, 11) != "TokNumfloat") {
        posicao--;
        return false;
    }

    posicao += 11;

    while(entrada[posicao] != '>') {
        posicao++;
    }

    posicao++;

    return true;
}

bool ehCaractere() {

    ConsomeEspacoEmBranco();

    if (entrada[posicao] != '<'){
        return false;
    }

    posicao++;

    if(entrada.substr(posicao, 12) != "TokCaractere") {
        posicao--;
        return false;
    }

    posicao += 12;

    while(entrada[posicao] != '>') {
        posicao++;
    }

    posicao++;

    return true;
}

bool AnalisarSintatico(string nomedoarquivo, TabelaDeSimbolos* table) {

    std::ifstream arquivo(nomedoarquivo); // Abre o arquivo para leitura

    ArvoreSintatica* Arvore = new ArvoreSintatica();

    if (arquivo.is_open()) { // Verifica se o arquivo foi aberto com sucesso
        std::string conteudo((std::istreambuf_iterator<char>(arquivo)), std::istreambuf_iterator<char>());

        // Processa o conteúdo do arquivo
        entrada = conteudo;
        tabela = table;

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