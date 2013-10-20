#include "sub.h"

/* Funktio flush tyhjentää puskurin kaikista syötteistä tai merkeistä.
* Ohjelmassa sitä käytetään ainostaan standardisyöttövirran tyhjentämiseen.
* @Param fp: Saa arvokseen joko tiedoston taikka syöttövirran.
*/
void flush(FILE *fp) {
	int ch = 0;
	while((ch = getc(fp)) != EOF && ch != '\n');
}

/* Funktio hash saa syötteenä merkkijonon, tässä tapauksessa aina
* henkilön nimen, jonka se sitten kääntää numeroarvoksi. Jakamalla arvo taulukon pituudella
* saadaan pieni numeroarvo, joka vastaa hajautustaulun alkiota. ns. tunniste
* @Param str: Stringi, tässä aina henklön nimi, josta tehdään numeroarvo.
* Palauttaa kyseisen numeroarvon.
* Funktio on omaksuttu sivulta http://www.cse.yorku.ca/~oz/hash.html,
* Kyseessä on Bernsteinin djb2-hashalgoritimi.
*/
unsigned long hash(char *str) {  

        unsigned long hash = 5381;
        int c;

        while (*str) { /* Käydään läpi niin kauan kun str sisältää tietoa */
		c = *str++;
        	hash = ((hash << 5) + hash) + c; /* Lerrotaan hash (hash * 33 + c) */
	}

        return hash;
}

/* Funktio etsii annetulla parametrillä kyseinen node alkion
* @Param search: Nimi jota etsitään.
* palauttaa noden josta nimi löytyi
*/

struct node *searchNode(char *search) {
	
	struct node *temp;
	unsigned long i = 0;
	
	i = hash(search) % HASH_SIZE;
	
	temp = hash_table[i];
	if(temp->hashKey == i)
		return temp;
	
	printf("Solua ei löytynyt.");
	return NULL;	
}

/* Funktio alustaa hash_tablen alkiot ja varaa näille muistia 
*/
void alloNode(void) {
	int i = 0;

	for (; i < HASH_SIZE; i++) {
		hash_table[i] = MALLOC(struct node, 1);
		hash_table[i]->hashKey = i;
		hash_table[i]->Key = NULL;
		hash_table[i]->next = NULL;
	}
	
}

/* Funktio tulostaa käyttäjälle kaikki alkiot missä on tietoa.
* Tulostaa nimen, palkan ja vuoden.
*/

void printAll(void) {

	struct node *aux;
	int i = 0;
	int check = 0;

	for (; i <= HASH_SIZE; i++) {
		aux = hash_table[i];
		while (aux != NULL) {
			if (aux->Key != NULL) {
				printf(" %s:\n  Palkka: %6.2fe/kk\n  Aloitusvuosi: %d\n", aux->Key, aux->palkka, aux->vuosi);
			/*	printf("%lu\n",aux->hashKey); testausta */
				check = 1;
			}
			aux = aux->next;		

		}

	}
	if (check == 0) {
		printf("Rekisterissä ei ole tietoa!\n");
	}

}
