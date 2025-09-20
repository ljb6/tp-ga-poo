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
    cout << "Inventario:\n" << endl;
    for (auto i : itens) {
        cout << i.getNome();
    }
    cout << endl;
}

int Inventario::getQuantidadeItens() {
    return itens.size();
}
