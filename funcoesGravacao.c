#include "./funcoesCriadas.h"
#include "./funcoesFornecidas.h"

void csv_para_bin()
{
    int i,j;                    //variavel auxiliar
    char nomecsv[31];           //nome do arquivo csv que sera aberto
    char nomebin[31];           //nome do arquivo bin que sera criado
    dados REGISTRO;             //variavel de registro

    readline(nomecsv);
    readline(nomebin);

    FILE *arquivocsv;
    FILE *arquivobin;
    arquivocsv = fopen(nomecsv, "r"); //abre o csv em modo leitura

    if(arquivocsv == NULL){
        printf(ERRO_PADRAO);     
    }
    else{


    }


    binarioNaTela(nomebin); //binario na tela, resultado
}

void escreve_cabecalho_bin(char nomebin[31],cabecalho CAB){
    FILE *arquivobin;
    arquivobin = fopen(nomebin, "ab");
    fwrite(CAB.status, 1, 1, arquivobin);
    fwrite(&CAB.topo, 4, 1, arquivobin);
    fwrite(&CAB.proxRRN, 4, 1, arquivobin);
    fwrite(&CAB.nroRegRem, 4, 1, arquivobin);
    fwrite(&CAB.nroPagDisco, 1, 1, arquivobin);
    fwrite(&CAB.qttCompacta, 4, 1, arquivobin);
    fwrite(CAB.lixo_pag, 1579, 1, arquivobin);
    fclose(arquivobin);
}

void escreve_dado_bin(char nomebin[31],dados DADO){
    FILE *arquivobin;
    arquivobin = fopen(nomebin, "ab");
    fwrite(DADO.removido, 1, 1, arquivobin);
    fwrite(&DADO.encadeamento, 4, 1, arquivobin);
    fwrite(&DADO.populacao, 4, 1, arquivobin);
    fwrite(&DADO.tamanho, 4, 1, arquivobin);
    fwrite(DADO.unidadeMedida, 1, 1, arquivobin);
    fwrite(&DADO.velocidade, 4, 1, arquivobin);
    fwrite(DADO.variavel, 142, 1, arquivobin);
    fclose(arquivobin);
}

void le_csv(){
    
}