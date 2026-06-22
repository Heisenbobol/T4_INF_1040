#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 100

typedef struct {
    int id;
    char nome[100];
    char cpf[12];
    char telefone[20];
} Cliente;


int cadastrarCliente( char *nome, char *cpf, char *telefone);
void listarClientes();
int buscarCliente(char *cpf);
int alterarCliente(char *cpf, char *novoNome, char *novoTelefone);
int excluirCliente(char *cpf);
void salvarClientes();
int validarCPF(char *cpf);
void carregarClientes();


#endif