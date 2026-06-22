#include "vendas.h"

int main(void)
{
    printf("TESTES\n");

    carregar_vendas();

    //GERAR_RELATORIO
    printf("\n===== CASO 42 =====\n");
    printf("gera_relatorio()\n");
    printf("Retorno: %d\n", gera_relatorio(30));

    
    //REGISTRA_VENDA
    adiciona_carrinho(1, 2);

    printf("\n===== CASO 44 =====\n");
    printf("registra_venda(cpf valido)\n");
    printf("Retorno: %d\n", registra_venda(123456789));

    printf("\n===== CASO 45 =====\n");
    printf("registra_venda(cpf invalido)\n");
    printf("Retorno: %d\n", registra_venda(-1));

    remove_carrinho(1);

    //ADICIONA_CARRINHO
    printf("\n===== CASO 46 =====\n");
    printf("adiciona_carrinho(id valido)\n");
    printf("Retorno: %d\n", adiciona_carrinho(1, 2));

    printf("\n===== CASO 47 =====\n");
    printf("adiciona_carrinho(medicamento nao cadastrado)\n");
    printf("Retorno: %d\n", adiciona_carrinho(9999, 2));

    printf("\n===== CASO 48 =====\n");
    printf("adiciona_carrinho(id invalido)\n");
    printf("Retorno: %d\n", adiciona_carrinho(-1, 2));

    //REMOVE_CARRINHO
    adiciona_carrinho(1, 2);

    printf("\n===== CASO 49 =====\n");
    printf("remove_carrinho(item presente)\n");
    printf("Retorno: %d\n", remove_carrinho(1));

    printf("\n===== CASO 50 =====\n");
    printf("remove_carrinho(item fora do carrinho)\n");
    printf("Retorno: %d\n", remove_carrinho(1));

    printf("\n===== CASO 51 =====\n");
    printf("remove_carrinho(medicamento nao cadastrado)\n");
    printf("Retorno: %d\n", remove_carrinho(9999));

    printf("\n===== CASO 52 =====\n");
    printf("remove_carrinho(id invalido)\n");
    printf("Retorno: %d\n", remove_carrinho(-1));

    //CONSULTA_CARRINHO
    Cart carrinho;

    printf("\n===== CASO 54 =====\n");
    printf("consulta_carrinho(vazio)\n");
    printf("Retorno: %d\n", consulta_carrinho(&carrinho));

    adiciona_carrinho(1, 2);

    printf("\n===== CASO 53 =====\n");
    printf("consulta_carrinho(com itens)\n");
    printf("Retorno: %d\n", consulta_carrinho(&carrinho));

    printf("Quantidade de itens: %d\n", carrinho.qtd_itens);

    //CONSULTA_HISTORICO

    Venda historico[MAX_VENDAS];
    int qtd;

    printf("\n===== CASO 55 =====\n");
    printf("consulta_historico(cliente com compras)\n");
    printf("Retorno: %d\n", consulta_historico(123456789,  historico, &qtd));

    printf("Quantidade de compras: %d\n", qtd);
    
    printf("\n===== CASO 56 =====\n");
    printf("consulta_historico(cliente sem compras)\n");
    printf("Retorno: %d\n", consulta_historico(222222222, historico, &qtd));

    printf("\n===== CASO 57 =====\n");
    printf("consulta_historico(cpf invalido)\n");
    printf("Retorno: %d\n", consulta_historico(-1, historico,  &qtd));

    salvar_vendas();

    return 0;
}