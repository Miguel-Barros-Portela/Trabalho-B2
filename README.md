# Sistema de Gestão de Estacionamento (`Trabalho-B2`)

## Identificação

- **Disciplina:** Lógica de Programação e Algoritmos
- **Semestre:** 2026/2
- **Título do Trabalho:** Trabalho do 2º Bimestre — Sistema de Gestão de Estacionamento
- **Integrante:**
  - Miguel Barros Portela — GitHub: `[https://github.com/Miguel-Barros-Portela](https://github.com/Miguel-Barros-Portela)`

> **Observação:** Trabalho realizado individualmente, pois não encontrei parceiro e o prazo de entrega está próximo.

---

## Descrição do Cenário e Escopo 

O sistema simula o controle operacional de um estacionamento de console em **C11** com capacidade máxima de **20 vagas**, organizadas em **4 fileiras** e **5 colunas**.

O escopo abrange o ciclo completo de permanência e organização dos veículos durante a execução do programa: entrada/cadastro com validação de dados e disponibilidade, consulta individual, alteração de informações cadastrais, remoção com liberação de vaga, remanejamento de veículo entre vagas, listagem geral, visualização do mapa de vagas e acompanhamento de indicadores de ocupação. A persistência ocorre em memória durante a execução do programa.

---

## Funcionalidades Implementadas e Menu Disponível

Ao executar a aplicação, o menu principal exibe as seguintes opções:

- `1` — **Cadastrar veículo:** valida identificador alfanumérico de 7 caracteres (sem duplicidade), descrição (até 60 caracteres), categoria, posição dentro da grade `4x5` e se a vaga está livre; registra o veículo e marca a vaga como ocupada.
- `2` — **Consultar veículo por identificador:** busca um veículo pelo identificador normalizado e exibe seus dados e localização atual.
- `3` — **Atualizar descrição ou categoria:** localiza um veículo existente e atualiza sua descrição e/ou categoria após validação.
- `4` — **Remover veículo:** remove o veículo correspondente ao identificador informado, libera a vaga na matriz `4x5`, reorganiza a coleção e ajusta/libera a memória conforme o estado da estrutura.
- `5` — **Mover veículo para outra vaga:** transfere um veículo de sua vaga atual para outra vaga válida e desocupada, atualizando tanto o registro do veículo quanto o mapa.
- `6` — **Listar veículos cadastrados:** exibe todos os veículos presentes no sistema no momento.
- `7` — **Exibir mapa de vagas:** mostra a grade `4x5` indicando vagas livres e ocupadas.
- `8` — **Exibir relatório da ocupação:** apresenta totais de vagas (total, ocupadas, livres, percentual de ocupação), estado da coleção dinâmica e distribuição por categoria.
- `0` — **Encerrar:** finaliza o loop principal e libera a memória alocada dinamicamente antes de encerrar.

---

## Estruturas Utilizadas

- **Matriz `4 x 5` (`mapa[FILEIRAS][COLUNAS]`):** matriz bidimensional de inteiros (`4` fileiras por `5` colunas, totalizando `20` posições) que representa fisicamente o estacionamento. Permite checar rapidamente se uma vaga está livre ou ocupada, ocupar uma posição no cadastro, liberar na remoção e atualizar ambas as posições na movimentação.
- **`struct Veiculo`:** agrupa em um único tipo os dados de cada veículo cadastrado (como identificador normalizado, descrição, categoria e índices de fileira e coluna), mantendo os atributos de cada registro coesos e fáceis de manipular.
- **Coleção dinâmica (quantidade e capacidade):** o conjunto de veículos é mantido em um vetor alocado dinamicamente (`malloc` / `realloc` / `free`), controlado por duas variáveis auxiliares:
  - **Quantidade (`qtd`):** número atual de veículos cadastrados (`0` até `20`).
  - **Capacidade (`cap`):** tamanho atual reservado na memória para o vetor de `Veiculo`. Quando o vetor atinge a capacidade atual (`qtd == cap`) e ainda há vagas disponíveis no estacionamento (`cap < 20`), a capacidade é expandida (respeitando o limite máximo de 20 vagas).

---

## Visão Geral da Modularização

O projeto é dividido em três arquivos principais dentro de `src/`:

- **`src/estacionamento.h`:** define as constantes da grade (`FILEIRAS` e `COLUNAS`), a `struct Veiculo` (e eventuais estruturas auxiliares compartilhadas) e os protótipos das funções públicas do módulo, com proteção de inclusão (`#ifndef` / `#define` / `#endif`).
- **`src/estacionamento.c`:** concentra a lógica de negócio das operações do menu (`inicializar_mapa`, `exibir_menu`, `cadastrar_veiculo`, `consultar_veiculo`, `atualizar_veiculo`, `remover_veiculo`, `mover_veiculo`, `listar_veiculos`, `exibir_mapa` e `exibir_relatorio`) e funções auxiliares internas marcadas com `static` (leitura/limpeza de buffer, validação e normalização de identificador, busca por identificador).
- **`src/main.c`:** inicializa as variáveis e o mapa, executa o laço principal do menu e direciona cada opção escolhida via `switch` para a respectiva função em `estacionamento.c`, encerrando com a liberação de memória.

---

## Instruções de Compilação e Execução

Com o terminal aberto na raiz do repositório (`Trabalho-B2`), compile todos os arquivos `.c` juntos no padrão **C11**:

### Windows (PowerShell / CMD)
```powershell
gcc -std=c11 -Wall -Wextra -pedantic src\main.c src\estacionamento.c -o estacionamento.exe
.\estacionamento.exe



#Hash versão submetida: eea81b2a8ccd0aa4b9cfaa51906f037fccb088cb