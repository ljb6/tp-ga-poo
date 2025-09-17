//
// Created by Lucca Jaroszeski Becker on 07/09/25.
//

#include "Inventario.h"

Inventario::Inventario() {

}

Inventario::~Inventario() {

}

void Inventario::adicionarItem(Item item_) {
    itens.push_back(item_);
}

void Inventario::mostrarInventario() {
    for (auto i : itens) {
        cout << i.getNome();
    }
}
