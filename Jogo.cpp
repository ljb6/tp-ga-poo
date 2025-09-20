//
// Created by Lucca Jaroszeski Becker on 10/09/25.
//
#include <fstream>
#include <iostream>
#include <string>
#include "Jogo.h"

#include "Lutador.h"
#include "Mago.h"


Jogo::Jogo() {

}

Jogo::~Jogo() {

}

void Jogo::novoJogo() {
    setPersonagem();
}

void Jogo::setPersonagem() {
    cout << "Selecione o tipo do personagem:" << endl;
    cout << "[1] - Lutador" << endl;
    cout << "[2] - Mago\n>" << endl;

    int tipo = 0; cin >> tipo;

    personagem_ = new Lutador();

    cout << "Digite um nome para o personagem: ";
    string nome_; cin >> nome_;
    //
    personagem_->setarNome(nome_);
    //
    // personagem_->mostrarInventario();
    //
    // personagem_->distribuirAtributos();

    lerCena();
}

void Jogo::lerCena() {
    salvarJogo();
    cenas_visitadas.push_back(cena);

    string caminho = "../cenas/" + to_string(cena) + ".txt";

    ifstream inputFile(caminho);

    string line;

    while (getline(inputFile, line)) {
        if (line[0] == '#') {
            cout << "[" << line.substr(1, 2) << "] - " << line.substr(4, line.length() - 1) << endl;
        } else {
            cout << line << endl;
        }
    }

    inputFile.close();

    cout << "Escolha uma opção:\n> ";
    int opcao; cin >> opcao;

    bool proximaCenaValida = verificarCena(opcao);
    if (!proximaCenaValida) {
        cout << "Você já passou por essa cena, escolha uma cena válida!" << endl;
        lerCena();
    }

    cena = opcao;
    lerCena();
}

bool Jogo::verificarCena(int cena_) {
    for (auto it = cenas_visitadas.begin(); it != cenas_visitadas.end(); ++it) {
        if (*it == cena_) return false;
    }
    return true;
}

void Jogo::salvarJogo() {
    ofstream file;

    string caminho = "../jogos_salvos/" + personagem_->getNome() + ".txt";
    file.open (caminho);

    file << "nome\n";
    file << personagem_->getNome() << "\n\n";

    file << "atributos\n";
    file << to_string(personagem_->getEnergia()) << endl;
    file << to_string(personagem_->getSorte()) << endl;
    file << to_string(personagem_->getEnergia()) << "\n\n";

    file << "itens\n";
    file << to_string(personagem_->getQuantidadeItens()) << endl;
    file << endl;

    file << "cena_atual" << endl << cena << "\n\n";

    file << "cenas_visitadas" << endl;
    for (auto c : cenas_visitadas) {
        file << to_string(c) << endl;
    }
    file << endl;


    file.close();
}
