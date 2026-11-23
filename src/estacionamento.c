#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estacionamento.h"

#define MAX_VAGAS (FILEIRAS * COLUNAS)

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
    scanf("%d", &menu);
}


// Funções auxiliares
static void limpar_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static int identificador_valido(const char *id) {
    if (strlen(id) != 7) {
        return 0;
    }
    for (int i = 0; i < 7; i++) {
        unsigned char c = (unsigned char)id[i];
        if (!isalnum(c)) {
            return 0;
        }
    }
    return 1;
}

static int identificador_duplicado(const Veiculo *veiculos, int qtd, const char *id) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(veiculos[i].identificador, id) == 0) {
            return 1;
        }
    }
    return 0;
}
//-------------------------------------------------------------------------------------------------------------//


