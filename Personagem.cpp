#include "Personagem.h"

Personagem::Personagem()
{
}

Personagem::Personagem(const string &nome, int habilidade, int energia, int sorte)
    : nome(nome), habilidade(habilidade), energia(energia), sorte(sorte)
{
    energia_maxima = energia;
}

Personagem::~Personagem()
{
}

void Personagem::setarNome(string nome_)
{
    nome = nome_;
}

void Personagem::mostrarAtributos()
{
    cout << "Você possui os seguintes atributos:" << endl;
    cout << "Habilidade: " << habilidade << "/12" << endl;
    cout << "Energia: " << energia << "/24" << endl;
    cout << "Sorte: " << sorte << "/12" << endl;
}

void Personagem::mostrarInventario()
{
    cout << "\n--- Estado do Personagem ---" << endl;
    cout << "Nome: " << nome << endl;
    cout << "Habilidade: " << habilidade << "/12" << endl;
    cout << "Energia: " << energia << "/" << energia_maxima << endl;
    cout << "Sorte: " << sorte << "/12" << endl;
    cout << "Tesouro: " << tesouro << " moedas" << endl;
    cout << "Provisões: " << provisoes << endl;
    cout << "---------------------------" << endl;
    inventario_.mostrarInventario();
}

void Personagem::distribuirAtributos()
{
    int p = 0;
    mostrarAtributos();
    cout << "Você pode distribuir mais 12 pontos de atributos!" << endl;

    while (p < 12)
    {
        cout << "Selecione uma opção para aumentar em +1 (" << 12 - p << " pontos restantes)" << endl;
        cout << "[1] Habilidade: " << habilidade << "/12" << endl;
        cout << "[2] Energia: " << energia << "/24" << endl;
        cout << "[3] Sorte: " << sorte << "/12" << endl;
        cout << "> ";
        int opcao;
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            if (habilidade < 12)
            {
                habilidade++;
                p++;
            }
            else
            {
                cout << "Pontuação máxima de habilidade atingida, escolha outro atributo" << endl;
            }
            break;
        case 2:
                if (energia < 24)
            {
                energia++;
                p++;
                energia_maxima = energia;
            }
            else
            {
                cout << "Pontuação máxima de energia atingida, escolha outro atributo" << endl;
            }
            break;
        case 3:
            if (sorte < 12)
            {
                sorte++;
                p++;
            }
            else
            {
                cout << "Pontuação máxima de sorte atingida, escolha outro atributo" << endl;
            }
            break;
        default:
            cout << "Escolha uma opção válida!" << endl;
        }
    }
    // define a energia máxima com base no valor final de energia escolhido
    energia_maxima = energia;
}

void Personagem::usarProvisao() {
    if (provisoes <= 0) {
        cout << "Você não tem provisões disponíveis." << endl;
        return;
    }
    provisoes -= 1;
    int recupera = 4;
    energia += recupera;
    if (energia > energia_maxima) energia = energia_maxima;
    cout << "Você usou uma provisão e recuperou " << recupera << " pontos de energia. Energia atual: " << energia << "/" << energia_maxima << endl;
}

bool Personagem::testarSorte() {
    if (sorte <= 0) {
        cout << "Você não tem sorte para testar." << endl;
        return false;
    }
    int valor_sorte = sorte;
    int roll = (rand() % 12) + 1; // 1..12
    bool sucesso = (roll <= valor_sorte);
    // decrementa sorte sempre que for usada
    sorte = max(0, sorte - 1);
    cout << "Teste de sorte: rolou " << roll << " contra Sorte atual (antes do uso): " << valor_sorte << ". Resultado: " << (sucesso ? "SUCESSO" : "FALHA") << ".\n";
    return sucesso;
}

string Personagem::getNome()
{
    return nome;
}

int Personagem::getEnergia()
{
    return energia;
}

int Personagem::getSorte()
{
    return sorte;
}

int Personagem::getHabilidade()
{
    return habilidade;
}

int Personagem::getQuantidadeItens()
{
    return inventario_.getQuantidadeItens();
}

vector<vector<string>> Personagem::getItens()
{
    return inventario_.getItens();
}

void Personagem::adicionarTesouro(int valor) {
    tesouro += valor;
}

void Personagem::adicionarProvisoes(int quantidade) {
    provisoes += quantidade;
}

void Personagem::setEnergia(int energia_)
{
    energia = energia_;
}

void Personagem::adicionarItem(Item item_)
{
    inventario_.adicionarItem(item_);
}

int Personagem::getTesouro()
{
    return tesouro;
}

int Personagem::getProvisoes()
{
    return provisoes;
}

int Personagem::getEnergiaMaxima(){
    return energia_maxima;
}

const Inventario& Personagem::getInventario() const {
    return inventario_;
}

bool Personagem::equiparItem(int index) {
    const auto &items = inventario_.getItemObjects();
    if (index < 0 || index >= (int)items.size()) return false;
    const Item &it = items[index];
    if (!it.isUsavelEmCombate()) return false;
    if (it.getTipoEnum() == TipoItem::Espada || it.getTipoEnum() == TipoItem::Cajado) {
        // equipa arma, desequipa antiga automaticamente
        equippedWeaponIndex = index;
        return true;
    }
    if (it.getTipoEnum() == TipoItem::Armadura) {
        // equipa armadura
        equippedArmorIndex = index;
        return true;
    }
    return false;
}

int Personagem::getEquippedWeaponIndex() const { return equippedWeaponIndex; }
int Personagem::getEquippedArmorIndex() const { return equippedArmorIndex; }

int Personagem::getEquippedWeaponFa() const {
    if (equippedWeaponIndex < 0) return 0;
    const auto &it = inventario_.getItemObjects()[equippedWeaponIndex];
    return it.isUsavelEmCombate() ? it.getFaBonus() : 0;
}

int Personagem::getEquippedArmorFa() const {
    if (equippedArmorIndex < 0) return 0;
    const auto &it = inventario_.getItemObjects()[equippedArmorIndex];
    return it.isUsavelEmCombate() ? it.getFaBonus() : 0;
}

int Personagem::getEquippedWeaponDano() const {
    if (equippedWeaponIndex < 0) return 0;
    const auto &it = inventario_.getItemObjects()[equippedWeaponIndex];
    return it.isUsavelEmCombate() ? it.getDano() : 0;
}

int Personagem::getEquippedArmorProt() const {
    if (equippedArmorIndex < 0) return 0;
    const auto &it = inventario_.getItemObjects()[equippedArmorIndex];
        return it.isUsavelEmCombate() ? it.getDano() : 0;
}