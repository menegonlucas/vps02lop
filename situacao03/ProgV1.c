#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUTOS 100

typedef struct {
    int numero_de_serie;
    int resistencia;
    int durabilidade;
} Produto;

int main() {
    Produto produtos[MAX_PRODUTOS];
    int num_produtos = 0;
    int soma_resistencia = 0, soma_durabilidade = 0;
    int maior_resistencia = -1, menor_resistencia = -1;
    int maior_durabilidade = -1, menor_durabilidade = -1;

    // Abre o arquivo para leitura
    FILE *arquivo = fopen("parametros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ignora a linha de cabeçalho
    char linha[100];
    fgets(linha, 100, arquivo);

    // Lê os dados do arquivo
    while (fscanf(arquivo, "%d;%d;%d", &produtos[num_produtos].numero_de_serie,
                                          &produtos[num_produtos].resistencia,
                                          &produtos[num_produtos].durabilidade) == 3) {
        // Atualiza as somas
        soma_resistencia += produtos[num_produtos].resistencia;
        soma_durabilidade += produtos[num_produtos].durabilidade;

        // Atualiza os produtos com maior e menor resistência
        if (maior_resistencia == -1 || produtos[num_produtos].resistencia > produtos[maior_resistencia].resistencia)
            maior_resistencia = num_produtos;
        if (menor_resistencia == -1 || produtos[num_produtos].resistencia < produtos[menor_resistencia].resistencia)
            menor_resistencia = num_produtos;

        // Atualiza os produtos com maior e menor durabilidade
        if (maior_durabilidade == -1 || produtos[num_produtos].durabilidade > produtos[maior_durabilidade].durabilidade)
            maior_durabilidade = num_produtos;
        if (menor_durabilidade == -1 || produtos[num_produtos].durabilidade < produtos[menor_durabilidade].durabilidade)
            menor_durabilidade = num_produtos;

        num_produtos++;
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Verifica se o arquivo está vazio
    if (num_produtos == 0) {
        printf("Nenhum produto encontrado no arquivo.\n");
        return 1;
    }

    // Calcula e exibe as médias de resistência e durabilidade
    float media_resistencia = (float)soma_resistencia / num_produtos;
    float media_durabilidade = (float)soma_durabilidade / num_produtos;
    printf("Média de resistência: %.2f\n", media_resistencia);
    printf("Média de durabilidade: %.2f\n", media_durabilidade);

    // Exibe os produtos com maior e menor resistência
    printf("Produto com maior resistência:\n");
    printf("Número de série: %d\n", produtos[maior_resistencia].numero_de_serie);
    printf("Resistência: %d\n", produtos[maior_resistencia].resistencia);
    printf("Durabilidade: %d\n", produtos[maior_resistencia].durabilidade);
    printf("\nProduto com menor resistência:\n");
    printf("Número de série: %d\n", produtos[menor_resistencia].numero_de_serie);
    printf("Resistência: %d\n", produtos[menor_resistencia].resistencia);
    printf("Durabilidade: %d\n", produtos[menor_resistencia].durabilidade);

    // Exibe os produtos com maior e menor durabilidade
    printf("\nProduto com maior durabilidade:\n");
    printf("Número de série: %d\n", produtos[maior_durabilidade].numero_de_serie);
    printf("Resistência: %d\n", produtos[maior_durabilidade].resistencia);
    printf("Durabilidade: %d\n", produtos[maior_durabilidade].durabilidade);
    printf("\nProduto com menor durabilidade:\n");
    printf("Número de série: %d\n", produtos[menor_durabilidade].numero_de_serie);
    printf("Resistência: %d\n", produtos[menor_durabilidade].resistencia);
    printf("Durabilidade: %d\n", produtos[menor_durabilidade].durabilidade);

    // Informa se existem mais produtos acima ou abaixo das médias
    int acima_media = 0, abaixo_media = 0;
    for (int i = 0; i < num_produtos; i++) {
        if (produtos[i].resistencia > media_resistencia && produtos[i].durabilidade > media_durabilidade)
            acima_media++;
        else if (produtos[i].resistencia < media_resistencia && produtos[i].durabilidade < media_durabilidade)
            abaixo_media++;
    }
    if (acima_media > abaixo_media)
        printf("\nExistem mais produtos acima das médias.\n");
    else if (acima_media < abaixo_media)
        printf("\nExistem mais produtos abaixo das médias.\n");
    else
        printf("\nO número de produtos acima e abaixo das médias é igual.\n");

    return 0;
}
