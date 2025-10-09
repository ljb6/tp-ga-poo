#ifndef TA_POO_LUTADOR_H
#define TA_POO_LUTADOR_H

#include <iostream>
#include "Personagem.h"

using namespace std;

class Lutador : public Personagem
{
public:
    Lutador();
    Lutador(const string &nome, int habilidade, int energia, int sorte, const vector<Item> &itens);
    ~Lutador();
};

#endif // TA_POO_LUTADOR_H
