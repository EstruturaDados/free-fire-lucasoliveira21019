#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ============================================================================
// VETOR (LISTA SEQUENCIAL)
// ============================================================================

// Declaração do vetor de structs para armazenar os itens
Item mochilaVetor[10];
int numItensVetor = 0; // Variável para controlar o número de itens na mochila
long long comparacoesSequencialVetor = 0;
long long comparacoesBinariaVetor = 0;

// Protótipos das funções para o vetor
void inserirItemVetor();
void removerItemVetor();
void listarItensVetor();
void buscarSequencialVetor();
void ordenarVetor();
void buscarBinariaVetor();

// ============================================================================
// LISTA ENCADEADA
// ============================================================================

// Definição da struct No
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Variável global para o ponteiro para o início da lista encadeada
No* inicioLista = NULL;
int numItensLista = 0;
long long comparacoesSequencialLista = 0;

// Protótipos das funções para a lista encadeada
void inserirItemLista();
void removerItemLista();
void listarItensLista();
void buscarSequencialLista();
void liberarLista();


// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    int opcaoEstrutura, opcaoMenu;

    do {
        limparTela();
        printf("\n--- Escolha a estrutura de dados ---");
        printf("\n1. Vetor (Lista Sequencial)");
        printf("\n2. Lista Encadeada");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcaoEstrutura);
        getchar(); // Consumir o newline deixado pelo scanf

        switch (opcaoEstrutura) {
            case 1: // Vetor
                do {
                    limparTela();
                    printf("\n--- Menu (Vetor) ---");
                    printf("\n1. Adicionar Item");
                    printf("\n2. Remover Item");
                    printf("\n3. Listar Itens");
                    printf("\n4. Buscar Item (Sequencial)");
                    printf("\n5. Ordenar Itens (Bubble Sort)");
                    printf("\n6. Buscar Item (Binaria)");
                    printf("\n0. Voltar");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d", &opcaoMenu);
                    getchar(); // Consumir o newline deixado pelo scanf

                    switch (opcaoMenu) {
                        case 1:
                            inserirItemVetor();
                            break;
                        case 2:
                            removerItemVetor();
                            break;
                        case 3:
                            listarItensVetor();
                            break;
                        case 4:
                            buscarSequencialVetor();
                            break;
                        case 5:
                            ordenarVetor();
                            break;
                        case 6:
                            buscarBinariaVetor();
                            break;
                        case 0:
                            printf("Voltando...\n");
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                } while (opcaoMenu != 0);
                break;

            case 2: // Lista Encadeada
                do {
                    limparTela();
                    printf("\n--- Menu (Lista Encadeada) ---");
                    printf("\n1. Adicionar Item");
                    printf("\n2. Remover Item");
                    printf("\n3. Listar Itens");
                    printf("\n4. Buscar Item (Sequencial)");
                    printf("\n0. Voltar");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d", &opcaoMenu);
                    getchar(); // Consumir o newline deixado pelo scanf

                    switch (opcaoMenu) {
                        case 1:
                            inserirItemLista();
                            break;
                        case 2:
                            removerItemLista();
                            break;
                        case 3:
                            listarItensLista();
                            break;
                        case 4:
                            buscarSequencialLista();
                            break;
                        case 0:
                            printf("Voltando...\n");
                            break;
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                    }
                } while (opcaoMenu != 0);
                break;

            case 0:
                printf("Saindo...\n");
                 // Libera a memória alocada pela lista encadeada antes de sair
                liberarLista();
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcaoEstrutura != 0);

    return 0;
}

// ============================================================================
// FUNÇÕES DO VETOR
// ============================================================================

// Função para inserir um novo item na mochila (Vetor)
void inserirItemVetor() {
    if (numItensVetor < 10) {
        Item novoItem;

        printf("\n--- Adicionar Item (Vetor) ---");
        printf("\nNome: ");
        scanf("%s", novoItem.nome);
        printf("Tipo (arma, municao, cura): ");
        scanf(" %s", novoItem.tipo);
        printf("Quantidade: ");
        scanf(" %d", &novoItem.quantidade);
        getchar(); // Consumir o newline

        mochilaVetor[numItensVetor] = novoItem;
        numItensVetor++;

        printf("Item adicionado com sucesso!\n");
        listarItensVetor();
    } else {
        printf("Mochila cheia! Nao eh possivel adicionar mais itens.\n");
    }
}

