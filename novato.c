#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura para representar um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int total = 0; // quantidade atual do itens
    int opcao;

    do
    {
        printf("\n==== Mochila Virtual - Free Fire =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: // Adiciona item
            if (total < MAX_ITENS) {
                printf("Digite o nome do item: ");
                scanf(" %[^\n]", mochila[total].nome);
                printf("Digite o tipo do item: ");
                scanf(" %[^\n]", mochila[total].tipo);
                printf("Digite a quantidade: ");
                scanf("%d", &mochila[total].quantidade);
                total++;
                printf("Item adicionado com sucesso!\n");
            } else {
                printf("Mochila cheia! Capacidade maxima de %d itens.\n", MAX_ITENS);
            }
            break;
        
        case 2: { // Remover item
            char nomeRemover[30];
            int encontrado = 0;
            printf("Digite o nome do item a remover: ");
            scanf(" %[^\n]", nomeRemover);

            for (int i = 0; i < total; i++) {
                if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                    // desloca os itens para preencher o espaço
                    for (int j = i; j < total - 1; j++) {
                        mochila[j] = mochila[j + 1];
                    } 
                    total--;
                    encontrado = 1;
                    printf("Item removido com sucesso!\n");
                    break;
                } 
            }
            if (!encontrado) {
                printf("Item nao encontrado na mochila.\n");
            }
            break;  
        }

        case 3: // Listar itens
            if (total == 0) {
                printf("Mochila vazia.\n");
            } else {
                printf("\n==== Itens na Mochila =====\n");
                printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                for (int i = 0; i < total; i++) {
                    printf("%-20s %-15s %-10d\n",
                        mochila[i].nome,
                        mochila[i].tipo,
                        mochila[i].quantidade);
                }
                
            }
            break;

        case 4:
            printf("Saindo do programa...\n");
            break;
            
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 4);

    return 0;
    
}
