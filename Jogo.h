//
// Created by Lucca Jaroszeski Becker on 10/09/25.
//

#ifndef TA_POO_JOGO_H
#define TA_POO_JOGO_H
#include "Inventario.h"
#include "Personagem.h"
#include <iostream>

using namespace std;

class Jogo {
public:
    Jogo();
    ~Jogo();

    void novoJogo();
    void salvarJogo();
    void carregarJogo();

    void setPersonagem();

private:
    Personagem *personagem_;
    Inventario inventario_;

    void lerCena();
    vector<int> cenas_visitadas;
    int cena = 1;
};


#endif //TA_POO_JOGO_H