#include "./funcoesCriadas.h"

//  Essa funcao abre um arquivo ja existente em modo de leitura
//  para que os registros de especie de todo o arquivo sejam exibidos
//  um atras do outro
    
/*
void exibe_campos()
{
    char nomearq[31];           //nome do arquivo que sera lido
    registro_especie REGISTRO;  //variavel de registro

    scanf("%s",nomearq);
    
    FILE *arquivo;
    arquivo = fopen(nomearq, "rb");
    //abre o arquivo no modo de leitura em binario

    //le os campos de cada registro um de cada vez
    //para evitar problemas, entao quando chegar no
    //fim do arquivo termina o processo

    if(arquivo == NULL){
        printf(ERRO_ARQUIVO);     
    }
    else{

        while(1){

            if(fread(&REGISTRO.SPECIES_ID, 4, 1, arquivo)==0)
                break;
            fread(REGISTRO.NAME, 41, 1, arquivo);
            fread(REGISTRO.SCIENTIFIC_NAME, 61, 1, arquivo);
            fread(&REGISTRO.POPULATION, 4, 1, arquivo);
            fread(REGISTRO.STATUS, 9, 1, arquivo);
            fread(&REGISTRO.LOCATION_LON, 4, 1, arquivo);
            fread(&REGISTRO.LOCATION_LAT, 4, 1, arquivo);
            if(fread(&REGISTRO.HUMAN_IMPACT, 4, 1, arquivo)==0)
                break;

            exibe_registro(REGISTRO);//exibe o registro apos salvar os campos
        }

        fclose(arquivo); // fecha o arquivo
    }
}

*/
//funcao simples que recebe uma variavel de registro de especie
//e exibe as informacoes contidas naquele registro
void exibe_registro(dados DADO){

    
    setlocale(LC_ALL, "");      //caracteres da lingua portuguesa
    
    printf("Nome: %s\n",DADO.variavel);
    printf("Especie: %s\n",DADO.variavel);
    printf("Tipo: %s\n",DADO.variavel);
    printf("Dieta: %s\n",DADO.variavel);
    printf("Lugar que habitava: %s\n",DADO.variavel);
    printf("Tamanho: %.1f m\n",DADO.tamanho);
    printf("Velocidade: %d %sm/h\n",DADO.velocidade,DADO.unidadeMedida);


}




