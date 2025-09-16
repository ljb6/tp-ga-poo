//
// Created by Lucca Jaroszeski Becker on 12/09/25.
//

#ifndef TA_POO_MAGO_H
#define TA_POO_MAGO_H

#include <iostream>
#include "Inventario.h"
#include "Personagem.h"
#include <vector>

using namespace std;

class Mago: public Personagem {
public:
    Mago();
    ~Mago();

    void adicionarItensIniciais(const vector<Itens>& itens);
    Inventario inventario_;

private:

};

#endif // TA_POO_MAGO_H
