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

    personagem_->setarNome(nome_);
    personagem_->distribuirAtributos();

    cout << "Invetário: " << endl;

    personagem_->mostrarInventario();

    lerCena();
}

void Jogo::lerCena() {
    cenas_visitadas.push_back(cena);

    string caminho = "../cenas/" + to_string(1) + ".txt";

    ifstream inputFile(caminho);

    string line;

    while (getline(inputFile, line)) {
        if (line[0] == '#') {
            cout << "[" << line[1] << "] - " << line.substr(4, line.length() - 1) << endl;
        } else {
            cout << line << endl;
        }
    }

    inputFile.close();

    cout << "Escolha uma opção:\n> ";
    int opcao; cin >> opcao;

    cena = opcao;

    lerCena();
}



