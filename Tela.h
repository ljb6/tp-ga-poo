#ifndef TELA_H
#define TELA_H

#include <iostream>

using namespace std;

class Tela {
public:
    Tela();
    ~Tela();

    void mostrarAbertura();
    void mostrarInvetario();
    void mostrarPadrao();
    void mostrarBatalha();

private:
    void exibirCreditos();
};

#endif