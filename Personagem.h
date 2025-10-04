#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <iostream>
#include <string>

#include "Inventario.h"

using namespace std;

class Personagem {
public:
    Personagem();
    ~Personagem();

    string getNome();
    int getHabilidade();
    int getEnergia();
    int getSorte();

    void distribuirAtributos();
    void setarNome(string nome_);
    bool testarSorte();
    void mostrarInventario();
    int getQuantidadeItens();
    vector<vector<string>> getItens();

private:
    string nome;
    int habilidade = 6;
    int energia = 12;
    int sorte = 6;

    void mostrarAtributos();

protected:
    Inventario inventario_;

};

#endif