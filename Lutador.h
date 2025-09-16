#ifndef TA_POO_LUTADOR_H
#define TA_POO_LUTADOR_H

#include <iostream>
#include "Inventario.h"
#include "Personagem.h"
#include <vector>

using namespace std;

class Lutador: public Personagem {
public:
    Lutador();
    ~Lutador();

    void adicionarItensIniciais(const vector<Itens>& itens);
    Inventario inventario_;

private:

};

#endif // TA_POO_LUTADOR_H
