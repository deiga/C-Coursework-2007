#ifndef _SUB_H_
#define _SUB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 512 /* Hash_table:n maksimi alkioiden m��r�, taulukon koolla ei ole v�li�, koska kaikki sis��n 
laitettavat alkiot ov ketjutettavissa */
#define MALLOC(type, n) (malloc((n)*sizeof(type)))

struct node * hash_table[HASH_SIZE]; /* Itse hajautus-taulukko, node taulukkona, joka viittaa alkioissaan oleviin nodeihin 
*/

struct node {
	char *Key; /*Henkil�n nimi selkokielell� */
	unsigned long hashKey; /* Nimi kun se on "hashattu" */
	double palkka; /*Henkil�n palkka */
	int vuosi; /*Henkil�n aloitusvuosi */
	struct node *next; /* Viite seuraavaan node:n jos tarvitsee ketjuttaa */
};

void flush(FILE *fp); /* Funktio annetun sy�tt�virrantyhjent�miseen. */
unsigned long hash(char *str); /* Hashaus -funktio, muuttaa merkkijonon arvoksi */
struct node *searchNode(char *search); /* Funktio jolla etsit��n tietty� nodea */
void alloNode(void); /* Funktio alustaa hash_table:n kaikki alkiot */
void printAll(void); /* Funktio tulostaa kaiken rekisteriss� olevan tiedon */

#endif
