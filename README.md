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

Na het importeren van de driver kunnen we deze gaan uitspitten. Zoals de [documentatie](https://www.st.com/resource/en/data_brief/stsw-img015.pdf) aangeeft moeten we eerst de sensor laten opstarten en nadien initialiseren a.d.h.v. de functies ```WaitDeviceBooted()``` & ```DataInit()```.