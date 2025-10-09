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

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::novoJogo()
{
    setPersonagem();
}

void Jogo::setPersonagem()
{
    cout << "Selecione o tipo do personagem:" << endl;
    cout << "[1] - Lutador" << endl;
    cout << "[2] - Mago\n>" << endl;

    int tipo = 0;
    cin >> tipo;

    personagem_ = new Lutador();

    cout << "Digite um nome para o personagem: ";
    string nome_;
    cin >> nome_;
    //
    personagem_->setarNome(nome_);
    //
    // personagem_->mostrarInventario();
    //
    // personagem_->distribuirAtributos();

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

void Jogo::lerCena()
{
    salvarJogo();
    cenas_visitadas.push_back(cena);

    string caminho = "../cenas/" + to_string(cena) + ".txt";

    ifstream inputFile(caminho);

    string line;

    while (getline(inputFile, line))
    {
        if (line[0] == '#')
        {
            cout << "[" << line.substr(1, 2) << "] - " << line.substr(4, line.length() - 1) << endl;
        }
        else
        {
            cout << line << endl;
        }
    }

    inputFile.close();

    cout << "Escolha uma opção:\n> ";
    int opcao;
    cin >> opcao;

    bool proximaCenaValida = verificarCena(opcao);
    if (!proximaCenaValida)
    {
        cout << "Você já passou por essa cena, escolha uma cena válida!" << endl;
        lerCena();
    }

    cena = opcao;
    lerCena();
}

bool Jogo::verificarCena(int cena_)
{
    for (auto it = cenas_visitadas.begin(); it != cenas_visitadas.end(); ++it)
    {
        if (*it == cena_)
            return false;
    }
    return true;
}

void Jogo::salvarJogo()
{
    ofstream file;

    string caminho = "../jogos_salvos/" + personagem_->getNome() + ".txt";
    file.open(caminho);

    file << "nome\n";
    file << personagem_->getNome() << "\n\n";

    file << "atributos\n";
    file << to_string(personagem_->getHabilidade()) << endl;
    file << to_string(personagem_->getEnergia()) << endl;
    file << to_string(personagem_->getSorte()) << "\n\n";

    file << "itens\n";
    file << to_string(personagem_->getQuantidadeItens()) << endl;

    vector<vector<string>> itens = personagem_->getItens();
    for (auto v : itens)
    {
        for (auto i : v)
        {
            file << i << " ";
        }
    }
    file << endl
         << endl;

    // Adicionado como comentário a parte das provisoes e tesouro
    // file<< "provisoes\n";
    // file << to_string(personagem_->getProvisoes()) << "\n\n";

    // file << "tesouro\n";
    // file << to_string(personagem_->getTesouro()) << "\n\n";

    file << "cena_atual" << endl
         << cena << "\n\n";

    file << "cenas_visitadas" << endl;
    file << cenas_visitadas.size() << endl;
    for (auto c : cenas_visitadas)
    {
        file << to_string(c) << " ";
    }
    file << endl
         << endl;

    file << "tipo_personagem\n";
    if (dynamic_cast<Lutador *>(personagem_))
    {
        file << "lutador";
    }
    else if (dynamic_cast<Mago *>(personagem_))
    {
        file << "mago";
    }

    file.close();
}

void Jogo::carregarJogo()
{
    string path = "../jogos_salvos";

    int counter = 0;
    vector<string> opcoes;

    for (const auto &entry : fs::directory_iterator(path))
    {
        string formatted_string = "";

        for (int i = 0; i < entry.path().string().length() - 1; i++)
        {
            if (i > 15 && i < entry.path().string().length() - 4)
            {
                formatted_string += entry.path().string()[i];
            }
        }

        opcoes.push_back(formatted_string); // movido para fora do loop interno
        cout << "[" << counter << "] " << formatted_string << endl;
        counter++;
    }

    int selected;
    cout << "Escolha um jogo salvo\n> " << endl;
    cin >> selected;

    if (selected < 0 || selected >= opcoes.size())
    {
        cout << "Opção inválida!" << endl;
        carregarJogo();
        return;
    }

    string line;
    string caminho = "../jogos_salvos/" + opcoes[selected] + ".txt";
    ifstream inputFile(caminho);

    string nome;

    int sorte, energia, habilidade;

    int quantidade_itens = 0;
    vector<string> itens_nao_formatado;
    vector<Item> itens;

    int quantidade_cenas = 0;
    int cena_atual;
    vector<int> cenas;

    string tipo_personagem;

    if (!inputFile.is_open())
    {
        cout << "Erro ao abrir arquivo: " << caminho << endl;
        return;
    }

    int actual_line = 1;
    while (getline(inputFile, line))
    {
        switch (actual_line)
        {
        case 2:
            nome = line;
            break;
        case 5:
            habilidade = stoi(line);
            break;
        case 6:
            energia = stoi(line);
            break;
        case 7:
            sorte = stoi(line);
            break;
        case 10:
            quantidade_itens = stoi(line);
            break;
        case 11:
            if (quantidade_itens > 0)
            {
                string texto = "";
                for (char c : line)
                {
                    if (c == ' ')
                    {
                        itens_nao_formatado.push_back(texto);
                        texto = "";
                    }
                    else
                    {
                        texto += c;
                    }
                }
            }

            break;
        case 14:
            cena_atual = stoi(line);
            break;
        case 17:
            quantidade_cenas = stoi(line);
            break;
        case 18:
            if (quantidade_cenas > 0)
            {
                string texto = "";
                for (char c : line)
                {
                    if (c == ' ')
                    {
                        cenas.push_back(stoi(texto));
                        texto = "";
                    }
                    else
                    {
                        texto += c;
                    }
                }
            }
            break;
        case 21:
            tipo_personagem = line;
            break;
        }

        actual_line++;
    }

    inputFile.close();

    // processa os itens
    if (quantidade_itens > 0)
    {
        for (int i = 0; i < quantidade_itens * 3; i += 3)
        {
            string nome = itens_nao_formatado[i];
            int dano = stoi(itens_nao_formatado[i + 1]);
            TipoItem tipo = fromStringToTipoItem(itens_nao_formatado[i + 2]);

            Item item(nome, dano, tipo);
            itens.push_back(item);
        }
    }

    if (tipo_personagem == "lutador")
    {
        cout << "Criando lutador " << endl;
        personagem_ = new Lutador(nome, habilidade, energia, sorte, itens);
    }
    // TODO: Ajeitar
    // else if (tipo_personagem == "mago")
    // {
    //     personagem_ = new Mago(nome, habilidade, energia, sorte, itens);
    // }
    else
    {
        personagem_ = new Lutador(nome, habilidade, energia, sorte, itens);
    }

    // aplica estado antes de ler a cena
    cena = cena_atual;
    cenas_visitadas = cenas;

    cout << "carregando..." << endl;
    lerCena();
}

TipoItem Jogo::fromStringToTipoItem(string str)
{
    if (str == "Espada")
        return Espada;
    if (str == "Cajado")
        return Cajado;
    if (str == "Armadura")
        return Armadura;
    return Espada;
}
//
// //TODO:tem que testar
// void Jogo::iniciarBatalha(Monstro& monstro) {
//     cout << "\n=== INÍCIO DA BATALHA ===\n";
//     monstro.mostrarInfo();
//
//     while (monstro.estaVivo() && personagem_->getEnergia() > 0) {
//         cout << "\nEscolha uma ação:\n";
//         cout << "[1] Atacar\n";
//         cout << "[2] Fugir\n> ";
//         int escolha;
//         cin >> escolha;
//
//         if (escolha == 2) {
//             cout << "Você fugiu da batalha!\n";
//             return;
//         }
//
//         int FA_jogador = personagem_->getHabilidade() + (rand() % 10 + 1);
//         int FA_inimigo = monstro.getHabilidade() + (rand() % 10 + 1);
//
//         cout << "\nSua Força de Ataque: " << FA_jogador;
//         cout << " | Força de Ataque do " << monstro.getNome() << ": " << FA_inimigo << endl;
//
//         if (FA_jogador > FA_inimigo) {
//             cout << "Você atingiu o inimigo!\n";
//             monstro.receberDano(2);
//         } else if (FA_inimigo > FA_jogador) {
//             cout << monstro.getNome() << " te atingiu!\n";
//             personagem_->setEnergia(personagem_->getEnergia() - 2);
//         } else {
//             cout << "Ambos erraram o ataque!\n";
//         }
//
//         cout << "Energia do inimigo: " << monstro.getEnergia() << endl;
//         cout << "Sua energia: " << personagem_->getEnergia() << endl;
//     }
//
//     cout << "\n=== FIM DA BATALHA ===\n";
//
//     if (monstro.estaVivo()) {
//         cout << "\nVocê foi derrotado pelo " << monstro.getNome() << "...\n";
//         cout << "Fim de jogo.\n";
//         exit(0);
//     }
//
//     cout << "\nVocê derrotou o " << monstro.getNome() << "!\n";
//
//     // Tesouro
//     if (monstro.getTesouro() > 0) {
//         cout << "Você encontrou " << monstro.getTesouro() << " moedas de ouro!\n";
//         personagem_->adicionarTesouro(monstro.getTesouro());}
//
//     //Provisoes
//     if (monstro.getProvisoes() > 0) {
//         cout << "Você pegou " << monstro.getProvisoes() << " provisões!\n";
//         personagem_->adicionarProvisoes(monstro.getProvisoes());}
//
//     //Drop itens
//     if (monstro.getItem().getNome() != "Nenhum") {
//         cout << "Você obteve o item: " << monstro.getItem().getNome() << "!\n";
//         personagem_->inventario_.adicionarItem(monstro.getItem());
//     }
//
//     //cout << "\nResumo da vitória:\n";
//     //cout << "- Tesouro: " << monstro.getTesouro() << " moedas\n";
//     //cout << "- Provisões: " << monstro.getProvisoes() << endl;
//     //cout << "- Item: " << monstro.getItem().getNome() << endl;
//
//     cout << "\nPressione ENTER para continuar...\n";
//     cin.ignore();
//     cin.get();
//}