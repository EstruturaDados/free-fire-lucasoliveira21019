#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Definição da struct Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Protótipos das funções
void entradaDados(Componente componentes[], int *numComponentes);
void bubbleSortNome(Componente componentes[], int numComponentes, long long *comparacoes);
void insertionSortTipo(Componente componentes[], int numComponentes, long long *comparacoes);
void selectionSortPrioridade(Componente componentes[], int numComponentes, long long *comparacoes);
int buscaBinariaPorNome(Componente componentes[], int numComponentes, char nomeBusca[], long long *comparacoes);
void mostrarComponentes(Componente componentes[], int numComponentes);
double medirTempo(void (*algoritmo)(Componente[], int, long long*), Componente componentes[], int numComponentes, long long *comparacoes);


int main() {
    Componente componentes[20];
    int numComponentes = 0;
    int opcao, indiceEncontrado;
    char nomeBusca[30];
    double tempoExecucao;
    long long comparacoes = 0;

    entradaDados(componentes, &numComponentes);

    do {
        //limparTela(); //Removido
        printf("\n--- Menu de Ordenacao e Busca ---");
        printf("\n1. Ordenar por Nome (Bubble Sort)");
        printf("\n2. Ordenar por Tipo (Insertion Sort)");
        printf("\n3. Ordenar por Prioridade (Selection Sort)");
        printf("\n4. Buscar por Nome (Busca Binaria - Apos ordenacao por nome)");
        printf("\n5. Mostrar Componentes");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Consumir o newline deixado pelo scanf

        switch (opcao) {
            case 1:
                ; //Empty statement to allow declaration after label
                Componente componentesBubble[20];
                memcpy(componentesBubble, componentes, sizeof(componentes)); //Criar uma cópia dos componentes para não alterar o original

                tempoExecucao = medirTempo((void (*)(Componente[], int, long long*))bubbleSortNome, componentesBubble, numComponentes, &comparacoes);

                printf("\nComponentes ordenados por Nome (Bubble Sort):\n");
                mostrarComponentes(componentesBubble, numComponentes);
                printf("Tempo de execucao: %lf segundos\n", tempoExecucao);
                printf("Numero de comparacoes: %lld\n", comparacoes);
                break;
            case 2:
                ;
                Componente componentesInsertion[20];
                memcpy(componentesInsertion, componentes, sizeof(componentes));

                tempoExecucao = medirTempo((void (*)(Componente[], int, long long*))insertionSortTipo, componentesInsertion, numComponentes, &comparacoes);

                printf("\nComponentes ordenados por Tipo (Insertion Sort):\n");
                mostrarComponentes(componentesInsertion, numComponentes);
                printf("Tempo de execucao: %lf segundos\n", tempoExecucao);
                printf("Numero de comparacoes: %lld\n", comparacoes);
                break;
            case 3:
                ;
                Componente componentesSelection[20];
                memcpy(componentesSelection, componentes, sizeof(componentes));

                tempoExecucao = medirTempo((void (*)(Componente[], int, long long*))selectionSortPrioridade, componentesSelection, numComponentes, &comparacoes);

                printf("\nComponentes ordenados por Prioridade (Selection Sort):\n");
                mostrarComponentes(componentesSelection, numComponentes);
                printf("Tempo de execucao: %lf segundos\n", tempoExecucao);
                printf("Numero de comparacoes: %lld\n", comparacoes);
                break;
            case 4:
                ;
                // Ordenar por nome ANTES da busca binária
                Componente componentesBuscaBinaria[20];
                memcpy(componentesBuscaBinaria, componentes, sizeof(componentes));

                bubbleSortNome(componentesBuscaBinaria, numComponentes, &comparacoes); //Necessário para a busca binária funcionar

                printf("Digite o nome do componente a ser buscado: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove o newline

                indiceEncontrado = buscaBinariaPorNome(componentesBuscaBinaria, numComponentes, nomeBusca, &comparacoes);

                if (indiceEncontrado != -1) {
                    printf("\nComponente encontrado:\n");
                    printf("Nome: %s\n", componentesBuscaBinaria[indiceEncontrado].nome);
                    printf("Tipo: %s\n", componentesBuscaBinaria[indiceEncontrado].tipo);
                    printf("Prioridade: %d\n", componentesBuscaBinaria[indiceEncontrado].prioridade);
                } else {
                    printf("Componente nao encontrado.\n");
                }
                printf("Numero de comparacoes (Busca Binaria): %lld\n", comparacoes);
                break;
            case 5:
                printf("\nLista de Componentes:\n");
                mostrarComponentes(componentes, numComponentes);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}



// Função para entrada de dados dos componentes
void entradaDados(Componente componentes[], int *numComponentes) {
    int i;
    printf("--- Cadastro de Componentes ---\n");
    for (i = 0; i < 20; i++) {
        printf("\nComponente %d:\n", i + 1);

        printf("Nome (ou 'fim' para encerrar): ");
        fgets(componentes[i].nome, sizeof(componentes[i].nome), stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = 0; // Remove o newline

        if (strcmp(componentes[i].nome, "fim") == 0) {
            break;
        }

        printf("Tipo: ");
        fgets(componentes[i].tipo, sizeof(componentes[i].tipo), stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = 0; // Remove o newline

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar(); // Consumir o newline deixado pelo scanf

        if (componentes[i].prioridade < 1 || componentes[i].prioridade > 10) {
            printf("Prioridade invalida. Defina um valor entre 1 e 10.\n");
            i--; // Decrementa para repetir a entrada do componente atual
        }
    }
    *numComponentes = i;
}


// Função para ordenar por nome (Bubble Sort)
void bubbleSortNome(Componente componentes[], int numComponentes, long long *comparacoes) {
    int i, j;
    Componente temp;
    *comparacoes = 0;

    for (i = 0; i < numComponentes - 1; i++) {
        for (j = 0; j < numComponentes - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os elementos
                temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
}


// Função para ordenar por tipo (Insertion Sort)
void insertionSortTipo(Componente componentes[], int numComponentes, long long *comparacoes) {
    int i, j;
    Componente chave;
    *comparacoes = 0;

    for (i = 1; i < numComponentes; i++) {
        chave = componentes[i];
        j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j = j - 1;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

// Função para ordenar por prioridade (Selection Sort)
void selectionSortPrioridade(Componente componentes[], int numComponentes, long long *comparacoes) {
    int i, j, min_idx;
    Componente temp;
    *comparacoes = 0;

    for (i = 0; i < numComponentes - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < numComponentes; j++) {
            (*comparacoes)++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }

        // Troca os elementos
        temp = componentes[i];
        componentes[i] = componentes[min_idx];
        componentes[min_idx] = temp;
    }
}

// Função para busca binária por nome
int buscaBinariaPorNome(Componente componentes[], int numComponentes, char nomeBusca[], long long *comparacoes) {
    int esquerda = 0, direita = numComponentes - 1, meio;
    *comparacoes = 0;

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        (*comparacoes)++;

        int resultadoComparacao = strcmp(componentes[meio].nome, nomeBusca);

        if (resultadoComparacao == 0) {
            return meio; // Elemento encontrado
        } else if (resultadoComparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1; // Elemento não encontrado
}

// Função para mostrar os componentes
void mostrarComponentes(Componente componentes[], int numComponentes) {
    int i;
    printf("| %-30s | %-20s | %-10s |\n", "Nome", "Tipo", "Prioridade");
    printf("|--------------------------------|----------------------|------------|\n");
    for (i = 0; i < numComponentes; i++) {
        printf("| %-30s | %-20s | %-10d |\n", componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
}


// Função para medir o tempo de execução de um algoritmo de ordenação
double medirTempo(void (*algoritmo)(Componente[], int, long long*), Componente componentes[], int numComponentes, long long *comparacoes) {
    clock_t inicio, fim;
    double tempoGasto;

    inicio = clock();
    algoritmo(componentes, numComponentes, comparacoes);
    fim = clock();

    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return tempoGasto;
}
