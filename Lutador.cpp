//
// Arquivo criado por Lucca Jaroszeski Becker em 07/09/25.
// Implementação da classe Lutador e itens iniciais padrões.
//

#include "Lutador.h"

Lutador::Lutador()
{
    vector<Item> itens_iniciais = {Item("Espada Longa", 5, TipoItem::Espada, true, 2), Item("Couraça", 0, TipoItem::Armadura, true, 1)};

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
