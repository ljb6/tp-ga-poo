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

string Item::getTipo() {
    return fromTipoItemToString(tipo);
}

int Item::getDano() {
    return dano;
}



string Item::fromTipoItemToString(TipoItem tipo_item_) {
    switch (tipo_item_) {
        case Espada:
            return "espada";
        case Armadura:
            return "armadura";
        case Cajado:
            return "cajado";
    }
}
