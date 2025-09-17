#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <vector>

#include "Item.h"

using namespace std;

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
