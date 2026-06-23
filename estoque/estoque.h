#ifndef ESTOQUE_H
#define ESTOQUE_H

#define MAX_ESTOQUE 100

typedef struct
{
    int idMedicamento;
    int quantidade;

} Estoque;

/* Interface pública */

//Adiciona medicamentos ao estoque
//---
//Parametros:
//- idMedicamento: Código do medicamento
//- quantidade: Quantidade a adicionar
//---
//Retornos:
//- Quantidade atual em estoque
//- -1: Medicamento não cadastrado
//- -2: ID inválido
int adiciona_estoque(int idMedicamento, int quantidade);

//Remove medicamentos do estoque
//---
//Parametros:
//- idMedicamento: Código do medicamento
//- quantidade: Quantidade a remover
//---
//Retornos:
//- Quantidade atual em estoque
//- -1: Medicamento não cadastrado
//- -2: ID inválido
//- -3: Quantidade insuficiente
int remove_estoque(int idMedicamento, int quantidade);

//Consulta a quantidade em estoque
//---
//Parametros:
//- idMedicamento: Código do medicamento
//- quantidade: Ponteiro que receberá a quantidade atual
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Medicamento não cadastrado
//- 2: ID inválido
int consulta_estoque(int idMedicamento, int *quantidade);

/* Persistência */

//Carrega os dados de estoque do arquivo
void carregar_estoque(void);

//Salva os dados de estoque no arquivo
void salvar_estoque(void);

#endif