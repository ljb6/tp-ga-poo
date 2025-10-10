# Documentação explicada do código — TP GA POO

Este documento explica o código do projeto arquivo-por-arquivo e função-por-função para auxiliar em estudos e apresentação.

Sumário
-------
- `main.cpp` — ponto de entrada
- `Tela.*` — interação com o usuário e fluxo de menu
- `Jogo.*` — orquestração de cenas, salvar/carregar e batalhas
- `Personagem.*` — modelo de personagem (atributos, inventário, equipamentos)
- `Item.*` — modelo de item (arma/armadura/consumível)
- `Inventario.*` — armazenamento de itens e visualização
- `Monstro.*` — modelo de adversários
- `Lutador.*` / `Mago.*` — subclasses concretas de `Personagem`

Cada seção abaixo detalha o propósito do arquivo e descreve as funções públicas e privadas com suas responsabilidades, parâmetros e efeitos.

## Convenções gerais
- Tipos básicos:
  - `TipoItem`: enum { `Espada`, `Cajado`, `Armadura` } — usado para categorizar itens.
- RNG: `rand()`/`srand()` é usado para gerar números aleatórios. A semente é inicializada com `time(nullptr)` em `Jogo`.
- Salvamento/Carregamento: os saves ficam em `jogos_salvos/` e são arquivos de texto divididos em seções (nome, atributos, itens, provisoes, tesouro, cena_atual, cenas_visitadas, tipo_personagem, equipamento).

---

## main.cpp

Função principal:
- `main()`
  - Cria um objeto `Tela` e chama `tela.mostrarAbertura()` para iniciar a interface do jogo.

Fluxo:
- `main()` não faz lógica de jogo; delega para `Tela` que constrói um `Jogo` quando necessário.

---

## Tela.h / Tela.cpp

Propósito:
- Responsável pela interação básica com o usuário no terminal e pelo menu inicial.
- Fornece utilitários simples de tela (limpar e mostrar créditos).

Funções públicas notáveis:
- `void Tela::mostrarAbertura()`
  - Exibe o menu inicial com opções: Novo jogo, Carregar jogo, Exibir créditos e Encerrar.
  - Lê uma opção do usuário com `cin >> opcao`.
  - Cria um `Jogo` local (`Jogo jogo;`) e chama `jogo.novoJogo()` ou `jogo.carregarJogo()` conforme a escolha.
  - Para opção inválida, reinvoca `mostrarAbertura()` recursivamente.

- `void Tela::limpar()`
  - Emite sequência ANSI para limpar o terminal (`\x1B[2J\x1B[H`).

- `void Tela::exibirCreditos()`
  - Mostra créditos e chama `mostrarAbertura()` em seguida.

Observações:
- `mostrarAbertura()` cria um objeto `Jogo` local — o ciclo de jogo então acontece a partir daquele objeto; se o usuário voltar, o objeto se destrói e um novo é criado.

---

## Jogo.h / Jogo.cpp

Responsabilidade geral:
- Coordena o estado global do jogo: personagem em memória, cena atual, cenas visitadas.
- Lê arquivos de cena da pasta `cenas/` e controla o loop principal de exibição e navegação entre cenas.
- Implementa salvar/carregar de jogos (persistência) e a rotina de batalhas contra `Monstro`.

Atributos principais:
- `Personagem *personagem_`: ponteiro para o personagem atual (alocado dinamicamente em `novoJogo()` e em `carregarJogo()`).
- `vector<int> cenas_visitadas`: mantém as cenas já visitadas para evitar repetição.
- `int cena`: número da cena atual.

Construtor/Destrutor:
- `Jogo::Jogo()` — inicializa `personagem_` como `nullptr` e chama `srand(time(nullptr))` para seed do RNG.
- `Jogo::~Jogo()` — deleta `personagem_` se presente.

