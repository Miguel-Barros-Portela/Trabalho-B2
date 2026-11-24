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
void consultar_veiculo(const Veiculo *veiculos, int qtd);
int atualizar_veiculo(Veiculo *veiculos, int qtd);
int remover_veiculo(Veiculo **veiculos, int *qtd, int *cap, int mapa[FILEIRAS][COLUNAS]);
int mover_veiculo(Veiculo *veiculos, int qtd, int mapa[FILEIRAS][COLUNAS]);
void listar_veiculos(const Veiculo *veiculos, int qtd);
void exibir_mapa(const int mapa[FILEIRAS][COLUNAS]);
void exibir_relatorio(const Veiculo *veiculos, int qtd, int cap, const int mapa[FILEIRAS][COLUNAS]);

#endif