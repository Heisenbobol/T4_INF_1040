#ifndef MEDICAMENTOS_H
#define MEDICAMENTOS_H

#include <stdbool.h>

#define MAX_MEDICAMENTOS 1000

typedef struct
{
    int id;
    char nome[100];
    float valor;
    bool receita;

} Medicamento;

/* Interface pública */

//Consulta um medicamento pelo ID
//---
//Parametros:
//- id_medicamento: Código do medicamento
//---
//Retornos:
//- Medicamento encontrado
//- Medicamento vazio caso não encontrado ou ID inválido
Medicamento consulta_medicamento(int id_medicamento);

//Cadastra um novo medicamento
//---
//Parametros:
//- id_medicamento: Código do medicamento
//- nome: Nome do medicamento
//- valor: Valor unitário
//- receita: Necessita receita médica
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Medicamento já cadastrado
//- 2: Informações inválidas
int cadastra_medicamento(int id_medicamento, char *nome, float valor, bool receita);

//Altera os dados de um medicamento
//---
//Parametros:
//- id_medicamento: Código do medicamento
//- novoNome: Novo nome
//- novoValor: Novo valor
//- novaReceita: Nova configuração de receita
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Medicamento não cadastrado
//- 2: ID inválido
int altera_medicamento(int id_medicamento, char *novoNome, float novoValor, bool novaReceita);

//Remove um medicamento
//---
//Parametros:
//- id_medicamento: Código do medicamento
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Medicamento não cadastrado
//- 2: ID inválido
int deleta_medicamento(int id_medicamento);

//Verifica se o medicamento exige receita
//---
//Parametros:
//- id_medicamento: Código do medicamento
//---
//Retornos:
//- true: Possui receita
//- false: Não possui receita
//- 1: Medicamento não cadastrado
//- 2: ID inválido
int verifica_receita(int id_medicamento);

//Consulta o valor de um medicamento
//---
//Parametros:
//- id_medicamento: Código do medicamento
//---
//Retornos:
//- Valor do medicamento
//- 1: Medicamento não cadastrado
//- 2: ID inválido
float consulta_valor(int id_medicamento);

/* Persistência */

//Carrega os medicamentos do arquivo
void carregarMedicamentos(void);

//Salva os medicamentos no arquivo
void salvarMedicamentos(void);

#endif