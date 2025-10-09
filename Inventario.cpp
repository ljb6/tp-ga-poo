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
    if (itens.empty()) {
        cout << "  (vazio)" << endl;
        return;
    }
    for (const auto &i : itens) {
        cout << "  - " << i.getNome() << " | Dano: " << i.getDano() << " | Tipo: " << i.getTipo() << endl;
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

const vector<Item>& Inventario::getItemObjects() const {
    return itens;
}

void Inventario::mostrarInventario(int equippedWeaponIndex, int equippedArmorIndex) const {
    cout << "Inventario:\n" << endl;
    if (itens.empty()) {
        cout << "  (vazio)" << endl;
        return;
    }
    for (size_t idx = 0; idx < itens.size(); ++idx) {
        const auto &i = itens[idx];
        cout << "  [" << idx << "] - " << i.getNome();
        if ((int)idx == equippedWeaponIndex) cout << " (equipped weapon)";
        if ((int)idx == equippedArmorIndex) cout << " (equipped armor)";
        cout << " | Tipo: " << i.getTipo() << " | Usavel em combate: " << (i.isUsavelEmCombate() ? "Sim" : "Nao");
        cout << " | FA: " << i.getFaBonus() << " | Dano/Prot: " << i.getDano() << endl;
    }
    cout << endl;
}
