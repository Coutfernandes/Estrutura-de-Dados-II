#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int Dia;
    int Mes;
} Data;

typedef struct {
    char Nome[41];
    char Telefone[16];
    char Celular[16];
    char Email[41];
    Data DataAniversario;
} Contato;

typedef struct elemento {
    Contato info;
    struct elemento *prox;
} Elemento;

Elemento* cria_agenda();
Elemento* insere_contato(Elemento *agenda, Contato novo_contato);
void lista_contatos(Elemento *agenda);
Elemento* busca_contato(Elemento *agenda, const char *nome_busca);
void remove_contato(Elemento **agenda);
void atualiza_contato(Elemento *agenda);
void ler_contato(Contato *c);
void exibe_contato(Contato c);
int menu();

Elemento* cria_agenda() {
    return NULL;
}

void ler_contato(Contato *c) {
    printf("--- Cadastro de Novo Contato ---\n");
    printf("Nome (max 40): ");
    scanf(" %40[^\n]", c->Nome);
    printf("Telefone (max 15): ");
    scanf(" %15[^\n]", c->Telefone);
    printf("Celular (max 15): ");
    scanf(" %15[^\n]", c->Celular);
    printf("Email (max 40): ");
    scanf(" %40[^\n]", c->Email);
    printf("Data de Aniversário (Dia Mes): ");
    scanf("%d %d", &c->DataAniversario.Dia, &c->DataAniversario.Mes);
}

void exibe_contato(Contato c) {
    printf("------------------------------\n");
    printf("Nome: %s\n", c.Nome);
    printf("Telefone: %s\n", c.Telefone);
    printf("Celular: %s\n", c.Celular);
    printf("Email: %s\n", c.Email);
    printf("Aniversário: %02d/%02d\n", c.DataAniversario.Dia, c.DataAniversario.Mes);
    printf("------------------------------\n");
}

Elemento* insere_contato(Elemento *agenda, Contato novo_contato) {
    Elemento *novo_elemento = (Elemento*) malloc(sizeof(Elemento));
    
    if (novo_elemento == NULL) {
        printf("Erro de alocação de memória.\n");
        return agenda;
    }
    
    novo_elemento->info = novo_contato;
    novo_elemento->prox = NULL;
    
    if (agenda == NULL) {
        return novo_elemento;
    }
    
    Elemento *p = agenda;
    while (p->prox != NULL) {
        p = p->prox;
    }
    
    p->prox = novo_elemento;
    
    printf("Contato \"%s\" inserido com sucesso.\n", novo_contato.Nome);
    return agenda;
}

void lista_contatos(Elemento *agenda) {
    if (agenda == NULL) {
        printf("A agenda está vazia.\n");
        return;
    }
    
    printf("\n--- LISTA DE CONTATOS ---\n");
    Elemento *p = agenda;
    int i = 1;
    while (p != NULL) {
        printf("Contato %d:\n", i++);
        exibe_contato(p->info);
        p = p->prox;
    }
    printf("--- FIM DA LISTA ---\n");
}

Elemento* busca_contato(Elemento *agenda, const char *nome_busca) {
    Elemento *p = agenda;
    
    while (p != NULL) {
        if (strcmp(p->info.Nome, nome_busca) == 0) {
            return p;
        }
        p = p->prox;
    }
    
    return NULL;
}

void remove_contato(Elemento **agenda) {
    char nome_busca[41];
    printf("Digite o nome do contato a ser removido: ");
    scanf(" %40[^\n]", nome_busca);
    
    Elemento *atual = *agenda;
    Elemento *anterior = NULL;

    while (atual != NULL && strcmp(atual->info.Nome, nome_busca) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("Contato \"%s\" não encontrado na agenda. Nada foi removido.\n", nome_busca);
        return;
    }
    
    if (anterior == NULL) {
        *agenda = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    
    free(atual);
    printf("Contato \"%s\" removido com sucesso.\n", nome_busca);
}

void atualiza_contato(Elemento *agenda) {
    char nome_busca[41];
    printf("Digite o nome do contato a ser editado: ");
    scanf(" %40[^\n]", nome_busca);

    Elemento *elemento_encontrado = busca_contato(agenda, nome_busca);
    
    if (elemento_encontrado == NULL) {
        printf("Contato \"%s\" não encontrado na agenda. Nenhuma alteração foi feita.\n", nome_busca);
        return;
    }
    
    printf("Contato encontrado. Digite as novas informações:\n");
    printf("\nDados Atuais:\n");
    exibe_contato(elemento_encontrado->info);

    Contato novo_dados;
    ler_contato(&novo_dados); 
    
    elemento_encontrado->info = novo_dados;
    
    printf("\nContato \"%s\" atualizado com sucesso.\n", nome_busca);
}

int menu() {
    int opcao;
    printf("\n--- MENU DA AGENDA TELEFÔNICA ---\n");
    printf("1. Inserir Contato\n");
    printf("2. Listar Contatos\n");
    printf("3. Buscar Contato\n");
    printf("4. Editar Contato\n");
    printf("5. Remover Contato\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    while (getchar() != '\n'); 
    return opcao;
}

int main() {
    Elemento *agenda = cria_agenda();
    int opcao;
    
    do {
        opcao = menu();
        
        switch (opcao) {
            case 1: {
                Contato novo;
                ler_contato(&novo);
                agenda = insere_contato(agenda, novo);
                break;
            }
            case 2: {
                lista_contatos(agenda);
                break;
            }
            case 3: {
                char nome_busca[41];
                printf("Digite o nome do contato a ser buscado: ");
                scanf(" %40[^\n]", nome_busca);
                
                Elemento *encontrado = busca_contato(agenda, nome_busca);
                
                if (encontrado != NULL) {
                    printf("--- Contato Encontrado ---\n");
                    exibe_contato(encontrado->info);
                } else {
                    printf("Contato \"%s\" não encontrado na agenda.\n", nome_busca);
                }
                break;
            }
            case 4: {
                atualiza_contato(agenda);
                break;
            }
            case 5: {
                remove_contato(&agenda);
                break;
            }
            case 6: {
                printf("Encerrando o programa. Memória da agenda será liberada.\n");
                break;
            }
            default: {
                printf("Opção inválida. Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 6);
    
    Elemento *atual = agenda;
    Elemento *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    
    return 0;
}
