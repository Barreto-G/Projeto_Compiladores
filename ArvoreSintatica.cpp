#include <iostream>
#include <vector>

const int maximo_chaves = 3; // Número máximo de chaves em cada nó

// Classe que representa um nó da árvore B
class No_Arvore_B {
    
public:
    bool leaf; // Indica se o nó é uma folha
    std::vector<int> chaves; // Chaves armazenadas no nó
    std::vector<No_Arvore_B*> filhos; // Ponteiros para os filhos

    // Construtor
    No_Arvore_B(bool ehFolha) : leaf(ehFolha) {}

    // Função para imprimir as chaves do nó
    void ImprimeChaves() {
        for (int chave : chaves) {
            std::cout << chave << " ";
        }
        std::cout << std::endl;
    }
};

// Classe que representa a árvore B
class BArvore {

public:
    No_Arvore_B* raiz; // Ponteiro para a raiz da árvore

    // Construtor
    BArvore() : raiz(nullptr) {}

    // Função para buscar uma chave na árvore B
    No_Arvore_B* procura(No_Arvore_B* no, int chave) {
        if (no == nullptr) {
            return nullptr;
        }

        int i = 0;
        while (i < no->chaves.size() && chave > no->chaves[i]) {
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
    void insert(int chave) {
        if (raiz == nullptr) {
            raiz = new No_Arvore_B(true);
            raiz->chaves.push_back(chave);
        } else {
            if (raiz->chaves.size() == maximo_chaves) {
                No_Arvore_B* newraiz = new No_Arvore_B(false);
                newraiz->filhos.push_back(raiz);
                splitChild(newraiz, 0, raiz);
                insertNonFull(newraiz, chave);
                raiz = newraiz;
            } else {
                insertNonFull(raiz, chave);
            }
        }
    }

private:
    // Função auxiliar para dividir um filho em um nó pai
    void splitChild(No_Arvore_B* no_pai, int endereco_filho, No_Arvore_B* no_filho) {
        No_Arvore_B* novo_no = new No_Arvore_B(no_filho->leaf);

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
    void insertNonFull(No_Arvore_B* no, int chave) {
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
                splitChild(no, i, no->filhos[i]);
                if (chave > no->chaves[i]) {
                    i++;
                }
            }
            insertNonFull(no->filhos[i], chave);
        }
    }
};

int main() {
    BArvore Arvore;

    Arvore.insert(10);
    Arvore.insert(20);
    Arvore.insert(5);
    Arvore.insert(30);
    Arvore.insert(15);

    No_Arvore_B* foundno = Arvore.procura(Arvore.raiz, 20);
    if (foundno != nullptr) {
        std::cout << "Chave encontrada!" << std::endl;
        foundno->ImprimeChaves();
    } else {
        std::cout << "Chave não encontrada!" << std::endl;
    }

    return 0;
}
