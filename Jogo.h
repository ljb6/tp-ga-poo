//
// Arquivo criado por Lucca Jaroszeski Becker em 10/09/25.
// Declaração da classe do jogo e APIs públicas para manipular salvamentos e cenas.
//

#ifndef TA_POO_JOGO_H
#define TA_POO_JOGO_H
#include "Inventario.h"
#include "Personagem.h"
#include <iostream>
#include <string>

// declaração antecipada (forward declaration) de classe usada nas assinaturas
class Monstro;

using namespace std;

class Jogo
{
public:
    Jogo();
    ~Jogo();

    void novoJogo();
    void salvarJogo();
    void carregarJogo();

    void setPersonagem();

    TipoItem fromStringToTipoItem(string str);

private:
    Personagem *personagem_;

    void lerCena();
    bool verificarCena(int cena_);
    void iniciarBatalha(Monstro& monstro);
    vector<int> cenas_visitadas;
    int cena = 1;
};

#endif // TA_POO_JOGO_H