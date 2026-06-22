#include <stdio.h>
#include <stdlib.h>

#include "clientes/clientes.h"
#include "medicamentos/medicamentos.h"
#include "estoque/estoque.h"
#include "vendas/vendas.h"


void pausar(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void limparTela(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void menuClientes(void)
{
    int opcao;

    do
    {
        limparTela();

        printf("===== CLIENTES =====\n\n");

        printf("1 - Listar clientes\n");
        printf("2 - Cadastrar cliente\n");
        printf("3 - Alterar cliente\n");
        printf("4 - Excluir cliente\n");
        printf("0 - Voltar\n\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            listarClientes();
            pausar();
        }

        else if(opcao == 2)
        {
            char nome[100];
            char cpf[12];
            char telefone[20];

            printf("Nome: ");
            scanf(" %99[^\n]", nome);

            printf("CPF: ");
            scanf("%11s", cpf);

            printf("Telefone: ");
            scanf("%19s", telefone);

            printf("Retorno: %d\n", cadastrarCliente(nome, cpf, telefone));

            pausar();
        }
        else if(opcao == 3)
        {
            char cpf[12];
            char novo_nome[100];
            char novo_telefone[20];

            
            printf("CPF: ");
            scanf("%11s", cpf);

            int retorno = buscarCliente(cpf);

            if(retorno >= 0){
                printf("Novo nome: ");
                scanf(" %99[^\n]", novo_nome);
                
                printf("Novo telefone: ");
                scanf("%19s", novo_telefone);

                printf("Retorno: %d\n", alterarCliente(cpf, novo_nome, novo_telefone));
            }
            else{
                if (retorno == -1){
                    printf("Cliente não cadastrado");
                }
                else if (retorno == -2){
                    printf("CPF invalido");
                }
            }

             pausar();
        }
        else if(opcao == 4)
        {
            char cpf[12];
            
            printf("CPF: ");
            scanf("%11s", cpf);

            int retorno = buscarCliente(cpf);

            if(retorno >= 0){
                printf("Retorno: %d\n", excluirCliente(cpf));
            }
            else{
                if (retorno == -1){
                    printf("Cliente não cadastrado");
                }
                else if (retorno == -2){
                    printf("CPF invalido");
                }
            }
            
             pausar();
        }

    } while(opcao != 0);
}

void menuMedicamentos(void)
{
    int opcao;

    do
    {
        limparTela();

        printf("===== MEDICAMENTOS =====\n\n");

        printf("1 - Consultar medicamento\n");
        printf("2 - Cadastrar medicamento\n");
        printf("3 - Alterar medicamento\n");
        printf("4 - Excluir medicamento\n");
        printf("0 - Voltar\n\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            int id;

            printf("ID: ");
            scanf("%d", &id);

            Medicamento med = consulta_medicamento(id);

            if (med.id == -1){
                printf("\nMedicamento não encontrado\n");
            }else{
                printf("\nNome: %s\n", med.nome);
                printf("Valor: %.2f\n", med.valor);
            }

            pausar();
        }

        else if(opcao == 2)
        {
            int id;
            char nome[100];
            float valor;
            int receita;

            printf("ID: ");
            scanf("%d", &id);

            printf("Nome: ");
            scanf(" %99[^\n]", nome);

            printf("Valor: ");
            scanf("%f", &valor);

            printf("Receita (0/1): ");
            scanf("%d", &receita);

            printf("Retorno: %d\n",
                   cadastra_medicamento(
                       id,
                       nome,
                       valor,
                       receita));

            pausar();
        }
        else if (opcao == 3)
        {
            int id;
            char novo_nome[100];
            float novo_valor;
            int nova_receita;

            printf("ID: ");
            scanf("%d", &id);

            Medicamento med = consulta_medicamento(id);

            if (med.id == -1){
                printf("\nMedicamento não encontrado\n");
            }
            else
            {
                printf("Novo nome: ");
                scanf(" %99[^\n]", novo_nome);
    
                printf("Novo valor: ");
                scanf("%f", &novo_valor);
    
                printf("Nova receita (0/1): ");
                scanf("%d", &nova_receita);
    
                printf("Retorno: %d\n", altera_medicamento(id, novo_nome, novo_valor, nova_receita));
            }

            pausar();
        }
        else if (opcao == 4)
        {
            int id;

            printf("ID: ");
            scanf("%d", &id);

            Medicamento med = consulta_medicamento(id);

            if (med.id == -1){
                printf("\nMedicamento não encontrado\n");
            }
            else
            {
                printf("Retorno: %d\n", deleta_medicamento(id));
            }

            pausar();
        }

    } while(opcao != 0);
}

void menuEstoque(void)
{
    int opcao;

    do
    {
        limparTela();

        printf("===== ESTOQUE =====\n\n");

        printf("1 - Consultar estoque\n");
        printf("2 - Adicionar estoque\n");
        printf("3 - Remover estoque\n");
        printf("0 - Voltar\n\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            int id;
            int qtd;

            printf("ID medicamento: ");
            scanf("%d", &id);

            if(consulta_estoque(id, &qtd) == 0)
                printf("Quantidade: %d\n", qtd);
            else printf("Não Encontrado");

            pausar();
        }

        else if(opcao == 2)
        {
            int id;
            int qtd;

            printf("ID medicamento: ");
            scanf("%d", &id);

            Medicamento med = consulta_medicamento(id);

            if (med.id == -1){
                printf("\nMedicamento não encontrado\n");
            }
            else{
                printf("Quantidade: ");
                scanf("%d", &qtd);

                printf("Retorno: %d\n", adiciona_estoque(id, qtd));
            }

            pausar();
        }
        else if(opcao == 3)
        {
            int id;
            int qtd;

            printf("ID medicamento: ");
            scanf("%d", &id);

            Medicamento med = consulta_medicamento(id);

            if (med.id == -1){
                printf("\nMedicamento não encontrado\n");
            }
            else{
                printf("Quantidade: ");
                scanf("%d", &qtd);

                printf("Retorno: %d\n", remove_estoque(id, qtd));
            }

            pausar();
        }

    } while(opcao != 0);
}

void menuVendas(void)
{
    int opcao;

    do
    {
        limparTela();

        printf("===== VENDAS =====\n\n");

        printf("1 - Adicionar ao carrinho\n");
        printf("2 - Remover do carrinho\n");
        printf("3 - Consultar carrinho\n");
        printf("4 - Registrar venda\n");
        printf("5 - Consultar historico\n");
        printf("6 - Gerar relatorio\n");
        printf("0 - Voltar\n\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
            {
                int id;
                int qtd;

                printf("ID: ");
                scanf("%d", &id);

                printf("Quantidade: ");
                scanf("%d", &qtd);

                int estoque;
                if (consulta_estoque(id, &estoque) == 0 && estoque < qtd){
                    printf("Estoque possui apenas %d unidades\n", estoque);
                }

                printf("Retorno: %d\n", adiciona_carrinho(id, qtd));

                pausar();
                break;
            }
            case 2:
            {
                int id;

                printf("ID: ");
                scanf("%d", &id);

                printf("Retorno: %d\n", remove_carrinho(id));

                pausar();
                break;
            }
            case 3:
            {
                Cart carrinho;
                float valor_total = 0;

                if(consulta_carrinho(&carrinho) == 0)
                {
                    int i;

                    printf("\nItens:\n");

                    for(i = 0; i < carrinho.qtd_itens; i++)
                    {
                        float valor_unitario = consulta_valor(carrinho.itens[i].id_medicamento);
                        int qtd = carrinho.itens[i].quantidade;

                        printf("%s - Valor unitario %.2f - Qtd %d - Semitotal: R$%.2f \n", carrinho.itens[i].nome, valor_unitario, qtd, (valor_unitario*qtd));
                        valor_total += valor_unitario*qtd;
                    }

                    printf("Total do carrinho: R$%.2f\n", valor_total);
                }

                pausar();
                break;
            }

            case 4:
            {
                long long cpf;

                printf("CPF: ");
                scanf("%lld", &cpf);

                printf("Retorno: %d\n", registra_venda(cpf));

                pausar();
                break;
            }
            case 5:
            {
                Venda historico[MAX_VENDAS];
                int qtd;
                char cpf[12];
                long long cpf_int;
                int status;

                printf("CPF: ");
                scanf("%lld", &cpf_int);

                snprintf(cpf, sizeof(cpf), "%lld", cpf_int);
                if(validarCPF(cpf) == 1){
                    printf("CPF invalido\n");
                }
                else{
                    status = consulta_historico(cpf_int,  historico, &qtd);
                    if(status == SUCESSO)
                    {
                        imprime_historico(historico, qtd);
                    }
                    else
                    {
                        if (status == ERRO_SEM_HISTORICO){
                            printf("Cliente nao possui vendas\n");
                        }
                    }
                }

                pausar();
                break;
            }
            case 6:
            {
                int dias;

                printf("Periodo (dias): ");
                scanf("%d", &dias);

                printf("Retorno: %d\n", gera_relatorio(dias));

                pausar();
                break;
            }
        }

    } while(opcao != 0);
}

void menuPrincipal(void)
{
    int opcao;

    do
    {
        limparTela();

        printf("=====================================\n");
        printf("      SISTEMA DE FARMACIA\n");
        printf("=====================================\n\n");

        printf("1 - Clientes\n");
        printf("2 - Medicamentos\n");
        printf("3 - Estoque\n");
        printf("4 - Vendas\n");
        printf("0 - Sair\n\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                menuClientes();
                break;

            case 2:
                menuMedicamentos();
                break;

            case 3:
                menuEstoque();
                break;

            case 4:
                menuVendas();
                break;
        }

    } while(opcao != 0);
}

int main(void)
{
    carregarClientes();
    carregarMedicamentos();
    carregar_estoque();
    carregar_vendas();

    menuPrincipal();

    salvarMedicamentos();
    salvar_estoque();
    salvar_vendas();
    salvarClientes();

    return 0;
}