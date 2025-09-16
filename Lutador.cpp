//
// Created by Lucca Jaroszeski Becker on 07/09/25.
//

#include "Lutador.h"

Lutador::Lutador() : Personagem() {
    vector<Itens> itens_iniciais = { Espada, ArmaduraDeCouro };
    adicionarItensIniciais(itens_iniciais);
}

Lutador::~Lutador() {}

void Lutador::adicionarItensIniciais(const vector<Itens>& itens) {
    for(const auto& item : itens) {
        inventario_.adicionarItem(item); 
    }
}


