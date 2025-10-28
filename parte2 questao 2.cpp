#include <stdio.h>
#include <stdlib.h>

int* cria_vetor_dinamico(int n) {
    int* vetor = (int*)malloc(n * sizeof(int));
    
    if (vetor == NULL) {
        printf("Erro: Falha na alocação de memória para o vetor.\n");
        exit(1);
    }
    
    printf("Memória alocada com sucesso para um vetor de %d elementos.\n", n);
    return vetor;
}

void imprime_vetor(int* vetor, int n) {
    printf("\n--- Elementos do Vetor ---\n");
    for (int i = 0; i < n; i++) {
        printf("Elemento %d: %d\n", i, vetor[i]);
    }
    printf("--------------------------\n");
}

void libera_vetor(int* vetor) {
    if (vetor != NULL) {
        free(vetor);
        printf("\nMemória do vetor liberada com sucesso.\n");
    }
}

int main() {
    int n;
    int *meu_vetor = NULL;

    printf("Digite o número de elementos (n) do vetor: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada inválida. O número deve ser um inteiro positivo.\n");
        return 1;
    }

    meu_vetor = cria_vetor_dinamico(n);

    printf("\nDigite os %d elementos do vetor:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Elemento [%d]: ", i);
        scanf("%d", &meu_vetor[i]);
    }

    imprime_vetor(meu_vetor, n);

    libera_vetor(meu_vetor);

    return 0;
}
