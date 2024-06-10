#include <stdio.h>
#include <stdlib.h>

// Função para calcular o valor do reembolso
double calcular_reembolso(double preco_litro, double distancia) {
    return (preco_litro * distancia) / 3;
}

// Estrutura para armazenar os dados de viagem
typedef struct {
    int matricula;
    char funcionario[50];
    char data[11];
    char origem[50];
    char destino[50];
    double distancia;
    double preco_litro;
    double reembolso;
} Viagem;

// Função para calcular o total de reembolso
double calcular_total_reembolso(Viagem* dados, int tamanho) {
    double total_geral = 0;
    for (int i = 0; i < tamanho; i++) {
        dados[i].reembolso = calcular_reembolso(dados[i].preco_litro, dados[i].distancia);
        total_geral += dados[i].reembolso;
    }
    return total_geral;
}

// Função para mostrar os dados por funcionário
void mostrar_dados_por_funcionario(Viagem* dados, int tamanho) {
    double subtotal = 0;
    int matricula_atual = -1;

    printf("Dados por funcionário:\n");
    for (int i = 0; i < tamanho; i++) {
        if (matricula_atual != dados[i].matricula) {
            if (matricula_atual != -1) {
                printf("Subtotal: R$ %.2f\n\n", subtotal);
            }
            matricula_atual = dados[i].matricula;
            subtotal = 0;
        }
        printf("%d\t%s\t%s\t%s\t%s\t%.2f\t%.2f\t%.2f\n",
               dados[i].matricula, dados[i].funcionario, dados[i].data, dados[i].origem,
               dados[i].destino, dados[i].distancia, dados[i].preco_litro, dados[i].reembolso);
        subtotal += dados[i].reembolso;
    }
    printf("Subtotal: R$ %.2f\n", subtotal);
}

// Função para gerar o relatório em formato Markdown
void gerar_relatorio_markdown(Viagem* dados, int tamanho, double total_geral) {
    FILE* file = fopen("RelatorioViagens.md", "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo\n");
        return;
    }
    
    fprintf(file, "# Relatório de Viagens\n\n");
    fprintf(file, "| Matrícula | Funcionário | Data       | Origem                 | Destino                | Distância | Preço  | Total  |\n");
    fprintf(file, "|-----------|-------------|------------|------------------------|------------------------|-----------|--------|--------|\n");
    
    double subtotal = 0;
    int matricula_atual = -1;

    for (int i = 0; i < tamanho; i++) {
        if (matricula_atual != dados[i].matricula) {
            if (matricula_atual != -1) {
                fprintf(file, "| Subtotal  |             |            |                        |                        |           |        | %.2f  |\n\n", subtotal);
            }
            matricula_atual = dados[i].matricula;
            subtotal = 0;
        }
        fprintf(file, "| %d         | %s         | %s | %s  | %s  | %.2f     | %.2f  | %.2f  |\n",
                dados[i].matricula, dados[i].funcionario, dados[i].data, dados[i].origem,
                dados[i].destino, dados[i].distancia, dados[i].preco_litro, dados[i].reembolso);
        subtotal += dados[i].reembolso;
    }
    fprintf(file, "| Subtotal  |             |            |                        |                        |           |        | %.2f  |\n\n", subtotal);
    fprintf(file, "## Total Geral de Reembolso\n\n");
    fprintf(file, "- *Total Geral*: R$ %.2f\n", total_geral);
    
    fclose(file);
}

int main() {
    Viagem dados_viagens[] = {
        {527, "Lucas", "01/05/2024", "Campinas", "Santo Antônio de Posse", 45, 3.92, 0},
        {527, "Lucas", "02/05/2024", "Jaguariúna", "Santo Antônio de Posse", 24, 3.86, 0},
        {527, "Lucas", "03/05/2024", "Santo Antônio de Posse", "Jaguariúna", 17, 3.95, 0},
        {527, "Lucas", "05/05/2024", "Amparo", "Hortolândia", 59, 3.84, 0},
        {527, "Lucas", "06/05/2024", "Artur Nogueira", "Hortolândia", 48, 3.84, 0},
        {527, "Lucas", "08/05/2024", "Amparo", "Campinas", 36, 3.69, 0},
        {527, "Lucas", "09/05/2024", "Holambra", "Jaguariúna", 17, 3.73, 0},
        {527, "Lucas", "10/05/2024", "Amparo", "Redreira", 25, 3.87, 0},
        {527, "Lucas", "19/05/2024", "Amparo", "Jaguariúna", 32, 3.95, 0},
        {527, "Lucas", "20/05/2024", "Jaguariúna", "Jaguariúna", 41, 3.83, 0},
        {527, "Lucas", "21/05/2024", "Santo Antônio de Posse", "Redreira", 29, 3.83, 0},
        {527, "Lucas", "22/05/2024", "Artur Nogueira", "Redreira", 20, 3.74, 0},
        {527, "Lucas", "23/05/2024", "Santo Antônio de Posse", "Artur Nogueira", 43, 3.92, 0},
        {527, "Lucas", "24/05/2024", "Campinas", "Campinas", 56, 3.71, 0},
        {527, "Lucas", "29/05/2024", "Santo Antônio de Posse", "Artur Nogueira", 36, 3.70, 0},
        {527, "Lucas", "31/05/2024", "Hortolândia", "Jaguariúna", 20, 3.74, 0},
        {529, "Carlos", "07/05/2024", "Santo Antônio de Posse", "Holambra", 36, 3.75, 0},
        {529, "Carlos", "30/05/2024", "Jaguariúna", "Jaguariúna", 28, 3.96, 0},
        {529, "Carlos", "16/05/2024", "Amparo", "Amparo", 41, 3.82, 0},
        {532, "Marcos", "04/05/2024", "Redreira", "Artur Nogueira", 42, 3.91, 0},
        {538, "Juliana", "14/05/2024", "Amparo", "Holambra", 57, 3.80, 0},
        {538, "Juliana", "15/05/2024", "Amparo", "Artur Nogueira", 41, 3.93, 0},
        {538, "Juliana", "11/05/2024", "Campinas", "Santo Antônio de Posse", 20, 3.98, 0},
        {538, "Juliana", "17/05/2024", "Artur Nogueira", "Holambra", 41, 3.94, 0},
        {538, "Juliana", "18/05/2024", "Holambra", "Santo Antônio de Posse", 34, 3.98, 0},
        {538, "Juliana", "12/05/2024", "Redreira", "Redreira", 22, 3.99, 0},
        {538, "Juliana", "13/05/2024", "Santo Antônio de Posse", "Amparo", 35, 3.84, 0},
        {542, "Mariana", "28/05/2024", "Hortolândia", "Amparo", 58, 3.75, 0},
        {542, "Mariana", "25/05/2024", "Holambra", "Amparo", 54, 3.88, 0},
        {542, "Mariana", "26/05/2024", "Hortolândia", "Redreira", 38, 3.77, 0},
        {542, "Mariana", "27/05/2024", "Jaguariúna", "Amparo", 48, 3.90, 0},
    };
    int tamanho = sizeof(dados_viagens) / sizeof(dados_viagens[0]);
    
    double total_geral = calcular_total_reembolso(dados_viagens, tamanho);
    printf("Total geral de reembolso: R$ %.2f\n", total_geral);
    
    mostrar_dados_por_funcionario(dados_viagens, tamanho);
    
    gerar_relatorio_markdown(dados_viagens, tamanho, total_geral);
    
    return 0;
}
