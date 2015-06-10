/* TRABALHO 1 - ORG ARQ
 *
 * Alunos:
 * 	Rafael Neto
 * 	Gabriel Cristiano
 * 	Marcelo Foresto
 * 	Leonardo Ventura
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tweet.h"

#define CMD_NT  "nt"	//new tweet
#define CMD_LT	"lt"	//list tweets
#define CMD_SU 	"su"	//search by user
#define CMD_SF 	"sf"	//search by favorite count
#define CMD_SL 	"sl"	//search by language
#define CMD_DF	"df"	//delete by favorite count

#define CMD_DR	"dr"	//delete by rrn
#define CMD_QT 	"qt"	//quit
#define CMD_LENGTH 25

void interface () {
	printf ("\n----------------------------------\n"
			"* New Tweet - press 'nt'\n"
			"* List all Tweets - press 'lt'\n"
			"* Search via User - press 'su'\n"
			"* Search via Favorite Count - press 'sf'\n"
			"* Search via Language - press 'sl'\n"
			"* Delete tweet by Favourite Count - press 'df\n"
			"* Delete tweet by RRN - press 'dr'\n"
			"* Search via RRN - press 'sr'\n"
			"* QUIT - press 'qt'\n\n:");
}


int main (void) {
	char cmd[CMD_LENGTH] = "";
		char filename[20] = "register.dat";

	interface();

	while (strcmp(cmd, CMD_QT)) {
		fgets (cmd, CMD_LENGTH, stdin);
		remove_new_line(cmd);
		if (strcmp(CMD_NT, cmd) == 0)
			new_tweet(filename);
		else if (strcmp(CMD_LT, cmd) == 0)
			list_tweets(filename);
		else if (strcmp(CMD_DF, cmd) == 0)
			printf ("cmd: %s", cmd);
		else if (strcmp(CMD_DR, cmd) == 0)
			printf ("cmd: %s", cmd);
		else if (strcmp(CMD_SF, cmd) == 0)
			printf ("cmd: %s", cmd);
		else if (strcmp(CMD_SL, cmd) == 0)
			printf ("cmd: %s", cmd);
		else if (strcmp(CMD_SU, cmd) == 0)
			printf ("cmd: %s", cmd);
		else if (strcmp(CMD_QT, cmd) == 0)
			return 0;
		else
			printf("invalid command: %s%s", cmd, fgets(cmd, sizeof cmd, stdin));

		interface();
	}


	return 0;
}
