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
  - [Importeren API VL53LXC](#importeren-api-vl53lxc)
  - [Importeer Andere Bestanden](#importeer-andere-bestanden)
  - [importeren HAL bibliotheek](#importeren-hal-bibliotheek)

----

# Inleiding

Dit markdown document zal de geschreven code wat verduidelijken in beste maten mogelijk. Het is de bedoeling dat dit document gebruikt kan worden om van scratch heel de software omgeving op te zetten en te kunnen gebruiken. 
Ook wordt er een sectie voorzien hoe dit systeem met een ander systeem kan communiceren met voorbeeld code.

Bij het begin van dit project had ik geen kennis over het programmeren van 32-bit microcontrollers. 

STM32CUBEIDE was me destijds ook onbekend. Gaandeweg dit project zijn beide items duidelijk geworden.

De API geschreven door ST-Elektronics ([hier](https://www.st.com/content/st_com/en/products/embedded-software/imaging-software/stsw-img015.html) te vinden) zal in dit document niet volledig beschreven worden. Enkel de gebruikte calls worden in dit document aangehaald. De handleiding om met de gegeven API te werken is [hier](https://www.st.com/resource/en/data_brief/stsw-img015.pdf) te vinden.

De gebruikte bibliotheek wordt in dit document opgesteld zodat deze stap voor stap na gebouwd kan worden. Er is ook al een reeds werkende bibliotheek aanwezig in de repo onder ... .

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

## Importeren API VL53LXC

Zoals gezegt in de [inleiding](#inleiding) hebben we voor de ToF-sensoren een API ter beschikking geschreven door ST zelf. Hier hebben we de **inc** en **src** folder waarin we de .h en .c  bestanden hebben staan. Deze bestanden moeten we overbrengen naar de **lib** folder waar we de **inc** en **src** bestanden kopiëren in de map **BSP_vl53l3cx**. 

!> Het is belangrijk dat we de bestanden rechtstreeks hierin plaatsen. We verkrijgen dus een map waarin zowel .h als .c bestanden staan. PLatformIo's [Library Dependency Finder (LDF)](https://docs.platformio.org/en/stable/librarymanager/ldf.html) werkt namelijk niet met een een *inc* folder. Voor simpliciteit gaan we dus alle .c en .h bestanden samen voegen in dezelfde folder.

Wanneer we het example project opendoen met de VL53L3CX sensoren, staan er nog enkele andere bestanden in die van belang zijn. Dit zijn:

* 53l3a2.c
* 53l3a2.h
* 53l3a2_ranging_sensor.c
* 53l3a2_ranging_sensor.h
* 53l3a2_conf_template.h
* ranging_sensor.h
* vl53l3cx.h
* vl53l3cx.c

Deze bestanden moeten eveneens in de folder **BSP_vl53l3cx** geplaatst worden.

Omdat het example project gebruik maakt van het [X-NUCLEO-53L3A2](https://www.st.com/en/evaluation-tools/x-nucleo-53l3a2.html) development kit, moeten we in bepaalde bestanden nog wat wijzigingen doorvoeren. 

?> De development kit maakt gebruik van een [STMP1600](https://html.alldatasheet.com/html-pdf/942880/STMICROELECTRONICS/STMPE1600/1946/1/STMPE1600.html) GPIO Expander die d.m.v. I²C communiceert. Ze gaan namelijk de XSHUT pinnen van de ToF-sensoren hiermee aansturen (Zie [hier](https://www.st.com/resource/en/user_manual/um2757-getting-started-with-xnucleo53l3a2-multi-target-ranging-tof-sensor-expansion-board-based-on-vl53l3cx-for-stm32-nucleo-stmicroelectronics.pdf) op pagina 5). Ook gebruikt deze development kit maar 3 ToF-sensoren (LEFT, CENTER, RIGHT) waar we in dit project er 5 gaan gebruiken (LEFT, CENTER, RIGHT, TOP, BOTTOM).

De veranderingen die we dus moeten doorvoeren is de manier waarop we de XSHUT pinnen gaan aansturen. Dit zal i.p.v. via de GPIO Expanders (die I²C verbinding hebben met de MCU) via gewone GPIO pinnen verlopen op de MCU.

Het desbetreffende bestand is *53l3a2.c* waarin we de wijzigingen gaan doorvoeren. De methode genaamd *int32_t VL53L3A2_ResetId(uint8_t DevNo, uint8_t state)* gaan we vervangen door een switch case waarin we de HAL bibliotheek gebruiken om ene GPIO op *state* te plaatsen.

``` 53l3a2.h
int32_t VL53L3A2_ResetId(uint8_t DevNo, uint8_t state)
{
  int32_t status;

  switch (DevNo)
  {
  case VL53L3A2_DEV_CENTER:

    HAL_GPIO_WritePin(XSHUT_1_Port, XSHUT_1_Pin, state);
    status = 1;
    break;

    ...

  }
  return status;
}
```

?> Zoals de [documentatie](https://www.st.com/resource/en/user_manual/um2778-vl53l3cx-timeofflight-ranging-module-with-multi-object-detection-stmicroelectronics.pdf) ons voorschrijft gebruiken we de XSHUT pin om de ToF-sensor in HW-Standby te plaatsen. We gebruiken deze methode later in ons programma om de ToF-sensoren van een uniek adres te voorzien.

!> We moeten dit dus voor elke XSHUT pin doen!

Om het aantal ToF-sensoren te verhogen naar 5 i.p.v. 3, gaan we in de bestanden *53l3a2_conf.h* en in *53l3a2.h* enkele wijzigingen doorvoeren.

In het bestand *53l3a2_conf.h* veranderen we de parameter *RANGING_SENSOR_INSTANCES_NBR* van (3U) naar (5U).

``` 53l3a2_conf.h
#define RANGING_SENSOR_INSTANCES_NBR    (5U)
```

in het bestand *53l3a2.h* veranderen we de enum *VL53L3A2_dev_e* zodat deze ook de TOP en BOTTOM bevat waarvan TOP gelijk is aan 3 en bottom gelijk is aan 4. 
``` 53l3a2.h
enum VL53L3A2_dev_e
{
  VL53L3A2_DEV_LEFT    =  0,
  VL53L3A2_DEV_CENTER  =  1,
  VL53L3A2_DEV_RIGHT   =  2,
  VL53L3A2_DEV_TOP     =  3,
  VL53L3A2_DEV_BOTTOM  =  4
};
```

## Importeer Andere Bestanden

Naast de gekregen API van ST, hebben we ook zelf een aantal bestanden gecreëerd om de code wat ordelijker en gestructureerder te maken. Zo hebben we voor elke gesture, calibratie, en extra rand methodes een aparte .c & .h bestand aangemaakt die ook van belang zijn in het project. Dit zijn de bestanden:

* CalibrationData.h
* CalibrationData.c
* GestureDetectDimming.h
* GestureDetectDimming.c
* GestureDetectLR.h
* GestureDetectLR.c
* GestureDetectRL.h
* GestureDetectRL.c
* GestureDetectUD.h
* GestureDetectUD.c
* GestureDetectDU.h
* GestureDetectDU.c
* GestureDetectObject.h
* GestureDetectObject.c

Al deze bestanden gaan eveneens onder de **lib** folder plaatsen in het bestand **Gesture_Detect**.

## importeren HAL bibliotheek

