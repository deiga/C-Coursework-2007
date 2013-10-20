/* Tiedosto sis�lt�� p��ohjelman, funktiot joilla k�sitell��n hash-taulun sis�lt��, 
*ohjelman lopettamista sek� tiedoston k�sittely�. Tiedosto k�ytt�� sub.c:n funktioita.
*/

#include "sub.h"

static FILE *tied = NULL; /* Globaalinen tiedostokahva, k�yt�ss� vain main.c:ss�. */
static int tallenna = 0; /* Globaalinen muuttuja mill� tarkistetaan onko muutettua tietoa 
tallennettu. */
int memsz = 32; /* Merkkijonojen lukemiseen ns. standardi muistim��r� */

int addEmployee(void); /* Lis�� ty�ntekij�n rekisteriin */
int rmEmployee(void); /* Poistaa ty�ntekij�n rekisterist� */
int editEmployee(void); /* Muuttaa ty�ntekij�n tietoja */
char * getInput(void); /* Lukee standardisy�tt�virrasta tekstisy�tteen ja suurentaa muistia tarvittaessa */
void cleanExit(void); /* Sulkee tiedostot, vapauttaa musitit ja tallentaa tarvittaessa muutokset */
void rmAll(void); /* Vapauttaa hash-taulun muistin */
void deleteNode(struct node *deleted); /* Vapauttaa hash-taulun muistin */
void showMenu(void); /* N�ytt�� valikon*/
void saveTo(void); /* Tallentaa rekisterin bin��ri-tiedostoon */
void readFrom(void); /* Lukee bin��ritiedostosta rekisterin */


int main(int argc, char **argv) {

	char c = 'h'; /* Menuvalikon esille tuominen ensimm�isell� kutsulla */
	char *str;
	int amEr = 0; /* tarkistus muuttuja */
	struct node *base;
	unsigned long i;
	int comparedLength = 0;
	int searchedLength = 0;

        if(argc == 2) {
		if (strlen(argv[1]) == strlen("help")) {
			if(strlen(argv[1]) == strlen("help")) {
                              printf("\nTy�ntekij�rekisteri toimii k�ytt�j�n antamin sy�ttein.\n\
Jos kysyt��n nime�, niin anna nimi muodossa Etunimi ja Sukunimi, toisen nimen voi halutessa antaa.\n\
Summia ja vuosilukuja kysytt�ess tarvitsee vain antaa luvut ilman yksik�it�.\n\n");
	}}}

	alloNode(); /* Allokoi hash-taululle muistin ja asettaa hashKey:lle arvot. */

	printf("	+----------------------------+\n\
	+                            +\n\
	+                            +\n\
	+     Ty�ntekij�rekisteri    +\n\
	+    	 by Timo Sand        +\n\
	+                            +\n\
	+                            +\n\
	+       Paina ENTER	     +\n\
	+----------------------------+\n");

	def:
	switch(c) { /* switch lauseke k�sittelee ohjelman menu-rakennetta */
		case 'a' : 
			c = 'h';
			if (addEmployee() == 1) { /* Tarkistaa funktion palautusarvon virheitten varalle */
				printf("Lis�ys ei onnistunut.\n");
			}
			break;
		case 'r' : 
			c = 'h';
			if (rmEmployee() == 1) { /* Tarkistaa funktion palautusarvon virheitten varalle */
				printf("Poisto-operaatio ei onnistunut.\n");
			}
			else printf("Tiedot poistettu! (Paina ENTER)\n");
			break;
		case 's' : /* Etsii rekisterist� nimetyn henkil�n. */
			c = 'h';			
			flush(stdin);
			printf("Sy�t� nimi, kenet haluat l�yt�� rekisterist�: ");
			str = getInput();
			i = hash(str) % HASH_SIZE;
			
			base = hash_table[i];
			if (base != NULL);
				/*printf("Key: %s\n", base->Key); Testituloste */
			else { printf("Rekisteri� ei ole.");
				break;
			}

			while (base != NULL && base->Key != NULL) { /* K�y hash-taulun alkiot l�pi kohdassa i ja tulostaa 
henkil�n tiedot kun on l�ytynyt oikea. */
				comparedLength = strlen(base->Key);
				searchedLength = strlen(str);
				if (comparedLength != searchedLength) { break; } 
				if (strcmp(base->Key, str) == 0) {
					printf(" %s:\n  Palkka: %6.2f\n  Aloitusvuosi: %d", str, base->palkka, base->vuosi);
					goto def;
				}
       			 }

			printf("Etsim��si henkil�� ei l�ytynyt.\n");
			break;
		case 'e' :
			c = 'h';
			if (editEmployee() == 1) { /* Tarkistaa funktion palautusarvon virheitten varalle */
				printf("Tietoja ei voinut muuttaa.\n");
			}
			break;
		case 't' :
			c = 'h';
			saveTo();
			break;
		case 'f' :
			c = 'h';
			readFrom();
			break;
		case 'h' :
			flush(stdin);
			showMenu();
			amEr = 0;
			c = 0;
			while (amEr == 0) {
				printf("Sy�t� kirjain, mink� vaihtoehdon haluat: ");
				amEr = 1;
				c = fgetc(stdin);
			}
			break;
		case 'x' :
			c = 'h';
			cleanExit();
			break;
		case 'p' :
			c = 'h';
			printAll();
			break;
		default :
			c = 'h'; 
			break;
	}
	goto def;
	
	return 0;
}	

