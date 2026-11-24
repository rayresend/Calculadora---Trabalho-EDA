/*Integrantes: Maria Clara Jardim e Rayssa Resende*/

#include "pilha.h"
#include <stdio.h>

static void limpar_entrada(void)
{
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

static void exibir_menu(void)
{
    printf("\n========== CALCULADORA COM PILHAS =========="
           "\n1. Empilhar valor real"
           "\n2. Empilhar operador"
           "\n3. Realizar calculo"
           "\n4. Imprimir pilhas"
           "\n0. Sair"
           "\nEscolha uma opcao: ");
}

int main(void)
{
    PilhaReais valores;
    PilhaOperadores operadores;
    int opcao;

    inicializar_pilhas(&valores, &operadores);
    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida. Digite um numero.\n");
            limpar_entrada();
            continue;
        }
        limpar_entrada();

        switch (opcao) {
            case 1: {
                double valor;
                printf("Digite o valor real: ");
                if (scanf("%lf", &valor) != 1) {
                    printf("Valor invalido.\n");
                    limpar_entrada();
                } else if (!empilhar_real(&valores, valor)) {
                    printf("Nao foi possivel alocar memoria.\n");
                    limpar_entrada();
                } else {
                    limpar_entrada();
                    printf("Valor empilhado com sucesso.\n");
                }
                break;
            }
            case 2: {
                char operador;
                printf("Digite um operador (+, -, * ou /): ");
                if (scanf(" %c", &operador) != 1) {
                    printf("Entrada invalida.\n");
                    limpar_entrada();
                } else if (!operador_valido(operador)) {
                    printf("Operador invalido. Use +, -, * ou /.\n");
                    limpar_entrada();
                } else if (!empilhar_operador(&operadores, operador)) {
                    printf("Nao foi possivel alocar memoria.\n");
                    limpar_entrada();
                } else {
                    limpar_entrada();
                    printf("Operador empilhado com sucesso.\n");
                }
                break;
            }
            case 3: {
                double resultado;
                int status = realizar_calculo(&valores, &operadores, &resultado);
                if (status == 1) {
                    printf("Resultado: %.2f\n", resultado);
                } else if (status == -1) {
                    printf("Erro: nao e possivel dividir por zero.\n");
                } else {
                    printf("Nao ha valores ou operador suficientes para calcular.\n");
                }
                break;
            }
            case 4:
                imprimir_pilha_reais(&valores);
                imprimir_pilha_operadores(&operadores);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberar_pilhas(&valores, &operadores);
    return 0;
}
