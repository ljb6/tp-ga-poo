//
// Created by Lucca Jaroszeski Becker on 12/09/25.
//

#include "Mago.h"

Mago::Mago() : Personagem() {
    vector<Item> itens_iniciais = {
        Item("Cajado Mágico", 7, TipoItem::Cajado)
    };

    for (auto i : itens_iniciais) {
        inventario_.adicionarItem(i);
    }
}

Mago::~Mago() {}


