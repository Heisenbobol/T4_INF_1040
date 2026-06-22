#include <stdio.h>
#include "estoque.h"

static Estoque estoque[MAX_ESTOQUE];
static int qtdEstoque = 0;

static int buscarPosicao(int idMedicamento)
{
    int i;

    for(i = 0; i < qtdEstoque; i++)
    {
        if(estoque[i].idMedicamento == idMedicamento)
        {
            return i;
        }
    }

    return -1;
}

void carregar_estoque(void)
{
    FILE *arquivo;

    arquivo = fopen("dados/estoque.txt", "r");

    if (arquivo == NULL)
    {
        printf("Arquivo de estoque nao encontrado.\n");
        return;
    }

    qtdEstoque = 0;

    while (
        fscanf(
            arquivo,
            "%d;%d",
            &estoque[qtdEstoque].idMedicamento,
            &estoque[qtdEstoque].quantidade
        ) == 2
    )
    {
        qtdEstoque++;
    }

    fclose(arquivo);
}

void salvar_estoque(void)
{
    FILE *arquivo;

    arquivo = fopen("dados/estoque.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao salvar arquivo de estoque.\n");
        return;
    }

    for (int i = 0; i < qtdEstoque; i++)
    {
        fprintf(
            arquivo,
            "%d;%d\n",
            estoque[i].idMedicamento,
            estoque[i].quantidade
        );
    }

    fclose(arquivo);
}

int consulta_estoque(int idMedicamento, int *quantidade)
{
    int pos;

    if (idMedicamento <= 0)
    {
        return 2;
    }

    pos = buscarPosicao(idMedicamento);

    if (pos == -1)
    {
        return 1;
    }

    *quantidade = estoque[pos].quantidade;

    return 0;
}

int adiciona_estoque(int idMedicamento, int quantidade)
{
    int pos;
    Medicamento med;

    if(idMedicamento <= 0 || quantidade <= 0)
    {
        return -2;
    }

    med = consulta_medicamento(idMedicamento);

    if(med.id == -1)
    {
        return -1;
    }

    pos = buscarPosicao(idMedicamento);

    if(pos == -1)
    {
        estoque[qtdEstoque].idMedicamento = idMedicamento;
        estoque[qtdEstoque].quantidade = quantidade;

        qtdEstoque++;

        return quantidade;
    }

    estoque[pos].quantidade += quantidade;

    return estoque[pos].quantidade;
}

int remove_estoque(int idMedicamento, int quantidade)
{
    int pos;

    if(idMedicamento <= 0)
    {
        return -2;
    }

    if(quantidade <= 0)
    {
        return -2;
    }

    pos = buscarPosicao(idMedicamento);

    if(pos == -1)
    {
        return -1;
    }

    if(estoque[pos].quantidade < quantidade)
    {
        return -3;
    }

    estoque[pos].quantidade -= quantidade;

    return estoque[pos].quantidade;
}

