#include <iostream>
#include <vector>
#include "Tokens.cpp"
#include "palavra_reservada.cpp"

const int maximo_chaves = 8; // Número máximo de chaves em cada nó

// Classe que representa um nó da árvore B
class No_ArvoreSintatica {
    
public:
    bool leaf; // Indica se o nó é uma folha
    std::vector<Token> chaves; // Chaves armazenadas no nó
    std::vector<No_ArvoreSintatica*> filhos; // Ponteiros para os filhos

    // Construtor
    No_ArvoreSintatica(bool ehFolha) : leaf(ehFolha) {}
};

// Classe que representa a árvore B
class ArvoreSintatica {

public:
    No_ArvoreSintatica* raiz; // Ponteiro para a raiz da árvore

    // Construtor
    ArvoreSintatica() : raiz(nullptr) {}

    // Função para buscar uma chave na árvore B
    No_ArvoreSintatica* procura(No_ArvoreSintatica* no, Token chave) {
        if (no == nullptr) {
            return nullptr;
        }

        int i = 0;
        while (i < no->chaves.size() && chave != no->chaves[i]) {
            i++;
        }

        if (i < no->chaves.size() && chave == no->chaves[i]) {
            return no;
        } else if (no->leaf) {
            return nullptr;
        } else {
            return procura(no->filhos[i], chave);
        }
    }

    // Função para inserir uma chave na árvore B
    void insert(Token chave) {
        if (raiz == nullptr) {
            raiz = new No_ArvoreSintatica(true);
            raiz->chaves.push_back(chave);
        } else {
            if (raiz->chaves.size() == maximo_chaves) {
                No_ArvoreSintatica* novaraiz = new No_ArvoreSintatica(false);
                novaraiz->filhos.push_back(raiz);
                separarFilhos(novaraiz, 0, raiz);
                inserirNoNaoCheio(novaraiz, chave);
                raiz = novaraiz;
            } else {
                inserirNoNaoCheio(raiz, chave);
            }
        }
    }

private:
    // Função auxiliar para dividir um filho em um nó pai
    void separarFilhos(No_ArvoreSintatica* no_pai, int endereco_filho, No_ArvoreSintatica* no_filho) {
        No_ArvoreSintatica* novo_no = new No_ArvoreSintatica(no_filho->leaf);

        no_pai->chaves.insert(no_pai->chaves.begin() + endereco_filho, no_filho->chaves[maximo_chaves / 2]);
        no_filho->chaves.erase(no_filho->chaves.begin() + maximo_chaves / 2);

        if (!no_filho->leaf) {
            for (int i = 0; i < maximo_chaves / 2; i++) {
                novo_no->chaves.push_back(no_filho->chaves[maximo_chaves / 2]);
                no_filho->chaves.erase(no_filho->chaves.begin() + maximo_chaves / 2);
            }
        }

        no_pai->filhos.insert(no_pai->filhos.begin() + endereco_filho + 1, novo_no);
    }

    // Função auxiliar para inserir uma chave em um nó não cheio
    void inserirNoNaoCheio(No_ArvoreSintatica* no, Token chave) {
        int i = no->chaves.size() - 1;

        if (no->leaf) {
            no->chaves.push_back(0);

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
                separarFilhos(no, i, no->filhos[i]);
                if (chave > no->chaves[i]) {
                    i++;
                }
            }
            inserirNoNaoCheio(no->filhos[i], chave);
        }
    }
};

int main() {
    ArvoreSintatica Arvore;

    No_ArvoreSintatica* foundno = Arvore.procura(Arvore.raiz, 20);
    if (foundno != nullptr) {
        std::cout << "Chave encontrada!" << std::endl;
    } else {
        std::cout << "Chave não encontrada!" << std::endl;
    }

    return 0;
}
