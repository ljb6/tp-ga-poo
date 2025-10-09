#ifndef TA_POO_ITEM_H
#define TA_POO_ITEM_H

#include <iostream>
#include <string>

using namespace std;

enum TipoItem {
    Espada,
    Cajado,
    Armadura,
};

class Item {
public:
    Item(string nome_, int dano_, TipoItem tipo_, bool combate_ = true, int faBonus_ = 0);
    ~Item();

    string getNome() const;
    int getDano() const;
    string getTipo() const;
    TipoItem getTipoEnum() const;

    bool isUsavelEmCombate() const;
    int getFaBonus() const;

    string fromTipoItemToString(TipoItem tipo_item_) const;
    TipoItem fromStringToTipoItem() const;

protected:
    string nome;
    int dano;
    TipoItem tipo;
    bool combate = false;
    int faBonus = 0;
};


#endif //TA_POO_ITEM_H