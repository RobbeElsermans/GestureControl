# Gesture Control

> Made By Robbe Elsermans 

Het Gesture Control project is een bachelor proef gemaakt op het bedrijf [ED&A](https://www.edna.eu/nl) en gecoördineerd door [AP Hogeschool](https://www.ap.be/).

Graag bedank ik al de collega's die me - tijdens deze leerrijke periode - hebben geholpen om dit project tot een goed einde te brengen.

----

# Inhoudsopgaven

- [Gesture Control](#gesture-control)
- [Inhoudsopgaven](#inhoudsopgaven)
- [Inleiding](#inleiding)
- [Project Definitie](#project-definitie)
- [Gebruikte Software](#gebruikte-software)
- [Opbouw Project](#opbouw-project)
  - [PinOut](#pinout)

----

# Inleiding

Dit markdown document zal de geschreven code wat verduidelijken in beste maten mogelijk. Het is de bedoeling dat dit document gebruikt kan worden om van scratch heel de software omgeving op te zetten en te kunnen gebruiken. 
Ook wordt er een sectie voorzien hoe dit systeem met een ander systeem kan communiceren met voorbeeld code.

Bij het begin van dit project had ik geen kennis over het programmeren van 32-bit microcontrollers. 

STM32CUBEIDE was me destijds ook onbekend. Gaandeweg dit project zijn beide items duidelijk geworden.

De API geschreven door ST-Elektronics ([hier](https://www.st.com/content/st_com/en/products/embedded-software/imaging-software/stsw-img015.html) te vinden) zal in dit document niet volledig beschreven worden. Enkel de gebruikte calls worden in dit document aangehaald. De handleiding om met de gegeven API te werken is [hier](https://www.st.com/resource/en/data_brief/stsw-img015.pdf) te vinden.

----

# Project Definitie

Het doel van dit project is om een apparaat te ontwikkelen die de user interface een extra dimensie geeft via handbewegingen. Hierdoor is de user niet gelimiteerd tot aanrakingen of spraak maar ook beweging van de handen. De handbewegingen gaan we detecteren met één (of meerdere) “goedkope” Time of Flight (ToF)-sensor(en). De data verkregen van de ToF-sensor(en) zal verwerkt worden met een geschikte Microcontroller (MCU).

De handbewegingen gaan voor deze opstelling simpel zijn zodat de scope niet te groot wordt in dit project. Ook zal er rekening gehouden worden met storing-factoren zoals een cover glas en/ of omgevingslicht. Hiermee verhoogt het applicatiegebied aanzienlijk.
Om de verwerkte data te gebruiken is een interface een must have. Hiermee kan de hand gesture controller gemakkelijk gekoppeld worden aan een apparaat naar keuzen.

----

# Gebruikte Software

Deze sectie zal de gebruikte software bevatten en waarom we deze gebruikt hebben. Ook welke versie er gebruikt is. Een download link/ installatie link wordt mee voorzien.

<div style="color:black; background-color:white">

| Software | Versie | Argumentatie | Link |
| -------- |: ------    | ------------  | ----      |
| STM32CubeIDE   |  V1.4.0    |De software geschreven door ST. Hiermee is het makkelijk om de MCU te pre-configureren zonder 1 lijn code te schrijven. Zo worden alle pheripherals en GPIO gebruik automatisch gegenereerd op basis van een userinterface. Op deze manier kunnen we een clean start maken van het project zonder te veel code te schrijven voor het initialiseren van de MCU.|[link](https://www.st.com/en/development-tools/stm32cubeide.html)|
|   Visual Code   |V1.65.2   | Een "open source" editor die een groot ecosysteem heeft van plugins. Deze editor is vooral gekozen omdat ik hier ervaring mee heb. Ook omdat dit draait op Linux.|[link](https://code.visualstudio.com/)|
| PlatformIO  IDE | Home: V3.4.1  Core: V5.2.5 | Een plugin van Visual Code om de STM32Nucleo te programmeren en hardware debugging uit te voeren.  | [link](https://platformio.org/install/ide?install=vscode)
|Docsify|V4.4.4|Om deze documentatie te schrijven is er gebruik gemaakt van Docsify die de markdown bestanden omzet in een interactieve website. |[link](https://docsify.js.org/)|
</div>

----

# Opbouw Project

Initieel ben ik gestart met STM32CubeIDE omdat hierbij examples geleverd waren om de desbetreffende ToF-sensoren te gebruiken. Hierdoor kon ik me eerst focussen op het leren werken met de ToF-sensoren en met STM32CubeIDE.

Nadien zag ik de mogelijkheid om met PlatformIO IDE (plugin van Visual Code) verder te werken. Het is een vertrouwde omgeving en de basis functionaliteiten zijn hetzelfde als bij STM32CubeIDE.

Omdat de gegenereerde code in STM32CubeIDE wel heel handig is, heb ik het project eerst in STM32CubeIDE opgezet (configuratie I²C, GPIO, ...) en nadien de bestanden overgeplaatst naar het PlatformIO project. uiteraard heeft PLatformIO ook de nodige HAL(Hardware Abstraction Layer) bibliotheken nodig om de gegenereerde code te compileren. Later bespreken we hoe we deze installeren.

## PinOut

In onderstaande Miro sheets worden de pinouts weergegeven van zowel de MCU als de arduino header pinout


PCB Pinout
<iframe width="768" height="600" src="https://miro.com/app/live-embed/uXjVOF_Iavc=/?moveToViewport=-1493,-812,2822,1560" frameBorder="0" scrolling="no" allowFullScreen></iframe>

Arduino Header pinout
<iframe width="768" height="600" src="https://miro.com/app/live-embed/uXjVOF_cksw=/?moveToViewport=-1651,-1262,3867,2149" frameBorder="0" scrolling="no" allowFullScreen></iframe>