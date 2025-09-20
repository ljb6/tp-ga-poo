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
    Item(string nome_, int dano_, TipoItem tipo_);
    ~Item();

    string getNome();
    int getDano();
    string getTipo();

    string fromTipoItemToString(TipoItem tipo_item_);
    TipoItem fromStringToTipoItem();

protected:
    string nome;
    int dano;
    TipoItem tipo;
};


#endif //TA_POO_ITEM_H