#include <stdio.h>

#define MAX_PRODUTOS 10

// Estrutura para armazenar os dados de cada produto
struct Produto {
    int numero_de_serie;
    int resistencia;
    int durabilidade;
};

int main() {
    // Abrir o arquivo de par�metros para leitura
    FILE *arquivo = fopen("parametros.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Array para armazenar os dados dos produtos
    struct Produto produtos[MAX_PRODUTOS];
    
    // Vari�veis para c�lculo das m�dias
    int soma_resistencia = 0;
    int soma_durabilidade = 0;

    // Leitura dos dados do arquivo e armazenamento dos produtos
    for (int i = 0; i < MAX_PRODUTOS; i++) {
        fscanf(arquivo, "%d;%d;%d", &produtos[i].numero_de_serie, &produtos[i].resistencia, &produtos[i].durabilidade);
        soma_resistencia += produtos[i].resistencia;
        soma_durabilidade += produtos[i].durabilidade;
    }

    // Fechar o arquivo ap�s a leitura
    fclose(arquivo);

    // C�lculo das m�dias
    float media_resistencia = (float)soma_resistencia / MAX_PRODUTOS;
    float media_durabilidade = (float)soma_durabilidade / MAX_PRODUTOS;

    // Exibi��o das m�dias na tela
    printf("M�dia de resist�ncia: %.2f\n", media_resistencia);
    printf("M�dia de durabilidade: %.2f\n", media_durabilidade);

    // Inicializa��o de vari�veis para os produtos com maior e menor resist�ncia e durabilidade
    int maior_resistencia = produtos[0].resistencia;
    int menor_resistencia = produtos[0].resistencia;
    int maior_durabilidade = produtos[0].durabilidade;
    int menor_durabilidade = produtos[0].durabilidade;

    // Itera��o para encontrar os produtos com maior e menor resist�ncia e durabilidade
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

    // Exibi��o dos produtos com maior e menor resist�ncia e durabilidade na tela
    printf("Produto com maior resist�ncia: %d\n", maior_resistencia);
    printf("Produto com menor resist�ncia: %d\n", menor_resistencia);
    printf("Produto com maior durabilidade: %d\n", maior_durabilidade);
    printf("Produto com menor durabilidade: %d\n", menor_durabilidade);

    // Verifica��o se existem mais produtos acima ou abaixo das m�dias
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

    // Exibi��o da informa��o sobre mais produtos acima ou abaixo das m�dias na tela
    if (acima_resistencia > abaixo_resistencia) {
        printf("Existem mais produtos acima da m�dia de resist�ncia.\n");
    } else if (acima_resistencia < abaixo_resistencia) {
        printf("Existem mais produtos abaixo da m�dia de resist�ncia.\n");
    } else {
        printf("N�mero igual de produtos acima e abaixo da m�dia de resist�ncia.\n");
    }

    if (acima_durabilidade > abaixo_durabilidade) {
        printf("Existem mais produtos acima da m�dia de durabilidade.\n");
    } else if (acima_durabilidade < abaixo_durabilidade) {
        printf("Existem mais produtos abaixo da m�dia de durabilidade.\n");
    } else {
        printf("N�mero igual de produtos acima e abaixo da m�dia de durabilidade.\n");
    }

    // Salvar a an�lise em um arquivo
    arquivo = fopen("qualidade.md", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de an�lise.\n");
        return 1;
    }

    // Escrever a an�lise no arquivo
    fprintf(arquivo, "An�lise de Qualidade\n");
    fprintf(arquivo, "---------------------\n");
    fprintf(arquivo, "M�dia de resist�ncia: %.2f\n", media_resistencia);
    fprintf(arquivo, "M�dia de durabilidade: %.2f\n", media_durabilidade);
    fprintf(arquivo, "Produto com maior resist�ncia: %d\n", maior_resistencia);
    fprintf(arquivo, "Produto com menor resist�ncia: %d\n", menor_resistencia);
    fprintf(arquivo, "Produto com maior durabilidade: %d\n", maior_durabilidade);
    fprintf(arquivo, "Produto com menor durabilidade: %d\n", menor_durabilidade);
    fprintf(arquivo, "Existem mais produtos acima ou abaixo das m�dias:\n");
    fprintf(arquivo, "Resist�ncia: Acima(%d) Abaixo(%d)\n", acima_resistencia, abaixo_resistencia);
    fprintf(arquivo, "Durabilidade: Acima(%d) Abaixo(%d)\n", acima_durabilidade, abaixo_durabilidade);

    // Fechar o arquivo ap�s a escrita
    fclose(arquivo);

    return 0;
}