Funções importantes:
- `void Jogo::novoJogo()`
  - Cria um `Lutador` default.
  - Pede o nome do personagem via `getline` e chama `personagem_->distribuirAtributos()` para permitir o jogador distribuir 12 pontos entre os atributos.
  - Define `cena = 1` e limpa `cenas_visitadas`, depois chama `lerCena()` para iniciar o loop de cenas.

- `void Jogo::lerCena()`
  - Loop principal de exibição de cenas. Em cada iteração:
    - Limpa tela condicionalmente com `Tela::limpar()`.
    - Salva o jogo chamando `salvarJogo()` (salvamento frequente automático).
    - Lê o arquivo da cena `cenas/<cena>.txt` inteiro para memória (vetor `lines`).
    - Determina a primeira linha significativa (ignora linhas em branco) para identificar se a cena é de batalha (linha começando com 'm' ou 'M').
    - Se for cena de monstro, faz parsing das linhas para construir um `Monstro` (N:, H:, S:, E:, T:, P:, I: para item, e uma linha com `vitoria;derrota`). Em seguida chama `iniciarBatalha(monstro)` e move para a cena de vitória/derrota dependendo do resultado.
    - Caso não seja batalha, exibe a cena normalmente e exibe um menu com opções:
      - [0] Sair do jogo (salvar)
      - [-1] Ver inventário
      - [-2] Usar provisão (+4 energia)
      - ou um número de cena para avançar (valida com `verificarCena`).
    - `lerCena()` é um loop crescente que só termina via `exit(0)` no programa ou retorno por erro na leitura de arquivos.

- `bool Jogo::verificarCena(int cena_)`
  - Verifica se `cena_` já está presente em `cenas_visitadas`. Retorna `false` se já visitada (inválida), `true` caso contrário.

- `void Jogo::salvarJogo()`
  - Cria o diretório `jogos_salvos/` se não existir e grava o estado do `personagem_` em um arquivo `<nome>.txt`.
  - Formato por seções: `nome`, `atributos` (habilidade/energia/sorte), `itens` (número e lista em formato `nome;tipo;combate;FA;dano`), `provisoes`, `tesouro`, `cena_atual`, `cenas_visitadas`, `tipo_personagem`, `equipamento` (índices: arma armadura).
  - Ao gravar nomes de itens, espaços são convertidos para `_'` para evitar quebra de token no formato salvo.

- `void Jogo::carregarJogo()`
  - Lista arquivos em `jogos_salvos/` e pede que o usuário escolha um save.
  - Lê o arquivo e faz parsing por seções. Implementa compatibilidade com dois formatos: o novo (campos separados por `;`) e o legado (tríades nome, dano, tipo).
  - Reconstrói `vector<Item> itens` do save e cria `personagem_` (atualmente sempre `Lutador`) com esses itens e atributos.
  - Restaura `cena` e `cenas_visitadas` e aplica equipamento salvo (índices).
  - Faz validações básicas de cena e chama `lerCena()` para iniciar.

- `TipoItem Jogo::fromStringToTipoItem(string str)`
  - Converte strings como "Espada", "Cajado", "Armadura" para `TipoItem`.

- `void Jogo::iniciarBatalha(Monstro& monstro)`
  - Implementa o loop de batalha entre `personagem_` e `monstro`.
  - Cada turno o jogador escolhe: Atacar, Fugir, Testar Sorte, Equipar item.
  - Cálculo de FA (Força de Ataque): combina habilidade base + FA de arma equipada + roll 1..10. Inimigo calcula similarmente; itens do monstro podem ajustar FA/FA do jogador.
  - Se jogador vence o turno, aplica dano no monstro: base 2 + dano de arma equipada do jogador (+2 adicional se teste de sorte com sucesso).
  - Se inimigo vence, aplica dano no jogador: base 2 - armadura equipada (+ dano de arma do monstro se tiver) (+1 se teste de sorte falhou).
  - Ao final, se o monstro morrer, aplicam-se ganhos: tesouro, provisões e drop de item (adicionado ao inventário do jogador).

