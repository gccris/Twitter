#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tweet.h"
#include "index.h"

#define BUFFER 140

//retorna os rrns dos registros em interseccao nos index
int* index_matching (int fav_count, char *language) {
	return NULL;
}

//retorna os rrns dos registros em combinacao nos index
int* index_merging (int fav_count, char *language) {
	return NULL;
}

//atualiza o index depois de uma insercao/remocao
//	obs: no caso da remocao poderiamos deixar no index e caso
// 	haja pesquisa ele retorna que foi removido
void update_index () {

}

int search_index_language(LanguageIndex *ind,int tamanho,char *valor){
    int i;
    for(i = 0;i<tamanho;i++){
        if(strcmp(ind[i].language,valor)==0)
            return i;
    }
    return -1;
}

int search_index_favorite(FavoriteIndex *ind,int tamanho,int valor){
    int i;
    for(i = 0;i<tamanho;i++){
        if(ind[i].favorite == valor)
            return i;
    }
    return -1;
}

void create_language_index(char *filename,LanguageIndex *ind,InvertedList *listaInvertida){
    FILE *file;
	//tweet *tweet = malloc (sizeof(tweet));
	char *token;
	int tamanho = 0,valor,posicaoIndice = 0,posicaoLista = 0,soma = 0;
	size_t nread;

	file = fopen (filename, "r+");

	if (file) {
		while ((nread = fread(&tamanho, 1, sizeof(int), file)) > 0) {
            soma+= tamanho;
            char* lido = malloc(sizeof(char)*tamanho);
            fread(lido,1,tamanho-12,file);
            token = strtok(lido, "|");
            token = strtok(NULL, "|");
            token = strtok(NULL, "|");
            token = strtok(NULL, "|");

            listaInvertida[posicaoLista].byteOffSet = soma;
            int posicao = search_index_favorite(ind,posicaoIndice,valor);
            if(posicao == -1){
                ind[posicaoIndice].language = malloc(sizeof(char)*BUFFER);
                strcpy(ind[posicaoIndice].language,token);
                ind[posicaoIndice].RRN = posicaoLista;
                listaInvertida[posicaoLista].proximo = -1;
                posicaoIndice++;
            }
            else{
                listaInvertida[posicaoLista].proximo = ind[posicaoIndice].RRN;
                ind[posicaoIndice].RRN = posicaoIndice;
            }
            posicaoLista++;
            fread(&valor, 1, sizeof(int), file);
            fread(&valor, 1, sizeof(int), file);
            fread(&valor, 1, sizeof(int), file);
            printf("\n");
		}
	}
	fclose(file);
}


//index fortemente ligado com a chave Fav_count
void create_favorite_index(char *filename,FavoriteIndex *ind,InvertedList *listaInvertida){
    FILE *file;
	//tweet *tweet = malloc (sizeof(tweet));
	char *token;
	int tamanho = 0,valor,posicaoIndice = 0,posicaoLista = 0,soma = 0;
	size_t nread;

	file = fopen (filename, "r+");

	if (file) {
		while ((nread = fread(&tamanho, 1, sizeof(int), file)) > 0) {
            soma+= tamanho;
            char* lido = malloc(sizeof(char)*tamanho);
            fread(lido,1,tamanho-12,file);
            token = strtok(lido, "|");
            token = strtok(NULL, "|");
            token = strtok(NULL, "|");
            token = strtok(NULL, "|");;

            fread(&valor, 1, sizeof(int), file);

            listaInvertida[posicaoLista].byteOffSet = soma;
            int posicao = search_index_favorite(ind,posicaoIndice,valor);
            if(posicao == -1){
                ind[posicaoIndice].favorite = valor;
                ind[posicaoIndice].RRN = posicaoLista;
                listaInvertida[posicaoLista].proximo = -1;
                posicaoIndice++;
            }
            else{
                listaInvertida[posicaoLista].proximo = ind[posicaoIndice].RRN;
                ind[posicaoIndice].RRN = posicaoIndice;
            }
            posicaoLista++;
            fread(&valor, 1, sizeof(int), file);
            fread(&valor, 1, sizeof(int), file);
            printf("\n");
		}
	}
	fclose(file);
}
