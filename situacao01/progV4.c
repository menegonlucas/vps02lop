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

void mostrarDados()
{
    printf("Viagens ACME:\n");
    printf("Matricula\tFuncionario\tData\t\tOrigem\t\t\tDestino\t\t\tDistância\tPreço\tTotal\t\tReembolso\n");

    // Estrutura para armazenar o total do reembolso por funcionário
    typedef struct
    {
        char funcionario[50];
        float totalReembolso;
    } ReembolsoFuncionario;

    ReembolsoFuncionario reembolsos[50];
    int totalFuncionarios = 0;

    for (i = 0; i < totalViagens; i++)
    {
        printf("%d\t\t%s\t\t%s\t%s\t\t%s\t\t%d\t\t%.2f\t%.2f\t%.2f\n", 
            viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem, viagens[i].destino, 
            viagens[i].distancia, viagens[i].preco, viagens[i].total, viagens[i].reembolso);

        // Verificar se o funcionário já está na lista de reembolsos
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

        // Se não encontrou, adiciona um novo funcionário na lista
        if (!found)
        {
            strcpy(reembolsos[totalFuncionarios].funcionario, viagens[i].funcionario);
            reembolsos[totalFuncionarios].totalReembolso = viagens[i].reembolso;
            totalFuncionarios++;
        }
    }

    printf("\nTotal geral de reembolso: %.2f\n", totalReembolsoGeral);

    // Mostrar o total do reembolso por funcionário
    printf("\nTotal de reembolso por funcionário:\n");
    for (int j = 0; j < totalFuncionarios; j++)
    {
        printf("Funcionário: %s, Total de Reembolso: %.2f\n", reembolsos[j].funcionario, reembolsos[j].totalReembolso);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    mostrarDados();
    return 0;
}

