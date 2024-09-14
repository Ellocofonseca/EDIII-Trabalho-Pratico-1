#include "./funcoesCriadas.h"
#include "./funcoes_fornecidas.h"

void csv_para_bin()
{
    int i,j;                    //variavel auxiliar
    char nomecsv[31];           //nome do arquivo csv que sera aberto
    char nomebin[31];           //nome do arquivo bin que sera criado
    dados REGISTRO;             //variavel de registro
    cabecalho CAB;              //variavel de cabecalho
    char linha[200];
    char limitador[2]="#";
    char *token;

    char *nome;
    char *especie;
    char *habitat;
    char *tipo;
    char *dieta;
    char *alimento;
    char var[142];

    scanf("%s",nomecsv);
    scanf("%s",nomebin);

    CAB.status='0';

    //escreve_cabecalho_bin(nomebin,CAB); //'reserva o espaco do cabecalho e marca a flag status'


    //LER DO CSV, IR GRAVANDO OS REGISTROS E ATUALIZANDO A STRUCT DO CABECALHO

    //nome,dieta,habitat,populacao,tipo,velocidade,unidadeMedida,tamanho,especie,alimento 
    FILE *arqcsv;
    arqcsv = fopen(nomecsv,"r");
    if(arqcsv==NULL){
        printf(ERRO_PADRAO);
    }
    else{
        fgets(linha, 200, arqcsv);//le e "descarta" a primeira linha
        while (fgets(linha, 200, arqcsv))//le as linhas subsequentes
        {
            nome = strtok(linha, ",");
            dieta = strtok(NULL, ",");
            habitat = strtok(NULL, ",");
            token = strtok(NULL, ",");      //populacao
            tipo = strtok(NULL, ",");
            token = strtok(NULL, ",");      //velocidade
            token = strtok(NULL, ",");      //unidMedida
            token = strtok(NULL, ",");      //tamanho
            especie = strtok(NULL, ",");
            alimento = strtok(NULL, ",");

            strcat(var, nome);
            strcat(var, limitador);
            strcat(var, especie);
            strcat(var, limitador);
            strcat(var, habitat);
            strcat(var, limitador);
            strcat(var, tipo);
            strcat(var, limitador);
            strcat(var, dieta);
            strcat(var, limitador);
            strcat(var, alimento);
            for(j=strlen(var); j<142;j++){    //coloca o cifrao no lugar dos espacos em branco, INCLUINDO O '\0'
                var[j] = '$';
            }
            //GUARDA OS VALORES NO ARQUIVO
            


            var[0]='\0'; //reinicia a string de valor variavel
        }   
        fclose(arqcsv);
    }


    CAB.status='1';
    //atualiza_cabecalho_bin(nomebin,CAB);

   // binarioNaTela(nomebin); //binario na tela, resultado
}


void escreve_cabecalho_bin(char nomebin[31],cabecalho CAB){
    FILE *arquivobin;
    char lixo='$';
    arquivobin = fopen(nomebin, "ab");  //cria o arquivo caso n exista
    fwrite(&CAB.status, 1, 1, arquivobin);
    fwrite(&CAB.topo, 4, 1, arquivobin);
    fwrite(&CAB.proxRRN, 4, 1, arquivobin);
    fwrite(&CAB.nroRegRem, 4, 1, arquivobin);
    fwrite(&CAB.nroPagDisco, 4, 1, arquivobin);
    fwrite(&CAB.qttCompacta, 4, 1, arquivobin);
    fwrite(&lixo, 1, 1579, arquivobin);
    fclose(arquivobin);
}

void atualiza_cabecalho_bin(char nomebin[31],cabecalho CAB){
    FILE *arquivobin;
    arquivobin = fopen(nomebin, "rb+"); //abre o arquivo para atualizar o cabecalho
    if(arquivobin==NULL){
        printf(ERRO_PADRAO);
    }
    else{
    fwrite(&CAB.status, 1, 1, arquivobin);
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
    fwrite(&DADO.removido, 1, 1, arquivobin);
    fwrite(&DADO.encadeamento, 4, 1, arquivobin);
    fwrite(&DADO.populacao, 4, 1, arquivobin);
    fwrite(&DADO.tamanho, 4, 1, arquivobin);
    fwrite(&DADO.unidadeMedida, 1, 1, arquivobin);
    fwrite(&DADO.velocidade, 4, 1, arquivobin);
    fwrite(DADO.variavel, 142, 1, arquivobin);
    fclose(arquivobin);
}