/* Funktio lis�� ty�ntekij�n ja t�m�n tiedot hash-listaan. T�m�n paikka l�ytyy kun "hashataan" ty�ntekij�n nimi.
* Funktiolla ei ole parametrej�, se kysyy kaiken tarvittavan tiedon k�ytt�j�lt�.
* Funktio palautta 0 jos suoritus oli onnistunut, 1 jos tapahtui virheu.
* Funktio antaa arvot node:n kentille Key, palkka ja vuosi.
*/

int addEmployee() {

	char *nimi;
	struct node *employee, *temp;
	double pay;
	int year;
	unsigned long i;
	int check = 0;

/* Kysyt��n nime� ja haetaan hash-taulusta oikea kohta */
	flush(stdin); /*Tyhjennet��n stdin muita merkeist� */
	
	printf("Sy�t� nimi (ei numeerinen), kenet haluat lis�t�: ");
	nimi = getInput();
	employee = searchNode(nimi);
	i = hash(nimi) % HASH_SIZE;
	temp = hash_table[i];
	
/* Varmistetaan, ett� etsitty nimi ei ole viel� tallennettu */
	while (temp != NULL) {
/*		printf(" Hash: %ld Key: %s Nimi: %s\n", i, temp->Key, nimi);		Testituloste */
		if(temp->Key != NULL) {  /* Virheentarkistusta*/
			if (strcmp(temp->Key,nimi) == 0) {
				printf("Nimi on jo rekisteriss�. Tallennus keskeytet��n. ");
				return 1;
			}
		}
		temp = temp->next;	
	}
/* Kysyt��n palkan ja vuoden arvoja, kunnes vuodella tulee oikeanlainen arvo */
	do {
		printf("Sy�t� %s:n palkka ja aloitusvuosi: ", nimi);
		scanf(" %lf %d", &pay, &year);
		check = 0;
		if (year < 1900 || year > 2050) {
			printf("Sy�tit v��r�n vuosiluvun. Sy�t� vuosi v�lilt� 1900 ja 2050.\n");
			flush(stdin);
			year = 0;
			check = 1;
		}
	} while (check == 1);

	if ((employee->Key = MALLOC(char, memsz)) == NULL) {
		printf("Muistia ei voinut varata.\n");
		return 1;
	}

	/* t�ss� asetetaan uuden ty�ntekij�n tiedot listaan */
	strcpy(employee->Key, nimi);
	employee->palkka = pay;
	employee->vuosi = year;
	employee->hashKey = i;
	employee->next = NULL;

	for (temp = hash_table[i]; temp->next != NULL; temp = temp->next); /* k�y��n listaa l�pi, kunnes l�ytyy viimeinen 
alkio*/
	/* Jos taulukon alkiossa ei viel� viitett� mihink��n node:n asetetaan t�m� ensimm�iseksi. */
	if (temp == NULL) {
		hash_table[i] = employee;
		hash_table[i]->next = NULL;
	} 
	else { 
		for (; temp->next != NULL; temp = temp->next);
		temp->next = employee;
		temp->next->next = NULL;
	}
	
	printf("Palkka: %6.2fe/kk, Vuosi: %d\n", employee->palkka, employee->vuosi); /* Osoitetaan k�ytt�j�lle, ett� 
ohjelma on ottanut sy�tteet vastaan oikein */
	tallenna = 1;
	memsz = 32;
	nimi = NULL;
	return 0;
	
}

/* Funktio on lukuv�line, se lukee standardisy�tt�virrasta teksti� kunnes tulee '\n' tai '\r' -merkki.
* Funktio my�s muuttaa mjonon pituutta, jos sy�te on pidempi kuin oletus.
* Ei parametrej�, kun ei ollut mit��n tarvetta.
* Funktio palauttaa lueton merkkijonon.
*/

