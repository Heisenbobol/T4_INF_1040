#include <stdio.h>

#include "estoque.h"

void menuEstoque(void)
{
    int opcao;

    carregar_estoque();

    do
    {
        printf("\n========================\n");
        printf(" MODULO ESTOQUE\n");
        printf("========================\n");
        printf("1 - Consultar estoque\n");
        printf("2 - Adicionar estoque\n");
        printf("3 - Remover estoque\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
            {
                int id, qtd;
                int retorno;

                printf("ID do medicamento: ");
                scanf("%d", &id);

                retorno = consulta_estoque(id, &qtd);

                if(retorno == 0)
                {
                    printf("Quantidade em estoque: %d\n", qtd);
                }
                else if(retorno == 1)
                {
                    printf("Medicamento nao encontrado no estoque.\n");
                }
                else
                {
                    printf("ID invalido.\n");
                }

                break;
            }

            case 2:
            {
                int id, qtd;
                int retorno;

                printf("ID do medicamento: ");
                scanf("%d", &id);

                printf("Quantidade a adicionar: ");
                scanf("%d", &qtd);

                retorno = adiciona_estoque(id, qtd);

                if(retorno >= 0)
                {
                    salvar_estoque();
                    printf("Estoque atualizado. Nova quantidade: %d\n", retorno);
                }
                else if(retorno == -1)
                {
                    printf("Medicamento nao existe no sistema.\n");
                }
                else
                {
                    printf("Dados invalidos.\n");
                }

                break;
            }

            case 3:
            {
                int id, qtd;
                int retorno;

                printf("ID do medicamento: ");
                scanf("%d", &id);

                printf("Quantidade a remover: ");
                scanf("%d", &qtd);

                retorno = remove_estoque(id, qtd);

                if(retorno >= 0)
                {
                    salvar_estoque();
                    printf("Estoque atualizado. Nova quantidade: %d\n", retorno);
                }
                else if(retorno == -1)
                {
                    printf("Medicamento nao encontrado no estoque.\n");
                }
                else if(retorno == -3)
                {
                    printf("Quantidade insuficiente em estoque.\n");
                }
                else
                {
                    printf("ID invalido.\n");
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
