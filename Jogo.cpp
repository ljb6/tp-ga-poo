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

// Funcao nova de lerCena deixei comentado para nao perder a original, mas tem que testar essa para validar a parte do monstro
// void Jogo::lerCena() {
//     salvarJogo();
//     cenas_visitadas.push_back(cena);

//     string caminho = "../cenas/" + to_string(cena) + ".txt";

//     ifstream inputFile(caminho);

//     if (!inputFile.is_open()) {
//         cout << "Erro ao abrir a cena " << caminho << endl;
//         return;
//     }

//     string line;
//     getline(inputFile, line);

//     //Cena Monstro
//     if (!line.empty() && line[0] == 'm') {
//         cout << "\nVocê encontrou um MONSTRO!\n";

//         string nome;
//         int habilidade = 0, sorte = 0, energia = 0, tesouro = 0, provisoes = 0;
//         Item item_drop("Nenhum", 0, TipoItem::Espada);
//         int cena_vitoria = -1;
//         int cena_derrota = -1;

//         // Leitura das linhas do arquivo
//         while (getline(inputFile, line)) {
//             if (line.rfind("N:", 0) == 0) nome = line.substr(3);
//             else if (line.rfind("H:", 0) == 0) habilidade = stoi(line.substr(3));
//             else if (line.rfind("S:", 0) == 0) sorte = stoi(line.substr(3));
//             else if (line.rfind("E:", 0) == 0) energia = stoi(line.substr(3));
//             else if (line.rfind("T:", 0) == 0) tesouro = stoi(line.substr(3));
//             else if (line.rfind("P:", 0) == 0) provisoes = stoi(line.substr(3));
//             else if (line.rfind("I:", 0) == 0) {
//                 string item_str = line.substr(3);
//                 vector<string> partes;
//                 string temp;
//                 stringstream ss(item_str);
//                 while (getline(ss, temp, ';')) partes.push_back(temp);

//                 if (partes.size() >= 5) {
//                     TipoItem tipo_item;
//                     if (partes[1] == "w") tipo_item = TipoItem::Espada;
//                     else if (partes[1] == "r") tipo_item = TipoItem::Armadura;
//                     else tipo_item = TipoItem::Cajado;

//                     item_drop = Item(partes[0], stoi(partes[4]), tipo_item);
//                 }
//             }
//             else if (line.find(';') != string::npos) {
//                 stringstream ss(line);
//                 string parte;
//                 vector<int> numeros;
//                 while (getline(ss, parte, ';')) {
//                     numeros.push_back(stoi(parte));
//                 }
//                 if (numeros.size() == 2) {
//                     cena_vitoria = numeros[0];
//                     cena_derrota = numeros[1];
//                 }
//             }
//         }

//         inputFile.close();

//         // Criar o monstro com os dados lidos
//         Monstro monstro(nome, habilidade, sorte, energia);
//         monstro.setTesouro(tesouro);
//         monstro.setProvisoes(provisoes);
//         monstro.setItem(item_drop);

//         // Iniciar a batalha
//         iniciarBatalha(monstro);

//         // Verificar o resultado e redirecionar
//         if (monstro.estaVivo()) {
//             cout << "\nVocê foi derrotado...\n";
//             if (cena_derrota != -1) {
//                 cena = cena_derrota;
//                 lerCena();
//             } else {
//                 cout << "Fim de jogo!\n";
//                 exit(0);
//             }
//         } else {
//             cout << "\nVocê venceu a batalha!\n";
//             if (cena_vitoria != -1) {
//                 cena = cena_vitoria;
//                 lerCena();
//             } else {
//                 cout << "Você venceu o jogo!\n";
//                 exit(0);
//             }
//         }
//         return;
//     }

//     //Cena Normal
//     while (getline(inputFile, line)) {
//         if (line[0] == '#') {
//             cout << "[" << line.substr(1, 2) << "] - " << line.substr(4, line.length() - 1) << endl;
//         } else {
//             cout << line << endl;
//         }
//     }

//     inputFile.close();

//     cout << "Escolha uma opção:\n> ";
//     int opcao; cin >> opcao;

//     bool proximaCenaValida = verificarCena(opcao);
//     if (!proximaCenaValida) {
//         cout << "Você já passou por essa cena, escolha uma cena válida!" << endl;
//         lerCena();
//     }

//     cena = opcao;
//     lerCena();
// }

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
            cout << "Você atingiu o inimigo!\n";
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
        cout << "\nVocê foi derrotado pelo " << monstro.getNome() << "...\n";
        cout << "Fim de jogo.\n";
        exit(0);
    }

    cout << "\nVocê derrotou o " << monstro.getNome() << "!\n";

    // Tesouro
    if (monstro.getTesouro() > 0) {
        cout << "Você encontrou " << monstro.getTesouro() << " moedas de ouro!\n";
        personagem_->adicionarTesouro(monstro.getTesouro());}

    //Provisoes
    if (monstro.getProvisoes() > 0) {
        cout << "Você pegou " << monstro.getProvisoes() << " provisões!\n";
        personagem_->adicionarProvisoes(monstro.getProvisoes());}

    //Drop itens
    if (monstro.getItem().getNome() != "Nenhum") {
        cout << "Você obteve o item: " << monstro.getItem().getNome() << "!\n";
        personagem_->inventario_.adicionarItem(monstro.getItem());
    }

    //cout << "\nResumo da vitória:\n";
    //cout << "- Tesouro: " << monstro.getTesouro() << " moedas\n";
    //cout << "- Provisões: " << monstro.getProvisoes() << endl;
    //cout << "- Item: " << monstro.getItem().getNome() << endl;

    cout << "\nPressione ENTER para continuar...\n";
    cin.ignore();
    cin.get();
}