// Função para remover um item da mochila pelo nome (Vetor)
void removerItemVetor() {
    if (numItensVetor > 0) {
        char nomeRemover[30];
        printf("\n--- Remover Item (Vetor) ---");
        printf("\nNome do item a ser removido: ");
        scanf("%s", nomeRemover);

        int i, j;
        bool encontrado = false;

        for (i = 0; i < numItensVetor; i++) {
            if (strcmp(mochilaVetor[i].nome, nomeRemover) == 0) {
                encontrado = true;
                // Deslocar os itens para preencher o espaço do item removido
                for (j = i; j < numItensVetor - 1; j++) {
                    mochilaVetor[j] = mochilaVetor[j + 1];
                }
                numItensVetor--;
                printf("Item removido com sucesso!\n");
                break;
            }
        }

        if (!encontrado) {
            printf("Item nao encontrado na mochila.\n");
        }

        listarItensVetor();
    } else {
        printf("Mochila vazia! Nao ha itens para remover.\n");
    }
}

// Função para listar todos os itens na mochila (Vetor)
void listarItensVetor() {
    printf("Valor de numItensVetor: %d\n", numItensVetor); // Debug line

    if (numItensVetor > 0) {
        printf("\n--- Lista de Itens na Mochila (Vetor) ---");
        printf("\n| %-30s | %-20s | %-10s |\n", "Nome", "Tipo", "Quantidade");
        printf("|--------------------------------|----------------------|------------|\n");

        // Verificação extra para garantir que não acessaremos posições inválidas
        int itensParaListar = (numItensVetor > 10) ? 10 : numItensVetor;

        for (int i = 0; i < itensParaListar; i++) {
            printf("| %-30s | %-20s | %-10d |\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
        }
    } else {
        printf("Mochila vazia!\n");
    }
}

// Função para buscar um item pelo nome (Busca Sequencial - Vetor)
void buscarSequencialVetor() {
    if (numItensVetor > 0) {
        char nomeBusca[30];
        printf("\n--- Buscar Item (Sequencial - Vetor) ---");
        printf("\nNome do item a ser buscado: ");
        scanf("%s", nomeBusca);

        int i;
        bool encontrado = false;
        comparacoesSequencialVetor = 0;

        for (i = 0; i < numItensVetor; i++) {
            comparacoesSequencialVetor++;
            if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
                encontrado = true;
                printf("\n--- Item Encontrado ---");
                printf("\nNome: %s\n", mochilaVetor[i].nome);
                printf("Tipo: %s\n", mochilaVetor[i].tipo);
                printf("Quantidade: %d\n", mochilaVetor[i].quantidade);
                break;
            }
        }

        if (!encontrado) {
            printf("Item nao encontrado na mochila.\n");
        }

        printf("Numero de comparacoes (Sequencial - Vetor): %lld\n", comparacoesSequencialVetor);
    } else {
        printf("Mochila vazia! Nao ha itens para buscar.\n");
    }
}

// Função para ordenar o vetor de itens por nome (Bubble Sort)
void ordenarVetor() {
    if (numItensVetor > 1) {
        int i, j;
        Item temp;
        for (i = 0; i < numItensVetor - 1; i++) {
            for (j = 0; j < numItensVetor - i - 1; j++) {
                if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                    // Troca os elementos
                    temp = mochilaVetor[j];
                    mochilaVetor[j] = mochilaVetor[j + 1];
                    mochilaVetor[j + 1] = temp;
                }
            }
        }
        printf("Mochila ordenada por nome com sucesso!\n");
        listarItensVetor();
    } else {
        printf("Nao ha itens suficientes para ordenar a mochila.\n");
    }
}

