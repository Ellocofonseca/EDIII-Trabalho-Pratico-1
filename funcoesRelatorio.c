#include "./funcoesCriadas.h"
#include "./funcoes_fornecidas.h"

//  Essa funcao abre um arquivo ja existente em modo de leitura
//  para que os registros de especie de todo o arquivo sejam exibidos
//  um atras do outro
    

void exibe_campos()
{
    char nomearq[31];           //nome do arquivo que sera lido
    dados DADO;                 //variavel de registro
    cabecalho CAB;

    scanf("%s",nomearq);
    
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
        fread(&CAB.status,1,1,arquivo);
        fread(&CAB.topo,4,1,arquivo);
        fread(&CAB.proxRRN,4,1,arquivo);
        fread(&CAB.nroRegRem,4,1,arquivo);
        fread(&CAB.nroPagDisco,4,1,arquivo);
        
        fseek(arquivo,1600,SEEK_SET);

        while(1){
            if(fread(&DADO.removido,1,1,arquivo)==0)
                break;
            fread(&DADO.encadeamento,4,1,arquivo);
            fread(&DADO.populacao,4,1,arquivo);
            fread(&DADO.tamanho,4,1,arquivo);
            fread(&DADO.unidadeMedida,1,1,arquivo);
            fread(&DADO.velocidade,4,1,arquivo);
            if(fread(DADO.variavel,142,1,arquivo)==0)
                break;
            
            if (DADO.removido=='0')
                exibe_registro(DADO);//exibe o registro apos salvar os campos, APENAS SE A FLAG FOR REMOVIDO FOR '0'
        }
        fclose(arquivo); // fecha o arquivo

        printf("Numero de paginas de disco: %d\n",CAB.nroPagDisco);
        
    }
}

//funcao simples que recebe uma variavel de registro de especie
//e exibe as informacoes contidas naquele registro
void exibe_registro(dados DADO){

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
    
    //setlocale(LC_ALL, "");      //caracteres da lingua portuguesa
    
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




