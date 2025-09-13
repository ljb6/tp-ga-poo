//
// Created by Lucca Jaroszeski Becker on 07/09/25.
//

#include "Lutador.h"

Lutador::Lutador() {
}

Lutador::~Lutador() {

}

void Lutador::adicionarItensIniciais(vector<Itens> itens_) {
    for (auto i : itens_) {
        inventario_.adicionarItem(i);
    }
}



