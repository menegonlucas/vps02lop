#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    int matricula;
    char funcionario[50];
    char data[12];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
    float reembolso;
} Viagem;

Viagem viagens[50];
int totalViagens = 0, i;
float totalReembolsoGeral = 0;

void carregaDados()
{
    FILE *arq;
    char linha[200];
    arq = fopen("viagens.txt", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 200, arq); // Ignorar a primeira linha
        while (fgets(linha, 200, arq) != NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            viagens[totalViagens].total = viagens[totalViagens].distancia * viagens[totalViagens].preco;
            viagens[totalViagens].reembolso = viagens[totalViagens].total / 3; // Calcular o reembolso
            totalReembolsoGeral += viagens[totalViagens].reembolso; // Acumular o total do reembolso
            totalViagens++;
        }
    }
    fclose(arq);
}

void gerarRelatorioMarkdown()
{
    FILE *arq;
    arq = fopen("RelatorioViagens.md", "w");
    if (arq == NULL)
    {
        printf("Erro ao criar o arquivo\n");
    }
    else
    {
        fprintf(arq, "# Relatório de Viagens\n\n");
        fprintf(arq, "## Viagens ACME\n\n");
        fprintf(arq, "| Matrícula | Funcionário | Data       | Origem         | Destino        | Distância | Preço | Total  | Reembolso |\n");
        fprintf(arq, "|-----------|-------------|------------|----------------|----------------|-----------|-------|--------|-----------|\n");

        for (i = 0; i < totalViagens; i++)
        {
            fprintf(arq, "| %d | %s | %s | %s | %s | %d | %.2f | %.2f | %.2f |\n",
                    viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem, viagens[i].destino,
                    viagens[i].distancia, viagens[i].preco, viagens[i].total, viagens[i].reembolso);
        }

        fprintf(arq, "\n\n---\n");
        fprintf(arq, "### Total Geral de Reembolso: %.2f\n\n", totalReembolsoGeral);

        fprintf(arq, "### Total de Reembolso por Funcionário:\n\n");
        fprintf(arq, "| Funcionário | Total Reembolso |\n");
        fprintf(arq, "|-------------|-----------------|\n");
        // Calculando e imprimindo o total de reembolso por funcionário
        typedef struct
        {
            char funcionario[50];
            float totalReembolso;
        } ReembolsoFuncionario;

        ReembolsoFuncionario reembolsos[50];
        int totalFuncionarios = 0;

        for (i = 0; i < totalViagens; i++)
        {
            int found = 0;
            for (int j = 0; j < totalFuncionarios; j++)
            {
                if (strcmp(reembolsos[j].funcionario, viagens[i].funcionario) == 0)
                {
                    reembolsos[j].totalReembolso += viagens[i].reembolso;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                strcpy(reembolsos[totalFuncionarios].funcionario, viagens[i].funcionario);
                reembolsos[totalFuncionarios].totalReembolso = viagens[i].reembolso;
                totalFuncionarios++;
            }
        }

        for (int j = 0; j < totalFuncionarios; j++)
        {
            fprintf(arq, "| %s | %.2f |\n", reembolsos[j].funcionario, reembolsos[j].totalReembolso);
        }
        fclose(arq);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    gerarRelatorioMarkdown();
    return 0;
}
