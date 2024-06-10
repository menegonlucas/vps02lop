#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 100

int main() {
    // Abrindo o arquivo para leitura
    FILE *arquivo;
    arquivo = fopen("producao.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Inicializando contadores para cada máquina
    int maquina1 = 0, maquina2 = 0, maquina3 = 0, maquina4 = 0;

    // Variáveis para armazenar os dados do arquivo
    char linha[MAX_LINE_LENGTH];
    char data[11], hora[6];
    int maquina;

    // Lendo linha por linha do arquivo
    while (fgets(linha, MAX_LINE_LENGTH, arquivo) != NULL) {
        // Utilizando sscanf para extrair os dados da linha
        sscanf(linha, "%10[^;];%5[^;];%d", data, hora, &maquina);

        // Incrementando o contador da máquina correspondente
        switch (maquina) {
            case 1:
                maquina1++;
                break;
            case 2:
                maquina2++;
                break;
            case 3:
                maquina3++;
                break;
            case 4:
                maquina4++;
                break;
            default:
                printf("Máquina inválida.\n");
                break;
        }
    }

    // Fechando o arquivo
    fclose(arquivo);

    // Exibindo o total de exposições produzidas por cada máquina
    printf("Máquina 1: %d\n", maquina1);
    printf("Máquina 2: %d\n", maquina2);
    printf("Máquina 3: %d\n", maquina3);
    printf("Máquina 4: %d\n", maquina4);

    return 0;
}
