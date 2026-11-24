#include <stdio.h>
#include <stdlib.h>
#include "estacionamento.h"

static void limpar_entrada_main(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int main(void) {
    Veiculo *veiculos = NULL;
    int qtd = 0;
    int cap = 0;
    int mapa[FILEIRAS][COLUNAS];
    int opcao = -1;

    inicializar_mapa(mapa);

    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            limpar_entrada_main();
            opcao = -1;
            continue;
        }
        limpar_entrada_main();

        switch (opcao) { 
            case 1:
                cadastrar_veiculo(&veiculos, &qtd, &cap, mapa);
                break;
            case 2:
                consultar_veiculo(veiculos, qtd);
                break;
            case 3:
                atualizar_veiculo(veiculos, qtd);
                break;
            case 4:
                remover_veiculo(&veiculos, &qtd, &cap, mapa);
                break;
            case 5:
                mover_veiculo(veiculos, qtd, mapa);
                break;
            case 6:
                listar_veiculos(veiculos, qtd);
                break;
            case 7:
                exibir_mapa(mapa);
                break;
            case 8:
                exibir_relatorio(veiculos, qtd, cap, mapa);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    free(veiculos);
    veiculos = NULL;
    return 0;
}