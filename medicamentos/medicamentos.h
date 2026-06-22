#ifndef MEDICAMENTOS_H
#define MEDICAMENTOS_H

#include <stdbool.h>

#define MAX_MEDICAMENTOS 1000

typedef struct {
    int id;
    char nome[100];
    float valor;
    bool receita;
} Medicamento;

Medicamento consulta_medicamento(int id_medicamento);

int cadastra_medicamento(int id_medicamento, char *nome, float valor, bool receita);

int altera_medicamento(int id_medicamento, char *novoNome, float novoValor, bool novaReceita);

int deleta_medicamento(int id_medicamento);

int verifica_receita(int id_medicamento);

float consulta_valor(int id_medicamento);

void carregarMedicamentos();
void salvarMedicamentos();

#endif