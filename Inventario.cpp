//
// Created by Lucca Jaroszeski Becker on 07/09/25.
//

#include "Inventario.h"

Inventario::Inventario() {

}

Inventario::~Inventario() {

}

void Inventario::adicionarItem(Itens item_) {
    itens.push_back(item_);
}


void Inventario::mostrarInventario() {
    cout << "Você possui os seguintes itens:" << endl;
    cout << "[";
    for (auto i : itens) {
        cout << i;
    }
    cout << "]";
}
