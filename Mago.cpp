//
// Arquivo criado por Lucca Jaroszeski Becker em 12/09/25.
// Implementação do Mago e itens iniciais.
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


