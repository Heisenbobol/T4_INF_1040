#ifndef VENDAS_H
#define VENDAS_H

#include <time.h>
#include <stdio.h>

#define MAX_ITENS_CARRINHO 100
#define MAX_ITENS_VENDA 100
#define MAX_VENDAS 1000

/* Códigos de retorno */

#define SUCESSO                     0

#define ERRO_NAO_CADASTRADO         1
#define ERRO_PARAMETRO_INVALIDO     2
#define ERRO_LEITURA_ESCRITA        4
#define ERRO_NAO_ENCONTRADO         5
#define ERRO_CARRINHO_VAZIO         6
#define ERRO_SEM_HISTORICO          7
#define ERRO_ESTOQUE               -3

/* Estruturas */

typedef struct
{
    int id_medicamento;
    int quantidade;

} ItemCarrinho;

typedef struct
{
    ItemCarrinho itens[MAX_ITENS_CARRINHO];
    int qtd_itens;

} Cart;

typedef struct
{
    int id_medicamento;
    int quantidade;
    float valor_unitario;

} ItemVenda;

typedef struct
{
    int id_venda;

    int cpf_cliente;

    time_t data;

    ItemVenda itens[MAX_ITENS_VENDA];

    int qtd_itens;

    float valor_total;

} Venda;

typedef struct
{
    Venda vendas[MAX_VENDAS];
    int qtd_vendas;
} BancoVendas;


/* Interface pública */

//Gera um relatório de vendas dos últimos X dias
//---
//Parametros:
//- periodo: Quantidade de dias que serão considerados
//---
//Retornos:
//- 0: Tudo Ok
//- 4: Erro de leitura/escrita no arquivo
int gera_relatorio(int periodo);

//Registra uma venda utilizando os itens presentes no carrinho
//---
//Parametros:
//- cpf_cliente: CPF do cliente que está realizando a compra
//---
//Retornos:
//- 0: Tudo Ok
//- 2: CPF inválido
int registra_venda(int cpf_cliente);

//Adiciona uma quantidade de medicamentos ao carrinho
//---
//Parametros:
//- id_medicamento: Codigo do medicamento a ser adicionado
//- quantidade: Quantidade desse medicamento a ser adicionado
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Medicamento não cadastrado
//- 2: Id do medicamento invalido
int adiciona_carrinho(int id_medicamento, int quantidade);

//Remove um medicamento do carrinho
//---
//Parametros:
//- id_medicamento: Codigo do medicamento a ser removido
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Medicamento não cadastrado
//- 2: Id do medicamento invalido
//- 5: Medicamento não está presente no carrinho
int remove_carrinho(int id_medicamento);

//Consulta o conteúdo atual do carrinho
//---
//Parametros:
//- carrinho: Estrutura que receberá os dados do carrinho
//---
//Retornos:
//- 0: Tudo Ok
//- 6: Carrinho vazio
int consulta_carrinho(Cart* carrinho);

//Consulta o histórico de compras de um cliente
//---
//Parametros:
//- cpf_cliente: CPF do cliente
//- historico: Vetor que receberá as vendas encontradas
//- qtd_vendas: Quantidade de vendas encontradas
//---
//Retornos:
//- 0: Tudo Ok
//- 2: CPF inválido
//- 7: Cliente não possui histórico de compras
int consulta_historico(int cpf_cliente, Venda historico[], int *qtd_vendas);

/* Persistência */

//Preenche o sistema com dados fictícios para testes
void popular_dados_teste(void);

//Carrega os dados de vendas do arquivo
//---
//Retornos:
//- 0: Tudo Ok
//- 4: Erro de leitura/escrita no arquivo
int carregar_vendas(void);

//Salva os dados de vendas no arquivo
//---
//Retornos:
//- 0: Tudo Ok
//- 4: Erro de leitura/escrita no arquivo
int salvar_vendas(void);

#endif