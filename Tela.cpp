#include "Tela.h"

#include "Jogo.h"
#include "Lutador.h"

Tela::Tela() {

}

Tela::~Tela() {

}

void Tela::exibirCreditos() {
    cout << "Desenvolvido por: Lucca J. Becker" << endl;
    mostrarAbertura();
}

void Tela::limpar() {
    // ANSI clear screen
    cout << "\x1B[2J\x1B[H";
}

void Tela::mostrarAbertura() {
    cout << "[1] Novo jogo" << endl;
    cout << "[2] Carregar jogo" << endl;
    cout << "[3] Exibir créditos" << endl;
    cout << "[4] Encerrar" << endl;
    cout << "Escolha uma opção\n> ";

    int opcao = 0;
    cin >> opcao;

    Jogo jogo;

    switch (opcao) {
        case 1:
            jogo.novoJogo();
            break;
        case 2:
            jogo.carregarJogo();
            break;
        case 3:
            exibirCreditos();
            break;
        case 4:
            exit(0);
        default:
            cout << "Digite uma opção válida!" << endl;
            mostrarAbertura();
    }
}


