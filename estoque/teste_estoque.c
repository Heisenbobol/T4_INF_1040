#include <stdio.h>
#include "estoque.h"

int main(void)
{
    int qtd;
    int retorno;

    printf("=====================================\n");
    printf("TESTADOR DO MODULO ESTOQUE\n");
    printf("=====================================\n\n");

    carregar_estoque();

    /* Caso 32 */
    printf("Caso 32 - Consulta de medicamento existente\n");
    retorno = consulta_estoque(1, &qtd);
    printf("Retorno esperado: 0\n");
    printf("Retorno obtido: %d\n", retorno);
    printf("Quantidade obtida: %d\n\n", qtd);

    /* Caso 33 */
    printf("Caso 33 - Medicamento nao encontrado\n");
    retorno = consulta_estoque(999, &qtd);
    printf("Retorno esperado: 1\n");
    printf("Retorno obtido: %d\n\n", retorno);

    /* Caso 34 */
    printf("Caso 34 - ID invalido\n");
    retorno = consulta_estoque(-1, &qtd);
    printf("Retorno esperado: 2\n");
    printf("Retorno obtido: %d\n\n", retorno);

    /* Caso 35 */
    printf("Caso 35 - Adicionar estoque de medicamento existente\n");
    retorno = adiciona_estoque(1, 10);
    printf("Retorno esperado: quantidade atual\n");
    printf("Retorno obtido: %d\n\n", retorno);

    /*
     * Caso 36
     * Este teste depende da integracao com o modulo Medicamentos.
     *
     * Comportamento esperado no projeto final:
     * retorno = -1 para medicamento nao cadastrado.
     *
     * Atualmente nao e possivel validar este caso,
     * pois o modulo Medicamentos ainda nao foi implementado.
     */
    printf("Caso 36 - PENDENTE (integracao com modulo Medicamentos)\n\n");

    /* Caso 37 */
    printf("Caso 37 - ID invalido ao adicionar estoque\n");
    retorno = adiciona_estoque(-1, 10);
    printf("Retorno esperado: -2\n");
    printf("Retorno obtido: %d\n\n", retorno);

    /* Caso 38 */
    printf("Caso 38 - Remover estoque com sucesso\n");
    retorno = remove_estoque(1, 5);
    printf("Retorno esperado: quantidade atual\n");
    printf("Retorno obtido: %d\n\n", retorno);

    /* Caso 39 */
    printf("Caso 39 - Quantidade insuficiente\n");
    retorno = remove_estoque(1, 9999);
    printf("Retorno esperado: -3\n");
    printf("Retorno obtido: %d\n\n", retorno);

    /* Caso 40 */
    printf("Caso 40 - Medicamento nao encontrado\n");
    retorno = remove_estoque(999, 5);
    printf("Retorno esperado: -1\n");
    printf("Retorno obtido: %d\n\n", retorno);

    /* Caso 41 */
    printf("Caso 41 - ID invalido\n");
    retorno = remove_estoque(-1, 5);
    printf("Retorno esperado: -2\n");
    printf("Retorno obtido: %d\n\n", retorno);

    printf("=====================================\n");
    printf("FIM DOS TESTES\n");
    printf("=====================================\n");

    return 0;
}