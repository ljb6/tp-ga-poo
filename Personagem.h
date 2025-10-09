#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <iostream>
#include <string>

#include "Inventario.h"

using namespace std;

class Personagem
{
public:
    Personagem();
    Personagem(const string &nome, int habilidade, int energia, int sorte);
    virtual ~Personagem();

    string getNome();
    int getHabilidade();
    int getEnergia();
    int getSorte();

    void distribuirAtributos();
    void setarNome(string nome_);
    bool testarSorte();
    void mostrarInventario();
    //int getQuantidadeItens();
    vector<vector<string>> getItens();
        const Inventario& getInventario() const;

        bool equiparItem(int index);
        int getEquippedWeaponIndex() const;
        int getEquippedArmorIndex() const;
        int getEquippedWeaponFa() const;
        int getEquippedArmorFa() const;
        int getEquippedWeaponDano() const;
        int getEquippedArmorProt() const;

    void setEnergia(int energia_);
    void adicionarItem(Item item_);

    void adicionarTesouro(int valor);
    void adicionarProvisoes(int quantidade);
    int getQuantidadeItens();
    int getTesouro();
    int getProvisoes();

    void usarProvisao();
    int getEnergiaMaxima();

private:
    string nome;
    int habilidade = 6;
    int energia = 12;
    int sorte = 6;
        // equipamento: índices no inventário (-1 = nenhum)
        int equippedWeaponIndex = -1;
        int equippedArmorIndex = -1;

    int tesouro = 0;
    int provisoes = 0;
    int energia_maxima = 0;

    void mostrarAtributos();

protected:
    Inventario inventario_;
};

#endif