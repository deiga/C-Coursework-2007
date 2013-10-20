/* Tiedosto sisältää pääohjelman, funktiot joilla käsitellään hash-taulun sisältöä, 
*ohjelman lopettamista sekä tiedoston käsittelyä. Tiedosto käyttää sub.c:n funktioita.
*/

#include "sub.h"

static FILE *tied = NULL; /* Globaalinen tiedostokahva, käytössä vain main.c:ssä. */
static int tallenna = 0; /* Globaalinen muuttuja millä tarkistetaan onko muutettua tietoa 
tallennettu. */
int memsz = 32; /* Merkkijonojen lukemiseen ns. standardi muistimäärä */

int addEmployee(void); /* Lisää työntekijän rekisteriin */
int rmEmployee(void); /* Poistaa työntekijän rekisteristä */
int editEmployee(void); /* Muuttaa työntekijän tietoja */
char * getInput(void); /* Lukee standardisyöttövirrasta tekstisyötteen ja suurentaa muistia tarvittaessa */
void cleanExit(void); /* Sulkee tiedostot, vapauttaa musitit ja tallentaa tarvittaessa muutokset */
void rmAll(void); /* Vapauttaa hash-taulun muistin */
void deleteNode(struct node *deleted); /* Vapauttaa hash-taulun muistin */
void showMenu(void); /* Näyttää valikon*/
void saveTo(void); /* Tallentaa rekisterin binääri-tiedostoon */
void readFrom(void); /* Lukee binääritiedostosta rekisterin */


