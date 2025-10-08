//
// Created by Lucca Jaroszeski Becker on 10/09/25.
//
#include <fstream>
#include <iostream>
#include <string>
#include "Jogo.h"
#include <filesystem>

#include "Lutador.h"
#include "Mago.h"
#include "Monstro.h"

namespace fs = std::filesystem;


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

    vector<vector<string>> itens = personagem_->getItens();
    for (auto v : itens) {
        for (auto i : v) {
            file << i << endl;
        }
    }
    file << endl << endl;

    file << "cena_atual" << endl << cena << "\n\n";

    file << "cenas_visitadas" << endl;
    for (auto c : cenas_visitadas) {
        file << to_string(c) << endl;
    }
    file << endl;


    file.close();
}

void Jogo::carregarJogo() {
    string path = "../jogos_salvos";

    int counter = 0;
    vector<string> opcoes;

    for (const auto & entry : fs::directory_iterator(path)) {
        string formatted_string = "";

        for (int i = 0; i < entry.path().string().length() - 1; i++) {
            if (i > 15 && i < entry.path().string().length() - 4) {
                formatted_string += entry.path().string()[i];
                opcoes.push_back(formatted_string);
            }
        }

        cout << "[" << counter << "] " << formatted_string << endl;
        counter++;
    }

    int selected;
    cout << "Escolha um jogo salvo\n> " << endl;
    cin >> selected;

    bool is_valid = false;
    for (auto opcao : opcoes) {
        if (opcao == opcoes[selected - 1]) is_valid = true;
    }

    if (!is_valid) carregarJogo();

    string line;
    string caminho = "../jogos_salvos/" + opcoes[selected - 1] + ".txt";
    ifstream inputFile(caminho);

    // TODO: Adicionar a classe (lutador ou mago)
    string nome;
    int sorte, energia, habilidade;
    string cena;
    vector<string> cenas_visitadas;
    vector<Item> itens;

    // AJEITAR
    personagem_ = new Lutador();

    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
}

//TODO:tem que testar
void Jogo::iniciarBatalha(Monstro& monstro) {
    cout << "\n=== INÍCIO DA BATALHA ===\n";
    monstro.mostrarInfo();

    while (monstro.estaVivo() && personagem_->getEnergia() > 0) {
        cout << "\nEscolha uma ação:\n";
        cout << "[1] Atacar\n";
        cout << "[2] Fugir\n> ";
        int escolha;
        cin >> escolha;

        if (escolha == 2) {
            cout << "Você fugiu da batalha!\n";
            return;
        }

        int FA_jogador = personagem_->getHabilidade() + (rand() % 10 + 1);
        int FA_inimigo = monstro.getHabilidade() + (rand() % 10 + 1);

        cout << "\nSua Força de Ataque: " << FA_jogador;
        cout << " | Força de Ataque do " << monstro.getNome() << ": " << FA_inimigo << endl;

        if (FA_jogador > FA_inimigo) {
            cout << "Você acertou o inimigo!\n";
            monstro.receberDano(2);
        } else if (FA_inimigo > FA_jogador) {
            cout << monstro.getNome() << " te atingiu!\n";
            personagem_->setEnergia(personagem_->getEnergia() - 2);
        } else {
            cout << "Ambos erraram o ataque!\n";
        }

        cout << "Energia do inimigo: " << monstro.getEnergia() << endl;
        cout << "Sua energia: " << personagem_->getEnergia() << endl;
    }

    cout << "\n=== FIM DA BATALHA ===\n";

    if (monstro.estaVivo()) {
        cout << "Você foi derrotado... fim de jogo!\n";
        exit(0);
    } else {
        cout << "Você derrotou o " << monstro.getNome() << "!\n";

        if (monstro.getTesouro() > 0)
            cout << "Você encontrou " << monstro.getTesouro() << " moedas de ouro!\n";
        if (monstro.getProvisoes() > 0)
            cout << "Você pegou " << monstro.getProvisoes() << " provisões!\n";
        if (monstro.getItem().getNome() != "Nenhum")
            cout << "Você obteve o item: " << monstro.getItem().getNome() << "!\n";
    }
}