Observações sobre `Jogo`:
- `personagem_` é um ponteiro cru (raw pointer) e liberado no destrutor; poderia ser melhor gerido com `std::unique_ptr`.
- `lerCena()` salva o jogo toda vez que exibe uma cena — útil para testes, mas pode causar muitos writes.
- O parser de saves é tolerante; aceita formatos legados e novo formato com campos extras.

---

## Item.h / Item.cpp

Responsabilidade:
- Representar itens do jogo, incluindo armas, armaduras e consumíveis.

Atributos:
- `string nome` — nome do item.
- `int dano` — valor numérico usado tanto para dano de armas quanto proteção de armaduras (armaduras usam `dano` como proteção no design atual).
- `TipoItem tipo` — enum do tipo do item.
- `bool combate` — indica se o item pode ser usado em combate.
- `int faBonus` — bônus à Força de Ataque (FA) ao usar o item em combate.

Funções públicas:
- Construtor: `Item(string nome_, int dano_, TipoItem tipo_, bool combate_ = true, int faBonus_ = 0)` — inicializa todos os campos.
- `string getNome() const` — retorna `nome`.
- `int getDano() const` — retorna `dano`.
- `string getTipo() const` — retorna um `string` legível para o `tipo` (`espada`, `armadura`, `cajado`).
- `TipoItem getTipoEnum() const` — retorna o enum.
- `bool isUsavelEmCombate() const` — se o item pode ser usado em combate.
- `int getFaBonus() const` — retorna o bônus de FA do item.

Notas:
- `fromTipoItemToString()` fornece a conversão para string em `getTipo()`.

---

## Inventario.h / Inventario.cpp

Responsabilidade:
- Armazenar e fornecer acesso aos `Item` do personagem.
- Fornecer visualização (com índices) para suporte a equipar itens.

Funções principais (implementadas em `Inventario.cpp`):
- `Inventario::adicionarItem(Item item_)` — adiciona um item ao vetor `itens`.
- `Inventario::mostrarInventario()` — versão simples que imprime nome, dano e tipo.
- `Inventario::getQuantidadeItens()` — retorna `itens.size()`.
- `Inventario::getItens()` — retorna uma matriz de strings com informações básicas (nome, dano, tipo) — usada para salvar/carregar.
- `const vector<Item>& Inventario::getItemObjects() const` — retorna referência constante ao vetor de objetos `Item` para uso por `Personagem` e `Jogo`.
- `Inventario::mostrarInventario(int equippedWeaponIndex, int equippedArmorIndex) const` — exibe o inventário com índices e marcação dos itens equipados; mostra também `FA` e `Dano/Prot` para cada item.

Observações:
- `mostrarInventario()` tem duas versões: uma que imprime resumo do inventário e outra que destaca itens equipados quando chamada durante batalhas.

---

## Personagem.h / Personagem.cpp

Responsabilidade:
- Modelar atributos do jogador: nome, habilidade, energia, sorte, provisões, tesouro e inventário.
- Gerenciar equipar itens (arma/armadura) e fornecer valores derivados (FA de arma, proteção de armadura).

Atributos principais:
- `nome, habilidade, energia, sorte` — atributos do personagem.
- `equippedWeaponIndex, equippedArmorIndex` — índices no inventário (-1 = nenhum equipado).
- `tesouro, provisoes` — recursos do personagem.
- `energia_maxima` — energia máxima definida após distribuição de pontos.
- `Inventario inventario_` — composição, armazena os itens.

