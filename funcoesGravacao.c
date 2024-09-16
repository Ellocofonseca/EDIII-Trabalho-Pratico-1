#include "./funcoesCriadas.h"
#include "./funcoes_fornecidas.h"

void csv_para_bin()
{
    int i,j;                    //variavel auxiliar
    int insercoes;
    char nomecsv[31];           //nome do arquivo csv que sera aberto
    char nomebin[31];           //nome do arquivo bin que sera criado
    dados REGISTRO;             //variavel de registro
    cabecalho CAB;              //variavel de cabecalho

    char* linha;                //variaveis que serao usadas para ler e manipular cada linha do csv      
    char tmp[200];

    //tokens/strings que formarao o campo de tamanho variavel do registro de especie
    char *token;            //usado para coletar os valores numericos(int e float)
    char limitador[2]="#";
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
    insercoes=0;

    escreve_cabecalho_bin(nomebin,CAB); //'reserva o espaco do cabecalho e marca a flag status'


    //LER DO CSV, IR GRAVANDO OS REGISTROS E ATUALIZANDO A STRUCT DO CABECALHO

    //nome,dieta,habitat,populacao,tipo,velocidade,unidadeMedida,tamanho,especie,alimento 
    FILE *arqcsv;
    arqcsv = fopen(nomecsv,"r");
    if(arqcsv==NULL){
        printf(ERRO_PADRAO);
    }
    else{
        fgets(tmp, 200, arqcsv);//le e "descarta" a primeira linha
        while (fgets(tmp, 200, arqcsv))//le as linhas subsequentes ate chegar no fim do arquivo
        {
            linha= strdup(tmp);
            //leitura de cada dado de uma linha do csv
            nome = strsep(&linha, ",");
            dieta = strsep(&linha, ",");
            habitat = strsep(&linha, ",");
            token = strsep(&linha, ",");      //populacao
            REGISTRO.populacao=atoi(token);
            tipo = strsep(&linha, ",");
            token = strsep(&linha, ",");      //velocidade
            REGISTRO.velocidade=atoi(token);
            token = strsep(&linha, ",");      //unidMedida
            REGISTRO.unidadeMedida=token[0];
            token = strsep(&linha, ",");      //tamanho     //algum problema ao representar 0
            REGISTRO.tamanho=atof(token);
            if(token[0]='\0')
                REGISTRO.tamanho=36;
            especie = strsep(&linha, ",");
            alimento = strsep(&linha, "\r");

            REGISTRO.encadeamento=-1;
            REGISTRO.removido='0';

            //montagem do campo de tamanho variavel 
            var[0]='\0';
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
            strcat(var, limitador);

            for(j=strlen(var); j<142;j++)    //coloca o cifrao no lugar dos espacos em branco
                var[j] = '$';

            strcpy(REGISTRO.variavel,var);  //coloca a string montada na variavel de registro
            
            for(j=0;j<142;j++)
                var[j]='\0';

            //GUARDA O REGISTRO NO ARQUIVO
            escreve_dado_bin(nomebin,REGISTRO);
            
        }   
        fclose(arqcsv);//fecha o csv depois de tudo ter sido lido e guardado
    }

    
    CAB.topo=-1;
    CAB.proxRRN=insercoes;
    CAB.nroRegRem=0;
    CAB.nroPagDisco=(1+(insercoes/10));
    if(CAB.nroPagDisco*10<insercoes+10){
        CAB.nroPagDisco++;
    }

    CAB.qttCompacta=0;
    CAB.status='1';
    atualiza_cabecalho_bin(nomebin,CAB);

    binarioNaTela(nomebin); //binario na tela, resultado
}


