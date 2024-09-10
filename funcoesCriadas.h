#ifndef __FUNCOES_CRIADAS__
#define __FUNCOES_CRIADAS__

//-------BIBLIOTECAS------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

//------MENSAGENS-DE-ERRO-----


// CADA PAGINA DE DISCO POSSUI 1600 BYTES
//REGISTRO DE CABECALHO, 21 BYTES + lixo = 1600 bytes
typedef struct
{
    char status;                // Indicacao da consistencia do arq. de dados, se for 1 esta consistente e se for 0 nao     1 byte
    int topo;                   // Armazena o RRN de um registro logicamente removido ou -1 caso nao haja                   4 bytes
    int proxRRN;                // Armazena o valor do prox RRN disponivel, inicia como 0 e muda caso necessario            4 bytes
    int nroRegRem;              // Armazena o nro de registros logicamene marcados como removidos, inicia como 0            4 bytes
    int nroPagDisco;            // Armazena o nro de paginas de disco ocupadas pelo arq. de dados                           4 bytes
    int qttCompacta;            // Indica a qtd de vezes que o arquivo foi compactado                                       4 bytes
    char lixo_pag[1579];        // Lixo para completar a pag de disco, preencher com '$'                                    1579 bytes
} cabecalho;


// REGISTRO DE DADOS, 18 BYTES fixos + 142 BYTES VARIAVEIS = 160   1/10 DE PAGINA DE DISCO
typedef struct
{
    char removido;              //  Indica se o registro esta logicamente removido                    1 byte
    int encadeamento;           //  Armazena o RRN do proximo registro logicamente removido           4 bytes
    int populacao;              //  Qtd de individuos da especie que viviam em determinado lugar      4 bytes
    float tamanho;              //  Tamanho do individuo                                              4 bytes
    char unidadeMedida;         //  Unidade de medida da velocidade do individuo                      1 byte
    int velocidade;             //  Velocidade do individuo                                           4 bytes

    char variavel[142];         //  Bytes variaveis                                                   142 bytes
                                //  Nome-Especie-Habitat-Tipo-Dieta-Alimento
                                //  Cada campo variavel eh separado por um delimitador '#'
                                //  As strings nao devem terminar com \0
                                //  Se sobrar espaço preencher com '$'

} dados;


//--------FUNCOES-DO-PROGRAMA------------



#endif // __FUNCOES__