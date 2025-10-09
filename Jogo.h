//
// Created by Lucca Jaroszeski Becker on 10/09/25.
//

#ifndef TA_POO_JOGO_H
#define TA_POO_JOGO_H
#include "Inventario.h"
#include "Personagem.h"
#include <iostream>

using namespace std;

class Jogo
{
public:
    Jogo();
    ~Jogo();

    void novoJogo();
    void salvarJogo();
    void carregarJogo();

    void setPersonagem();

    TipoItem fromStringToTipoItem(string str);

private:
    Personagem *personagem_;

    void lerCena();
    bool verificarCena(int cena_);
    vector<int> cenas_visitadas;
    int cena = 1;
};

#endif // TA_POO_JOGO_H