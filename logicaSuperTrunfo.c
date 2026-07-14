#include <stdio.h>
#include <string.h>

// Estrutura para armazenar os dados das cartas
typedef struct {
    char codigo[4];
    char pais[30];
    unsigned long int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade;
    float pib_per_capita; // NOVO
    int medalhas;         // NOVO
} Carta;

// Função para exibir o menu dinâmico de atributos
void exibir_menu(int bloqueado) {
    if (bloqueado != 1) printf("1. Populacao\n");
    if (bloqueado != 2) printf("2. Area\n");
    if (bloqueado != 3) printf("3. PIB\n");
    if (bloqueado != 4) printf("4. Pontos Turisticos\n");
    if (bloqueado != 5) printf("5. Densidade Demografica (Menor vence)\n");
    if (bloqueado != 6) printf("6. PIB per Capita\n");
    if (bloqueado != 7) printf("7. Medalhas Olimpicas\n");
    printf("Escolha uma opcao: ");
}

// Função para obter o valor do atributo escolhido e retornar seu nome
float obter_atributo(Carta c, int opcao, char *nome_attr) {
    switch (opcao) {
        case 1: strcpy(nome_attr, "Populacao"); return (float)c.populacao;
        case 2: strcpy(nome_attr, "Area"); return c.area;
        case 3: strcpy(nome_attr, "PIB"); return c.pib;
        case 4: strcpy(nome_attr, "Pontos Turisticos"); return (float)c.pontos_turisticos;
        case 5: strcpy(nome_attr, "Densidade Demografica"); return c.densidade;
        case 6: strcpy(nome_attr, "PIB per Capita"); return c.pib_per_capita;
        case 7: strcpy(nome_attr, "Medalhas Olimpicas"); return (float)c.medalhas;
        default: strcpy(nome_attr, "Invalido"); return 0;
    }
}

int main() {
    // 1. Pré-cadastro das duas cartas com os novos atributos
    Carta carta1 = {"A01", "Brasil", 214300000, 8515767.0, 1608000.0, 50, 0.0, 0.0, 150};
    carta1.densidade = (float)carta1.populacao / carta1.area;
    carta1.pib_per_capita = (carta1.pib * 1000000.0f) / (float)carta1.populacao; // Ajuste de escala do PIB

    Carta carta2 = {"B02", "Japao", 125700000, 377975.0, 4941000.0, 82, 0.0, 0.0, 500};
    carta2.densidade = (float)carta2.populacao / carta2.area;
    carta2.pib_per_capita = (carta2.pib * 1000000.0f) / (float)carta2.populacao;

    int attr1_opcao = 0, attr2_opcao = 0;
    char nome_attr1[30], nome_attr2[30];

    printf("=== SUPER TRUNFO - PAISES (7 ATRIBUTOS) ===\n\n");

    // 2. Menu do Primeiro Atributo
    printf("Escolha o PRIMEIRO atributo para comparacao:\n");
    exibir_menu(0);
    if (scanf("%d", &attr1_opcao) != 1 || attr1_opcao < 1 || attr1_opcao > 7) {
        printf("\n[ERRO] Opcao invalida! O programa sera encerrado.\n");
        return 1;
    }

    // 3. Menu Dinâmico do Segundo Atributo
    printf("\nEscolha o SEGUNDO atributo para comparacao:\n");
    exibir_menu(attr1_opcao); // Esconde a primeira escolha
    if (scanf("%d", &attr2_opcao) != 1 || attr2_opcao < 1 || attr2_opcao > 7 || attr2_opcao == attr1_opcao) {
        printf("\n[ERRO] Opcao invalida ou repetida! O programa sera encerrado.\n");
        return 1;
    }

    // 4. Extração dos valores dos atributos
    float v1_c1 = obter_atributo(carta1, attr1_opcao, nome_attr1);
    float v1_c2 = obter_atributo(carta2, attr1_opcao, nome_attr1);

    float v2_c1 = obter_atributo(carta2, attr2_opcao, nome_attr2); // corrigido para carta1 no fluxo lógico real
    v2_c1 = obter_atributo(carta1, attr2_opcao, nome_attr2);
    float v2_c2 = obter_atributo(carta2, attr2_opcao, nome_attr2);

    // 5. Lógica de Pesos para a Soma (Inverte apenas para a Densidade que é a opção 5)
    float peso1_c1 = (attr1_opcao == 5) ? (1.0f / v1_c1) : v1_c1;
    float peso1_c2 = (attr1_opcao == 5) ? (1.0f / v1_c2) : v1_c2;

    float peso2_c1 = (attr2_opcao == 5) ? (1.0f / v2_c1) : v2_c1;
    float peso2_c2 = (attr2_opcao == 5) ? (1.0f / v2_c2) : v2_c2;

    // 6. Cálculo da Soma dos Atributos
    float soma_c1 = peso1_c1 + peso2_c1;
    float soma_c2 = peso1_c2 + peso2_c2;

    // 7. Exibição Clara dos Resultados
    printf("\n=============================================\n");
    printf("               RESULTADO DA RODADA           \n");
    printf("=============================================\n");
    printf("Carta 1: %s (%s)\n", carta1.pais, carta1.codigo);
    printf("Carta 2: %s (%s)\n", carta2.pais, carta2.codigo);
    printf("---------------------------------------------\n");
    printf("Atributo 1: %s\n", nome_attr1);
    printf("  - %s: %.2f\n", carta1.pais, v1_c1);
    printf("  - %s: %.2f\n", carta2.pais, v1_c2);
    printf("  Vencedor do Atributo 1: %s\n", (attr1_opcao == 5) ? (v1_c1 < v1_c2 ? carta1.pais : carta2.pais) : (v1_c1 > v1_c2 ? carta1.pais : carta2.pais));
    printf("---------------------------------------------\n");
    printf("Atributo 2: %s\n", nome_attr2);
    printf("  - %s: %.2f\n", carta1.pais, v2_c1);
    printf("  - %s: %.2f\n", carta2.pais, v2_c2);
    printf("  Vencedor do Atributo 2: %s\n", (attr2_opcao == 5) ? (v2_c1 < v2_c2 ? carta1.pais : carta2.pais) : (v2_c1 > v2_c2 ? carta1.pais : carta2.pais));
    printf("---------------------------------------------\n");
    
    // 8. Determinação do Vencedor Geral por Soma
    printf("VENCEDOR GERAL DA RODADA: ");
    if (soma_c1 == soma_c2) {
        printf("Empate!\n");
    } else {
        printf("%s\n", (soma_c1 > soma_c2) ? carta1.pais : carta2.pais);
    }
    printf("=============================================\n");

    return 0;
}
