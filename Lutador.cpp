//
// Created by Lucca Jaroszeski Becker on 07/09/25.
//

#include "Lutador.h"

Lutador::Lutador() {
    inicializarItens();
}

Lutador::~Lutador() {

}

void Lutador::inicializarItens() {
    inventario_.adicionarItem(
        Item("Espada Longa", 5, TipoItem::Espada));
}




