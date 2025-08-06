#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARQUIVO_BINARIO "Agosto.dat"
#define ARQUIVO_TEXTO "Agosto.txt"


typedef struct {
    char descricao[100];
    double valor;
    char tipo;
    char data[11];
} Transacao;


void addTrans();
void verCofre();
void verMovimentos();
void verSaldo();
void limparDados();
void gerarRelatorio();
void limpar_buffer();
void menu();

int main() {
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                addTrans();
                break;
            case 2:
                verCofre();
                break;
            case 3:
                verMovimentos();
                break;
            case 4:
                verSaldo();
                break;
            case 5:
                limparDados();
                break;
            case 6:
                gerarRelatorio();
                break;
            case 0:
                printf("\n------------------ Programa Finalizado ------------------\n\n");
                break;
            default:
                printf("Opcao Invalida. Pressione Enter para tentar novamente.\n");
                getchar();
                break;
        }

    } while (opcao != 0);

    return 0;
}

void menu() {

    system("cls");
    // system("clear"); // Para Linux e macOS

    printf("\n=== Menu Financeiro ===\n");
    printf("1. Realizar transacao\n");
    printf("2. Consultar cofrinho\n");
    printf("3. Verificar movimentacoes\n");
    printf("4. Ver saldos atuais\n");
    printf("5. Limpar todos os dados\n");
    printf("6. Gerar Relatorio em arquivo de texto\n");
    printf("0. Sair do programa\n");
    printf("\nSelecione a opcao desejada: ");
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void gerarRelatorio() {
    system("cls");
    FILE *fp_bin, *fp_txt;
    Transacao trans;


    fp_bin = fopen(ARQUIVO_BINARIO, "rb");
    if (fp_bin == NULL) {
        printf("\nNenhum dado encontrado para gerar o relatorio.\n");
        printf("Pressione Enter para voltar ao menu...");
        getchar();
        return;
    }


    fp_txt = fopen(ARQUIVO_TEXTO, "w");
    if (fp_txt == NULL) {
        printf("\nErro ao criar o arquivo de relatorio!\n");
        fclose(fp_bin);
        return;
    }

    printf("\nGerando relatorio...\n");


    fprintf(fp_txt, "+------------+-----------+------------------------------------------+---------------+\n");
    fprintf(fp_txt, "| Data       | Tipo      | Descrição                                |    Valor (R$) |\n");
    fprintf(fp_txt, "+------------+-----------+------------------------------------------+---------------+\n");

    while (fread(&trans, sizeof(Transacao), 1, fp_bin) == 1) {
        char tipo_str[10];
        if (trans.tipo == 'R') strcpy(tipo_str, "Receita");
        else if (trans.tipo == 'D') strcpy(tipo_str, "Despesa");
        else strcpy(tipo_str, "Cofre");

        fprintf(fp_txt, "| %-10s | %-9s | %-40.40s | %13.2f |\n",
                trans.data, tipo_str, trans.descricao, trans.valor);
    }


    fprintf(fp_txt, "+------------+-----------+------------------------------------------+---------------+\n");

    fclose(fp_bin);
    fclose(fp_txt);

    printf("\nRelatorio '%s' gerado com sucesso!\n", ARQUIVO_TEXTO);
    printf("Pressione Enter para voltar ao menu...");
    getchar();
}


void limparDados() {
    char confirmacao;
    printf("\n!!! ATENCAO !!!\n");
    printf("Esta acao ira apagar TODOS os registros de transacoes permanentemente.\n");
    printf("Voce tem certeza que deseja continuar? (S/N): ");
    scanf(" %c", &confirmacao);
    limpar_buffer();

    if (toupper(confirmacao) == 'S') {
        int status_bin = remove(ARQUIVO_BINARIO);
        int status_txt = remove(ARQUIVO_TEXTO);

        if (status_bin == 0 || status_txt == 0) {
            printf("\nTodos os dados foram excluidos com sucesso.\n");
        } else {
            printf("\nNenhum dado encontrado para excluir ou ocorreu um erro.\n");
        }
    } else {
        printf("\nOperacao cancelada. Seus dados estao seguros.\n");
    }

    printf("Pressione Enter para voltar ao menu...");
    getchar();
}

void addTrans() {
    system("cls");
    Transacao nova;
    FILE *fp_bin;

    printf("\n\t\t+ Nova Transacao +\n");

    do {
        printf("\nTipo (R para RECEITA, D para DESPESA, C para COFRINHO): ");
        scanf(" %c", &nova.tipo);
        nova.tipo = toupper(nova.tipo);
        limpar_buffer();
        if (nova.tipo != 'R' && nova.tipo != 'D' && nova.tipo != 'C') {
            printf("Tipo invalido. Use R, D ou C.\n");
        }
    } while (nova.tipo != 'R' && nova.tipo != 'D' && nova.tipo != 'C');

    printf("\nDescricao: ");
    fgets(nova.descricao, 100, stdin);
    nova.descricao[strcspn(nova.descricao, "\n")] = 0;

    printf("\nData (DD/MM/AAAA): ");
    fgets(nova.data, 11, stdin);
    nova.data[strcspn(nova.data, "\n")] = 0;
    limpar_buffer();

    printf("\nValor (use ponto para centavos): ");
    scanf("%lf", &nova.valor);
    limpar_buffer();

    fp_bin = fopen(ARQUIVO_BINARIO, "ab");
    if (fp_bin == NULL) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }
    fwrite(&nova, sizeof(Transacao), 1, fp_bin);
    fclose(fp_bin);

    printf("\nTransacao adicionada com sucesso!\n");
    printf("Pressione Enter para voltar ao menu...");
    getchar();
}

