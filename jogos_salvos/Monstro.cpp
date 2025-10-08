#include "Monstro.h"

Monstro::Monstro() {}

Monstro::Monstro(string nome_, int habilidade_, int sorte_, int energia_) {
    nome = nome_;
    habilidade = habilidade_;
    sorte = sorte_;
    energia = energia_;
}

Monstro::~Monstro() {}

string Monstro::getNome() { return nome; }
int Monstro::getHabilidade() { return habilidade; }
int Monstro::getSorte() { return sorte; }
int Monstro::getEnergia() { return energia; }
int Monstro::getTesouro() { return tesouro; }
int Monstro::getProvisoes() { return provisoes; }
Item Monstro::getItem() { return item_drop; }

void Monstro::setNome(string nome_) { nome = nome_; }
void Monstro::setHabilidade(int habilidade_) { habilidade = habilidade_; }
void Monstro::setSorte(int sorte_) { sorte = sorte_; }
void Monstro::setEnergia(int energia_) { energia = energia_; }
void Monstro::setTesouro(int tesouro_) { tesouro = tesouro_; }
void Monstro::setProvisoes(int provisoes_) { provisoes = provisoes_; }
void Monstro::setItem(Item item_) { item_drop = item_; }

bool Monstro::estaVivo() {
    return energia > 0;
}

void Monstro::receberDano(int dano) {
    energia -= dano;
    if (energia < 0) energia = 0;
}

void Monstro::mostrarInfo() {
    cout << "\n=== Monstro Encontrado ===\n";
    cout << "Nome: " << nome << endl;
    cout << "Habilidade: " << habilidade << endl;
    cout << "Sorte: " << sorte << endl;
    cout << "Energia: " << energia << endl;
    cout << "Tesouro: " << tesouro << endl;
    cout << "Provisões: " << provisoes << endl;
    cout << "Item Drop: " << item_drop.getNome() << endl;
    cout << "==========================\n";
}
