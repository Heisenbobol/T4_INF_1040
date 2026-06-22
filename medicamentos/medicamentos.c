#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "medicamentos.h"

Medicamento medicamentos[MAX_MEDICAMENTOS];
int qtdMedicamentos = 0;

void carregarMedicamentos()
{
    FILE *arq;
    Medicamento medicamento;

    qtdMedicamentos = 0;

    arq = fopen("medicamentos.dat", "rb");

    if(arq == NULL)
        return;

    while(fread(&medicamento,
                sizeof(Medicamento),
                1,
                arq))
    {
        medicamentos[qtdMedicamentos++] =
            medicamento;
    }

    fclose(arq);
}

void salvarMedicamentos()
{
    FILE *arq;

    arq = fopen("medicamentos.dat", "wb");

    if(arq == NULL)
        return;

    fwrite(medicamentos,
           sizeof(Medicamento),
           qtdMedicamentos,
           arq);

    fclose(arq);
}

Medicamento consulta_medicamento(int id_medicamento)
{
    Medicamento vazio;

    vazio.id = -1;
    strcpy(vazio.nome, "");
    vazio.valor = -1;
    vazio.receita = false;

    if(id_medicamento <= 0)
        return vazio;

    for(int i = 0; i < qtdMedicamentos; i++)
    {
        if(medicamentos[i].id ==
           id_medicamento)
        {
            return medicamentos[i];
        }
    }

    return vazio;
}

int cadastra_medicamento(int id_medicamento,  char *nome, float valor,  bool receita)
{
    if(id_medicamento <= 0 ||
       nome == NULL ||
       valor < 0)
    {
        return 2;
    }

    for(int i = 0; i < qtdMedicamentos; i++)
    {
        if(medicamentos[i].id ==
           id_medicamento)
        {
            return 1;
        }
    }

    Medicamento novo;

    novo.id = id_medicamento;
    strcpy(novo.nome, nome);
    novo.valor = valor;
    novo.receita = receita;

    medicamentos[qtdMedicamentos] = novo;
    qtdMedicamentos++;

    return 0;
}

int altera_medicamento(int id_medicamento,  char *novoNome, float novoValor, bool novaReceita)
{
    if(id_medicamento <= 0)
        return 2;

    for(int i = 0; i < qtdMedicamentos; i++)
    {
        if(medicamentos[i].id ==
           id_medicamento)
        {
            strcpy(medicamentos[i].nome,
                   novoNome);

            medicamentos[i].valor =
                novoValor;

            medicamentos[i].receita =
                novaReceita;

            return 0;
        }
    }

    return 1;
}

int deleta_medicamento(int id_medicamento)
{
    if(id_medicamento <= 0)
        return 2;

    int indice = -1;

    for(int i = 0; i < qtdMedicamentos; i++)
    {
        if(medicamentos[i].id ==
           id_medicamento)
        {
            indice = i;
            break;
        }
    }

    if(indice == -1)
        return 1;

    for(int i = indice;
        i < qtdMedicamentos - 1;
        i++)
    {
        medicamentos[i] =
            medicamentos[i + 1];
    }

    qtdMedicamentos--;

    return 0;
}

int verifica_receita(int id_medicamento)
{
    if(id_medicamento <= 0)
        return 2;

    for(int i = 0; i < qtdMedicamentos; i++)
    {
        if(medicamentos[i].id ==
           id_medicamento)
        {
            return medicamentos[i].receita;
        }
    }

    return -1;
}

float consulta_valor(int id_medicamento)
{
    if(id_medicamento <= 0)
        return -2;

    for(int i = 0; i < qtdMedicamentos; i++)
    {
        if(medicamentos[i].id ==
           id_medicamento)
        {
            return medicamentos[i].valor;
        }
    }

    return -1;
}