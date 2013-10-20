C-Ohjelmointi syksy 2007
Harjoitustyö - Työntekijärekisteri
Timo Sand


Ohjelma:

	Kyseessä on työntekijärekisteri, joka mahdollistaa 
	työntekijöiden lisäämisen, poistamisen ja muuttamisen 
	rekisterissä. Ohjelma tallentaa rakenteen binääritiedostoon 
	ja pystyy lukeen saman rakenteen tiedostosta.
	
	Ohjelam tallentaa rekisteriin ainoastaan työntekijän nimen, 
	palkan ja aloitusvuoden. Näitä arvoja ohjelma pystyy myös 
	tulostamaan käyttäjälle.


Eroavaa: 

	Ei eroavaa

Rakenne:

	Ohjelmassa on kaksi moduulia, main ja sub. Sub sisältää 
	funktiota, jotka käsittelevät ohjelman piilotettua puolta, 
	kuten taulun alustaminen. Main sisältää pääohjelman ja 
	taulun sisältöä käsitteleviä funktioita.

	Main:ssa on funktiot, joilla käsitellään taulukon sisäistä 
	tietoa, tiedoston tallentamista ja lataamista, sekä ohjelman 
	sulkeminen.
	
	Sub sisältää funktiot, jotka alustavat hash-taulun, 
	mahdollistavat sieltä etsimisen, muuttavat nimet 
	hash-numeroiksi ja tyhjentävät syöttövirtaa.

	Main:
	
		main 		- Funktio, joka käsittelee mitä käyttäjä haluaa tehdä.
		getInput	- Funktio, joka lukee standardisyöttövirtaa.
		addEmploye	- Funktio, joka lisää työntekijän.
		editEmployee	- Funktio, jolla voi muuttaa tietoja
		rmEmployee	- Fukntio, joka poistaa työntekijän
		rmAll		- Funktio, joka tyhjentää hash-taulun
		cleanExit	- Funktio, tekee puhtaan ohjleman lopetuksen
		showMenu	- Funktio näyttää käyttäjälle valikon
		deleteNode	- Funktio vapauttaa kaiken musitin annetussa taulukkoalkiossa
		saveTo		- Tallentaa tiedot tekstitiedostoon
		readFrom	- Lukee tiedot tekstitiedostosta

	Sub:

		hash		- Laskee annetusta nimestä arvon, jolla voi hakea nopeammin taulukosta alkioita
		flush		- Tyhjentää syöttövirran ylijääneistä merkeistä
		searchNode	- Etsii taulukosta tietyn noden ja palauttaa
		alloNode	- Alustaa taulukon alkiot ja varaa musitit
		printAll	- Tulostaa ruudulle reksiterin sisällön

Käyttöohje:

	Ohjelman käynnistykseen vaihtoehtoina on parametreillä tai 
	ilman. Ainoa käyettävä parametri on "help", joka tuo esille 
	pienen apu-tekstin. Muuten käynnistäessä ilman parametreja, 
	niin ohjelma opastaa mitä se haluaa käytäjältä. Ohjelma 
	kysyy pitki suoritusta nimiä, palkkoja taivuosilukuja. Nimet 
	annetaan aina Etunimi (toinen nimi) (Sukunimi) -muodossa. 
	Palkat ja muut luvut annetaan sellaisenaan, ohjelma 
	huolehtii yksiköistä itse. Ohjelma pysähtyy usein 
	suorituksen aikana tyhjään rivii, tällöin se odottaa 
	käyttäjältä ENTER-painikettä, ellei muuta ole kysytty.

Testaus:

	Ohjelman toiminto on täysin käyttäjän käsillä, ja se vaati 
	usein käyttäjää syöttämään valintoja, nimiä tai muuta 
	vastaavaa. Kaikki syötteet on tarkistettu ohjelman sisällä, 
	niin ettei käyttäjän syötteistä koidu virheitä.
	
	Muutama tapaus mitä olen testannu ja mennyt läpi:
		- Parametrit: parametrejän määrä ei vaikuta ohjelman suoritukseen
		- Syötteiden määrä ei tuota ongelmia
		- Syötteiden oikeellisuus tarkistetaan ja huomautetaan virheistä.
		
	Varsinaisia testitapauksia on vaikea tehdä ohjelmalle, kun 
	kaikki funktiot toimii ns. itsestään. Ja jos ohjelma tarvii 
	jotain niin kysyy käyttäjältä.
