/*Integrantes: Maria Clara Jardim e Rayssa Resende*/

#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>


void inicializar_pilhas(PilhaReais *valores, PilhaOperadores *operadores)
{
    if (valores != NULL) {
        valores->topo = NULL;
        valores->tamanho = 0;
    }
    if (operadores != NULL) {
        operadores->topo = NULL;
        operadores->tamanho = 0;
    }
}

void liberar_pilhas(PilhaReais *valores, PilhaOperadores *operadores)
{
    double valor;
    char operador;

    if (valores != NULL) {
        while (desempilhar_real(valores, &valor)) {
        }
    }
    if (operadores != NULL) {
        while (desempilhar_operador(operadores, &operador)) {
        }
    }
}

int empilhar_real(PilhaReais *pilha, double valor)
{
    NoReal *novo;

    if (pilha == NULL) {
        return 0;
    }
    novo = malloc(sizeof(*novo));
    if (novo == NULL) {
        return 0;
    }
    novo->valor = valor;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
    return 1;
}

int empilhar_operador(PilhaOperadores *pilha, char operador)
{
    NoOperador *novo;

    if (pilha == NULL || !operador_valido(operador)) {
        return 0;
    }
    novo = malloc(sizeof(*novo));
    if (novo == NULL) {
        return 0;
    }
    novo->operador = operador;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
    return 1;
}

int desempilhar_real(PilhaReais *pilha, double *valor)
{
    NoReal *removido;

    if (pilha == NULL || pilha->topo == NULL) {
        return 0;
    }
    removido = pilha->topo;
    if (valor != NULL) {
        *valor = removido->valor;
    }
    pilha->topo = removido->proximo;
    pilha->tamanho--;
    free(removido);
    return 1;
}

int desempilhar_operador(PilhaOperadores *pilha, char *operador)
{
    NoOperador *removido;

    if (pilha == NULL || pilha->topo == NULL) {
        return 0;
    }
    removido = pilha->topo;
    if (operador != NULL) {
        *operador = removido->operador;
    }
    pilha->topo = removido->proximo;
    pilha->tamanho--;
    free(removido);
    return 1;
}

int operador_valido(char operador)
{
    return operador == '+' || operador == '-' || operador == '*' || operador == '/';
}

int realizar_calculo(PilhaReais *valores, PilhaOperadores *operadores,
                     double *resultado)
{
    double primeiro = 0.0;
    double segundo = 0.0;
    double calculado;
    char operador = '\0';

    if (valores == NULL || operadores == NULL || valores->tamanho < 2 ||
        operadores->tamanho < 1) {
        return 0;
    }

    /* O primeiro valor retirado do topo é o segundo operando. */
    desempilhar_real(valores, &segundo);
    desempilhar_real(valores, &primeiro);
    desempilhar_operador(operadores, &operador);

    if (operador == '/' && segundo == 0.0) {
        empilhar_real(valores, primeiro);
        empilhar_real(valores, segundo);
        empilhar_operador(operadores, operador);
        return -1;
    }

    switch (operador) {
        case '+': calculado = primeiro + segundo; break;
        case '-': calculado = primeiro - segundo; break;
        case '*': calculado = primeiro * segundo; break;
        case '/': calculado = primeiro / segundo; break;
        default:
            empilhar_real(valores, primeiro);
            empilhar_real(valores, segundo);
            empilhar_operador(operadores, operador);
            return 0;
    }

    if (!empilhar_real(valores, calculado)) {
        empilhar_real(valores, primeiro);
        empilhar_real(valores, segundo);
        empilhar_operador(operadores, operador);
        return 0;
    }
    if (resultado != NULL) {
        *resultado = calculado;
    }
    return 1;
}

void imprimir_pilha_reais(const PilhaReais *pilha)
{
    const NoReal *atual;

    printf("Pilha de valores (topo para base): ");
    if (pilha == NULL || pilha->topo == NULL) {
        printf("vazia\n");
        return;
    }
    atual = pilha->topo;
    while (atual != NULL) {
        printf("%.2f", atual->valor);
        if (atual->proximo != NULL) {
            printf(" -> ");
        }
        atual = atual->proximo;
    }
    printf("\n");
}

void imprimir_pilha_operadores(const PilhaOperadores *pilha)
{
    const NoOperador *atual;

    printf("Pilha de operadores (topo para base): ");
    if (pilha == NULL || pilha->topo == NULL) {
        printf("vazia\n");
        return;
    }
    atual = pilha->topo;
    while (atual != NULL) {
        printf("%c", atual->operador);
        if (atual->proximo != NULL) {
            printf(" -> ");
        }
        atual = atual->proximo;
    }
    printf("\n");
}