void verMovimentos() {
    system("cls");
    Transacao trans;
    FILE *fp_bin;

    fp_bin = fopen(ARQUIVO_BINARIO, "rb");
    if (fp_bin == NULL) {
        printf("\nNenhuma transacao registrada ainda.\n");
        printf("Pressione Enter para voltar ao menu...");
        getchar();
        return;
    }

    printf("\n\t\t--- Todas as Movimentacoes (lido do .dat) ---\n");
    while (fread(&trans, sizeof(Transacao), 1, fp_bin) == 1) {
        printf("----------------------------------------\n");
        printf("Data: %s\n", trans.data);
        printf("Tipo: %c\n", trans.tipo);
        printf("Descricao: %s\n", trans.descricao);
        printf("Valor: R$ %.2f\n", trans.valor);
    }
    printf("----------------------------------------\n");

    fclose(fp_bin);
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

void verSaldo() {
    system("cls");
    Transacao trans;
    FILE *fp_bin;
    double saldo_total = 0.0, total_receitas = 0.0, total_despesas = 0.0, total_cofre = 0.0;

    fp_bin = fopen(ARQUIVO_BINARIO, "rb");
    if (fp_bin == NULL) {
        printf("\nNenhuma transacao registrada ainda.\n");
        printf("Pressione Enter para voltar ao menu...");
        getchar();
        return;
    }

    while (fread(&trans, sizeof(Transacao), 1, fp_bin) == 1) {
        switch (trans.tipo) {
            case 'R':
                total_receitas += trans.valor;
                break;
            case 'D':
                total_despesas += trans.valor;
                break;
            case 'C':
                total_cofre += trans.valor;
                break;
        }
    }
    fclose(fp_bin);

    saldo_total = total_receitas - total_despesas - total_cofre;

    printf("\n\t\t--- Saldos Atuais ---\n");
    printf("Total de Receitas: R$ %.2f\n", total_receitas);
    printf("Total de Despesas: R$ %.2f\n", total_despesas);
    printf("Total guardado no Cofre: R$ %.2f\n", total_cofre);
    printf("----------------------------------------\n");
    printf("Saldo Disponivel Atual: R$ %.2f\n", saldo_total);
    printf("----------------------------------------\n");

    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}

void verCofre() {
    system("cls");
    Transacao trans;
    FILE *fp_bin;
    double total_cofre = 0.0;

    fp_bin = fopen(ARQUIVO_BINARIO, "rb");
    if (fp_bin == NULL) {
        printf("\nNenhuma transacao registrada para o cofrinho.\n");
        printf("Pressione Enter para voltar ao menu...");
        getchar();
        return;
    }

    printf("\n\t\t--- Movimentacoes do Cofrinho ---\n");
    while (fread(&trans, sizeof(Transacao), 1, fp_bin) == 1) {
        if (trans.tipo == 'C') {
            printf("----------------------------------------\n");
            printf("Data: %s\n", trans.data);
            printf("Descricao: %s\n", trans.descricao);
            printf("Valor guardado: R$ %.2f\n", trans.valor);
            total_cofre += trans.valor;
        }
    }
    printf("----------------------------------------\n");
    printf("Total acumulado no cofrinho: R$ %.2f\n", total_cofre);
    printf("----------------------------------------\n");

    fclose(fp_bin);
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
}
