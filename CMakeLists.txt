cmake_minimum_required(VERSION 3.28.3)
project(TA_POO)

set(CMAKE_CXX_STANDARD 20)

add_executable(TA_POO main.cpp
        Tela.cpp
        Tela.h
        Personagem.cpp
        Personagem.h
        Inventario.cpp
        Inventario.h
        Lutador.cpp
        Lutador.h
        Jogo.cpp
        Jogo.h
        Mago.cpp
        Mago.h
        Item.cpp
        Item.h
        Monstro.cpp
        Monstro.h
)
