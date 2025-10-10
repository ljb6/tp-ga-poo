# TP - GA - POO

Este repositório contém um jogo simples em C++ (terminal) desenvolvido para a disciplina de Programação Orientada a Objetos.

Resumo
------
- Linguagem: C++ (C++17)
- Compilador: g++
- Estrutura: arquivos .cpp/.h no diretório raiz
- Binário gerado: `programa`

Requisitos
---------
- g++ (GNU C++ 17)
- make (opcional)

Como compilar
-------------
Abra um terminal na raiz do projeto e rode:

```bash
# compilar todos os .cpp do diretório atual
g++ -std=gnu++17 -g *.cpp -o programa
```

Como executar
-------------
Após compilar, execute:

```bash
./programa
```

Você verá um menu com opções para iniciar novo jogo, carregar jogo salvo e mais.

Formato de arquivos de cena
---------------------------
As cenas (pasta `cenas/`) são arquivos de texto simples com as descrições mostradas no jogo. Caso falte um arquivo de cena, o jogo busca em `cenas/` pelo número pedido.

Formato de arquivos de save
---------------------------
Os saves ficam em `jogos_salvos/` e usam um formato por seções. As seções conhecidas incluem:
- `nome` — nome do personagem
- `atributos` — atributos, cada linha contém um par `chave:valor` para os atributos principais
- `itens` — itens do inventário. Cada item é salvo em uma linha com o formato:

```
<nome>;<tipo>;<combate>;<FA>;<dano>
```

Onde:
- `<tipo>` é `w` (weapon), `r` (armor/rosto?) ou `c` (consumable) — siga o código do jogo para o mapa de tipos
- `<combate>` é `1` se o item pode ser usado em combate, `0` caso contrário
- `<FA>` é o bônus de fator de ação (FA) do item
- `<dano>` é o dano base que o item causa (0 para armaduras ou consumíveis sem dano)

Exemplo de linha de item:

```
Espada de Ferro;w;1;2;4
```

Seção `equipamento`
-------------------
A seção `equipamento` contém dois índices (arma e armadura) apontando para itens no inventário, separados por `;`:

```
0;1
```

Compatibilidade
---------------
O loader é tolerante e suporta versões antigas do formato de item (apenas `nome;tipo`), mapeando valores faltantes para padrões.

Notas do desenvolvedor
---------------------

Executando um teste rápido (fluxo batalha)
-----------------------------------------
1. Compile e execute `./programa`.
2. Crie um novo jogo (opção 1) e avance até uma cena com batalha.
3. Durante a batalha, teste equipar itens no inventário para ver os efeitos de FA e dano.
