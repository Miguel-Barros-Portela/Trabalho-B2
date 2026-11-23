#include <stdio.h>
#include "estacionamento.h"

void inicializar_mapa(int mapa[FILEIRAS][COLUNAS]) {
    for (int f = 0; f < FILEIRAS; f++) {
        for (int c = 0; c < COLUNAS; c++) {
            mapa[f][c] = 0;
        }
    }
}

void exibir_menu(void) {
    printf("\n=== SISTEMA DE GESTAO DE ESTACIONAMENTO ===\n");
    printf("1 - Cadastrar veiculo\n");
    printf("2 - Consultar veiculo por identificador\n");
    printf("3 - Atualizar descricao ou categoria\n");
    printf("4 - Remover veiculo\n");
    printf("5 - Mover veiculo para outra vaga\n");
    printf("6 - Listar veiculos cadastrados\n");
    printf("7 - Exibir mapa de vagas\n");
    printf("8 - Exibir relatorio da ocupacao\n");
    printf("0 - Encerrar\n");
    printf("Escolha uma opcao: ");
}