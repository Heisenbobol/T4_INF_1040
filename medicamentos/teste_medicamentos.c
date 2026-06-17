#include <stdio.h>
#include <stdbool.h>

#include "medicamentos.h"

int main()
{
    carregarMedicamentos();

    printf("=== CADASTRO ===\n");

    printf("%d\n",
           cadastra_medicamento(
               1,
               "Dipirona",
               15.50,
               false));

    printf("%d\n",
           cadastra_medicamento(
               1,
               "Dipirona",
               15.50,
               false));

    printf("%d\n",
           cadastra_medicamento(
               -1,
               "Dipirona",
               15.50,
               false));



    printf("\n=== CONSULTA ===\n");

    Medicamento m;

    m = consulta_medicamento(1);

    printf("ID=%d Nome=%s Valor=%.2f Receita=%d\n",
           m.id,
           m.nome,
           m.valor,
           m.receita);

    m = consulta_medicamento(999);

    printf("ID=%d\n", m.id);



    printf("\n=== ALTERACAO ===\n");

    printf("%d\n",
           altera_medicamento(
               1,
               "Dipirona Alterada",
               20.00,
               true));

    printf("%d\n",
           altera_medicamento(
               999,
               "Teste",
               10.00,
               false));



    printf("\n=== RECEITA ===\n");

    printf("%d\n",
           verifica_receita(1));

    printf("%d\n",
           verifica_receita(999));

    printf("%d\n",
           verifica_receita(-1));



    printf("\n=== VALOR ===\n");

    printf("%.2f\n",
           consulta_valor(1));

    printf("%.2f\n",
           consulta_valor(999));

    printf("%.2f\n",
           consulta_valor(-1));



    printf("\n=== EXCLUSAO ===\n");

    printf("%d\n",
           deleta_medicamento(1));

    printf("%d\n",
           deleta_medicamento(1));

    printf("%d\n",
           deleta_medicamento(-1));



    salvarMedicamentos();

    return 0;
}