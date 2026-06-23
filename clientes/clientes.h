#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 100

typedef struct
{
    int id;
    char nome[100];
    char cpf[12];
    char telefone[20];

} Cliente;

/* Interface pública */

//Cadastra um novo cliente
//---
//Parametros:
//- nome: Nome do cliente
//- cpf: CPF do cliente
//- telefone: Telefone do cliente
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Cliente já cadastrado
//- 2: Informações inválidas
int cadastrarCliente(char *nome, char *cpf, char *telefone);

//Lista todos os clientes cadastrados
void listarClientes(void);

//Busca um cliente pelo CPF
//---
//Parametros:
//- cpf: CPF do cliente
//---
//Retornos:
//- 0: Cliente encontrado
//- 1: Cliente não encontrado
//- 2: CPF inválido
int buscarCliente(char *cpf);

//Altera os dados de um cliente
//---
//Parametros:
//- cpf: CPF do cliente
//- novoNome: Novo nome
//- novoTelefone: Novo telefone
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Cliente não cadastrado
//- 2: CPF inválido
int alterarCliente(char *cpf,
                   char *novoNome,
                   char *novoTelefone);

//Remove um cliente do sistema
//---
//Parametros:
//- cpf: CPF do cliente
//---
//Retornos:
//- 0: Tudo Ok
//- 1: Cliente não cadastrado
//- 2: CPF inválido
int excluirCliente(char *cpf);

//Valida um CPF
//---
//Parametros:
//- cpf: CPF a ser validado
//---
//Retornos:
//- 0: CPF válido
//- 1: CPF inválido
int validarCPF(char *cpf);

/* Persistência */

//Carrega os clientes do arquivo
void carregarClientes(void);

//Salva os clientes no arquivo
void salvarClientes(void);

#endif