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

    // Abre o arquivo de saída para escrita
    FILE *saida = fopen("qualidade.md", "w");
    if (saida == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    // Abre o arquivo de entrada para leitura
    FILE *arquivo = fopen("parametros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        fclose(saida);
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

    // Fecha o arquivo de entrada
    fclose(arquivo);

    // Verifica se o arquivo de entrada está vazio
    if (num_produtos == 0) {
        printf("Nenhum produto encontrado no arquivo.\n");
        fclose(saida);
        return 1;
    }

    // Calcula as médias de resistência e durabilidade
    float media_resistencia = (float)soma_resistencia / num_produtos;
    float media_durabilidade = (float)soma_durabilidade / num_produtos;

    // Escreve a análise no arquivo de saída
    fprintf(saida, "# Análise de Qualidade\n\n");
    fprintf(saida, "## Médias\n\n");
    fprintf(saida, "- Média de resistência: %.2f\n", media_resistencia);
    fprintf(saida, "- Média de durabilidade: %.2f\n\n", media_durabilidade);

    fprintf(saida, "## Produtos\n\n");
    fprintf(saida, "### Maior Resistência\n\n");
    fprintf(saida, "- Número de série: %d\n", produtos[maior_resistencia].numero_de_serie);
    fprintf(saida, "- Resistência: %d\n", produtos[maior_resistencia].resistencia);
    fprintf(saida, "- Durabilidade: %d\n\n", produtos[maior_resistencia].durabilidade);

    fprintf(saida, "### Menor Resistência\n\n");
    fprintf(saida, "- Número de série: %d\n", produtos[menor_resistencia].numero_de_serie);
    fprintf(saida, "- Resistência: %d\n", produtos[menor_resistencia].resistencia);
    fprintf(saida, "- Durabilidade: %d\n\n", produtos[menor_resistencia].durabilidade);

    fprintf(saida, "### Maior Durabilidade\n\n");
    fprintf(saida, "- Número de série: %d\n", produtos[maior_durabilidade].numero_de_serie);
    fprintf(saida, "- Resistência: %d\n", produtos[maior_durabilidade].resistencia);
    fprintf(saida, "- Durabilidade: %d\n\n", produtos[maior_durabilidade].durabilidade);

    fprintf(saida, "### Menor Durabilidade\n\n");
    fprintf(saida, "- Número de série: %d\n", produtos[menor_durabilidade].numero_de_serie);
    fprintf(saida, "- Resistência: %d\n", produtos[menor_durabilidade].resistencia);
    fprintf(saida, "- Durabilidade: %d\n\n", produtos[menor_durabilidade].durabilidade);

    // Informa se existem mais produtos acima ou abaixo das médias
    int acima_media = 0, abaixo_media = 0;
    for (int i = 0; i < num_produtos; i++) {
        if (produtos[i].resistencia > media_resistencia && produtos[i].durabilidade > media_durabilidade)
            acima_media++;
        else if (produtos[i].resistencia < media_resistencia && produtos[i].durabilidade < media_durabilidade)
            abaixo_media++;
    }

    if (acima_media > abaixo_media)
        fprintf(saida, "Existem mais produtos acima das médias.\n\n");
    else if (acima_media < abaixo_media)
        fprintf(saida, "Existem mais produtos abaixo das médias.\n\n");
    else
        fprintf(saida, "O número de produtos acima e abaixo das médias é igual.\n\n");

    // Fecha o arquivo de saída
    fclose(saida);

    printf("Análise salva com sucesso no arquivo 'qualidade.md'.\n");

    return 0;
}

