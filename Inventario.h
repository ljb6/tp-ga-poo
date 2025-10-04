#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <vector>
#include <string>

#include "Item.h"

using namespace std;

class Inventario {
public:
    Inventario();
    ~Inventario();

    void mostrarInventario();
    int getQuantidadeItens();
    void adicionarItem(Item item_);
    vector<vector<string>> getItens();
    //void removerItem();

private:
    vector<Item> itens;
};

#endif
