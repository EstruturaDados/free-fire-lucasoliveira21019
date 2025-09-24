#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Declaração do vetor de structs para armazenar os itens
Item mochila[10];
int numItens = 0; // Variável para controlar o número de itens na mochila

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

int main() {
    int opcao;

    do {
        // Menu interativo
        printf("\n--- Menu ---");
        printf("\n1. Adicionar Item");
        printf("\n2. Remover Item");
        printf("\n3. Listar Itens");
        printf("\n4. Buscar Item");
        printf("\n0. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Consumir o newline deixado pelo scanf

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
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

// Função para inserir um novo item na mochila
void inserirItem() {
    if (numItens < 10) {
        Item novoItem;

        printf("\n--- Adicionar Item ---");
        printf("\nNome: ");
        scanf("%s", novoItem.nome);
        printf("Tipo (arma, municao, cura): ");
        scanf(" %s", novoItem.tipo);
        printf("Quantidade: ");
        scanf(" %d", &novoItem.quantidade);
        getchar(); // Consumir o newline

        mochila[numItens] = novoItem;
        numItens++;

        printf("Item adicionado com sucesso!\n");
        listarItens();
    } else {
        printf("Mochila cheia! Nao eh possivel adicionar mais itens.\n");
    }
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    if (numItens > 0) {
        char nomeRemover[30];
        printf("\n--- Remover Item ---");
        printf("\nNome do item a ser removido: ");
        scanf("%s", nomeRemover);

        int i, j;
        bool encontrado = false;

        for (i = 0; i < numItens; i++) {
            if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                encontrado = true;
                // Deslocar os itens para preencher o espaço do item removido
                for (j = i; j < numItens - 1; j++) {
                    mochila[j] = mochila[j + 1];
                }
                numItens--;
                printf("Item removido com sucesso!\n");
                break;
            }
        }

        if (!encontrado) {
            printf("Item nao encontrado na mochila.\n");
        }

        listarItens();
    } else {
        printf("Mochila vazia! Nao ha itens para remover.\n");
    }
}

// Função para listar todos os itens na mochila
void listarItens() {
    if (numItens > 0) {
        printf("\n--- Lista de Itens na Mochila ---");
        printf("\n| %-30s | %-20s | %-10s |\n", "Nome", "Tipo", "Quantidade");
        printf("|--------------------------------|----------------------|------------|\n");
        for (int i = 0; i < numItens; i++) {
            printf("| %-30s | %-20s | %-10d |\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    } else {
        printf("Mochila vazia!\n");
    }
}

// Função para buscar um item pelo nome
void buscarItem() {
    if (numItens > 0) {
        char nomeBusca[30];
        printf("\n--- Buscar Item ---");
        printf("\nNome do item a ser buscado: ");
        scanf("%s", nomeBusca);

        int i;
        bool encontrado = false;

        for (i = 0; i < numItens; i++) {
            if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                encontrado = true;
                printf("\n--- Item Encontrado ---");
                printf("\nNome: %s\n", mochila[i].nome);
                printf("Tipo: %s\n", mochila[i].tipo);
                printf("Quantidade: %d\n", mochila[i].quantidade);
                break;
            }
        }

        if (!encontrado) {
            printf("Item nao encontrado na mochila.\n");
        }
    } else {
        printf("Mochila vazia! Nao ha itens para buscar.\n");
    }
}