#include "./funcoesCriadas.h"
#include "./funcoes_fornecidas.h"


//funcao que abre um arquivo csv para realizar a leitura dos dados dele para que esses dados sejam salvos
//em um arquivo binario em formato especificado alem de seu cabecalho que tambem eh salvo

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

    escreve_cabecalho_bin(nomebin,CAB); //'reserva o espaco do cabecalho e marca a flag status='0'


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

            token = strsep(&linha, ",");        //populacao
            REGISTRO.populacao=atoi(token);
            if (REGISTRO.populacao==0)          //se o campo estiver vazio coloca o valor invalido -1
                REGISTRO.populacao=-1;

            tipo = strsep(&linha, ",");

            token = strsep(&linha, ",");        //velocidade
            REGISTRO.velocidade=atoi(token);
            if (REGISTRO.velocidade==0)            //se o campo estiver vazio coloca o valor invalido -1
                REGISTRO.velocidade=-1;
            
            token = strsep(&linha, ",");         //unidMedida
            REGISTRO.unidadeMedida=token[0];
            if (!strcmp(token,""))              //se o campo estiver vazio coloca o valor invalido $
                REGISTRO.unidadeMedida='$';


            token = strsep(&linha, ",");      //tamanho     //algum problema ao representar 0
            REGISTRO.tamanho=atof(token);
            if (fabs(0-REGISTRO.tamanho)<0.001)//se o campo estiver vazio coloca o valor invalido -1
                REGISTRO.tamanho=-1;

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
            
            for(j=0;j<142;j++)//limpa a string montada de tamanho variado 
                var[j]='\0';

            //GUARDA O REGISTRO NO ARQUIVO
            escreve_dado_bin(nomebin,REGISTRO);
            insercoes++;
            
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
    atualiza_cabecalho_bin(nomebin,CAB);    //atualiza o cabecalho ao final da insercao de todos os dados do csv

    binarioNaTela(nomebin); //binario na tela, resultado
}


//para evitar o uso de diversos fseeks o arquivo é lido de forma reversa
void remocao_logica(){
    int nroRemocoes,regRemovidos;
    int i, codigo_campo;
    char nomearq[31];           //nome do arquivo que sera lido
    char nomecampo[21];         //campo que sera checado para pesquisa
    char valorcampo[41];        //valor do campo que sera checado
    dados DADO;                 //variavel de registro

    cabecalho CAB;              //variavel do cabecalho

    //ponteiros para uso strdup e strsep para ler a parte variavel do registro de dados
    char *linha;
    char *nome;
    char *especie;
    char *habitat;
    char *tipo;
    char *dieta;
    char *alimento;

    FILE *arquivo;
    scanf("%s",nomearq);            //le o nome do arquivo que sera aberto
    arquivo = fopen(nomearq, "rb+"); //abre o arquivo em modo de leitura binaria + escrita

    if(arquivo==NULL){          //checa se o arquivo foi devidamente aberto
        printf(ERRO_PADRAO);
    }else{
        fclose(arquivo);        //fecha o arquivo depois de checar se ele existe
        scanf("%d",&nroRemocoes);

        for(i=0;i<nroRemocoes;i++){
            scanf("%s",nomecampo);
            scan_quote_string(valorcampo); 

            codigo_campo=checa_nome_campo(nomecampo);   //FUNCAO QUE TESTA A STRING NOMECAMPO E RETORNA UM INTEIRO DE ACORDO COM O NOME DE CAMPO

            if(codigo_campo==-1)
                printf(ERRO_COMANDO);
            

            DADO=le_registro(arquivo);

            if (DADO.removido=='2') //a variavel removido eh alterada para '2' dentro da funcao le registro se chegar no fim do arquivo
                break;

            linha=strdup(DADO.variavel);    //separa os campos de tamanho variado do dado em varias strrings
            nome = strsep(&linha, "#");
            especie = strsep(&linha, "#");
            habitat = strsep(&linha, "#");
            tipo = strsep(&linha, "#");
            dieta = strsep(&linha, "#");
            alimento = strsep(&linha, "#");


            while (codigo_campo!=-1)
            {
                switch (codigo_campo)
                {
                case 1:
                    if (!strcmp(valorcampo,nome)){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;

                case 2:
                    if (!strcmp(valorcampo,especie)){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;

                case 3:
                    if (!strcmp(valorcampo,habitat)){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;

                case 4:
                    if (!strcmp(valorcampo,tipo)){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;

                case 5:
                    if (!strcmp(valorcampo,dieta)){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;

                case 6:
                    if (!strcmp(valorcampo,alimento)){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;

                case 7:
                    if (valorcampo[0]==DADO.unidadeMedida){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;

                case 8:
                    if (atoi(valorcampo)==DADO.velocidade){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;

                case 9:
                    if (fabs(atof(valorcampo)-DADO.tamanho)<0.001){
                        remove_dado_bin(nomearq,arquivo);
                        regRemovidos++;
                    }
                    break;
                
                default:
                    break;
                }//FIM DO SWITCH
            }//FIM DO WHILE


            
        }//FIM DO FOR
        CAB.nroRegRem=regRemovidos;
        atualiza_cabecalho_bin(nomearq,CAB);
    }

}
