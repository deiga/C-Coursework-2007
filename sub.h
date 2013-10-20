#ifndef _SUB_H_
#define _SUB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 512 /* Hash_table:n maksimi alkioiden määrä, taulukon koolla ei ole väliä, koska kaikki sisään 
laitettavat alkiot ov ketjutettavissa */
#define MALLOC(type, n) (malloc((n)*sizeof(type)))

struct node * hash_table[HASH_SIZE]; /* Itse hajautus-taulukko, node taulukkona, joka viittaa alkioissaan oleviin nodeihin 
*/

struct node {
	char *Key; /*Henkilön nimi selkokielellä */
	unsigned long hashKey; /* Nimi kun se on "hashattu" */
	double palkka; /*Henkilön palkka */
	int vuosi; /*Henkilön aloitusvuosi */
	struct node *next; /* Viite seuraavaan node:n jos tarvitsee ketjuttaa */
};

void flush(FILE *fp); /* Funktio annetun syöttövirrantyhjentämiseen. */
unsigned long hash(char *str); /* Hashaus -funktio, muuttaa merkkijonon arvoksi */
struct node *searchNode(char *search); /* Funktio jolla etsitään tiettyä nodea */
void alloNode(void); /* Funktio alustaa hash_table:n kaikki alkiot */
void printAll(void); /* Funktio tulostaa kaiken rekisterissä olevan tiedon */

#endif
