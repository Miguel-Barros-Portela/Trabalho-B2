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

static int ler_identificador_normalizado(char *destino, size_t tam_destino) {
    char buffer[128];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    buffer[strcspn(buffer, "\r\n")] = '\0';
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        buffer[i] = (char)toupper((unsigned char)buffer[i]);
    }
    if (!identificador_valido(buffer) || strlen(buffer) >= tam_destino) {
        return 0;
    }
    strcpy(destino, buffer);
    return 1;
}

static int buscar_indice_por_id(const Veiculo *veiculos, int qtd, const char *id) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(veiculos[i].identificador, id) == 0) {
            return i;
        }
    }
    return -1;
}

//-------------------------------------------------------------------------------------------------------------//

//Função 1 do menu
int cadastrar_veiculo(Veiculo **veiculos, int *qtd, int *cap, int mapa[FILEIRAS][COLUNAS]) {
    if (veiculos == NULL || qtd == NULL || cap == NULL || mapa == NULL) {
        return 0;
    }

    if (*qtd >= MAX_VAGAS) {
        printf("Estacionamento lotado (%d vagas).\n", MAX_VAGAS);
        return 0;
    }

    if (*cap == 0) {
        Veiculo *inicial = malloc(2 * sizeof(Veiculo));
        if (inicial == NULL) {
            printf("Falha ao alocar memoria inicial.\n");
            return 0;
        }
        *veiculos = inicial;
        *cap = 2;
    } else if (*qtd == *cap) {
        int nova_cap = (*cap) * 2;
        if (nova_cap > MAX_VAGAS) {
            nova_cap = MAX_VAGAS;
        }
        Veiculo *temp = realloc(*veiculos, (size_t)nova_cap * sizeof(Veiculo));
        if (temp == NULL) {
            printf("Falha ao expandir memoria com realloc.\n");
            return 0;
        }
        *veiculos = temp;
        *cap = nova_cap;
    }

    Veiculo novo;
    char buffer[128];

    printf("Identificador (7 caracteres A-Z / 0-9): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    buffer[strcspn(buffer, "\r\n")] = '\0';
    for (size_t i = 0; buffer[i] != '\0'; i++) {
        buffer[i] = (char)toupper((unsigned char)buffer[i]);
    }
    if (!identificador_valido(buffer)) {
        printf("Identificador invalido.\n");
        return 0;
    }
    if (identificador_duplicado(*veiculos, *qtd, buffer)) {
        printf("Ja existe um veiculo com esse identificador.\n");
        return 0;
    }
    strcpy(novo.identificador, buffer);

    printf("Descricao (ate 60 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    buffer[strcspn(buffer, "\r\n")] = '\0';
    if (buffer[0] == '\0' || strlen(buffer) > 60) {
        printf("Descricao invalida.\n");
        return 0;
    }
    strcpy(novo.descricao, buffer);

    printf("Categoria (1 ou 2): ");
    if (scanf("%d", &novo.categoria) != 1 || (novo.categoria != 1 && novo.categoria != 2)) {
        printf("Categoria invalida.\n");
        limpar_buffer();
        return 0;
    }
    limpar_buffer();

    int fileira_exibida = 0;
    int coluna_exibida = 0;
    printf("Fileira (1 a %d) e Coluna (1 a %d): ", FILEIRAS, COLUNAS);
    if (scanf("%d %d", &fileira_exibida, &coluna_exibida) != 2) {
        printf("Posicao invalida.\n");
        limpar_buffer();
        return 0;
    }
    limpar_buffer();

    if (fileira_exibida < 1 || fileira_exibida > FILEIRAS ||
        coluna_exibida < 1 || coluna_exibida > COLUNAS) {
        printf("Posicao fora do intervalo permitido.\n");
        return 0;
    }

    int f = fileira_exibida - 1;
    int c = coluna_exibida - 1;
    if (mapa[f][c] != 0) {
        printf("A vaga (%d, %d) ja esta ocupada.\n", fileira_exibida, coluna_exibida);
        return 0;
    }

    novo.fileira = f;
    novo.coluna = c;

    (*veiculos)[*qtd] = novo;
    (*qtd)++;
    mapa[f][c] = 1;

    printf("Veiculo cadastrado com sucesso na vaga (%d, %d).\n", fileira_exibida, coluna_exibida);
    return 1;
}
//-------------------------------------------------------------------------------------------------------------//

//Função 2 do menu
void consultar_veiculo(const Veiculo *veiculos, int qtd) {
    if (veiculos == NULL || qtd == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    char id[8];
    printf("Digite o identificador (7 caracteres): ");
    if (!ler_identificador_normalizado(id, sizeof(id))) {
        printf("Identificador invalido.\n");
        return;
    }

    int idx = buscar_indice_por_id(veiculos, qtd, id);
    if (idx == -1) {
        printf("Veiculo com identificador %s nao encontrado.\n", id);
        return;
    }

    const Veiculo *v = &veiculos[idx];
    printf("\n--- Veiculo encontrado ---\n");
    printf("Identificador: %s\n", v->identificador);
    printf("Descricao: %s\n", v->descricao);
    printf("Categoria: %d\n", v->categoria);
    printf("Vaga: Fileira %d, Coluna %d\n", v->fileira + 1, v->coluna + 1);
}
//-------------------------------------------------------------------------------------------------------------//
//Função 3 do menu
int atualizar_veiculo(Veiculo *veiculos, int qtd) {
    if (veiculos == NULL || qtd == 0) {
        printf("Nenhum veiculo cadastrado.\n");
        return 0;
    }

    char id[8];
    printf("Identificador do veiculo a atualizar: ");
    if (!ler_identificador_normalizado(id, sizeof(id))) {
        printf("Identificador invalido.\n");
        return 0;
    }

    int idx = buscar_indice_por_id(veiculos, qtd, id);
    if (idx == -1) {
        printf("Veiculo nao encontrado.\n");
        return 0;
    }

    char buffer[128];
    printf("Nova descricao (ate 60 caracteres): ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    buffer[strcspn(buffer, "\r\n")] = '\0';
    if (buffer[0] == '\0' || strlen(buffer) > 60) {
        printf("Descricao invalida.\n");
        return 0;
    }

    int nova_cat = 0;
    printf("Nova categoria (1 ou 2): ");
    if (scanf("%d", &nova_cat) != 1 || (nova_cat != 1 && nova_cat != 2)) {
        printf("Categoria invalida.\n");
        limpar_buffer();
        return 0;
    }
    limpar_buffer();

    strcpy(veiculos[idx].descricao, buffer);
    veiculos[idx].categoria = nova_cat;
    printf("Dados do veiculo %s atualizados com sucesso.\n", veiculos[idx].identificador);
    return 1;
}
//-------------------------------------------------------------------------------------------------------------//
//Função 4 do menu
int remover_veiculo(Veiculo **veiculos, int *qtd, int *cap, int mapa[FILEIRAS][COLUNAS]) {
    if (veiculos == NULL || *veiculos == NULL || qtd == NULL || cap == NULL || mapa == NULL) {
        return 0;
    }
    if (*qtd == 0) {
        printf("Nenhum veiculo cadastrado para remover.\n");
        return 0;
    }

    char id[8];
    printf("Identificador do veiculo a remover: ");
    if (!ler_identificador_normalizado(id, sizeof(id))) {
        printf("Identificador invalido.\n");
        return 0;
    }

    int idx = buscar_indice_por_id(*veiculos, *qtd, id);
    if (idx == -1) {
        printf("Veiculo nao encontrado.\n");
        return 0;
    }

    int f = (*veiculos)[idx].fileira;
    int c = (*veiculos)[idx].coluna;
    mapa[f][c] = 0;

    for (int i = idx; i < (*qtd) - 1; i++) {
        (*veiculos)[i] = (*veiculos)[i + 1];
    }
    (*qtd)--;

    if (*qtd == 0) {
        free(*veiculos);
        *veiculos = NULL;
        *cap = 0;
    } else if (*cap > 2 && (*qtd) <= (*cap) / 4) {
        int nova_cap = (*cap) / 2;
        if (nova_cap < 2) {
            nova_cap = 2;
        }
        Veiculo *temp = realloc(*veiculos, (size_t)nova_cap * sizeof(Veiculo));
        if (temp != NULL) {
            *veiculos = temp;
            *cap = nova_cap;
        }
    }

    printf("Veiculo %s removido e vaga (%d, %d) liberada.\n", id, f + 1, c + 1);
    return 1;
}
//-------------------------------------------------------------------------------------------------------------//