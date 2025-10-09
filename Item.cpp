//
// Created by Lucca Jaroszeski Becker on 12/09/25.
//

#include "Item.h"

Item::Item(string nome_, int dano_, TipoItem tipo_, bool combate_, int faBonus_) {
    nome = nome_;
    dano = dano_;
    tipo = tipo_;
    combate = combate_;
    faBonus = faBonus_;
}

Item::~Item() {

}

string Item::getNome() const {
    return nome;
}

string Item::getTipo() const {
    return fromTipoItemToString(tipo);
}

int Item::getDano() const {
    return dano;
}

TipoItem Item::getTipoEnum() const { return tipo; }

bool Item::isUsavelEmCombate() const { return combate; }

int Item::getFaBonus() const { return faBonus; }



string Item::fromTipoItemToString(TipoItem tipo_item_) const {
    switch (tipo_item_) {
        case Espada:
            return "espada";
        case Armadura:
            return "armadura";
        case Cajado:
            return "cajado";
    }
    return "desconhecido";
}

