#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tweet.h"
#include "index.h"

#define BUFFER 140
#define REGISTER_SIZE 100

void remove_new_line(char *line) {
    size_t ln = strlen(line) - 1;
    if (line[ln] == '\n')
        line[ln] = '\0';
}

void new_tweet (char *filename) {

	FILE *datafile;

	datafile = fopen(filename, "a+");

	char *strTexto = (char*) malloc (sizeof(char)*BUFFER);
	char *strUser = (char*) malloc (sizeof(char)*BUFFER);
	char *strCoordinates = (char*) malloc (sizeof(char)*BUFFER);
	char *strLanguage = (char*) malloc (sizeof(char)*BUFFER);
	char *delimitador = (char*) malloc (sizeof(char));
	strcpy(delimitador,"|");

	int favoriteCount;
	int retweetCount;
	int viewCount;
    int soma = 4; // ja conta o tamanho dos delimitadores
	printf ("insert text: ");
	fgets (strTexto, BUFFER, stdin);
	remove_new_line (strTexto);


	printf ("insert user: ");
	fgets (strUser, BUFFER, stdin);
	remove_new_line (strUser);


	printf ("insert coordinates: ");
	fgets (strCoordinates, BUFFER, stdin);
	remove_new_line (strCoordinates);

	printf ("insert language: ");
	fgets (strLanguage, BUFFER, stdin);
	remove_new_line (strLanguage);

	printf ("insert favorite count: ");
	scanf ("%d", &favoriteCount);

	printf ("insert retweet count: ");
	scanf ("%d", &retweetCount);

	printf ("insert view count: ");
	scanf ("%d", &viewCount);

    soma += strlen(strTexto)+strlen(strUser)+strlen(strCoordinates)+strlen(strLanguage)+3*sizeof(int);
    fwrite(&soma,sizeof(int),1,datafile);
    fwrite(strTexto,sizeof(char), strlen(strTexto), datafile);
    fwrite(delimitador,sizeof(char),strlen(delimitador),datafile);
    fwrite(strUser,sizeof(char), strlen(strUser), datafile);
    fwrite(delimitador,sizeof(char),strlen(delimitador),datafile);
    fwrite(strCoordinates,sizeof(char), strlen(strCoordinates), datafile);
    fwrite(delimitador,sizeof(char),strlen(delimitador),datafile);
    fwrite(strLanguage,sizeof(char), strlen(strLanguage), datafile);
    fwrite(delimitador,sizeof(char),strlen(delimitador),datafile);
    fwrite(&favoriteCount,sizeof(int), 1, datafile);
    fwrite(&retweetCount,sizeof(int), 1, datafile);
    fwrite(&viewCount,sizeof(int), 1, datafile);

	printf ("\nNEW TWEET POSTED!\n");

    fclose(datafile);
}

void list_tweets (char *filename) {
    FILE *file;
	//tweet *tweet = malloc (sizeof(tweet));
	char *token;
	int tamanho = 0,valor;
	size_t nread;

	file = fopen (filename, "r+");

	if (file) {
		while ((nread = fread(&tamanho, 1, sizeof(int), file)) > 0) {
            char* lido = malloc(sizeof(char)*tamanho);
            fread(lido,1,tamanho-12,file);
            token = strtok(lido, "|");

            printf ("text: %s\n", token);
            token = strtok(NULL, "|");
            printf ("user: %s\n", token);
            token = strtok(NULL, "|");
            printf ("coordinates: %s\n", token);
            token = strtok(NULL, "|");;
            printf ("language: %s\n", token);

            fread(&valor, 1, sizeof(int), file);
            printf ("favorite count: %d\n", valor);
            fread(&valor, 1, sizeof(int), file);
            printf ("retweet count: %d\n", valor);
            fread(&valor, 1, sizeof(int), file);
            printf ("views count: %d\n", valor);
            printf("\n");
		}
	}
	fclose(file);
}

void search_user (char *filename) {
}

//void search_favorite (char *filename) {
//    FavoriteIndex *ind = malloc(sizeof(FavoriteIndex)* REGISTER_SIZE);
//    InvertedList *lista = malloc(sizeof(InvertedList) * REGISTER_SIZE);
//    int tamanhoListaInvertida = 0;
//    create_index_favorite(filename,ind,lista);
//}

void search_language (char *filename) {
}

/*
 * Permita a recuperação dos dados de um ou mais registros com base nos valores dos
campos FAVORITE_COUNT E LANGUAGE simultaneamente
 */
void fav_and_language (char *filename) {
	int fav_count;
	char *language = NULL;

	printf ("insert favorite count: ");
	scanf ("%d", &fav_count);
	printf ("insert language count: ");
	fgets (language, 25, stdin);
	remove_new_line(language);

	index_matching(fav_count, language);
}

/*
 * Permita a recuperação dos dados de um ou mais registros com base nos valores dos
campos FAVORITE_COUNT OU LANGUAGE simultaneamente
 */
void fav_or_language (char *filename) {
	int fav_count;
	char *language = NULL;

	printf ("insert favorite count: ");
	scanf ("%d", &fav_count);
	printf ("insert language count: ");
	fgets (language, 25, stdin);
	remove_new_line(language);

	index_merging(fav_count, language);
}

void delete_favorite (char *filename) {
}

void delete_rrn (char *filename) {
}
