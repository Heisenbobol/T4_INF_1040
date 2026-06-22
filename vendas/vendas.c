#include <string.h>
#include "vendas.h"
#include "../clientes/clientes.h"
#include "../estoque/estoque.h"
#include "../medicamentos/medicamentos.h"

static BancoVendas banco_vendas;
static Cart carrinho_atual;

/*MOCKINGs*/
/*
int consulta_medicamento(int id){
    if (id == 1){
        return 1;
    }
    return 0;
}
int consulta_cliente(int cpf){
    if (cpf == 123456789 || cpf == 222222222){
        return SUCESSO;
    }
    return ERRO_PARAMETRO_INVALIDO;
}
float consulta_valor(int id){
    if (id == 1){
        return 25.50;
    }
    return 42.75;
}
int consulta_estoque(int id, int* quantidade){
    if (id == 1){
        *quantidade = 10;
        return 0;
    }
    return 1;
}
*/

void popular_dados_teste(void)
{
    banco_vendas.qtd_vendas = 2;

    banco_vendas.vendas[0].id_venda = 1;
    banco_vendas.vendas[0].cpf_cliente = 123456789;
    banco_vendas.vendas[0].data = time(NULL);
    banco_vendas.vendas[0].valor_total = 25.50;

    banco_vendas.vendas[1].id_venda = 2;
    banco_vendas.vendas[1].cpf_cliente = 123456789;
    banco_vendas.vendas[1].data = time(NULL);
    banco_vendas.vendas[1].valor_total = 42.75;

    salvar_vendas();
}

int consulta_carrinho(Cart *resultado)
{
    if(resultado == NULL)
        return ERRO_PARAMETRO_INVALIDO;

    if(carrinho_atual.qtd_itens == 0)
        return ERRO_CARRINHO_VAZIO;

    *resultado = carrinho_atual;

    return SUCESSO;
}

int adiciona_carrinho(int id_medicamento, int quantidade)
{
    int i;
    Medicamento med;

    if(id_medicamento <= 0 || quantidade <= 0)
        return ERRO_PARAMETRO_INVALIDO;

    med = consulta_medicamento(id_medicamento);

    if(med.id == -1)
        return ERRO_NAO_CADASTRADO;

    for(i = 0; i < carrinho_atual.qtd_itens; i++)
    {
        if(carrinho_atual.itens[i].id_medicamento == id_medicamento)
        {
            carrinho_atual.itens[i].quantidade += quantidade;
            return SUCESSO;
        }
    }

    if(carrinho_atual.qtd_itens >= MAX_ITENS_CARRINHO)
        return ERRO_PARAMETRO_INVALIDO;

    carrinho_atual.itens[carrinho_atual.qtd_itens].id_medicamento = id_medicamento;
    strcpy(carrinho_atual.itens[carrinho_atual.qtd_itens].nome, med.nome);
    carrinho_atual.itens[carrinho_atual.qtd_itens].quantidade = quantidade;

    carrinho_atual.qtd_itens++;

    return SUCESSO;
}

int remove_carrinho(int id_medicamento)
{
    int i;
    int j;
    Medicamento med;

    if(id_medicamento <= 0)
        return ERRO_PARAMETRO_INVALIDO;

    med = consulta_medicamento(id_medicamento);

    if(med.id == -1)
        return ERRO_NAO_CADASTRADO;

    for(i = 0; i < carrinho_atual.qtd_itens; i++)
    {
        if(carrinho_atual.itens[i].id_medicamento == id_medicamento)
        {
            for(j = i; j < carrinho_atual.qtd_itens - 1; j++)
            {
                carrinho_atual.itens[j] = carrinho_atual.itens[j + 1];
            }

            carrinho_atual.qtd_itens--;

            return SUCESSO;
        }
    }

    return ERRO_NAO_ENCONTRADO;
}

int registra_venda(long long cpf_cliente)
{
    Venda venda;
    int i;

    /* valida cpf */
    char cpf[12];
    snprintf(cpf, sizeof(cpf), "%lld", cpf_cliente);
    if(buscarCliente(cpf) != SUCESSO)
        return ERRO_PARAMETRO_INVALIDO;

    /* carrinho vazio */
    if(carrinho_atual.qtd_itens == 0)
        return ERRO_CARRINHO_VAZIO;

    /* inicializa venda */
    venda.id_venda = banco_vendas.qtd_vendas + 1;
    venda.cpf_cliente = cpf_cliente;
    venda.data = time(NULL);
    venda.qtd_itens = 0;
    venda.valor_total = 0;

    /* copia itens do carrinho para a venda */
    for(i = 0; i < carrinho_atual.qtd_itens; i++)
    {
        int id = carrinho_atual.itens[i].id_medicamento;
        int qtd = carrinho_atual.itens[i].quantidade;
        float valor = consulta_valor(id);
        int estoque;
        int status = consulta_estoque(id, &estoque);

        if(estoque <= qtd || status != 0){
            printf("Quantidade: %d\n",qtd);
            return ERRO_ESTOQUE;
        }

        venda.itens[i].id_medicamento = id;
        venda.itens[i].quantidade = qtd;
        venda.itens[i].valor_unitario = valor;

        venda.valor_total += valor * qtd;
        venda.qtd_itens++;
    }

    /* salva no histórico */
    if(banco_vendas.qtd_vendas >= MAX_VENDAS)
        return ERRO_LEITURA_ESCRITA;

    banco_vendas.vendas[banco_vendas.qtd_vendas++] = venda;

    /* limpa carrinho */
    carrinho_atual.qtd_itens = 0;

    return SUCESSO;
}

