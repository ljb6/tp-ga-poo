#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <vector>

using namespace std;

enum Itens {
    Espada,
    Cajado,
};

class Inventario {
public:
    Inventario();
    ~Inventario();

    void mostrarInventario();
    void adicionarItem(Itens item_);
    void removerItem();

private:
    vector<Itens> itens;
};

#endif