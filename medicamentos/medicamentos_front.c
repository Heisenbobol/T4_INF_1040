#include <stdio.h>
#include <stdbool.h>

#include "medicamentos.h"

void menuMedicamentos(void)
{
    int opcao;
    carregarMedicamentos();

    do
    {
        printf("\n========================\n");
        printf(" MODULO MEDICAMENTOS\n");
        printf("========================\n");
        printf("1 - Cadastrar medicamento\n");
        printf("2 - Consultar medicamento\n");
        printf("3 - Alterar medicamento\n");
        printf("4 - Excluir medicamento\n");
        printf("5 - Consultar valor\n");
        printf("6 - Verificar receita\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
{
    int id;
    char nome[100];
    float valor;
    int receita;
    int retorno;

    printf("ID: ");
    scanf("%d", &id);

    printf("Nome: ");
    scanf(" %[^\n]", nome);

    printf("Valor: ");
    scanf("%f", &valor);

    printf("Receita? (1-Sim / 0-Nao): ");
    scanf("%d", &receita);

    retorno =
        cadastra_medicamento(
            id,
            nome,
            valor,
            receita
        );

   if(retorno == 0)
{
    salvarMedicamentos();
    printf("Medicamento cadastrado com sucesso!\n");
}
    else if(retorno == 1)
    {
        printf("Medicamento ja cadastrado.\n");
    }
    else
    {
        printf("Dados invalidos.\n");
    }

    break;
}

            case 2:
{
    int id;
    Medicamento med;

    printf("ID do medicamento: ");
    scanf("%d", &id);

    med = consulta_medicamento(id);

    if(med.id == -1)
    {
        printf("Medicamento nao encontrado.\n");
    }
    else
    {
        printf("\nDados do medicamento:\n");
        printf("ID: %d\n", med.id);
        printf("Nome: %s\n", med.nome);
        printf("Valor: %.2f\n", med.valor);
        printf("Receita: %s\n",
               med.receita ? "Sim" : "Nao");
    }

    break;
}

            case 3:
{
    int id;
    char nome[100];
    float valor;
    int receita;
    int retorno;

    printf("ID do medicamento: ");
    scanf("%d", &id);

    printf("Novo nome: ");
    scanf(" %[^\n]", nome);

    printf("Novo valor: ");
    scanf("%f", &valor);

    printf("Precisa de receita? (1-Sim / 0-Nao): ");
    scanf("%d", &receita);

    retorno =
        altera_medicamento(
            id,
            nome,
            valor,
            receita
        );

    if(retorno == 0)
    {
        salvarMedicamentos();
        printf("Medicamento alterado com sucesso.\n");
    }
    else if(retorno == 1)
    {
        printf("Medicamento nao encontrado.\n");
    }
    else
    {
        printf("ID invalido.\n");
    }

    break;
}
            case 4:
{
    int id;
    int retorno;

    printf("ID do medicamento: ");
    scanf("%d", &id);

    retorno = deleta_medicamento(id);

    if(retorno == 0)
    {
        salvarMedicamentos();
        printf("Medicamento removido com sucesso.\n");
    }
    else if(retorno == 1)
    {
        printf("Medicamento nao encontrado.\n");
    }
    else
    {
        printf("ID invalido.\n");
    }

    break;
}

            case 5:
{
    int id;
    float valor;

    printf("ID do medicamento: ");
    scanf("%d", &id);

    valor = consulta_valor(id);

    if(valor == -1)
    {
        printf("Medicamento nao encontrado.\n");
    }
    else if(valor == -2)
    {
        printf("ID invalido.\n");
    }
    else
    {
        printf("Valor: R$ %.2f\n", valor);
    }

    break;
}

            case 6:
{
    int id;
    int retorno;

    printf("ID do medicamento: ");
    scanf("%d", &id);

    retorno = verifica_receita(id);

    if(retorno == -1)
    {
        printf("Medicamento nao encontrado.\n");
    }
    else if(retorno == 2)
    {
        printf("ID invalido.\n");
    }
    else if(retorno == 1)
    {
        printf("Medicamento exige receita.\n");
    }
    else
    {
        printf("Medicamento nao exige receita.\n");
    }

    break;
}

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while(opcao != 0);
}
