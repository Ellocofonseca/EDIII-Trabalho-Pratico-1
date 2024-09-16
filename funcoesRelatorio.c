#include "./funcoesCriadas.h"
#include "./funcoes_fornecidas.h"

//  Essa funcao abre um arquivo ja existente em modo de leitura
//  para que os registros de especie de todo o arquivo sejam exibidos
//  um atras do outro
    
void exibe_campos()
{
    char nomearq[31];           //nome do arquivo que sera lido
    dados DADO;                 //variavel de registro
    cabecalho CAB;              //variavel do cabecalho

    scanf("%s",nomearq);        //le o nome do arquivo que sera aberto
    
    FILE *arquivo;
    arquivo = fopen(nomearq, "rb");
    //abre o arquivo no modo de leitura em binario

    //le os campos de cada registro um de cada vez
    //para evitar problemas, entao quando chegar no
    //fim do arquivo termina o processo

    if(arquivo == NULL){
        printf(ERRO_PADRAO);     
    }
    else{
        //LEITURA DAS INFORMACOES DO CABECALHO
        CAB=le_cabecalho(arquivo);
        //ajusta o ponteiro para o comeco dos dados
        fseek(arquivo,1600,SEEK_SET);

        //loop de leitura dos dados e suas exibicoes
        while(1){
            DADO=le_registro(arquivo);
            if (DADO.removido=='2') //a variavel eh alterada para '2' se chegar no fim do arquivo
                break;
            if (DADO.removido=='0')
                exibe_registro(DADO);//exibe o registro apos salvar os campos, APENAS SE A FLAG REMOVIDO FOR '0'
        }
        fclose(arquivo); // fecha o arquivo
        printf("Numero de paginas de disco: %d\n",CAB.nroPagDisco);
        
    }
}



//  Essa funcao abre um arquivo ja existente em modo de leitura
//  para que os registros de especie do arquivo que passarem
//  uma condicao de pesquisa sejam exibidos

void busca_determinada(){
    int nroBuscas,regEncontrados;
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
    arquivo = fopen(nomearq, "rb"); //abre o arquivo em modo de leitura binaria

    if(arquivo==NULL){          //checa se o arquivo foi devidamente aberto
        printf(ERRO_PADRAO);
    }else{
        fclose(arquivo);        //fecha o arquivo depois de checar se ele existe
        scanf("%d",&nroBuscas);

        for(i=0;i<nroBuscas;i++){
            scanf("%s",nomecampo);
            scan_quote_string(valorcampo); 

            codigo_campo=checa_nome_campo(nomecampo);   //FUNCAO QUE TESTA A STRING NOMECAMPO E RETORNA UM INTEIRO DE ACORDO COM O NOME DE CAMPO

            if(codigo_campo==-1)
                printf(ERRO_COMANDO);
            
            //print do nro da busca que foi feita
            printf("Busca %d\n",i+1);
            regEncontrados=0;

            //abre o arquivo e le o cabecalho
            arquivo = fopen(nomearq, "rb");
            CAB=le_cabecalho(arquivo);

            
            //ajusta o ponteiro para o comeco dos dados
            fseek(arquivo,1600,SEEK_SET);

            //loop de leitura dos dados e suas exibicoes
            while(1){

                if(codigo_campo==-1)    //se o codigo digitado nao for valido nao le o arquivo
                    break;

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

                switch (codigo_campo)
                {
                case 1:
                    if (!strcmp(valorcampo,nome)){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;

                case 2:
                    if (!strcmp(valorcampo,especie)){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;

                case 3:
                    if (!strcmp(valorcampo,habitat)){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;

                case 4:
                    if (!strcmp(valorcampo,tipo)){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;

                case 5:
                    if (!strcmp(valorcampo,dieta)){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;

                case 6:
                    if (!strcmp(valorcampo,alimento)){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;

                case 7:
                    if (valorcampo[0]==DADO.unidadeMedida){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;

                case 8:
                    if (atoi(valorcampo)==DADO.velocidade){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;

                case 9:
                    if (fabs(atof(valorcampo)-DADO.tamanho)<0.001){
                        exibe_registro(DADO);
                        regEncontrados++;
                    }
                    break;
                
                default:
                    break;
                }
  
            }

            fclose(arquivo);
            
            if(regEncontrados==-1 && codigo_campo!=-1){
                printf(ERRO_REGISTRO);
                printf("\n");
            }
            printf("Numero de paginas de disco: %d\n\n",CAB.nroPagDisco);

        }

    }
}
//funcao simples que recebe uma variavel de registro de especie
//e exibe as informacoes contidas naquele registro

void exibe_registro(dados DADO){

    //ponteiros utilizados nas funcoes strdup e strsep, com elas eh possivel separar 
    //as palavras de acordo com o divisor '#' e contabilizar informacoes nao inseridas
    char* linha;
    char *nome;
    char *especie;
    char *habitat;
    char *tipo;
    char *dieta;
    char *alimento;

    linha=strdup(DADO.variavel);
    nome = strsep(&linha, "#");
    especie = strsep(&linha, "#");
    habitat = strsep(&linha, "#");
    tipo = strsep(&linha, "#");
    dieta = strsep(&linha, "#");
    alimento = strsep(&linha, "#");
    
    //print dos dados das criaturas, se nao constar nao eh exibido

    printf("Nome: %s\n",nome);

    if(strcmp(especie,""))
        printf("Especie: %s\n",especie);

    if(strcmp(tipo,""))
        printf("Tipo: %s\n",tipo);

    if(strcmp(dieta,""))
        printf("Dieta: %s\n",dieta);

    if(strcmp(habitat,""))
        printf("Lugar que habitava: %s\n",habitat);

    if(DADO.tamanho>0)
        printf("Tamanho: %.1f m\n",DADO.tamanho);

    if(DADO.velocidade>0)
        printf("Velocidade: %d %cm/h\n\n",DADO.velocidade,DADO.unidadeMedida);

}





