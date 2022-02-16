# GestureControl
Gesture control with ToF sensor

Made by Robbe Elsermans with ED&A


# Analyse VL53L3CX ToF sensor

De [VL53L3CX](https://www.st.com/en/imaging-and-photonics-solutions/vl53l3cx.html) is een ToF-sensor (Time of Flight) die d.m.v. een laser de afstand zal bepalen.

**Enkele eigenschappen:**
* 500cm range (5m)
* immuun voor afdekglas & vuil op het glas
* dynamisch regelen van compensaties
* meerdere objecten detecteerbaar en afstand meetbaarheid
* een FoV (Field of View) van 25°
* I²C interface tot 1MHz (adres: 0x52)
* C en linux software drivers
* GPIO interrupts & reset
* afdekglas correctie verder dan 80cm

Om de sensor te gebruiken gaan we gebruik maken van een [API](https://www.st.com/content/st_com/en/products/embedded-software/imaging-software/stsw-img015.html) (Application Programming Interface) die geschreven is door ST. Documentatie over deze API is te vinden [hier](https://www.st.com/resource/en/data_brief/stsw-img015.pdf) in een pdf.

Het project wordt opgebouwd in STM32CubeIDE waar we de nodige drivers voor de ToF sensor gaan importeren. 

Na het importeren van de driver kunnen we deze gaan uitspitten. Zoals de [documentatie](https://www.st.com/resource/en/data_brief/stsw-img015.pdf) aangeeft moeten we eerst de sensor laten opstarten en nadien initialiseren.

Deze is te vinden als ```MX_TOF_Init();``` waar we de 3 sensoren af zetten via de reset pin (XSHUT). Nadien starten we ze terug op van links naar rechts en telkens geven we ze een ander adres waarop we ze later kunnen bereiken. Nadien checken we de communicatie met elke sensor om zeker te zijn dat ze werken.

Na de init fase gaan we verder naar de niet eindigende lus die leid naar ```MX_TOF_Process();```. Hier starten we de 1ste sensor (VL53L3A2_DEV_CENTER) die zal detecteren wanneer er een object nadert. Daarna gaan we weer naar een niet eindigende lus die de metingen zal doen en de zaken die erop volgen.

Wanneer er een object nadert moet deze aan bepaalde voorwaarden voldoen om als object te worden aanzien:

* Het verschil tussen de huidige en de vorige meeting moet minstens 1000mm bedragen (1m) - **(preDis1 - dis1) > threshold**
* De maximale afstand dat een object van de sensor mag staan is huidig 500 mm  - **(dis1 <= minDistanceObject)**
* De sensor moet het object duidelijk kunnen zien - **(uint8_t)Result.ZoneResult[0].Status[0] != 12**

Wanneer het object nu aan deze parameters voldoet, dan gaan we de andere 2 sensoren (links & rechts) aanzetten om later de hand gesture controlling te doen. Ook plaatsen we de boolean ObjectPresent op true.

Wanneer nu een object weer weg gaat zal dit ook aan bepaalde parameters vasthangen:

* De huidige en vorige meeting mogen samen niet minder dan de threshold zijn - **(preDis1 + dis1) > threshold**
* Er moet voordien een object gedetecteerd zijn - **ObjectPresent**

Dit zal de 2 buitenste sensoren weer laten stoppen zodat ze geen overbodige zaken doen.

Later gaan we ook een vertraging inbouwen wanneer er een object gedetecteerd wordt. Zo zal bv. het object voor enkele seconden voor de sensor moeten staan om het geheel te activeren.