char * getInput(void) {

	char *mjono;
	int i, index;
	int check = 0;
	
	if ((mjono = MALLOC(char, memsz)) == NULL) {
		printf("Muistia ei voinut varata!\n");
		return NULL;
	}
/*	flush(stdin); Todettu turhaksi, voi k�ytt�� hidastaakseen ohjelman suoritusta*/
	index = 0;

	while ((i = fgetc(stdin)) != '\n') { /* kopio merkin kerrallaan mjono muuttujaan, jos kasvaa yli memsz, niin 
tuplataan ja sit kopioidaan lis�� */
		if (i != '\r') {
			mjono[index] = (char)i;
			index++;
			if (index == memsz) {
				memsz = memsz << 1;
				mjono = realloc(mjono, memsz);
			}
		}
       	}
	mjono[index] = '\0';
	check = 0;
	return mjono;
}

/* Funktio antaa k�ytt�j�n poistaa ty�ntekj�n rekisterist�.
* Ei parametrej�, kaikki tarvittava kysyt��n k�ytt�j�lt�.
* Palautusarvo kertoo oliko funktion suorituksessa mit��n ongelmia.
*/

int rmEmployee(void) {

	char *nimi;
	struct node *temp, *aux;
	unsigned long i;
	int comparedLength = 0;
	int searchedLength = 0;

	flush(stdin);
	printf("Sy�t� nimi, kenet haluat poistaa rekisterist�: ");
	nimi = getInput();

	i = hash(nimi) % HASH_SIZE;
/*	printf("Hash: %ld\n", i);Testituloste */
	
	temp = hash_table[i];
	if (temp == NULL) { /* Tarksitetaan, ett� kohdassa i on alkioita */
		printf("Nime� ei ole rekisteriss�.");
		return 1;
	}
	
	if (hash_table[i] != NULL && hash_table[i]->next == NULL) { /* Tarkastetaan onko poistettava ensimm�inen ja ainut alkio*/
		hash_table[i]->hashKey = i;
		hash_table[i]->Key = NULL;
		hash_table[i]->next = NULL;
		tallenna = 1;
		return 0;
	}
	
	while (temp != NULL && temp->Key != NULL) {
		comparedLength = strlen(temp->Key);
		searchedLength = strlen(nimi);
		if (comparedLength != searchedLength) { /* Jos kummatkin ovar eripituisi, ei ne voi olla samoja. */
			break; 
		}
		if (strcmp(temp->Key, nimi) == 0) { /* Tarkistetaan onko kysess� samat arvot.*/
            aux = temp;
            if(temp->next != NULL) {
            	temp = temp->next;
            }
            else {
                temp = NULL;
            }
            tallenna = 1;
            free(aux);
            aux = NULL;
            return 0;
		}
	}
		
	printf("Etsim��nne henkil�� ei l�ytynyt.\n");
	memsz = 32;
	return 1;		

}

/* Funktio antaa mahdollisuuden muuttaa ty�ntekij�n palkkaa/aloitusvuotta tai kumpaakin.
* Parametrej� ei k�yet�t, ainoi tarvittava tieto on etsitty nimi ja se kysyt��n k�ytt�j�lt�.
* Palauta 0 jos kaikki meni hyvin, 1 jos jokin virhe sattui
*/

int editEmployee() {
	
	char *nimi;
	struct node *temp;
	double pay;
	int year, choice, comparedLength, searchedLength;
	int check = 0;
	unsigned long i;


	flush(stdin);
	printf("Sy�t� nimi, kenen tietoja haluat muuttaa: ");
	nimi = getInput();
	memsz = 32;
	i = hash(nimi) % HASH_SIZE;
	temp = hash_table[i];

	 while(temp != NULL){ /* K�yd��n kohta i l�pi, jotta etsitty l�ytyy */
		if(temp->Key != NULL)
            		 comparedLength = strlen(temp->Key);
		else{ if (temp->next != NULL)
	        	     temp = temp->next;
			else { printf("Ei merkintoj� rekisteriss�.\n");
				return 1;
			}
		}
                searchedLength = strlen(nimi);
                if(comparedLength != searchedLength)
                        temp = temp->next;
		else if (temp->Key != NULL) {
                	if(strcmp(temp->Key, nimi) != 0)
                        	temp = temp->next;
                	else
                        	break;
		}
        }
			
	while (1) {
		printf("Haluatko muuttaa henkil�n palkkaa(1), aloitusvuotta(2) vai kumpaakin(3)?\n");
		/*flush(stdin);*/
		choice = fgetc(stdin);
		tallenna = 1;
		switch(choice) {
			case '1':
				printf("Palkka: %6.2fe/kk\n", temp->palkka);
				printf("Sy�t� uusi palkka: \n");
				scanf("%lf", &pay);
				temp->palkka = pay;
				break;
				/*Muuttaa structin palkkaa*/
			case '2':
				printf("Aloitusvuosi: %d\n", temp->vuosi);
				do {
					printf("Sy�t� uusi Aloitusvuosi: \n");
					scanf("%d", &year);
					if (year < 1900 || year > 2050)
						check = 1;
				} while(check == 1);
				temp->vuosi = year;
				break;
				/*Muuttaa structin vuotta*/
			case '3':
				printf("Palkka ja Alotusvosi: %6.2f, %d \n", temp->palkka, temp->vuosi);
				do {
					printf("Sy�t� uusi palkka ja aloitusvuosi: \n");
					scanf("%lf %d", &pay, &year);
					if (year < 1900 || year > 2050)
						check = 1;
				} while (check == 1);
				temp->palkka = pay;
				temp->vuosi = year;
				break;
				/* Muuttaa palkkaa ja vuotta */
			default: continue;
		}
		return 0;
	}
}

