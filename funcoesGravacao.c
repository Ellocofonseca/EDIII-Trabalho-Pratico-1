#include "./funcoesCriadas.h"
#include "./funcoes_fornecidas.h"

void csv_para_bin()
{
    int i,j;                    //variavel auxiliar
    char nomecsv[31];           //nome do arquivo csv que sera aberto
    char nomebin[31];           //nome do arquivo bin que sera criado
    dados REGISTRO;             //variavel de registro
    cabecalho CAB;              //variavel de cabecalho
    char linha[500];
    char *token;

    readline(nomecsv);
    readline(nomebin);

    FILE *arqcsv;

    CAB.status='0';

    //escreve_cabecalho_bin(nomebin,CAB); //'reserva o espaco do cabecalho e marca a flag status'


    //LER DO CSV, IR GRAVANDO OS REGISTROS E ATUALIZANDO A STRUCT DO CABECALHO
    while (fgets(linha, 500, arqcsv))
    {

        token = strtok(linha, ",");

        while(token != NULL)
        {
            printf("Token: %s\n", token);
            token = strtok(NULL, ",");
        }

    }


    CAB.status='1';
    //atualiza_cabecalho_bin(nomebin,CAB);

   // binarioNaTela(nomebin); //binario na tela, resultado
}

void le_csv_e_escreve_bin(char nomecsv[31],cabecalho CAB){
    
    FILE *arq;
    char linha[500];
    char *token;

    arq = fopen(nomecsv,"r");

    //nome,dieta,habitat,populacao,tipo,velocidade,unidadeMedida,tamanho,especie,alimento
    while (feof(arq) != true)
    {
        fgets(linha, 500, arq);

        token = strtok(linha, ",");

        while(token != NULL)
        {
            printf("Token: %s\n", token);
            token = strtok(NULL, ",");
        }

    }
    

    return 0;

}


void escreve_cabecalho_bin(char nomebin[31],cabecalho CAB){
    FILE *arquivobin;
    arquivobin = fopen(nomebin, "ab");  //cria o arquivo caso n exista
    fwrite(CAB.status, 1, 1, arquivobin);
    fwrite(&CAB.topo, 4, 1, arquivobin);
    fwrite(&CAB.proxRRN, 4, 1, arquivobin);
    fwrite(&CAB.nroRegRem, 4, 1, arquivobin);
    fwrite(&CAB.nroPagDisco, 4, 1, arquivobin);
    fwrite(&CAB.qttCompacta, 4, 1, arquivobin);
    fwrite('$', 1, 1579, arquivobin);
    fclose(arquivobin);
}

void atualiza_cabecalho_bin(char nomebin[31],cabecalho CAB){
    FILE *arquivobin;
    arquivobin = fopen(nomebin, "rb+"); //abre o arquivo para atualizar o cabecalho
    if(arquivobin==NULL){
        printf(ERRO_PADRAO);
    }
    else{
    fwrite(CAB.status, 1, 1, arquivobin);
    fwrite(&CAB.topo, 4, 1, arquivobin);
    fwrite(&CAB.proxRRN, 4, 1, arquivobin);
    fwrite(&CAB.nroRegRem, 4, 1, arquivobin);
    fwrite(&CAB.nroPagDisco, 4, 1, arquivobin);
    fwrite(&CAB.qttCompacta, 4, 1, arquivobin);
    fclose(arquivobin);
    }
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