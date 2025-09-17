#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <vector>

#include "Item.h"

using namespace std;

enum Itens {
    Espada,
    Cajado,
    Armadura_de_Couro,
    Roupa_magica
};

class Inventario {
public:
    Inventario();
    ~Inventario();

    void mostrarInventario();
    void adicionarItem(Item item_);
    //void removerItem();

private:
    vector<Item> itens;
};

#endif