/* Funktio tallentaa Nimen,hashavaimen,palkan ja vuoden tekstitiedostoon
* Tallenetaan k�ytt�j�n antamaan tiedostoon tai perusasteuksena annettuun nimeen. 
*/
void saveTo() {

	int i = 0;
	struct node *aux;
	char *fname;
	int tallennettu = 0;
	
	do { /* Kysyt��n k�ytt�j�lt� vastausta kunnes tulee oikean lainen sy�te */
		printf("Haluatko tallentaa muuhun kuin standarditiedostoon(rekisteri.txt)? 1: Kyll� 2: Ei ");
		flush(stdin);
		i = fgetc(stdin);
	/*	printf("%d\n", i); Testituloste */
	}  while ( i < '1' && i > '2');
	if (i == '1') {
		printf("Sy�t� tiedoston nimi: ");
		flush(stdin);
		fname = getInput();
	}
	else fname = "rekisteri.txt";	
	
	if (tied == NULL) {
		if ((tied = fopen(fname, "w")) == NULL) {
			printf("Tiedostoa ei voinut avata.");
			return;
		}
	}
	
	/*K�y l�pi Rekisterin ja tallentaa jokaisen taulukon alkion */
	for (i = 0; i < HASH_SIZE; i++) {
		aux = hash_table[i];
		/*printf("%d ",i); testausta */
		if (aux != NULL) {
			/*printf("OK! "); testausta */
			if (aux->Key != NULL) {
				fprintf(tied,"%s,%ld,%6.2f,%d,",aux->Key,aux->hashKey,aux->palkka,aux->vuosi);
				tallennettu++;
				for (; aux->next != NULL; aux = aux->next) {
					if (aux->Key != NULL) { 
						fprintf(tied,"%s,%ld,%6.2f,%d,",aux->Key,aux->hashKey,aux->palkka,aux->vuosi);
						tallennettu++;
					}
				}
			}
		}
	}	
	printf("Tallennettu %d kpl. (Paina ENTER)\n",tallennettu);
	fclose(tied);
	tied = NULL;
	tallenna = 0;
}

