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

void carregaDados()
{
    FILE *arq;
    char linha[200]; // Aumentei o tamanho da linha para 200 para garantir que caberá o conteúdo
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
            totalViagens++;
        }
    }
    fclose(arq);
}

void mostrarDados()
{
    printf("Viagens ACME:\n");
    printf("Matricula\tFuncionario\tData\tOrigem\tDestino\tDistância\tPreço\tTotal\tReembolso\n");
    for(i=0; i < totalViagens; i++)
    {
        printf("%d\t%s\t%s\t%s\t%s\t%d\t%.2f\t%.2f\t%.2f\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem,  viagens[i].destino, viagens[i].distancia, viagens[i].preco,  viagens[i].total, viagens[i].reembolso);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    mostrarDados();
    return 0;
}
