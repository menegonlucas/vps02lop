#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_DAYS 31 // Número máximo de dias em um mês

int main() {
    // Abrindo o arquivo para leitura
    FILE *arquivo;
    arquivo = fopen("producao.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Inicializando contadores para cada máquina e para cada dia
    int producao_por_dia[MAX_DAYS][4] = {0};
    int total_por_maquina[4] = {0};

    // Variáveis para armazenar os dados do arquivo
    char linha[MAX_LINE_LENGTH];
    char data[11], hora[6];
    int dia, maquina;

    // Lendo linha por linha do arquivo
    while (fgets(linha, MAX_LINE_LENGTH, arquivo) != NULL) {
        // Utilizando sscanf para extrair os dados da linha
        sscanf(linha, "%d/%*d/%*d;%*d:%*d;%d", &dia, &maquina);

        // Incrementando o contador da máquina correspondente e do dia correspondente
        total_por_maquina[maquina - 1]++;
        producao_por_dia[dia - 1][maquina - 1]++;
    }

    // Fechando o arquivo
    fclose(arquivo);

    // Salvando o relatório em um arquivo Markdown
    FILE *relatorio;
    relatorio = fopen("explosivos.md", "w");

    if (relatorio == NULL) {
        printf("Erro ao criar o arquivo de relatório.\n");
        return 1;
    }

    // Escrevendo no arquivo de relatório
    fprintf(relatorio, "# Relatório de Produção\n\n");
    fprintf(relatorio, "| Dia | Máquina 1 | Máquina 2 | Máquina 3 | Máquina 4 | Total |\n");
    fprintf(relatorio, "|-----|------------|------------|------------|------------|-------|\n");

    int total_geral = 0;

    for (int i = 0; i < MAX_DAYS; i++) {
        int total_por_dia = 0;
        fprintf(relatorio, "| %2d  |", i + 1);

        for (int j = 0; j < 4; j++) {
            fprintf(relatorio, " %10d |", producao_por_dia[i][j]);
            total_por_dia += producao_por_dia[i][j];
        }

        fprintf(relatorio, " %7d |\n", total_por_dia);
        total_geral += total_por_dia;
    }

    // Escrevendo o total por máquina
    fprintf(relatorio, "\n\n");
    fprintf(relatorio, "## Total por Máquina\n\n");
    fprintf(relatorio, "| Máquina | Total |\n");
    fprintf(relatorio, "|---------|-------|\n");

    for (int i = 0; i < 4; i++) {
        fprintf(relatorio, "|   %2d    | %5d |\n", i + 1, total_por_maquina[i]);
    }

    // Escrevendo o total geral
    fprintf(relatorio, "\n\n");
    fprintf(relatorio, "## Total Geral: %d\n", total_geral);

    // Fechando o arquivo de relatório
    fclose(relatorio);

    printf("Relatório gerado com sucesso!\n");

    return 0;
}