/* Funktio lukee tekstitiedostosta tallennetut arvot ja tallettaa rakenteeseen.
*Samalla kaikki vanha tieto tulee ylikirjoitettua.
*K�ytt�j�lt� kysyt��n mik� tiedosto luetaan.
*Toiminnaltaan tismalleen sama kuin tallentava funktio, vain vastakkaiseen suuntaan
*/
void readFrom() {
	
	int kirjain = 0;
	struct node *aux, *temp;
	char *fname, *mjono;
	int check = 0;
	int luettu = 0;
	int sisLuet = 0;
	int i = 0;
	int index = 0;
	unsigned long placeh, n;
	
	do {
		printf("Haluatko lukea muusta kuin standarditiedostosta(rekisteri.txt)? 1: Kyll� 2: Ei ");
		flush(stdin);
		kirjain = fgetc(stdin);
	/*	printf("%d\n", kirjain); Testituloste */
	}  while ( kirjain < '1' && kirjain > '2');
	if (kirjain == '1') {
		printf("Sy�t� tiedoston nimi: ");
		flush(stdin);
		fname = getInput();
	}
	else fname = "rekisteri.txt";	
	
	if (tied == NULL) {
		if ((tied = fopen(fname, "r")) == NULL) {
			printf("Tiedostoa ei voinut avata.\n");
			return;
		}
	}
	
	while (!feof(tied)) {
	
		if ((mjono = MALLOC(char, memsz)) == NULL) {
			printf("Muistia ei voinut varata!\n");
			return;
		}
		
		temp = MALLOC(struct node, 1);
		temp->Key = NULL;
		temp->next = NULL;
	
		index = 0;

		while ((i = fgetc(tied))) {
			if (i == EOF) break;
			/*printf("%d\n",i); */
			if ((i == ',')) break;
			mjono[index] = (char)i;
			index++;
			if (index == memsz) {
				memsz = memsz << 1;
				mjono = realloc(mjono, memsz);
			}
		}
		mjono[index] = '\0';
		temp->Key= mjono;
		printf("Tulostaa :%s %s\n", mjono, temp->Key); /*Testi� */
			
		fscanf(tied,"%lu,%lf,%d,",&placeh,&temp->palkka,&temp->vuosi);
		check = 1;
		n = hash(mjono) % HASH_SIZE;
		temp->hashKey = n;
		aux = hash_table[n];
		if (aux == NULL) {
			hash_table[n] = temp;
			/*strcpy(hash_table[n]->Key, temp->Key);*/
			hash_table[n]->next = NULL;
		}
		else {
			for (; aux->next != NULL; aux = aux->next);
			aux->next = temp;
/*			strcpy(aux->next->Key,temp->Key);*/
			aux->next->next = NULL;
			sisLuet++;
		}
		if ((i = fgetc(tied)) == '\n') break;
		ungetc(i,tied);
	}
	if (check == 1) {
		printf("Luettu: %d kpl ja %d kpl.\n",luettu, sisLuet);
	}
	else printf("Lukeminen ep�onnistui. (Paina ENTER)\n");
	
	fclose(tied);
	tied = NULL;
}
/* Funktio sulkee ohjelman mahdollisimman "n�tisti". Se koittaa vapauttaa kaiken k�tetyn muistin.
* Tarksitaa josko ohjelma on muuttanut tai lis�nnyt asioita tallentamisen j�lkeen.
* tallenna -muuttuja toimii t�ss� lippuna. Jos arvona on 1 niin kysyt��n tallentamista
*/
void cleanExit() {

	char yOrN;
	
	if (tallenna == 1) {
		printf("Haluatko tallentaa avoinna olevan rekiterin tiedostoon? (y/n) ");
		flush(stdin);
		yOrN = fgetc(stdin);
		if (yOrN == 'n') {
			printf("Suljetaan, tallentamatta!\n");
			rmAll(); /* Tyhjnet�� koko taulukon*/
			tallenna = 0;
			exit(EXIT_SUCCESS);
		}
		if (yOrN == 'y') {
			saveTo();
			printf("Tallennetaan!\n");
			rmAll(); /* Tyhjnet�� koko taulukon*/
			tallenna = 0;
			exit(EXIT_SUCCESS);
		}

	}
	else { 
		rmAll(); /* Tyhjnet�� koko taulukon*/
		tallenna = 0;
		
		exit(EXIT_SUCCESS);
	 }		
}

/*Funktio vapauttaa parametrin� annetun node:n muistin.
* @Param deleted: Node mist� teenp�in halutaankaikki linkitetyt nodet vapauttaa. 
*/
void deleteNode(struct node *deleted){
             if(deleted->next != NULL) /*Jos seuraavassa alkiossa dataa vapauta se kanssa */
                      deleteNode(deleted->next);
             else
                     free(deleted);
}

/* Funktio k�ynnist�� prosessin joka tyhjent�� koko hash_table -taulukon alkioista ja vapauttaa sen muistin.
*/
void rmAll(){
 	int i;
 	for(i = 0; i < HASH_SIZE; i++){
     		deleteNode(hash_table[i]);
     		hash_table[i] = NULL;
 	}
}

/* Funktio n�ytt�� k�ytt�j�lle menun.
*/
void showMenu(void) {	
	printf("	 _____________________________________________\n\
	|					      |\n\
	|   a: Lis�� ty�ntekij�                       |\n\
	|   r: Poista ty�ntekij�                      |\n\
	|   e: Muuta ty�ntekij�ntietoja  	      |\n\
	|   t: Tallenna rekisteri tiedostoon  	      |\n");
	printf("	|   f: Lue rekisteri tiedostosta  	      |\n\
	|   p: Tulostaa muistissa olevan rekisterin   |\n\
	|   s: Etsi henkil� rekisterist�	      |\n\
	|   h: Menu  				      |\n\
	|   x: Poistu ohjelmasta  		      |\n\
	|_____________________________________________|\n\n");
	
}
