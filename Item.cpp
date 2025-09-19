//
// Created by Lucca Jaroszeski Becker on 12/09/25.
//

#include "Item.h"

Item::Item(string nome_, int dano_, TipoItem tipo_) {
    nome = nome_;
    dano = dano_;
    tipo = tipo_;
}

Item::~Item() {

}

string Item::getNome() {
    return nome;
}
