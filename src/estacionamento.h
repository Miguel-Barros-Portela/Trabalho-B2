#ifndef ESTACIONAMENTO_H
#define ESTACIONAMENTO_H

#define FILEIRAS 4
#define COLUNAS 5

typedef struct {
    char identificador[8]; 
    char descricao[61];    
    int categoria;
    int fileira;
    int coluna;
} Veiculo;

//struct auxiliar
typedef struct {
    int total_vagas;
    int ocupadas;
    int livres;
} RelatorioOcupacao;

void inicializar_mapa(int mapa[FILEIRAS][COLUNAS]);
void exibir_menu(void);
int cadastrar_veiculo(Veiculo **veiculos, int *qtd, int *cap, int mapa[FILEIRAS][COLUNAS]);

#endif