int main(int argc, char **argv) {

	char c = 'h'; /* Menuvalikon esille tuominen ensimmäisellä kutsulla */
	char *str;
	int amEr = 0; /* tarkistus muuttuja */
	struct node *base;
	unsigned long i;
	int comparedLength = 0;
	int searchedLength = 0;

        if(argc == 2) {
		if (strlen(argv[1]) == strlen("help")) {
			if(strlen(argv[1]) == strlen("help")) {
                              printf("\nTyöntekijärekisteri toimii käyttäjän antamin syöttein.\n\
Jos kysytään nimeä, niin anna nimi muodossa Etunimi ja Sukunimi, toisen nimen voi halutessa antaa.\n\
Summia ja vuosilukuja kysyttäess tarvitsee vain antaa luvut ilman yksiköitä.\n\n");
	}}}

	alloNode(); /* Allokoi hash-taululle muistin ja asettaa hashKey:lle arvot. */

	printf("	+----------------------------+\n\
	+                            +\n\
	+                            +\n\
	+     Työntekijärekisteri    +\n\
	+    	 by Timo Sand        +\n\
	+                            +\n\
	+                            +\n\
	+       Paina ENTER	     +\n\
	+----------------------------+\n");

	def:
	switch(c) { /* switch lauseke käsittelee ohjelman menu-rakennetta */
		case 'a' : 
			c = 'h';
			if (addEmployee() == 1) { /* Tarkistaa funktion palautusarvon virheitten varalle */
				printf("Lisäys ei onnistunut.\n");
			}
			break;
		case 'r' : 
			c = 'h';
			if (rmEmployee() == 1) { /* Tarkistaa funktion palautusarvon virheitten varalle */
				printf("Poisto-operaatio ei onnistunut.\n");
			}
			else printf("Tiedot poistettu! (Paina ENTER)\n");
			break;
		case 's' : /* Etsii rekisteristä nimetyn henkilön. */
			c = 'h';			
			flush(stdin);
			printf("Syötä nimi, kenet haluat löytää rekisteristä: ");
			str = getInput();
			i = hash(str) % HASH_SIZE;
			
			base = hash_table[i];
			if (base != NULL);
				/*printf("Key: %s\n", base->Key); Testituloste */
			else { printf("Rekisteriä ei ole.");
				break;
			}

			while (base != NULL && base->Key != NULL) { /* Käy hash-taulun alkiot läpi kohdassa i ja tulostaa 
henkilön tiedot kun on löytynyt oikea. */
				comparedLength = strlen(base->Key);
				searchedLength = strlen(str);
				if (comparedLength != searchedLength) { break; } 
				if (strcmp(base->Key, str) == 0) {
					printf(" %s:\n  Palkka: %6.2f\n  Aloitusvuosi: %d", str, base->palkka, base->vuosi);
					goto def;
				}
       			 }

			printf("Etsimääsi henkilöä ei löytynyt.\n");
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
				printf("Syötä kirjain, minkä vaihtoehdon haluat: ");
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

/* Funktio lisää työntekijän ja tämän tiedot hash-listaan. Tämän paikka löytyy kun "hashataan" työntekijän nimi.
* Funktiolla ei ole parametrejä, se kysyy kaiken tarvittavan tiedon käyttäjältä.
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

/* Kysytään nimeä ja haetaan hash-taulusta oikea kohta */
	flush(stdin); /*Tyhjennetään stdin muita merkeistä */
	
	printf("Syötä nimi (ei numeerinen), kenet haluat lisätä: ");
	nimi = getInput();
	employee = searchNode(nimi);
	i = hash(nimi) % HASH_SIZE;
	temp = hash_table[i];
	
/* Varmistetaan, että etsitty nimi ei ole vielä tallennettu */
	while (temp != NULL) {
/*		printf(" Hash: %ld Key: %s Nimi: %s\n", i, temp->Key, nimi);		Testituloste */
		if(temp->Key != NULL) {  /* Virheentarkistusta*/
			if (strcmp(temp->Key,nimi) == 0) {
				printf("Nimi on jo rekisterissä. Tallennus keskeytetään. ");
				return 1;
			}
		}
		temp = temp->next;	
	}
/* Kysytään palkan ja vuoden arvoja, kunnes vuodella tulee oikeanlainen arvo */
	do {
		printf("Syötä %s:n palkka ja aloitusvuosi: ", nimi);
		scanf(" %lf %d", &pay, &year);
		check = 0;
		if (year < 1900 || year > 2050) {
			printf("Syötit väärän vuosiluvun. Syötä vuosi väliltä 1900 ja 2050.\n");
			flush(stdin);
			year = 0;
			check = 1;
		}
	} while (check == 1);

	if ((employee->Key = MALLOC(char, memsz)) == NULL) {
		printf("Muistia ei voinut varata.\n");
		return 1;
	}

	/* tässä asetetaan uuden työntekijän tiedot listaan */
	strcpy(employee->Key, nimi);
	employee->palkka = pay;
	employee->vuosi = year;
	employee->hashKey = i;
	employee->next = NULL;

	for (temp = hash_table[i]; temp->next != NULL; temp = temp->next); /* käyään listaa läpi, kunnes löytyy viimeinen 
alkio*/
	/* Jos taulukon alkiossa ei vielä viitettä mihinkään node:n asetetaan tämä ensimmäiseksi. */
	if (temp == NULL) {
		hash_table[i] = employee;
		hash_table[i]->next = NULL;
	} 
	else { 
		for (; temp->next != NULL; temp = temp->next);
		temp->next = employee;
		temp->next->next = NULL;
	}
	
	printf("Palkka: %6.2fe/kk, Vuosi: %d\n", employee->palkka, employee->vuosi); /* Osoitetaan käyttäjälle, että 
ohjelma on ottanut syötteet vastaan oikein */
	tallenna = 1;
	memsz = 32;
	nimi = NULL;
	return 0;
	
}

/* Funktio on lukuväline, se lukee standardisyöttövirrasta tekstiä kunnes tulee '\n' tai '\r' -merkki.
* Funktio myös muuttaa mjonon pituutta, jos syöte on pidempi kuin oletus.
* Ei parametrejä, kun ei ollut mitään tarvetta.
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
/*	flush(stdin); Todettu turhaksi, voi käyttää hidastaakseen ohjelman suoritusta*/
	index = 0;

	while ((i = fgetc(stdin)) != '\n') { /* kopio merkin kerrallaan mjono muuttujaan, jos kasvaa yli memsz, niin 
tuplataan ja sit kopioidaan lisää */
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

/* Funktio antaa käyttäjän poistaa työntekjän rekisteristä.
* Ei parametrejä, kaikki tarvittava kysytään käyttäjältä.
* Palautusarvo kertoo oliko funktion suorituksessa mitään ongelmia.
*/

int rmEmployee(void) {

	char *nimi;
	struct node *temp, *aux;
	unsigned long i;
	int comparedLength = 0;
	int searchedLength = 0;

	flush(stdin);
	printf("Syötä nimi, kenet haluat poistaa rekisteristä: ");
	nimi = getInput();

	i = hash(nimi) % HASH_SIZE;
/*	printf("Hash: %ld\n", i);Testituloste */
	
	temp = hash_table[i];
	if (temp == NULL) { /* Tarksitetaan, että kohdassa i on alkioita */
		printf("Nimeä ei ole rekisterissä.");
		return 1;
	}
	
	if (hash_table[i] != NULL && hash_table[i]->next == NULL) { /* Tarkastetaan onko poistettava ensimmäinen ja ainut alkio*/
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
		if (strcmp(temp->Key, nimi) == 0) { /* Tarkistetaan onko kysessä samat arvot.*/
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
		
	printf("Etsimäänne henkilöä ei löytynyt.\n");
	memsz = 32;
	return 1;		

}

/* Funktio antaa mahdollisuuden muuttaa työntekijän palkkaa/aloitusvuotta tai kumpaakin.
* Parametrejä ei käyetät, ainoi tarvittava tieto on etsitty nimi ja se kysytään käyttäjältä.
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
	printf("Syötä nimi, kenen tietoja haluat muuttaa: ");
	nimi = getInput();
	memsz = 32;
	i = hash(nimi) % HASH_SIZE;
	temp = hash_table[i];

	 while(temp != NULL){ /* Käydään kohta i läpi, jotta etsitty löytyy */
		if(temp->Key != NULL)
            		 comparedLength = strlen(temp->Key);
		else{ if (temp->next != NULL)
	        	     temp = temp->next;
			else { printf("Ei merkintojä rekisterissä.\n");
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
		printf("Haluatko muuttaa henkilön palkkaa(1), aloitusvuotta(2) vai kumpaakin(3)?\n");
		/*flush(stdin);*/
		choice = fgetc(stdin);
		tallenna = 1;
		switch(choice) {
			case '1':
				printf("Palkka: %6.2fe/kk\n", temp->palkka);
				printf("Syötä uusi palkka: \n");
				scanf("%lf", &pay);
				temp->palkka = pay;
				break;
				/*Muuttaa structin palkkaa*/
			case '2':
				printf("Aloitusvuosi: %d\n", temp->vuosi);
				do {
					printf("Syötä uusi Aloitusvuosi: \n");
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
					printf("Syötä uusi palkka ja aloitusvuosi: \n");
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
* Tallenetaan käyttäjän antamaan tiedostoon tai perusasteuksena annettuun nimeen. 
*/
void saveTo() {

	int i = 0;
	struct node *aux;
	char *fname;
	int tallennettu = 0;
	
	do { /* Kysytään käyttäjältä vastausta kunnes tulee oikean lainen syöte */
		printf("Haluatko tallentaa muuhun kuin standarditiedostoon(rekisteri.txt)? 1: Kyllä 2: Ei ");
		flush(stdin);
		i = fgetc(stdin);
	/*	printf("%d\n", i); Testituloste */
	}  while ( i < '1' && i > '2');
	if (i == '1') {
		printf("Syötä tiedoston nimi: ");
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
	
	/*Käy läpi Rekisterin ja tallentaa jokaisen taulukon alkion */
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
*Käyttäjältä kysytään mikä tiedosto luetaan.
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
		printf("Haluatko lukea muusta kuin standarditiedostosta(rekisteri.txt)? 1: Kyllä 2: Ei ");
		flush(stdin);
		kirjain = fgetc(stdin);
	/*	printf("%d\n", kirjain); Testituloste */
	}  while ( kirjain < '1' && kirjain > '2');
	if (kirjain == '1') {
		printf("Syötä tiedoston nimi: ");
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
		printf("Tulostaa :%s %s\n", mjono, temp->Key); /*Testiä */
			
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
	else printf("Lukeminen epäonnistui. (Paina ENTER)\n");
	
	fclose(tied);
	tied = NULL;
}
/* Funktio sulkee ohjelman mahdollisimman "nätisti". Se koittaa vapauttaa kaiken kätetyn muistin.
* Tarksitaa josko ohjelma on muuttanut tai lisännyt asioita tallentamisen jälkeen.
* tallenna -muuttuja toimii tässä lippuna. Jos arvona on 1 niin kysytään tallentamista
*/
void cleanExit() {

	char yOrN;
	
	if (tallenna == 1) {
		printf("Haluatko tallentaa avoinna olevan rekiterin tiedostoon? (y/n) ");
		flush(stdin);
		yOrN = fgetc(stdin);
		if (yOrN == 'n') {
			printf("Suljetaan, tallentamatta!\n");
			rmAll(); /* Tyhjnetää koko taulukon*/
			tallenna = 0;
			exit(EXIT_SUCCESS);
		}
		if (yOrN == 'y') {
			saveTo();
			printf("Tallennetaan!\n");
			rmAll(); /* Tyhjnetää koko taulukon*/
			tallenna = 0;
			exit(EXIT_SUCCESS);
		}

	}
	else { 
		rmAll(); /* Tyhjnetää koko taulukon*/
		tallenna = 0;
		
		exit(EXIT_SUCCESS);
	 }		
}

/*Funktio vapauttaa parametrinä annetun node:n muistin.
* @Param deleted: Node mistä teenpäin halutaankaikki linkitetyt nodet vapauttaa. 
*/
void deleteNode(struct node *deleted){
             if(deleted->next != NULL) /*Jos seuraavassa alkiossa dataa vapauta se kanssa */
                      deleteNode(deleted->next);
             else
                     free(deleted);
}

/* Funktio käynnistää prosessin joka tyhjentää koko hash_table -taulukon alkioista ja vapauttaa sen muistin.
*/
void rmAll(){
 	int i;
 	for(i = 0; i < HASH_SIZE; i++){
     		deleteNode(hash_table[i]);
     		hash_table[i] = NULL;
 	}
}

/* Funktio näyttää käyttäjälle menun.
*/
void showMenu(void) {	
	printf("	 _____________________________________________\n\
	|					      |\n\
	|   a: Lisää työntekijä                       |\n\
	|   r: Poista työntekijä                      |\n\
	|   e: Muuta työntekijäntietoja  	      |\n\
	|   t: Tallenna rekisteri tiedostoon  	      |\n");
	printf("	|   f: Lue rekisteri tiedostosta  	      |\n\
	|   p: Tulostaa muistissa olevan rekisterin   |\n\
	|   s: Etsi henkilö rekisteristä	      |\n\
	|   h: Menu  				      |\n\
	|   x: Poistu ohjelmasta  		      |\n\
	|_____________________________________________|\n\n");
	
}
