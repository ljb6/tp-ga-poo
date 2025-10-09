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
    void mostrarInventario(int equippedWeaponIndex, int equippedArmorIndex) const;
    int getQuantidadeItens();
    void adicionarItem(Item item_);
    vector<vector<string>> getItens();
    const vector<Item>& getItemObjects() const;
    //void removerItem();

private:
    vector<Item> itens;
};

#endif
