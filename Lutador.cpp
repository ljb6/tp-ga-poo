//
// Created by Lucca Jaroszeski Becker on 07/09/25.
//

#include "Lutador.h"

Lutador::Lutador()
{
    vector<Item> itens_iniciais = {Item("Espada Longa", 5, TipoItem::Espada)};

    for (auto i : itens_iniciais)
    {
        inventario_.adicionarItem(i);
    }
}

Lutador::Lutador(const string &nome, int habilidade, int energia, int sorte, const vector<Item> &itens)
    : Personagem(nome, habilidade, energia, sorte)
{
    for (const auto &i : itens)
    {
        inventario_.adicionarItem(i);
    }
}

Lutador::~Lutador()
{
}
