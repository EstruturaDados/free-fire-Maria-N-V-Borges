#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Estrutura para representar um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // valores de 1 a 5
} Item;

typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Função de ordenação (Insertion Sort)
int ordenar(Item mochila[], int total, CriterioOrdenacao criterio) {
    int comparacoes = 0;
    for (int i = 0; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j>= 0) {
            bool condicao = false;
            if (criterio == ORDENAR_NOME) {
                comparacoes++;
                condicao = strcmp(mochila[j].nome, chave.nome) > 0;
            } else if (criterio == ORDENAR_TIPO) {
                comparacoes++;
                condicao = strcmp(mochila[j].tipo, chave.tipo) > 0;
            } else if (criterio == ORDENAR_PRIORIDADE) {
                comparacoes++;
                condicao = mochila[j].prioridade > chave.prioridade;
            }
        
            if (condicao) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }  
        }
        mochila[j + 1] = chave;
    }
    return comparacoes;
}

// Função de busca binária por nome
int buscaBinaria(Item mochila[], int total, char nomeBusca[]) {
    int esquerda = 0, direita = total - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1;
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0; // quantidade atual de itens
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("\n===== Mochila Virtual - Free Fire =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar mochila\n");
        printf("5. Buscar item por nome (binaria)\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Adicionar item
                if (total < MAX_ITENS) {
                    printf("Digite o nome do item: ");
                    scanf(" %[^\n]", mochila[total].nome);
                    printf("Digite o tipo do item: ");
                    scanf(" %[^\n]", mochila[total].tipo);
                    printf("Digite a quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    printf("Digite a prioridade (1 a 5): ");
                    scanf("%d", &mochila[total].prioridade);
                    total++;
                    ordenadoPorNome = false; // perdeu ordenação
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
                        ordenadoPorNome = false;
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
                    printf("\n===== Itens na Mochila =====\n");
                    printf("%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
                    for (int i = 0; i < total; i++) {
                        printf("%-20s %-15s %-10d %-10d\n",
                               mochila[i].nome,
                               mochila[i].tipo,
                               mochila[i].quantidade,
                               mochila[i].prioridade);
                    }
                }
                break;
            
            case 4: { // Ordenar
                int criterio;
                printf("Escolha criterio de ordenacao:\n");
                printf("1. Nome\n2. Tipo\n3. Prioridade\n");
                scanf("%d", &criterio);

                int comparacoes = ordenar(mochila, total, criterio);
                printf("Mochila ordenada! Comparacoes realizadas: %d\n", comparacoes);

                if (criterio == ORDENAR_NOME) {
                    ordenadoPorNome = true;
                } else {
                    ordenadoPorNome = false;
                }
                break;
            }
            
            case 5: { // Buscar binária
                if (!ordenadoPorNome) {
                    printf("A lista deve estar ordenada por nome para busca binaria!\n");
                } else {
                    char nomeBusca[30];
                    printf("Digite o nome do item a buscar: ");
                    scanf(" %[^\n]", nomeBusca);

                    int pos = buscaBinaria(mochila, total, nomeBusca);
                    if (pos != -1) {
                        printf("\nItem encontrado!\n");
                        printf("Nome: %s\n", mochila[pos].nome);
                        printf("Tipo: %s\n", mochila[pos].tipo);
                        printf("Quantidade: %d\n", mochila[pos].quantidade);
                        printf("Prioridade: %d\n", mochila[pos].prioridade);
                    } else {
                        printf("Item nao encontrado.\n");
                    }
                }
                break;
            }

            case 6:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while(opcao != 6);

    return 0;
}