Funções públicas notáveis:
- Construtores e destrutor.
- `void distribuirAtributos()` — permite ao jogador distribuir 12 pontos entre habilidade, energia e sorte. Atualiza `energia_maxima`.
- `void mostrarInventario()` — exibe estado do personagem e delega para `inventario_.mostrarInventario()`.
- `bool testarSorte()` — consome 1 ponto de sorte, rola 1..12 e retorna `true` se o roll for <= sorte anterior.
- `void usarProvisao()` — consome uma provisão (se disponível) e recupera 4 pontos de energia (limitado por `energia_maxima`).
- `bool equiparItem(int index)` — tenta equipar o item no índice fornecido. Só permite equipar itens com `isUsavelEmCombate()==true`. Armas (Espada/Cajado) são tratadas como armas; Armadura como armadura.
- Getters para `getEquippedWeaponFa()`, `getEquippedWeaponDano()`, `getEquippedArmorFa()`, `getEquippedArmorProt()` — retornam valores derivados dos itens equipados (0 se nenhum equipado).

Observações:
- A função `getEquippedArmorProt()` retorna `it.getDano()` como proteção: a propriedade `dano` do `Item` é reutilizada para o valor de proteção de armaduras.
- `equiparItem()` recusa itens que não são usáveis em combate (consumíveis).

---

## Monstro.h / Monstro.cpp

Responsabilidade:
- Modelar inimigos com atributos simples: nome, habilidade, sorte, energia, tesouro, provisões e possível `Item` drop.

Funções públicas:
- Construtores padrão e parametrizado.
- Getters e setters para cada atributo.
- `bool estaVivo()` — retorna `energia > 0`.
- `void receberDano(int dano)` — subtrai dano da energia e garante mínimo 0.
- `void mostrarInfo()` — imprime os atributos do monstro.

Observações:
- `item_drop` inicia por padrão como `Item("Nenhum", 0, TipoItem::Espada)`.

---

## Lutador / Mago

- `Lutador` e `Mago` são subclasses de `Personagem` que adicionam itens iniciais ao inventário.
- `Lutador()` inicializa com dois itens: `Espada Longa` (dano 5, FA 2) e `Couraça` (dano 0, proteção 1).
- `Mago()` inicializa com `Cajado Mágico` (dano 7).

---

## Fluxo de execução típico
1. `main()` cria `Tela` e chama `mostrarAbertura()`.
2. Usuário escolhe `Novo jogo` ou `Carregar jogo`.
3. `novoJogo()` cria o personagem (Lutador por padrão) e chama `distribuirAtributos()`.
4. `lerCena()` entra em um loop: salva jogo, carrega arquivo de cena e exibe opções. Se cena for de monstro, chama `iniciarBatalha()`.
5. `iniciarBatalha()` permite ações de batalha e atualiza energia/vidas, aplica drops ao final.

---

## Pontos para apresentação / perguntas frequentes
- Por que usar ponteiro cru para `personagem_`?
  - Simplicidade: o código instancia e destrói manualmente. Melhoria recomendada: substituir por `std::unique_ptr<Personagem>` para evitar vazamento de memória e clarificar propriedade.

- Como os itens afetam a batalha?
  - Armas adicionam `faBonus` à FA do jogador e `dano` ao dano aplicado quando o jogador acerta.
  - Armaduras fornecem `faBonus` negativo ao oponente (reduz FA) e usam `dano` como proteção contra dano recebido.
  - Monstros podem ter um item que afeta FA/dano também.

- Formato de save compatível: o loader aceita o formato novo (`nome;tipo;combate;FA;dano`) e também o formato legado (`nome dano tipo`). Isso deixa o parser tolerante a variações.

---

## Sugestões de melhorias (para estudo)
- Substituir `Personagem *personagem_` por `std::unique_ptr<Personagem>`.
- Injetar um RNG (`std::mt19937`) em vez de usar `rand()` para permitir testes determinísticos.
- Extrair a lógica de parsing/saving para uma classe `SaveManager` para separar responsabilidades.
- Escrever testes automatizados que simulem um fluxo de batalha com entradas pré-definidas.

---

Se quiser, posso:
- Gerar uma versão em PDF/HTML desse documento.
- Comitar `CODE_EXPLAIN.md` e dar push.
- Gerar uma versão mais curta com pontos para a apresentação (slides ou fichas resumidas).

