//
// Created by Lucca Jaroszeski Becker on 12/09/25.
//

#ifndef TA_POO_MAGO_H
#define TA_POO_MAGO_H
#include "Inventario.h"
#include "Personagem.h"


using namespace std;

class Mago: public Personagem {
public:
    Mago();
    ~Mago();

private:
    Inventario inventario_;
};


#endif //TA_POO_MAGO_H