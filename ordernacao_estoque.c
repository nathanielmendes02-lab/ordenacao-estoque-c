#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL 12
#define ESTOQUE_MINIMO 10



typedef struct {
    int codigo;
    char nome[30];
    int quantidade;
    float preco;
} Produto;

typedef struct {
    long comparacoes;
    long trocas;
} Contador;

/* FUNCOES AUXILIARES */
void trocar(Produto *a, Produto *b) {
    Produto temp = *a;
    *a = *b;
    *b = temp;
}

void exibir(const char *titulo, const Produto v[], int n) {
    printf("\n=== %s ===\n", titulo);
    printf("%-3s %-8s %-20s %-10s %-10s %s\n",
           "#", "Codigo", "Produto", "Estoque", "Preco (R$)", "Situacao");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d %-8d %-20s %-10d %-10.2f %s\n",
               i + 1, v[i].codigo, v[i].nome, v[i].quantidade, v[i].preco,
               v[i].quantidade <= ESTOQUE_MINIMO ? "REPOR" : "ok");
    }
}

int estaOrdenado(const Produto v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i].quantidade > v[i + 1].quantidade) {
            return 0;
        }
    }
    return 1;
}


void bubbleSort(Produto v[], int n, Contador *c) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;

        for (int j = 0; j < n - 1 - i; j++) {
            c->comparacoes++;
            if (v[j].quantidade > v[j + 1].quantidade) {
                trocar(&v[j], &v[j + 1]);
                c->trocas++;
                trocou = 1;
            }
        }

        if (!trocou) {
            break;
        }
    }
}


int particionar(Produto v[], int inicio, int fim, Contador *c) {
    int pivo = v[fim].quantidade;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        c->comparacoes++;
        if (v[j].quantidade <= pivo) {
            i++;
            if (i != j) {
                trocar(&v[i], &v[j]);
                c->trocas++;
            }
        }
    }

    if (i + 1 != fim) {
        trocar(&v[i + 1], &v[fim]);
        c->trocas++;
    }
    return i + 1;
}

void quickSort(Produto v[], int inicio, int fim, Contador *c) {
    if (inicio < fim) {
        int p = particionar(v, inicio, fim, c);
        quickSort(v, inicio, p - 1, c);
        quickSort(v, p + 1, fim, c);
    }
}

/* EXECUCAO DOS ALGORITMOS */
Contador executar(int algoritmo, const Produto original[], Produto resultado[]) {
    Contador c = {0, 0};
    memcpy(resultado, original, TOTAL * sizeof(Produto));

    if (algoritmo == 1) {
        bubbleSort(resultado, TOTAL, &c);
    } else {
        quickSort(resultado, 0, TOTAL - 1, &c);
    }

    return c;
}

int lerOpcao(void) {
    char linha[32];
    int opcao;

    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return 0;
    }

    if (sscanf(linha, "%d", &opcao) != 1) {
        return -1;
    }

    return opcao;
}

int main(void) {
    const Produto estoque[TOTAL] = {
        {101, "Arroz 5kg",        48, 22.90f},
        {102, "Feijao 1kg",       15,  8.49f},
        {103, "Acucar 1kg",       92,  4.79f},
        {104, "Oleo de soja",      7,  9.99f},
        {105, "Leite integral",  120,  5.49f},
        {106, "Cafe 500g",        33, 17.90f},
        {107, "Macarrao 500g",    61,  4.29f},
        {108, "Sabao em po",      24, 18.50f},
        {109, "Farinha de trigo",  5,  6.99f},
        {110, "Biscoito",         76,  3.89f},
        {111, "Detergente",       39,  2.59f},
        {112, "Sal 1kg",          10,  3.29f}
    };

    Produto ordenado[TOTAL];
    int opcao;

    printf("=========================================================\n");
    printf("  MERCADO DO BAIRRO - PRODUTOS POR QUANTIDADE EM ESTOQUE\n");
    printf("=========================================================\n");

    do {
        printf("\nMENU\n");
        printf("  1 - Ordenar com Bubble Sort\n");
        printf("  2 - Ordenar com Quick Sort\n");
        printf("  3 - Comparar os dois algoritmos\n");
        printf("  0 - Sair\n");
        printf("Escolha: ");
        opcao = lerOpcao();

        if (opcao == 1 || opcao == 2) {
            const char *nome = (opcao == 1) ? "BUBBLE SORT" : "QUICK SORT";
            Contador c = executar(opcao, estoque, ordenado);

            exibir("ANTES da ordenacao (ordem de cadastro)", estoque, TOTAL);
            printf("\n>>> Aplicando %s...\n", nome);
            exibir("DEPOIS da ordenacao (menor estoque primeiro)", ordenado, TOTAL);

            printf("\nComparacoes: %ld | Trocas: %ld | Verificacao: %s\n",
                   c.comparacoes, c.trocas,
                   estaOrdenado(ordenado, TOTAL) ? "OK, em ordem crescente"
                                                 : "ERRO, fora de ordem");
        }
        else if (opcao == 3) {
            Produto resBubble[TOTAL], resQuick[TOTAL];
            Contador cb = executar(1, estoque, resBubble);
            Contador cq = executar(2, estoque, resQuick);

            exibir("ANTES da ordenacao (ordem de cadastro)", estoque, TOTAL);
            exibir("DEPOIS - Bubble Sort", resBubble, TOTAL);
            exibir("DEPOIS - Quick Sort", resQuick, TOTAL);

            printf("\n%-14s %-13s %-8s %s\n", "Algoritmo", "Comparacoes", "Trocas", "Verificacao");
            printf("-----------------------------------------------------\n");
            printf("%-14s %-13ld %-8ld %s\n", "Bubble Sort", cb.comparacoes, cb.trocas,
                   estaOrdenado(resBubble, TOTAL) ? "OK" : "ERRO");
            printf("%-14s %-13ld %-8ld %s\n", "Quick Sort", cq.comparacoes, cq.trocas,
                   estaOrdenado(resQuick, TOTAL) ? "OK" : "ERRO");
            printf("\nOs dois produzem a mesma ordem final; o que muda e o esforco\n");
            printf("(numero de operacoes) para chegar la, que cresce bem mais\n");
            printf("rapido no Bubble Sort quando a quantidade de dados aumenta.\n");
        }
        else if (opcao != 0) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    printf("\nEncerrando. Ate logo!\n");
    return 0;
}