// Função para buscar um item pelo nome (Busca Binária - Vetor)
void buscarBinariaVetor() {
    if (numItensVetor > 0) {
        char nomeBusca[30];
        printf("\n--- Buscar Item (Binaria - Vetor) ---");
        printf("\nNome do item a ser buscado: ");
        scanf("%s", nomeBusca);

        int esquerda = 0, direita = numItensVetor - 1, meio;
        bool encontrado = false;
        comparacoesBinariaVetor = 0;

        while (esquerda <= direita) {
            meio = esquerda + (direita - esquerda) / 2;
            comparacoesBinariaVetor++;

            int resultadoComparacao = strcmp(mochilaVetor[meio].nome, nomeBusca);

            if (resultadoComparacao == 0) {
                encontrado = true;
                printf("\n--- Item Encontrado ---");
                printf("\nNome: %s\n", mochilaVetor[meio].nome);
                printf("Tipo: %s\n", mochilaVetor[meio].tipo);
                printf("Quantidade: %d\n", mochilaVetor[meio].quantidade);
                break;
            } else if (resultadoComparacao < 0) {
                esquerda = meio + 1;
            } else {
                direita = meio - 1;
            }
        }

        if (!encontrado) {
            printf("Item nao encontrado na mochila.\n");
        }

        printf("Numero de comparacoes (Binaria - Vetor): %lld\n", comparacoesBinariaVetor);
    } else {
        printf("Mochila vazia! Nao ha itens para buscar.\n");
    }
}


// ============================================================================
// FUNÇÕES DA LISTA ENCADEADA
// ============================================================================

// Função para inserir um novo item na lista encadeada
void inserirItemLista() {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o novo item.\n");
        return;
    }

    printf("\n--- Adicionar Item (Lista Encadeada) ---");
    printf("\nNome: ");
    scanf("%s", novoNo->dados.nome);
    printf("Tipo (arma, municao, cura): ");
    scanf(" %s", novoNo->dados.tipo);
    printf("Quantidade: ");
    scanf(" %d", &novoNo->dados.quantidade);
    getchar(); // Consumir o newline

    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    numItensLista++;

    printf("Item adicionado com sucesso!\n");
    listarItensLista();
}


// Função para remover um item da lista encadeada pelo nome
void removerItemLista() {
    if (inicioLista == NULL) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remover Item (Lista Encadeada) ---");
    printf("\nNome do item a ser removido: ");
    scanf("%s", nomeRemover);

    No* atual = inicioLista;
    No* anterior = NULL;
    bool encontrado = false;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeRemover) == 0) {
            encontrado = true;
            if (anterior == NULL) {
                // Item a ser removido é o primeiro da lista
                inicioLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            numItensLista--;
            printf("Item removido com sucesso!\n");
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }

    listarItensLista();
}


// Função para listar todos os itens na lista encadeada
void listarItensLista() {
    if (inicioLista == NULL) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\n--- Lista de Itens na Mochila (Lista Encadeada) ---");
    printf("\n| %-30s | %-20s | %-10s |\n", "Nome", "Tipo", "Quantidade");
    printf("|--------------------------------|----------------------|------------|\n");

    No* atual = inicioLista;
    while (atual != NULL) {
        printf("| %-30s | %-20s | %-10d |\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}


// Função para buscar um item pelo nome na lista encadeada (Busca Sequencial)
void buscarSequencialLista() {
    if (inicioLista == NULL) {
        printf("Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Buscar Item (Sequencial - Lista Encadeada) ---");
    printf("\nNome do item a ser buscado: ");
    scanf("%s", nomeBusca);

    No* atual = inicioLista;
    bool encontrado = false;
    comparacoesSequencialLista = 0;

    while (atual != NULL) {
        comparacoesSequencialLista++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            encontrado = true;
            printf("\n--- Item Encontrado ---");
            printf("\nNome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("Item nao encontrado na mochila.\n");
    }

    printf("Numero de comparacoes (Sequencial - Lista Encadeada): %lld\n", comparacoesSequencialLista);
}

// Função para liberar a memória alocada para a lista encadeada
void liberarLista() {
    No* atual = inicioLista;
    No* proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    inicioLista = NULL; // Define o início da lista como NULL após liberar a memória
    numItensLista = 0; // Reinicializa o contador de itens
}