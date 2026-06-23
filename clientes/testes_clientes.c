#include <stdio.h>
#include "clientes.h"

int main()
{
    carregarClientes();

    printf("=== CADASTRO ===\n");

    printf("%d\n",
           cadastrarCliente(
               "Lorenzo",
               "52998224725",
               "21999999999"));

    printf("%d\n",
           cadastrarCliente(
               "Lorenzo",
               "52998224725",
               "21999999999"));

    printf("%d\n",
           cadastrarCliente(
               "Joao",
               "123",
               "21999999999"));



    printf("\n=== BUSCA ===\n");

    printf("%d\n",
           buscarCliente(
               "52998224725"));

    printf("%d\n",
           buscarCliente(
               "11111111111"));



    printf("\n=== ALTERACAO ===\n");

    printf("%d\n",
           alterarCliente(
               "52998224725",
               "Novo Nome",
               "21888888888"));

    printf("%d\n",
           alterarCliente(
               "00000000000",
               "Teste",
               "11111111111"));



    printf("\n=== EXCLUSAO ===\n");

    printf("%d\n",
           excluirCliente(
               "52998224725"));

    printf("%d\n",
           excluirCliente(
               "52998224725"));

    printf("%d\n",
           excluirCliente(
               "123"));



    printf("\n=== LISTAGEM ===\n");

    listarClientes();

    salvarClientes();

    return 0;
}
