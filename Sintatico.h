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

bool ehListaDeDeclaracao();

bool ehDeclaracao();

bool ehExpressaoDeAtribuicao();

bool ehEspecificadorDeTipo();

bool ehExpressaoPosFixa();

bool ehListaDeExpressaoDeArgumento();

bool ehExpressaoPrimaria();

bool ehConstante();

bool ehIdentificador();

bool ehInteiro();

bool ehFlutuante();

bool ehCaractere();
