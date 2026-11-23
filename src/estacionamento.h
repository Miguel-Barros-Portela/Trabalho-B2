#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#define FILEIRAS 4
#define COLUNAS 5
#define TOTAL_VAGAS 20
#define CAPACIDADE_INICIAL 2
#define TAM_ID 7
#define TAM_DESC 60

typedef struct {
    char id[TAM_ID + 1];
    char descricao[TAM_DESC + 1];
    int categoria; 
    int fileira;   
    int coluna;    
} Veiculo;

void inicializar_mapa(int mapa[FILEIRAS][COLUNAS]);
void exibir_menu(void);

#endif