#include "Personagem.h"

Personagem::Personagem() {

}

Personagem::~Personagem() {

}

void Personagem::setarNome(string nome_) {
    nome = nome_;
}



void Personagem::mostrarAtributos() {
    cout << "Você possui os seguintes atributos:" << endl;
    cout << "Habilidade: " << habilidade << "/12" << endl;
    cout << "Energia: " << energia << "/24" << endl;
    cout << "Sorte: " << sorte << "/12" << endl;
}

void Personagem::mostrarInventario() {
    inventario_.mostrarInventario();
}


void Personagem::distribuirAtributos() {
    int p = 0;
    mostrarAtributos();
    cout << "Você pode distribuir mais 12 pontos de atributos!" << endl;

    while (p < 12) {
        cout << "Selecione uma opção para aumentar em +1 (" << 12 - p << " pontos restantes)" << endl;
        cout << "[1] Habilidade: " << habilidade << "/12" << endl;
        cout << "[2] Energia: " << energia << "/24" << endl;
        cout << "[3] Sorte: " << sorte << "/12" << endl;
        cout << "> ";
        int opcao; cin >> opcao;

        switch (opcao) {
            case 1:
                if (habilidade < 12) {
                    habilidade++;
                    p++;
                } else {
                    cout << "Pontuação máxima de habilidade atingida, escolha outro atributo" << endl;
                }
                break;
            case 2:
                if (energia < 12) {
                    energia++;
                    p++;
                } else {
                    cout << "Pontuação máxima de energia atingida, escolha outro atributo" << endl;
                }
                break;
            case 3:
                if (sorte < 12) {
                    sorte++;
                    p++;
                } else {
                    cout << "Pontuação máxima de sorte atingida, escolha outro atributo" << endl;
                }
                break;
            default:
                cout << "Escolha uma opção válida!" << endl;
        }
    }
}

string Personagem::getNome() {
    return nome;
}

int Personagem::getEnergia() {
    return energia;
}

int Personagem::getSorte() {
    return sorte;
}

int Personagem::getHabilidade() {
    return habilidade;
}

int Personagem::getQuantidadeItens() {
    inventario_.getQuantidadeItens();
}
