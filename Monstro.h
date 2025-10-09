#ifndef MONSTRO_H
#define MONSTRO_H

#include <iostream>
#include <string>
#include "Item.h"

using namespace std;

class Monstro {
public:
    Monstro();
    Monstro(string nome_, int habilidade_, int sorte_, int energia_);
    ~Monstro();

    // Getters
    string getNome();
    int getHabilidade();
    int getSorte();
    int getEnergia();
    int getTesouro();
    int getProvisoes();
    Item getItem();

    // Setters
    void setNome(string nome_);
    void setHabilidade(int habilidade_);
    void setSorte(int sorte_);
    void setEnergia(int energia_);
    void setTesouro(int tesouro_);
    void setProvisoes(int provisoes_);
    void setItem(Item item_);

    bool estaVivo();
    void receberDano(int dano);
    void mostrarInfo();

private:
    string nome;
    int habilidade;
    int sorte;
    int energia;
    int tesouro = 0;
    int provisoes = 0;
    Item item_drop = Item("Nenhum", 0, TipoItem::Espada); // padrão
};

#endif