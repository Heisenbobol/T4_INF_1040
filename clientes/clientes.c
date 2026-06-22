#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clientes.h"

Cliente clientes[MAX_CLIENTES];
int qtdClientes;

void carregarClientes()
{
    FILE *arq;
    Cliente cliente;

    qtdClientes = 0;

    arq = fopen("clientes.dat", "rb");

    if(arq == NULL)
        return;

    while(fread(&cliente, sizeof(Cliente), 1, arq))
    {
        if(qtdClientes < MAX_CLIENTES)
        {
            clientes[qtdClientes] = cliente;
            qtdClientes++;
        }
    }

    fclose(arq);
}

void salvarClientes()
{
    FILE *arq;

    arq = fopen("clientes.dat", "wb");

    if(arq == NULL)
    {
        printf("Erro ao salvar clientes.\n");
        return;
    }

    fwrite(clientes,
           sizeof(Cliente),
           qtdClientes,
           arq);

    fclose(arq);
}

int buscarCliente(char *cpf)
{
    if(validarCPF(cpf) == 1){
        printf("Cpf invalido: ");
        return -2;
    }

    for(int i = 0; i < qtdClientes; i++)
    {
        if(strcmp(clientes[i].cpf, cpf) == 0)
        {
            printf("\nNome: %s", clientes[i].nome);
            printf("\nCPF: %s", clientes[i].cpf);
            printf("\nTelefone: %s\n", clientes[i].telefone);

            return i;
        }
    }

    return -1;
}

int cadastrarCliente( char *nome,  char *cpf, char *telefone)
{
    if(validarCPF(cpf) == 1){
        printf("Cpf inválido");
        return 2;
    }

    for(int i = 0; i < qtdClientes; i++) // Verifica se cpf já foi cadastrado
    {
        if(strcmp(clientes[i].cpf, cpf) == 0){
            printf("Cliente já cadastrado");
            return 1;
        }
    }

    Cliente novo;

    strcpy(novo.nome, nome);
    strcpy(novo.cpf, cpf);
    strcpy(novo.telefone, telefone);

    clientes[qtdClientes] = novo;
    qtdClientes++;

    return 0;
}

void listarClientes()
{
    if(qtdClientes == 0)
    {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for(int i = 0; i < qtdClientes; i++)
    {
        
        printf("\nNome: %s", clientes[i].nome);
        printf("\nCPF: %s", clientes[i].cpf);
        printf("\nTelefone: %s", clientes[i].telefone);
    }
}

int alterarCliente(char *cpf, char *novoNome, char *novoTelefone)
{
    if(validarCPF(cpf) == 1){
        printf("Cpf inválido");
        return 2;
    }

    for(int i = 0; i < qtdClientes; i++)
    {
        if(strcmp(clientes[i].cpf, cpf) == 0)
        {
            strcpy(clientes[i].nome, novoNome);
            strcpy(clientes[i].telefone, novoTelefone);
            return 0;
        }
    }

    return 1;
}

int excluirCliente(char *cpf)
{
    int indice = -1;

    if(validarCPF(cpf) == 1){
        printf("Cpf inválido");
        return 2;

    }

    for(int i = 0; i < qtdClientes; i++)
    {
        if(strcmp(clientes[i].cpf, cpf) == 0)
        {
            indice = i;
            break;
        }
    }

    if(indice == -1)
        return 1;

    for(int i = indice; i < qtdClientes - 1; i++)
    {
        clientes[i] = clientes[i + 1];
    }

    qtdClientes--;
    return 0;
}

int validarCPF(char *cpf)
{
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11)
        return 1;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 1; ///se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 1; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 1; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 0;
}

