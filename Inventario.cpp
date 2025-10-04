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

vector<vector<string>> Inventario::getItens() {
    vector<vector<string>> output;
    for (auto i : itens) {
        vector<string> item;
        item.push_back(i.getNome());
        item.push_back(to_string(i.getDano()));
        item.push_back(i.getTipo());
        output.push_back(item);
    }
    return output;
}
