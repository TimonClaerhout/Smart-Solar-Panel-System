# Logboek

* 29-03 : Kiezen project met de groep -> Solar Flower  
* 05-04 : Online meeting -> bespreken hoe we het gaan uitwerken, wie wat doet, ...  
* 21-04 : Presentatie over hoe we het project gaan aanpakken, feedback, ontvangen sensoren  
        Robin: maken opstelling zonnepaneel + implementatie motoren  
        Timon, Maxim: Aansluiten zonnenpanelen + batterij  
        Dieter: afwezig  
* 22-04 : Gezamelijk werken aan project + bestellen van sensoren indien nodig  
        -> stroom-spanningsmeter, lux sensor, accelerometer  
          Robin, Dieter: Uittesten motoren met H-brug + programmeren van Arduino met H-brug en bedraden van componenten op het project  
          Timon: Aansluiten zonnepanelen op Sunny Buddy om batterij op te laden + bestellen van nieuwe Lux sensor want stuurde andere waarde door + maken van website om sensor waarden door te sturen en mooi weer te geven  
          Maxim: Presentatie maken voor 30/04: Presenting Proof of Concept  
* 30-04 : Presentatie over ons project: welke componenten we gebruikt hebben -> gekozen voor Adafruit dashboard die we met ESP doorsturen omdat de website geen succes was.    
          Robin: Programmeren ESP -> aanmaken Adafruit dashboard om sensorwaarden weer te geven + uittesten accelerometer  
          Dieter: Uittesten van digitaal kompas en GPS-module  
          Timon: Uittesten lux sensor op Arduino UNO  
          Timon, Dieter: spanning-stroom meter op de zonnenpanelen met Arduino  
          Maxim: ...  
* 02-04 : Timon : bekijken digitaal kompas om dit automatisch naar het Noorden te laten wijzen  
* 07-05 : Gezamenlijk werken aan project  
          Robin, Timon: Aansluiten wifi van labo op project en via voeding van powerbank bekijken als de sensor waarden worden doorgestuurd en hoeveel stroom de zonnepanelen   leveren  
          Timon: Testen om data te schrijven naar EEPROM (later niet gedaan omdat het niet lukte)  
          Dieter: Testen op digitaal kompas aan de hand van de registers om het te callibreren + afwerken bedrading + programma's van sensoren implementeren in eindprogramma.  
          Maxim: ...  
* 8-05 :  Dieter: Verder testen uitgevoerd op het compass. Op het einde van de dag een offset gemaakt die werkte bij mij thuis.
* 9-05 :  Robin, Dieter: Opstelling testen met labo voeding omdat de batterij gesneuveld was. Gezien dat het niet meer werkte.
* 10-05 : Presenteren finaal project  
          Dieter, Robin: offset digitaal kompas opnieuw berekent in lokaal. Hier gezien dat we het compass moeten callibreren op elke nieuwe locatie.  
          Dieter, Robin: 's avonds testen uitgevoerd om compass te calibreren bij Robin thuis. Met de bedoeling om het te filmen.  
          Timon: Aanmaken README en logboek voor project  
          Maxim: ...  
* 11-05 : Testen om demo te filmen  
          Robin: Demo proberen te filmen. (was gelukt voor 4 uur). Hierna liep compass vast waardoor we reset hebben verzonnen.  
          Robin: Eerste testen uitgevoerd om compass aan en uit te zetten via relais contact.  
* 12-05 : Testen om demo te filmen  
          Dieter, Robin: Relais contact afgewerkt en programma ervoor geschreven zodat het compass om de zo veel tijd reset. Om fouten te voorkomen. Buiten geplaatsd om 24h test te doen. Deze test is mislukt. Daardoor 's avonds verder gezocht naar oplossingen door vaker te resetten maar zonder resultaat.  
* 13-05 : Testen om demo te filmen  
          Dieter, Robin: Gezien dat compass om de zoveel tijd niet meer verandert van waarde. Daardoor array voorzien die controleert of compass nog verandert. Indien deze niet meer veranderde reset van compass. Nieuwe fout gecreeërd omdat deze andere variabelen begon te overschrijven. (test was gelukt voor 1,5 uur). Hierna opgegeven omdat we geen oplossing meer zagen voor het probleem.  
* 16-05 : Testen om demo te filmen  
          Dieter, Robin: De tijd versneld laten lopen om ervoor te zorgen dat het compass niet meer vastloopt tijdens de test. Hierdoor hebben we dan 3 volle dagen kunnen filmen in een tijdspanne van 20 minuten.  
          Dieter, Timon, Robin en Maxim: Opname video voor eindpresentatie  
          Dieter: Samenvoeging van alle video's in 1 video.  
* 18-05 : Iedere groep toont video over zijn project  
