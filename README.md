C-Ohjelmointi syksy 2007
Harjoitusty� - Ty�ntekij�rekisteri
Timo Sand


Ohjelma:

	Kyseess� on ty�ntekij�rekisteri, joka mahdollistaa 
	ty�ntekij�iden lis��misen, poistamisen ja muuttamisen 
	rekisteriss�. Ohjelma tallentaa rakenteen bin��ritiedostoon 
	ja pystyy lukeen saman rakenteen tiedostosta.
	
	Ohjelam tallentaa rekisteriin ainoastaan ty�ntekij�n nimen, 
	palkan ja aloitusvuoden. N�it� arvoja ohjelma pystyy my�s 
	tulostamaan k�ytt�j�lle.


Eroavaa: 

	Ei eroavaa

Rakenne:

	Ohjelmassa on kaksi moduulia, main ja sub. Sub sis�lt�� 
	funktiota, jotka k�sittelev�t ohjelman piilotettua puolta, 
	kuten taulun alustaminen. Main sis�lt�� p��ohjelman ja 
	taulun sis�lt�� k�sittelevi� funktioita.

	Main:ssa on funktiot, joilla k�sitell��n taulukon sis�ist� 
	tietoa, tiedoston tallentamista ja lataamista, sek� ohjelman 
	sulkeminen.
	
	Sub sis�lt�� funktiot, jotka alustavat hash-taulun, 
	mahdollistavat sielt� etsimisen, muuttavat nimet 
	hash-numeroiksi ja tyhjent�v�t sy�tt�virtaa.

	Main:
	
		main 		- Funktio, joka k�sittelee mit� k�ytt�j� haluaa tehd�.
		getInput	- Funktio, joka lukee standardisy�tt�virtaa.
		addEmploye	- Funktio, joka lis�� ty�ntekij�n.
		editEmployee	- Funktio, jolla voi muuttaa tietoja
		rmEmployee	- Fukntio, joka poistaa ty�ntekij�n
		rmAll		- Funktio, joka tyhjent�� hash-taulun
		cleanExit	- Funktio, tekee puhtaan ohjleman lopetuksen
		showMenu	- Funktio n�ytt�� k�ytt�j�lle valikon
		deleteNode	- Funktio vapauttaa kaiken musitin annetussa taulukkoalkiossa
		saveTo		- Tallentaa tiedot tekstitiedostoon
		readFrom	- Lukee tiedot tekstitiedostosta

	Sub:

		hash		- Laskee annetusta nimest� arvon, jolla voi hakea nopeammin taulukosta alkioita
		flush		- Tyhjent�� sy�tt�virran ylij��neist� merkeist�
		searchNode	- Etsii taulukosta tietyn noden ja palauttaa
		alloNode	- Alustaa taulukon alkiot ja varaa musitit
		printAll	- Tulostaa ruudulle reksiterin sis�ll�n

K�ytt�ohje:

	Ohjelman k�ynnistykseen vaihtoehtoina on parametreill� tai 
	ilman. Ainoa k�yett�v� parametri on "help", joka tuo esille 
	pienen apu-tekstin. Muuten k�ynnist�ess� ilman parametreja, 
	niin ohjelma opastaa mit� se haluaa k�yt�j�lt�. Ohjelma 
	kysyy pitki suoritusta nimi�, palkkoja taivuosilukuja. Nimet 
	annetaan aina Etunimi (toinen nimi) (Sukunimi) -muodossa. 
	Palkat ja muut luvut annetaan sellaisenaan, ohjelma 
	huolehtii yksik�ist� itse. Ohjelma pys�htyy usein 
	suorituksen aikana tyhj��n rivii, t�ll�in se odottaa 
	k�ytt�j�lt� ENTER-painikett�, ellei muuta ole kysytty.

Testaus:

	Ohjelman toiminto on t�ysin k�ytt�j�n k�sill�, ja se vaati 
	usein k�ytt�j�� sy�tt�m��n valintoja, nimi� tai muuta 
	vastaavaa. Kaikki sy�tteet on tarkistettu ohjelman sis�ll�, 
	niin ettei k�ytt�j�n sy�tteist� koidu virheit�.
	
	Muutama tapaus mit� olen testannu ja mennyt l�pi:
		- Parametrit: parametrej�n m��r� ei vaikuta ohjelman suoritukseen
		- Sy�tteiden m��r� ei tuota ongelmia
		- Sy�tteiden oikeellisuus tarkistetaan ja huomautetaan virheist�.
		
	Varsinaisia testitapauksia on vaikea tehd� ohjelmalle, kun 
	kaikki funktiot toimii ns. itsest��n. Ja jos ohjelma tarvii 
	jotain niin kysyy k�ytt�j�lt�.
