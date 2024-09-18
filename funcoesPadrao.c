#include "./funcoesCriadas.h"

//funcao que direciona o codigo para cada funcao de acordo com o numero selecionado

void direcionaComando(int codigo){
    switch (codigo){

    case 1:
        csv_para_bin();
        break;

    case 2:
        exibe_campos();
        break;

    case 3:
        busca_determinada();
        break;

    case 4:
        remocao_logica();
        break;

    case 5:
        break;

    case 6:
        compactador();
        break;

    default:
        printf(ERRO_COMANDO);    //PRINT DA MENSAGEM PADRAO DE ERRO CASO O USUARIO DIGITE UM COMANDO INEXISTENTE
        break;
    }

}

//funcao que compara uma string dada com nomes de campos existentes, se a string dada nao for igual a nada retorna -1 

int checa_nome_campo(char *string){
    
    if (!strcmp(string, "nome"))
    {
        return 1;
    }
    if (!strcmp(string, "especie"))
    {
        return 2;
    }
    if (!strcmp(string, "habitat"))
    {
        return 3;
    }
    if (!strcmp(string, "tipo"))
    {
        return 4;
    }
    if (!strcmp(string, "dieta"))
    {
        return 5;
    }
    if (!strcmp(string, "alimento"))
    {
        return 6;
    }
    if (!strcmp(string, "unidade"))
    {
        return 7;
    }
    if (!strcmp(string, "velocidade"))
    {
        return 8;
    }
    if (!strcmp(string, "tamanho"))
    {
        return 9;
    }
    if (!strcmp(string, "populacao"))
    {
        return 10;
    }
    return -1;
}
