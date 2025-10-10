//
// Created by Lucca Jaroszeski Becker on 10/09/25.
//
#include <fstream>
#include <iostream>
#include <string>
#include "Jogo.h"
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <limits>

#include "Lutador.h"
#include <ctime>
#include "Tela.h"
#include "Mago.h"
#include "Monstro.h"

namespace fs = std::filesystem;

Jogo::Jogo()
{
    personagem_ = nullptr;
    srand((unsigned)time(nullptr));
}

Jogo::~Jogo()
{
    if (personagem_) delete personagem_;
}

void Jogo::novoJogo()
{
    // cria um personagem padrão (Lutador) e configura atributos
    personagem_ = new Lutador();
    string nome;
    cout << "Digite o nome do personagem:\n> ";
    getline(cin >> ws, nome);
    if (nome.empty()) nome = "Hero";
    personagem_->setarNome(nome);
    personagem_->distribuirAtributos();
    cena = 1;
    cenas_visitadas.clear();
    lerCena();
}

void Jogo::setPersonagem()
{
    // stub — atualmente não utilizado
}

void Jogo::lerCena()
{
    // Loop principal de cenas — evita recursão profunda
    bool limpar = true; // controla se devemos limpar a tela antes de exibir a cena
    while (true) {
        if (limpar) Tela::limpar();
        salvarJogo();
        if (std::find(cenas_visitadas.begin(), cenas_visitadas.end(), cena) == cenas_visitadas.end())
            cenas_visitadas.push_back(cena);

        string caminho = "../cenas/" + to_string(cena) + ".txt";
        ifstream inputFile(caminho);
        if (!inputFile.is_open()) {
            cout << "Erro ao abrir a cena " << caminho << endl;
            return;
        }

        string line;
        // lê todo o arquivo em memória para poder limpar/mostrar
        vector<string> lines;
        while (getline(inputFile, line)) lines.push_back(line);
        inputFile.close();

        // encontra a primeira linha significativa
        string firstLine;
        for (auto &ln : lines) {
            auto pos = ln.find_first_not_of(" \t\r\n");
            if (pos != string::npos) { firstLine = ln.substr(pos); break; }
        }

        // se for cena monstro
        if (!firstLine.empty() && tolower((unsigned char)firstLine[0]) == 'm') {
            // parse do monstro a partir das linhas
            string nome;
            int habilidade = 0, sorte = 0, energia = 0, tesouro = 0, provisoes = 0;
            Item item_drop("Nenhum", 0, TipoItem::Espada);
            int cena_vitoria = -1, cena_derrota = -1;

            for (auto &ln : lines) {
                auto l = ln;
                auto b = l.find_first_not_of(" \t\r\n");
                if (b == string::npos) continue;
                l = l.substr(b);
                if (l.rfind("N:", 0) == 0) nome = l.substr(3);
                else if (l.rfind("H:", 0) == 0) try { habilidade = stoi(l.substr(3)); } catch(...) {}
                else if (l.rfind("S:", 0) == 0) try { sorte = stoi(l.substr(3)); } catch(...) {}
                else if (l.rfind("E:", 0) == 0) try { energia = stoi(l.substr(3)); } catch(...) {}
                else if (l.rfind("T:", 0) == 0) try { tesouro = stoi(l.substr(3)); } catch(...) {}
                else if (l.rfind("P:", 0) == 0) try { provisoes = stoi(l.substr(3)); } catch(...) {}
                else if (l.rfind("I:", 0) == 0) {
                    string item_str = l.substr(3);
                    vector<string> partes; string temp; stringstream ss(item_str);
                    while (getline(ss, temp, ';')) partes.push_back(temp);
                    if (partes.size() >= 5) {
                        TipoItem tipo_item = (partes[1] == "w") ? Espada : (partes[1] == "r" ? Armadura : Cajado);
                        try { item_drop = Item(partes[0], stoi(partes[4]), tipo_item); } catch(...) {}
                    }
                } else if (l.find(';') != string::npos) {
                    stringstream ss(l); string parte; vector<int> numeros;
                    while (getline(ss, parte, ';')) try { numeros.push_back(stoi(parte)); } catch(...) {}
                    if (numeros.size() == 2) { cena_vitoria = numeros[0]; cena_derrota = numeros[1]; }
                }
            }

            Monstro monstro(nome, habilidade, sorte, energia);
            monstro.setTesouro(tesouro);
            monstro.setProvisoes(provisoes);
            monstro.setItem(item_drop);

            iniciarBatalha(monstro);

            if (monstro.estaVivo()) {
                cout << "\nVocê foi derrotado...\n";
                if (cena_derrota != -1) { cena = cena_derrota; limpar = true; continue; }
                else { cout << "Fim de jogo!\n"; exit(0); }
            } else {
                cout << "\nVocê venceu a batalha!\n";
                if (cena_vitoria != -1) { cena = cena_vitoria; limpar = true; continue; }
                else { cout << "Você venceu o jogo!\n"; exit(0); }
            }
        }

        // mostrar cena normal
        if (!firstLine.empty()) {
            if (firstLine[0] == '#') {
                if (firstLine.length() >= 4) cout << "[" << firstLine.substr(1,2) << "] - " << firstLine.substr(4) << endl;
                else cout << firstLine << endl;
            } else cout << firstLine << endl;
        }
        for (size_t i = 0; i < lines.size(); ++i) {
            // já mostramos a primeira significativa; mostrar o restante
            if (i == 0) continue; // simples: mostramos tudo abaixo também
            cout << lines[i] << endl;
        }

        // menu de opções na cena
        while (true) {
            cout << "Escolha uma opção:\n";
            cout << "[0] - Sair do jogo (salvar)\n";
            cout << "[-1] - Ver inventário\n";
            cout << "[-2] - Usar provisão (+4 energia)\n";
            cout << "> ";

            string entrada;
            if (!getline(cin, entrada)) { cin.clear(); }
            // se entrada vazia (por causa de leitura anterior), pega de cin >>
            if (entrada.empty()) {
                if (!(cin >> entrada)) { cin.clear(); string dummy; getline(cin, dummy); }
            }

            // trim
            auto b = entrada.find_first_not_of(" \t\r\n");
            if (b == string::npos) { cout << "Entrada inválida. Tente novamente." << endl; continue; }
            auto e = entrada.find_last_not_of(" \t\r\n");
            string token = entrada.substr(b, e - b + 1);

            int opcao = 0;
            try { opcao = stoi(token); } catch(...) { cout << "Entrada inválida. Tente novamente." << endl; continue; }

            if (opcao == 0) { salvarJogo(); cout << "Jogo salvo. Saindo..." << endl; exit(0); }
            if (opcao == -1) {
                // mostra inventário em tela limpa e espera ENTER; depois reexibe a cena sem limpar
                Tela::limpar();
                if (personagem_) personagem_->mostrarInventario();
                cout << "\nPressione ENTER para voltar à cena..." << endl;
                string _dummy;
                getline(cin, _dummy);
                limpar = false;
                break; /* reexibe mesma cena */
            }
            if (opcao == -2) {
                // usar provisão em tela limpa e esperar ENTER para mostrar a cena novamente
                Tela::limpar();
                if (personagem_) personagem_->usarProvisao();
                cout << "\nPressione ENTER para voltar à cena..." << endl;
                string _dummy;
                getline(cin, _dummy);
                limpar = false;
                break;
            }

            if (!verificarCena(opcao)) { cout << "Você já passou por essa cena, escolha uma cena válida!" << endl; continue; }

            cena = opcao;
            limpar = true;
            break; // sai do menu e reexiba próxima cena
        }
        // loop volta e exibe nova cena (ou mesma, se -1 ou -2 foram escolhidos)
    }
    // função encerra aqui; controle de loop é feito internamente
}

