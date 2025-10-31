#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define TAM 5

typedef struct {
    int id;
    char tipo;
} Peca;

typedef struct {
    Peca pecas[TAM];
    int inicio;
    int fim;
    int qtd;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
    f->qtd = 0;
}

char gerarTipo() {
    char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    return tipos[rand() % 7];
}

Peca gerarPeca(int id) {
    Peca p;
    p.id = id;
    p.tipo = gerarTipo();
    return p;
}

int filaCheia(Fila *f) {
    return f->qtd == TAM;
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->fim = (f->fim + 1) % TAM;
    f->pecas[f->fim] = p;
    f->qtd++;
}

Peca desenfileirar(Fila *f) {
    Peca p = {0, '-'};
    if (filaVazia(f)) return p;
    p = f->pecas[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->qtd--;
    return p;
}

void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila de peças:\n");
    int i, idx;
    for (i = 0; i < f->qtd; i++) {
        idx = (f->inicio + i) % TAM;
        printf("[%d - %c] ", f->pecas[idx].id, f->pecas[idx].tipo);
    }
    printf("\n");
}

int main() {
    Fila fila;
    int id = 1, opcao;
    srand(time(NULL));
    inicializarFila(&fila);

    for (int i = 0; i < TAM; i++)
        enfileirar(&fila, gerarPeca(id++));

    do {
        printf("\n1 - Jogar peça\n2 - Inserir nova peça\n3 - Exibir fila\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = desenfileirar(&fila);
            if (jogada.id != 0)
                printf("Peça jogada: [%d - %c]\n", jogada.id, jogada.tipo);
            else
                printf("Fila vazia.\n");
        } else if (opcao == 2) {
            if (filaCheia(&fila))
                printf("Fila cheia!\n");
            else {
                enfileirar(&fila, gerarPeca(id++));
                printf("Nova peça inserida!\n");
            }
        } else if (opcao == 3) {
            exibirFila(&fila);
        }

    } while (opcao != 0);

    return 0;
}

