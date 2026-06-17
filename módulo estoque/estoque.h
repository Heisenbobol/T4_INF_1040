#ifndef ESTOQUE_H
#define ESTOQUE_H

#define MAX_ESTOQUE 100

typedef struct
{
    int idMedicamento;
    int quantidade;
} Estoque;

/* Persistência */
void carregar_estoque(void);
void salvar_estoque(void);

/* Operações */
int adiciona_estoque(int idMedicamento, int quantidade);
int remove_estoque(int idMedicamento, int quantidade);

int consulta_estoque(
    int idMedicamento,
    int *quantidade
);

#endif