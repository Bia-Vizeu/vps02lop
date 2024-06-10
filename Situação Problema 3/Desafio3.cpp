#include <stdio.h>

#define MAX_PRODUTOS 10

// Estrutura para armazenar os dados de cada produto
struct Produto {
    int numero_de_serie;
    int resistencia;
    int durabilidade;
};

int main() {
    // Abrir o arquivo de parâmetros para leitura
    FILE *arquivo = fopen("parametros.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Array para armazenar os dados dos produtos
    struct Produto produtos[MAX_PRODUTOS];
    
    // Variáveis para cálculo das médias
    int soma_resistencia = 0;
    int soma_durabilidade = 0;

    // Leitura dos dados do arquivo e armazenamento dos produtos
    for (int i = 0; i < MAX_PRODUTOS; i++) {
        fscanf(arquivo, "%d;%d;%d", &produtos[i].numero_de_serie, &produtos[i].resistencia, &produtos[i].durabilidade);
        soma_resistencia += produtos[i].resistencia;
        soma_durabilidade += produtos[i].durabilidade;
    }

    // Fechar o arquivo após a leitura
    fclose(arquivo);

    // Cálculo das médias
    float media_resistencia = (float)soma_resistencia / MAX_PRODUTOS;
    float media_durabilidade = (float)soma_durabilidade / MAX_PRODUTOS;

    // Exibição das médias na tela
    printf("Média de resistência: %.2f\n", media_resistencia);
    printf("Média de durabilidade: %.2f\n", media_durabilidade);

    // Inicialização de variáveis para os produtos com maior e menor resistência e durabilidade
    int maior_resistencia = produtos[0].resistencia;
    int menor_resistencia = produtos[0].resistencia;
    int maior_durabilidade = produtos[0].durabilidade;
    int menor_durabilidade = produtos[0].durabilidade;

    // Iteração para encontrar os produtos com maior e menor resistência e durabilidade
    for (int i = 1; i < MAX_PRODUTOS; i++) {
        if (produtos[i].resistencia > maior_resistencia) {
            maior_resistencia = produtos[i].resistencia;
        }
        if (produtos[i].resistencia < menor_resistencia) {
            menor_resistencia = produtos[i].resistencia;
        }
        if (produtos[i].durabilidade > maior_durabilidade) {
            maior_durabilidade = produtos[i].durabilidade;
        }
        if (produtos[i].durabilidade < menor_durabilidade) {
            menor_durabilidade = produtos[i].durabilidade;
        }
    }

    // Exibição dos produtos com maior e menor resistência e durabilidade na tela
    printf("Produto com maior resistência: %d\n", maior_resistencia);
    printf("Produto com menor resistência: %d\n", menor_resistencia);
    printf("Produto com maior durabilidade: %d\n", maior_durabilidade);
    printf("Produto com menor durabilidade: %d\n", menor_durabilidade);

    // Verificação se existem mais produtos acima ou abaixo das médias
    int acima_resistencia = 0;
    int abaixo_resistencia = 0;
    int acima_durabilidade = 0;
    int abaixo_durabilidade = 0;

    for (int i = 0; i < MAX_PRODUTOS; i++) {
        if (produtos[i].resistencia > media_resistencia) {
            acima_resistencia++;
        } else {
            abaixo_resistencia++;
        }

        if (produtos[i].durabilidade > media_durabilidade) {
            acima_durabilidade++;
        } else {
            abaixo_durabilidade++;
        }
    }

    // Exibição da informação sobre mais produtos acima ou abaixo das médias na tela
    if (acima_resistencia > abaixo_resistencia) {
        printf("Existem mais produtos acima da média de resistência.\n");
    } else if (acima_resistencia < abaixo_resistencia) {
        printf("Existem mais produtos abaixo da média de resistência.\n");
    } else {
        printf("Número igual de produtos acima e abaixo da média de resistência.\n");
    }

    if (acima_durabilidade > abaixo_durabilidade) {
        printf("Existem mais produtos acima da média de durabilidade.\n");
    } else if (acima_durabilidade < abaixo_durabilidade) {
        printf("Existem mais produtos abaixo da média de durabilidade.\n");
    } else {
        printf("Número igual de produtos acima e abaixo da média de durabilidade.\n");
    }

    // Salvar a análise em um arquivo
    arquivo = fopen("qualidade.md", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de análise.\n");
        return 1;
    }

    // Escrever a análise no arquivo
    fprintf(arquivo, "Análise de Qualidade\n");
    fprintf(arquivo, "---------------------\n");
    fprintf(arquivo, "Média de resistência: %.2f\n", media_resistencia);
    fprintf(arquivo, "Média de durabilidade: %.2f\n", media_durabilidade);
    fprintf(arquivo, "Produto com maior resistência: %d\n", maior_resistencia);
    fprintf(arquivo, "Produto com menor resistência: %d\n", menor_resistencia);
    fprintf(arquivo, "Produto com maior durabilidade: %d\n", maior_durabilidade);
    fprintf(arquivo, "Produto com menor durabilidade: %d\n", menor_durabilidade);
    fprintf(arquivo, "Existem mais produtos acima ou abaixo das médias:\n");
    fprintf(arquivo, "Resistência: Acima(%d) Abaixo(%d)\n", acima_resistencia, abaixo_resistencia);
    fprintf(arquivo, "Durabilidade: Acima(%d) Abaixo(%d)\n", acima_durabilidade, abaixo_durabilidade);

    // Fechar o arquivo após a escrita
    fclose(arquivo);

    return 0;
}
