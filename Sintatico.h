#include <iostream>
#include <fstream>
#include <string>
#include "TabelaDeSimbolos.cpp"
#include "Tabela_palavras_chave.cpp"
#include "ArvoreSintatica.cpp"

using namespace std;

// Variáveis globais
string entrada;    // entrada a ser analisada
int posicao = 0;     // Posição atual no entrada
int aux = 0;    //Variável auxiliar
int valor = 0;
TabelaDeSimbolos* tabela;

bool ehEspacoEmBranco(char c);

void ConsomeEspacoEmBranco();

int AcharLinha(int pos);

bool ehPrograma();

bool ehPrincipal();

bool ehDefinicaoDeFuncao();

bool ehListaDeParametros();

bool ehParametro();

bool ehDeclaracaoComposta();

bool ehEspecificadorDeTipo();

bool ehEspecificadorDeTipoDeFuncao();

bool ehListaDeDeclaracao();

bool ehDeclaracao();

bool ehDeclaracaoDeExpressao();

bool ehDeclaracaoDeSelecao();

bool ehDeclaracaoDeIteracao();

bool ehDeclaracaoDeRetorno();

bool ehDeclaracaoDeRegraDeTres();

bool ehExpressaoDeAtribuicao();

bool ehExpressaoLogicaOU();

bool ehExpressaoLogicaE();

bool ehExpressaoDeIgualdade();

bool ehExpressaoRelacional();

bool ehExpressaoAditiva();

bool ehExpressaoMultiplicativa();

bool ehExpressaoPosFixa();

bool ehListaDeExpressaoDeArgumento();

bool ehExpressaoPrimaria();

bool ehConstante();

bool ehIdentificador();

bool ehInteiro();

bool ehFlutuante();

bool ehCaractere();
