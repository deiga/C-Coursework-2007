#include "sub.h"

/* Funktio flush tyhjent�� puskurin kaikista sy�tteist� tai merkeist�.
* Ohjelmassa sit� k�ytet��n ainostaan standardisy�tt�virran tyhjent�miseen.
* @Param fp: Saa arvokseen joko tiedoston taikka sy�tt�virran.
*/
void flush(FILE *fp) {
	int ch = 0;
	while((ch = getc(fp)) != EOF && ch != '\n');
}

/* Funktio hash saa sy�tteen� merkkijonon, t�ss� tapauksessa aina
* henkil�n nimen, jonka se sitten k��nt�� numeroarvoksi. Jakamalla arvo taulukon pituudella
* saadaan pieni numeroarvo, joka vastaa hajautustaulun alkiota. ns. tunniste
* @Param str: Stringi, t�ss� aina henkl�n nimi, josta tehd��n numeroarvo.
* Palauttaa kyseisen numeroarvon.
* Funktio on omaksuttu sivulta http://www.cse.yorku.ca/~oz/hash.html,
* Kyseess� on Bernsteinin djb2-hashalgoritimi.
*/
unsigned long hash(char *str) {  

        unsigned long hash = 5381;
        int c;

        while (*str) { /* K�yd��n l�pi niin kauan kun str sis�lt�� tietoa */
		c = *str++;
        	hash = ((hash << 5) + hash) + c; /* Lerrotaan hash (hash * 33 + c) */
	}

        return hash;
}

/* Funktio etsii annetulla parametrill� kyseinen node alkion
* @Param search: Nimi jota etsit��n.
* palauttaa noden josta nimi l�ytyi
*/

struct node *searchNode(char *search) {
	
	struct node *temp;
	unsigned long i = 0;
	
	i = hash(search) % HASH_SIZE;
	
	temp = hash_table[i];
	if(temp->hashKey == i)
		return temp;
	
	printf("Solua ei l�ytynyt.");
	return NULL;	
}

/* Funktio alustaa hash_tablen alkiot ja varaa n�ille muistia 
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

/* Funktio tulostaa k�ytt�j�lle kaikki alkiot miss� on tietoa.
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
		printf("Rekisteriss� ei ole tietoa!\n");
	}

}
