#include <iostream>
#include "TabelaDeSimbolos.cpp"

// Variáveis globais
std::string entrada;    // entrada a ser analisado
int posicao = 0;     // Posição atual no entrada
int aux = 0;

bool ehPrograma();

bool ehPrincipal();

bool ehDefinicaoDeFuncao();

bool ehListaDeParametros();

bool ehParametro();

bool ehDeclaracaoComposta();

bool ehEspecificadorDeTipo();

bool ehListaDeDeclaracao();

bool ehDeclaracao();

bool ehDeclaracaoDeExpressao();

bool ehDeclaracaoDeSelecao();

bool ehDeclaracaoDeIteracao();

bool ehDeclaracaoDeRetorno();

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
