#include <iostream>
#include <vector>
#include "Tokens.cpp"
#include "palavra_reservada.cpp"

const int maximo_chaves = 8; // Número máximo de chaves em cada nó

// Classe que representa um nó da árvore sintática
class No_ArvoreSintatica {
    
public:
    bool folha; // Indica se o nó é uma folha
    std::vector<Token*> chaves; // Chaves armazenadas no nó
    std::vector<No_ArvoreSintatica*> filhos; // Ponteiros para os filhos

    // Construtor
    No_ArvoreSintatica(bool ehFolha) : folha(ehFolha) {}

    // Função auxiliar para dividir um filho em um nó pai
    void separarFilhos(No_ArvoreSintatica* no_pai, int endereco_filho, No_ArvoreSintatica* no_filho) {
        No_ArvoreSintatica* novo_no = new No_ArvoreSintatica(no_filho->folha);

        no_pai->chaves.insert(no_pai->chaves.begin() + endereco_filho, no_filho->chaves[maximo_chaves / 2]);
        no_filho->chaves.erase(no_filho->chaves.begin() + maximo_chaves / 2);

        if (!no_filho->folha) {
            for (int i = 0; i < maximo_chaves / 2; i++) {
                novo_no->chaves.push_back(no_filho->chaves[maximo_chaves / 2]);
                no_filho->chaves.erase(no_filho->chaves.begin() + maximo_chaves / 2);
            }
        }

        no_pai->filhos.insert(no_pai->filhos.begin() + endereco_filho + 1, novo_no);
    }
};

// Classe que representa a árvore sintática
class ArvoreSintatica {

public:
    No_ArvoreSintatica* raiz; // Ponteiro para a raiz da árvore

    // Construtor
    ArvoreSintatica() : raiz(nullptr) {}

    // Função para buscar uma chave na árvore sintática
    No_ArvoreSintatica* procura(No_ArvoreSintatica* no, Token* chave) {
        if (no == nullptr) {
            return nullptr;
        }

        int i = 0;
        while (i < no->chaves.size() && chave != no->chaves[i]) {
            i++;
        }

        if (i < no->chaves.size() && chave == no->chaves[i]) {
            return no;
        } else if (no->folha) {
            return nullptr;
        } else {
            return procura(no->filhos[i], chave);
        }
    }

    // Função para inserir uma chave na árvore sintática
    void insert(Token* chave) {
        if (raiz == nullptr) {
            raiz = new No_ArvoreSintatica(true);
            raiz->chaves.push_back(chave);
        } else {
            if (raiz->chaves.size() == maximo_chaves) {
                No_ArvoreSintatica* novaraiz = new No_ArvoreSintatica(false);
                novaraiz->filhos.push_back(raiz);
                novaraiz->separarFilhos(novaraiz, 0, raiz);
                inserirNoNaoCheio(novaraiz, chave);
                raiz = novaraiz;
            } else {
                inserirNoNaoCheio(raiz, chave);
            }
        }
    }
    

private:

    // Função auxiliar para inserir uma chave em um nó não cheio
    void inserirNoNaoCheio(No_ArvoreSintatica* no, Token* chave) {
        int i = no->chaves.size() - 1;

        if (no->folha) {
            no->chaves.push_back(nullptr);

            while (i >= 0 && chave < no->chaves[i]) {
                no->chaves[i + 1] = no->chaves[i];
                i--;
            }

            no->chaves[i + 1] = chave;
        } else {
            while (i >= 0 && chave < no->chaves[i]) {
                i--;
            }
            i++;

            if (no->filhos[i]->chaves.size() == maximo_chaves) {
                no->filhos[i]->separarFilhos(no, i, no->filhos[i]);
                if (chave > no->chaves[i]) {
                    i++;
                }
            }
            inserirNoNaoCheio(no->filhos[i], chave);
        }
    }
};

No_ArvoreSintatica* inserirNo(No_ArvoreSintatica* no, Token* chave) {
    if (no == nullptr) {
        no = new No_ArvoreSintatica(true);
        no->chaves.push_back(chave);
        return no;
    }

    if (no->folha) {
        int i = no->chaves.size() - 1;
        no->chaves.push_back(nullptr);

        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }

        no->chaves[i + 1] = chave;
        return no;
    } else {
        int i = no->chaves.size() - 1;
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;

        if (no->filhos[i]->chaves.size() == maximo_chaves) {
            no->filhos[i]->separarFilhos(no, i, no->filhos[i]);
            if (chave > no->chaves[i]) {
                i++;
            }
        }
        no->filhos[i] = inserirNo(no->filhos[i], chave);
        return no;
    }
}
