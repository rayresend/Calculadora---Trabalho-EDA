/*Integrantes: Maria Clara Jardim e Rayssa Resende*/

#ifndef PILHA_H
#define PILHA_H

#include <stddef.h>

typedef struct NoReal {
    double valor;
    struct NoReal *proximo;
} NoReal;

typedef struct {
    NoReal *topo;
    size_t tamanho;
} PilhaReais;

typedef struct NoOperador {
    char operador;
    struct NoOperador *proximo;
} NoOperador;

typedef struct {
    NoOperador *topo;
    size_t tamanho;
} PilhaOperadores;

void inicializar_pilhas(PilhaReais *valores, PilhaOperadores *operadores);
void liberar_pilhas(PilhaReais *valores, PilhaOperadores *operadores);
int empilhar_real(PilhaReais *pilha, double valor);
int empilhar_operador(PilhaOperadores *pilha, char operador);
int desempilhar_real(PilhaReais *pilha, double *valor);
int desempilhar_operador(PilhaOperadores *pilha, char *operador);
int operador_valido(char operador);
int realizar_calculo(PilhaReais *valores, PilhaOperadores *operadores,
                     double *resultado);
void imprimir_pilha_reais(const PilhaReais *pilha);
void imprimir_pilha_operadores(const PilhaOperadores *pilha);

#endif /* PILHA_H */
