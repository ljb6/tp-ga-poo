//
// Created by Lucca Jaroszeski Becker on 12/09/25.
//

#include "Mago.h"

Mago::Mago() : Personagem() {
    vector<Itens> itens_iniciais = { Cajado, Roupao };
    adicionarItensIniciais(itens_iniciais);
}

Mago::~Mago() {}

void Mago::adicionarItensIniciais(const vector<Itens>& itens) {
    for(const auto& item : itens) {
        inventario_.adicionarItem(item); 
    }
}
