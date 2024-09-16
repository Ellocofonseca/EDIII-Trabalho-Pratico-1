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
        break;

    case 4:
        break;

    case 5:
        break;

    case 6:
        break;

    default:
        printf(ERRO_COMANDO);    //PRINT DA MENSAGEM PADRAO DE ERRO CASO O USUARIO DIGITE UM COMANDO INEXISTENTE
        break;
    }

}
