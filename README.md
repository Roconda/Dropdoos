Dropdoos
========


Eisen server
--------

* ~~Wacht op een tcp-poort op verbinding van een client~~
* Leest opdracht, handelt die af en stuurt informatie terug naar client
* ~~Houdt verbinding open totdat de client opdracht tot sluiten geeft~~
* ~~Draait op de achtergrond (heeft geen user-interface)~~
* ~~Hoeft niet multithreaded~~
* ~~De server is niet door een client af te sluiten.~~



Eisen client
--------

* Heeft een user-interface (tekst of grafisch)
* Krijgt de naam of het ip-adres van de gewenste server van de gebruiker
* Maakt verbinding met server als de gebruiker daar om vraagt.
* Stuurt namens de gebruiker opdrachten naar de server
* Verwerkt de teruggestuurde resultaten en laat informatie zien aan de gebruiker.

Eisen protocol
--------
* ~~Het is een applicatieprotocol op tcp.~~
* Het protocol is afgestemd met een andere groep.
* Er is een duidelijke beschrijving van het protocol.
* De volgende opdrachten zijn in iedere geval geïmplementeerd:
* ~~INFO geeft naam en versie van de server~~
* DIR dirname geeft een lijst van bestandsnamen in een directory, bijvoorbeeld DIR C:\TEST
* GET om een bestand van de server op te halen
* PUT om een bestand naar de server te sturen
* DEL om een bestand op de server te verwijderen
* REN om een bestand op de server te hernoemen
* ~~QUIT sluit de verbinding~~
* Alle communicatie bestaat uit leesbare regels tekst, afgesloten met een newline ('\n') en geen carriage return ('\r')
* Antwoorden van de server kunnen uit meerdere, niet-lege regels bestaan
* Aan het eind van een antwoord stuurt de server altijd een lege regel
* Bestandnamen met spaties en/of niet-ascii tekens geven geven geen problemen, bijvoorbeeld "Mijn ideeën".
* Client en server kunnen elkaar niet laten vastlopen.
* Storing of wegvallen van de verbinding moet geen vastlopers veroorzaken.
* Binaire bestanden zoals .exe en .jpg komen onbeschadigd over.
* Een bestandsoverdracht kan onderbroken worden (bijvoorbeeld met ctrl-c). Daarbij blijven geen incomplete bestanden achter.
* Busy waiting en polling zijn zo veel mogelijk vermeden.
* Het belangrijkste commando is natuurlijk:
* SYNC local-folder remote-folder
* Dit commando zorgt dat een map op de client (local-folder) wordt gesynchroniseerd met een map op de server (remote-folder). Met andere woorden: alle wijzigingen in die in de map (en submappen) aan de client-kant zijn aangebracht, worden gespiegeld op de aangegeven map (en submappen) op de server. Volg de volgende regels:
* Bestanden die niet bestaan op de client en wel op de server: worden verwijderd
* Bestanden die bestaan op client maar niet op de server: worden naar de server verzonden
* Bestanden die nieuwer zijn op de client dan op de server: worden naar de server verzonden
* Zorg ervoor dat bestanden bij de volgende SYNC niet onnodig opnieuw worden verzonden

Technische eisen
--------

* De server functioneel
* Er is een duidelijke verdeling in klasses
* Namen van klasses, typen, variabelen en functies zijn logisch, duidelijk en consequent
* Elke klasse heeft een .cpp en een .h
* De code is voorzien van zinvol commentaar
* In elke .h-file worden de niet-private onderdelen van de klasse beschreven voor de programmeur.
* Er zijn aantoonbaar geen memory leaks
* Foutafhandeling werkt met try-catch
* De demo-versie is zonder debugging gebouwd
* Bestanden worden verstuurd in blokken van eeen paar KB, om snel te zijn en toch zuinig met geheugen.