// (construtor/destrutor/novoJogo já implementados no topo do arquivo)

// void Jogo::lerCena()
// {
//     salvarJogo();
//     cenas_visitadas.push_back(cena);

//     string caminho = "../cenas/" + to_string(cena) + ".txt";

//     ifstream inputFile(caminho);

//     string line;

//     if (!inputFile.is_open()) {
//     cout << "Erro: não foi possível abrir o arquivo " << caminho << endl;
//     return;
//     }

//     while (getline(inputFile, line))
//     {
//         if (line[0] == '#')
//         {
//             cout << "[" << line.substr(1, 2) << "] - " << line.substr(4, line.length() - 1) << endl;
//         }
//         else
//         {
//             cout << line << endl;
//         }
//     }

//     inputFile.close();

//     cout << "Escolha uma opção:\n> ";
//     int opcao;
//     cin >> opcao;

//     bool proximaCenaValida = verificarCena(opcao);
//     if (!proximaCenaValida)
//     {
//         cout << "Você já passou por essa cena, escolha uma cena válida!" << endl;
//         lerCena();
//     }

//     cena = opcao;
//     lerCena();
// }

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
    // garante que o diretório exista
    fs::create_directories("jogos_salvos");

    if (!personagem_) return;

    string caminho = "jogos_salvos/" + personagem_->getNome() + ".txt";
    ofstream file(caminho);
    if (!file.is_open()) {
        cerr << "Erro ao salvar jogo em: " << caminho << endl;
        return;
    }

    file << "nome\n";
    file << personagem_->getNome() << "\n\n";

    file << "atributos\n";
    file << to_string(personagem_->getHabilidade()) << endl;
    file << to_string(personagem_->getEnergia()) << endl;
    file << to_string(personagem_->getSorte()) << "\n\n";

    file << "itens\n";
    file << to_string(personagem_->getQuantidadeItens()) << endl;
    // escreve itens no formato: nome;tipo;combate;FA;dano separados por espaço
    const auto &itensObjs = personagem_->getInventario().getItemObjects();
    for (const auto &it : itensObjs) {
        char tipo_code = 'c';
        if (it.getTipoEnum() == TipoItem::Armadura) tipo_code = 'r';
        else if (it.getTipoEnum() == TipoItem::Espada || it.getTipoEnum() == TipoItem::Cajado) tipo_code = 'w';
        int combate_flag = it.isUsavelEmCombate() ? 1 : 0;
        int fa_bonus = it.getFaBonus();
        int dano = it.getDano();
        string nome_s = it.getNome();
        for (auto &c : nome_s) if (c == ' ') c = '_';
        file << nome_s << ";" << tipo_code << ";" << combate_flag << ";" << fa_bonus << ";" << dano << " ";
    }
    file << endl << endl;

    file << "provisoes\n";
    file << to_string(personagem_->getProvisoes()) << "\n\n";

    file << "tesouro\n";
    file << to_string(personagem_->getTesouro()) << "\n\n";

    file << "cena_atual" << endl << cena << "\n\n";

    file << "cenas_visitadas" << endl;
    file << cenas_visitadas.size() << endl;
    for (auto c : cenas_visitadas) file << to_string(c) << " ";
    file << endl << endl;

    file << "tipo_personagem\n";
    if (dynamic_cast<Lutador *>(personagem_)) file << "lutador";
    else if (dynamic_cast<Mago *>(personagem_)) file << "mago";

    // equipamento: índices dos itens equipados (weaponIndex armorIndex), -1 se nenhum
    file << "equipamento\n";
    int wi = personagem_->getEquippedWeaponIndex();
    int ai = personagem_->getEquippedArmorIndex();
    file << to_string(wi) << " " << to_string(ai) << "\n";

    file.close();
}