int gera_relatorio(int periodo)
{
    FILE *arquivo;
    time_t agora;
    time_t limite;

    int i;
    int qtd_vendas = 0;

    float faturamento = 0;

    agora = time(NULL);
    limite = agora - (periodo * 24 * 60 * 60);

    arquivo = fopen("relatorio.txt", "w");

    if(arquivo == NULL)
        return ERRO_LEITURA_ESCRITA;

    for(i = 0; i < banco_vendas.qtd_vendas; i++)
    {
        if(banco_vendas.vendas[i].data >= limite)
        {
            qtd_vendas++;
            faturamento += banco_vendas.vendas[i].valor_total;
        }
    }

    fprintf(arquivo, "RELATORIO DOS ULTIMOS %d DIAS\n\n", periodo);

    fprintf(arquivo, "Quantidade de vendas: %d\n", qtd_vendas);

    fprintf(arquivo, "Faturamento total: R$ %.2f\n", faturamento);

    fclose(arquivo);

    return SUCESSO;
}

void imprime_historico(Venda historico[], int qtd_vendas)
{
    int i;
    int j;

    if(qtd_vendas == 0)
    {
        printf("Nenhuma venda encontrada.\n");
        return;
    }

    printf("\n========== HISTORICO DE COMPRAS ==========\n");

    for(i = 0; i < qtd_vendas; i++)
    {
        printf("\nVenda #%d\n",
               historico[i].id_venda);

        printf("CPF: %lld\n",
               historico[i].cpf_cliente);

        printf("Data: %s",
               ctime(&historico[i].data));

        printf("Valor Total: R$ %.2f\n",
               historico[i].valor_total);

        printf("Itens:\n");

        for(j = 0; j < historico[i].qtd_itens; j++)
        {
            printf("  Medicamento: %d",
                   historico[i].itens[j].id_medicamento);

            printf(" | Qtd: %d",
                   historico[i].itens[j].quantidade);

            printf(" | Valor Unit.: R$ %.2f\n",
                   historico[i].itens[j].valor_unitario);
        }

        printf("------------------------------------------\n");
    }
}

int consulta_historico(long long cpf_cliente, Venda historico[], int *qtd_vendas)
{
    int i;
    int encontradas = 0;

    if(qtd_vendas == NULL){
        return ERRO_PARAMETRO_INVALIDO;
    }

    char cpf[12];
    snprintf(cpf, sizeof(cpf), "%lld", cpf_cliente);
    if(buscarCliente(cpf) != SUCESSO){
        return ERRO_PARAMETRO_INVALIDO;
    }

    for(i = 0; i < banco_vendas.qtd_vendas; i++)
    {
        if(banco_vendas.vendas[i].cpf_cliente == cpf_cliente)
        {
            historico[encontradas] = banco_vendas.vendas[i];
            encontradas++;
        }
    }

    if(encontradas == 0)
        return ERRO_SEM_HISTORICO;

    *qtd_vendas = encontradas;

    return SUCESSO;
}

int salvar_vendas(void)
{
    FILE *arquivo;

    arquivo = fopen("vendas.dat", "wb");

    if(arquivo == NULL)
        return ERRO_LEITURA_ESCRITA;

    fwrite(&banco_vendas.qtd_vendas,
           sizeof(int),
           1,
           arquivo);

    fwrite(banco_vendas.vendas,
           sizeof(Venda),
           banco_vendas.qtd_vendas,
           arquivo);

    fclose(arquivo);

    return SUCESSO;
}

int carregar_vendas(void)
{
    FILE *arquivo;

    arquivo = fopen("vendas.dat", "rb");

    if(arquivo == NULL)
    {
        banco_vendas.qtd_vendas = 0;
        return SUCESSO;
    }

    fread(&banco_vendas.qtd_vendas,
          sizeof(int),
          1,
          arquivo);

    fread(banco_vendas.vendas,
          sizeof(Venda),
          banco_vendas.qtd_vendas,
          arquivo);
    
    if(banco_vendas.qtd_vendas < 0 || banco_vendas.qtd_vendas > MAX_VENDAS)
    {
        fclose(arquivo);
        return ERRO_LEITURA_ESCRITA;
    }

    fclose(arquivo);

    return SUCESSO;
}