void Jogo::carregarJogo()
{
    string path = "jogos_salvos";

    if (!fs::exists(path) || !fs::is_directory(path)) {
        cout << "Nenhum jogo salvo encontrado (diretório 'jogos_salvos' ausente)." << endl;
        return;
    }

    int counter = 0;
    vector<string> opcoes;

    for (const auto &entry : fs::directory_iterator(path))
    {
        if (!entry.is_regular_file()) continue;
        if (entry.path().extension() != ".txt") continue;
        string nome_arquivo = entry.path().stem().string();
        opcoes.push_back(nome_arquivo);
        cout << "[" << counter << "] " << nome_arquivo << endl;
        counter++;
    }

    if (opcoes.empty()) {
        cout << "Nenhum jogo salvo encontrado." << endl;
        return;
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
    string caminho = "jogos_salvos/" + opcoes[selected] + ".txt";
    ifstream inputFile(caminho);

    string nome;

    int sorte, energia, habilidade;

    int quantidade_itens = 0;
    vector<string> itens_nao_formatado;
    vector<Item> itens;

    int quantidade_cenas = 0;
    int cena_atual;
    vector<int> cenas;

    int loaded_equipped_weapon = -1;
    int loaded_equipped_armor = -1;

    string tipo_personagem;

    if (!inputFile.is_open())
    {
        cout << "Erro ao abrir arquivo: " << caminho << endl;
        return;
    }

    // Parser por seções - mais tolerante a linhas em branco e nomes com espaços
    auto is_number = [](const string &s) {
        if (s.empty()) return false;
        for (char c : s) if (!isdigit((unsigned char)c)) return false;
        return true;
    };

    // lê o arquivo por seções
    while (getline(inputFile, line)) {
        // trim espaços à esquerda/direita
        auto l = line;
        // remove espaços do começo e fim
        auto lbegin = l.find_first_not_of(" \t\r\n");
        if (lbegin == string::npos) continue; // linha vazia
        l = l.substr(lbegin);
        auto lend = l.find_last_not_of(" \t\r\n");
        if (lend != string::npos) l = l.substr(0, lend + 1);

        if (l == "nome") {
            if (getline(inputFile, line)) {
                nome = line;
            }
        } else if (l == "atributos") {
            if (getline(inputFile, line)) {
                try { habilidade = stoi(line); } catch(...) { habilidade = 6; }
            }
            if (getline(inputFile, line)) {
                try { energia = stoi(line); } catch(...) { energia = 12; }
            }
            if (getline(inputFile, line)) {
                try { sorte = stoi(line); } catch(...) { sorte = 6; }
            }
        } else if (l == "itens") {
            if (getline(inputFile, line)) {
                quantidade_itens = 0;
                try { quantidade_itens = stoi(line); } catch(...) { quantidade_itens = 0; }
                if (quantidade_itens > 0) {
                    if (getline(inputFile, line)) {
                        // tokeniza por espaços (preserva múltiplos espaços)
                        vector<string> tokens;
                        string token;
                        for (size_t i = 0; i < line.size(); ++i) {
                            char c = line[i];
                            if (isspace((unsigned char)c)) {
                                if (!token.empty()) { tokens.push_back(token); token.clear(); }
                            } else token.push_back(c);
                        }
                        if (!token.empty()) tokens.push_back(token);

                        // agora processa tokens procurando padrões.
                        // Suporta formato estendido por ';' (nome_sem_espacos;tipo;combate;FA;dano) ou formato legado nome dano tipo
                        // Primeiro, verifica se há ';' nos tokens (formato novo)
                        bool any_semicolon = false;
                        for (const auto &tk : tokens) if (tk.find(';') != string::npos) { any_semicolon = true; break; }
                        if (any_semicolon) {
                            for (const auto &tk : tokens) {
                                if (tk.find(';') == string::npos) continue;
                                vector<string> parts; string tmp; stringstream sst(tk);
                                while (getline(sst, tmp, ';')) parts.push_back(tmp);
                                if (parts.size() >= 5) {
                                    // nome: reverte '_' para espaços
                                    string nome_item = parts[0]; for (auto &c : nome_item) if (c == '_') c = ' ';
                                    string tipo_code = parts[1];
                                    bool combate_flag = (parts[2] == "1");
                                    int fa_v = 0; try { fa_v = stoi(parts[3]); } catch(...) {}
                                    int dano_v = 0; try { dano_v = stoi(parts[4]); } catch(...) {}
                                    // cria item com todos os campos
                                    TipoItem tipo = Espada;
                                    if (tipo_code == "r") tipo = Armadura;
                                    else if (tipo_code == "w") tipo = Espada; // arma
                                    else tipo = Cajado;
                                    Item it(nome_item, dano_v, tipo, combate_flag, fa_v);
                                    itens.push_back(it);
                                }
                            }
                        } else {
                            // formato antigo: nome dano tipo (tokens may contain name with spaces)
                            size_t idx = 0;
                            while (idx < tokens.size()) {
                                // procura próximo token que seja número (dano)
                                size_t j = idx;
                                while (j < tokens.size() && !is_number(tokens[j])) j++;
                                if (j >= tokens.size() || j + 1 >= tokens.size()) break; // formato inesperado
                                // nome é a junção de tokens[idx..j-1]
                                string nome_item = tokens[idx];
                                for (size_t k = idx + 1; k < j; ++k) nome_item += string(" ") + tokens[k];
                                string dano_s = tokens[j];
                                string tipo_s = tokens[j+1];
                                itens_nao_formatado.push_back(nome_item);
                                itens_nao_formatado.push_back(dano_s);
                                itens_nao_formatado.push_back(tipo_s);
                                idx = j + 2;
                            }
                        }
                    }
                }
            }
        } else if (l == "provisoes") {
            if (getline(inputFile, line)) {
                // opcionalmente ignorar
            }
        } else if (l == "tesouro") {
            if (getline(inputFile, line)) {
                // opcionalmente ignorar
            }
        } else if (l == "cena_atual") {
            if (getline(inputFile, line)) {
                try { cena_atual = stoi(line); } catch(...) { cena_atual = 1; }
            }
        } else if (l == "cenas_visitadas") {
            if (getline(inputFile, line)) {
                try { quantidade_cenas = stoi(line); } catch(...) { quantidade_cenas = 0; }
                if (quantidade_cenas > 0) {
                    if (getline(inputFile, line)) {
                        // parse números separados por espaço
                        string cur = "";
                        for (char c : line) {
                            if (isspace((unsigned char)c)) {
                                if (!cur.empty()) { cenas.push_back(stoi(cur)); cur.clear(); }
                            } else cur.push_back(c);
                        }
                        if (!cur.empty()) cenas.push_back(stoi(cur));
                    }
                }
            }
        } else if (l == "tipo_personagem") {
            if (getline(inputFile, line)) tipo_personagem = line;
        } else if (l == "equipamento") {
            if (getline(inputFile, line)) {
                // espera: "wi ai"
                stringstream sline(line);
                int wi = -1, ai = -1; sline >> wi >> ai; loaded_equipped_weapon = wi; loaded_equipped_armor = ai;
            }
        }
    }

    inputFile.close();

    // processa os itens de forma defensiva (formato legado)
    if (!itens_nao_formatado.empty())
    {
        size_t triples = itens_nao_formatado.size() / 3;
        for (size_t t = 0; t < triples; ++t)
        {
            size_t i = t * 3;
            string nome = itens_nao_formatado[i];
            int dano = 0;
            try {
                dano = stoi(itens_nao_formatado[i + 1]);
            } catch (...) {
                // token inválido, pula este item
                cerr << "Aviso: dano inválido para item '" << nome << "': '" << itens_nao_formatado[i+1] << "' - pulando\n";
                continue;
            }
            TipoItem tipo = fromStringToTipoItem(itens_nao_formatado[i + 2]);

            Item item(nome, dano, tipo, false, 0);
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

    // aplica equipamento salvo (indices)
    if (personagem_) {
        if (loaded_equipped_weapon >= 0) personagem_->equiparItem(loaded_equipped_weapon);
        if (loaded_equipped_armor >= 0) personagem_->equiparItem(loaded_equipped_armor);
    }

    // valida cena
    if (cena < 1) {
        cout << "Aviso: cena invalida no save (" << cena << "). Reiniciando para cena 1." << endl;
        cena = 1;
    }
    string cena_path = string("../cenas/") + to_string(cena) + ".txt";
    if (!fs::exists(cena_path)) {
        cout << "Aviso: arquivo de cena não encontrado: " << cena_path << ". Reiniciando para cena 1." << endl;
        cena = 1;
    }

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

//TODO:tem que testar
void Jogo::iniciarBatalha(Monstro& monstro) {
    Tela::limpar();
    cout << "\n=== INÍCIO DA BATALHA ===\n";
    monstro.mostrarInfo();

    while (monstro.estaVivo() && personagem_->getEnergia() > 0) {
        cout << "\nEscolha uma ação:\n";
    cout << "[1] Atacar\n";
    cout << "[2] Fugir\n";
    cout << "[3] Testar Sorte (consome 1 de sorte)\n";
    cout << "[4] Equipar item do inventário\n> ";
        int escolha;
        cin >> escolha;

        if (escolha == 2) {
            cout << "Você fugiu da batalha!\n";
            return;
        }

        if (escolha == 4) {
            Tela::limpar();
            // mostra inventário com índices e marcas
            personagem_->getInventario().mostrarInventario(personagem_->getEquippedWeaponIndex(), personagem_->getEquippedArmorIndex());
            cout << "Digite o índice do item para equipar (ou -1 para cancelar): ";
            int idx; cin >> idx;
            if (idx >= 0) {
                if (personagem_->equiparItem(idx)) cout << "Item equipado." << endl;
                else cout << "Não foi possível equipar esse item." << endl;
            }
            cout << "Pressione ENTER para continuar..." << endl;
            string _dummy; getline(cin, _dummy); getline(cin, _dummy);
            continue; // volta ao loop da batalha
        }

        bool sorte_usada = false;
        bool teste_sorte_sucesso = false;
        if (escolha == 3) {
            sorte_usada = true;
            teste_sorte_sucesso = personagem_->testarSorte();
            // após testar sorte, prossegue para um ataque normal neste turno
        }

        // FA base + equipamento (arma) + roll
        int FA_jogador = personagem_->getHabilidade() + personagem_->getEquippedWeaponFa() + (rand() % 10 + 1);
        int FA_inimigo = monstro.getHabilidade() + (rand() % 10 + 1);
        // monstro item adjustments
        if (monstro.getItem().isUsavelEmCombate()) {
            if (monstro.getItem().getTipoEnum() == TipoItem::Armadura) {
                FA_jogador = max(0, FA_jogador - monstro.getItem().getFaBonus());
            } else {
                FA_inimigo += monstro.getItem().getFaBonus();
            }
        }
        // reduzir o FA do inimigo pela armadura do jogador equipada
        FA_inimigo = FA_inimigo + (rand() % 10 + 1) - personagem_->getEquippedArmorFa();

        // se usou sorte com sucesso, aumenta FA_jogador em 2; se falhou, reduz em 1
        if (sorte_usada) {
            if (teste_sorte_sucesso) FA_jogador += 2;
            else FA_jogador = max(0, FA_jogador - 1);
        }

        cout << "\nSua Força de Ataque: " << FA_jogador;
        cout << " | Força de Ataque do " << monstro.getNome() << ": " << FA_inimigo << endl;

        if (FA_jogador > FA_inimigo) {
            int dano = 2;
            // aplica dano de arma equipada do personagem
            dano += personagem_->getEquippedWeaponDano();
            if (sorte_usada && teste_sorte_sucesso) dano += 2;
            monstro.receberDano(dano);
        } else if (FA_inimigo > FA_jogador) {
            cout << monstro.getNome() << " te atingiu!\n";
            int dano = 2;
            // aplica reducao de dano por armadura equipada do jogador
            dano = max(0, dano - personagem_->getEquippedArmorProt());
            // adiciona dano de arma equipada do monstro (se ele tiver e for arma)
            if (monstro.getItem().isUsavelEmCombate() && (monstro.getItem().getTipoEnum() == TipoItem::Espada || monstro.getItem().getTipoEnum() == TipoItem::Cajado)) {
                dano += monstro.getItem().getDano();
            }
            // se o jogador usou sorte e falhou, recebe dano extra de 1
            if (sorte_usada && !teste_sorte_sucesso) dano += 1;
            personagem_->setEnergia(personagem_->getEnergia() - dano);
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
    personagem_->adicionarItem(monstro.getItem());
    }

    cout << "\nPressione ENTER para continuar...\n";
    cin.ignore();
    cin.get();
}