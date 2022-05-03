# Onderzoek

Dit markdown bestand bevat wat gegevens over onderzoeken die ik gaandeweg de analyse heb onderzocht.

Het zal bepaalde onderdelen staven waarom ik de desbetreffende zaken in het project heb gekozen.

----

# Inhoudsopgaven

- [Onderzoek](#onderzoek)
- [Inhoudsopgaven](#inhoudsopgaven)
- [Plaats Sensoren Development Kit](#plaats-sensoren-development-kit)
- [Snelheid Metingen Development Kit](#snelheid-metingen-development-kit)
  - [Eén sensor](#eén-sensor)
    - [BLOCKING_CONTINUOUS](#blocking_continuous)
    - [ASYNC_CONTINUOUS](#async_continuous)
  - [Vijf sensoren](#vijf-sensoren)
    - [BLOCKING_CONTINUOUS](#blocking_continuous-1)
    - [ASYNC_CONTINUOUS](#async_continuous-1)
- [Plaats Sensoren PCBV0.3](#plaats-sensoren-pcbv03)
  - [Kruislings](#kruislings)
  - [Piramide](#piramide)
  - [Trap](#trap)
- [Snelheid Metingen PCBV0.3](#snelheid-metingen-pcbv03)
- [Coverglas](#coverglas)
- [Smudge Detection](#smudge-detection)
  - [Normale werking](#normale-werking)
  - [VL53LX_SMUDGE_CORRECTION_SINGLE](#vl53lx_smudge_correction_single)
  - [VL53LX_SMUDGE_CORRECTION_CONTINUOUS](#vl53lx_smudge_correction_continuous)


----

# Plaats Sensoren Development Kit

Dit project is ontworpen om te reageren op bewegingen gegeven door een gebruiker. Omdat dit meestal een hand zal zijn, moet er gekeken worden hoe de sensoren juist t.o.v. elkaar moeten staan (kruis, ster, cirkel, ...).

Initieel starten we met een beweging dat van links naar rechts beweegt waarbij we 3 ToF-sensoren gebruiken. Deze kunnen we op enkelen manieren opstellen:

<div style="align:center">
<img src="./foto's/stand_3_sensoren_1.jpg" width="33%">
<img src="./foto's/stand_3_sensoren_2.jpg" width="33%">
<img src="./foto's/stand_3_sensoren_3.jpg" width="33%">
</div>

Ik neem voorbeeld 1 omdat dit makkelijker is om een opstelling voor te maken. Voor s1 en s2 hebben we een afstand van 100mm (10cm) gekozen. Dit is ongeveer de breedte van mijn hand. Op deze manier zal 1 enkele sensor mijn hand zien wanneer ik deze ervoor breng en niet alle sensoren tegelijkertijd.

Als de gesture commando's uitgebreid worden, moeten we ook meerdere sensoren gebruiken om ze te kunnen detecteren. Hier hebben we ook enkele ideeën hoe we de sensoren kunnen plaatsen t.o.v. elkaar:

<img src="./foto's/stand_5_sensoren_1.jpg" width="33%">
<img src="./foto's/stand_5_sensoren_2.jpg" width="33%">
<img src="./foto's/stand_5_sensoren_3.jpg" width="33%">

Uiteraard zijn dit niet de enige mogelijke opstellingen. Het is maar een idee hoe we ze kunnen plaatsen.

Wederom voor deze opstelling nemen we de simpelste opstelling dat een kruis voorstelt (1ste foto) met s1 en s2 op 100mm.

?> Wanneer de custom made PCB aankomt (PCBV0.3) kan er geëxperimenteerd worden met meer exotische opstellingen + afstanden.

Bij de gekregen Dev-kit is de genomen opstelling niet mogelijk zonder wat knip en plak werk. Daarom maken we een 3D geprinte opstelling waarop we de sensoren kunnen bevestigen.

<iframe src="https://myhub.autodesk360.com/ue2fad720/shares/public/SH9285eQTcf875d3c5394184e6c7b619f119?mode=embed" width="800" height="600" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true"  frameborder="0"></iframe>

Dat uiteindelijk uitkomt op dit:

<img src="./foto's/OpstellingV1.jpg" width="50%">

De printplaat waarop de Nucleo-F401RE bevestigd is, wordt op een houten plaat bevestigd zodat deze verticaal staat. Op deze printplaat staan ook nog extra led's en drukknoppen om de analyse wat zichtbaar te maken.


# Snelheid Metingen Development Kit

!> De I2C klok frequentie is bij deze metingen ingesteld op 100kHz. Later wanneer PCBV0.3 onder handen wordt genomen, gaan we de klok frequentie proberen te verhogen naar 1MHz.

## Eén sensor

### BLOCKING_CONTINUOUS

!> De metingen die te zien zijn in de terminal screenshots zijn gebeurd zonder kalibratie van de sensor. Daarom dat deze afwijkend zijn van elkaar. De nauwkeurigheid van de sensor(en) heeft geen invloed op dit onderzoek.


Bij de gekregen Dev-kit werden de sensoren met mode *BLOCKING_CONTINUOUS* aangestuurd. Dit houd in dat de software zelf zal wachten totdat de sensor terug stuurt dat de data beschikbaar is. Dit proces herhalen we telkens.

|                       |min|typ|max|eenheid|
|-----------------------|---|---|---|-------|
|TimingBudget           |500|35 |16 |ms     |
|gemeten waarde software|507|43 |24 |ms     |

terminal beelden

**minimaal**

![terminal beeld minimaal](foto's/terminal_min_speed.jpg)

**standaard**

![terminal beeld standaard](foto's/terminal_typ_speed.jpg)

**maximaal**

![terminal beeld maximaal](foto's/terminal_max_speed.jpg)

gebruikte code
``` C
 while (1)
      {
        timerTotal = HAL_GetTick();

        getResults(VL53L3A2_DEV_LEFT, Result);

        if ((HAL_GetTick() - timer) >= 2000)
        {
          int dis0 = Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Distance[0];
          int dis1 = Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Distance[0];
          int dis2 = Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Distance[0];
          int dis3 = Result[VL53L3A2_DEV_TOP].ZoneResult[0].Distance[0];
          int dis4 = Result[VL53L3A2_DEV_BOTTOM].ZoneResult[0].Distance[0];
          timer = HAL_GetTick();
          
          printf("dis 0: %5ld \t dis 1: %5ld \t dis 2: %5ld \t dis 3: %5ld \t dis 4: %5ld \t totalTime: %5d\r\n", dis0, dis1,dis2,dis3,dis4, prevTotalTime);
          prevTotalTime = 0;
        }
        totalTime = HAL_GetTick() - timerTotal;
        if(prevTotalTime < totalTime)
          prevTotalTime = totalTime;
        
        HAL_GPIO_TogglePin(L_Y_GPIO_Port, L_Y_Pin);
      }
```

### ASYNC_CONTINUOUS

Onderstaande metingen zijn uitgevoerd met LEFT sensor (1 sensor) die *ASYNC_CONTINUOUS* werkt. Dit gebeurd d.m.v. een interrupt waar we nadien de gegevens uitlezen en de flag resetten. 
Hier hebben we een maximale snelheid bereiken van 16ms.

|                       |min|typ|max|eenheid|
|-----------------------|---|---|---|-------|
|TimingBudget           |500|35 |16 |ms     |
|gemeten waarde software|16 |16 |24 |ms     |
|gemeten waarde scoop   |494|35 |16 |ms     |

Scope beelden

**minimaal**

![scoop beeld minimaal](foto's/scoop_beeld_minimaal_snelheid_interrupt.png)

**standaard**

![scoop beeld standaard](foto's/scoop_beeld_standaard_snelheid_interrupt.png)

**maximaal**

![scoop beeld maximaal](foto's/scoop_beeld_maximaal_snelheid_interrupt.png)


De scoop beelden zeggen dat de tijd die de sensor op interrupt mode staat even lang blijft namelijk +-16ms ongeachte *TimingBudget*. De hoge periodes worden wel beïnvloed door *TimingBudget*. In de software daarentegen wijn de tijden wel korter dan bij *BLOCKING_CONTINUOUS*.

**minimaal**

![terminal beeld minimaal](foto's/terminal_min_speed_interrupt.jpg)

**standaard**

![terminal beeld standaard](foto's/terminal_typ_speed_interrupt.jpg)

**maximaal**

![terminal beeld maximaal](foto's/terminal_max_speed_interrupt.jpg)

Uiteraard krijgen we pas een meeting binnen wanneer de sensor gereed is (een interrupt heeft gecreëerd) wat ook gevolgen heeft voor onze code. De snelheid van de code blijft wel op de 16ms~24ms ongeachte het *TimingBudget*.

code

``` C
while (1)
      {
        timerTotal = HAL_GetTick();

        checkSensorReady(isStarted0, isReady0, VL53L3A2_DEV_LEFT, Result);

        if ((HAL_GetTick() - timer) >= 2000)
        {
          int dis0 = Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Distance[0];
          int dis1 = Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Distance[0];
          int dis2 = Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Distance[0];
          int dis3 = Result[VL53L3A2_DEV_TOP].ZoneResult[0].Distance[0];
          int dis4 = Result[VL53L3A2_DEV_BOTTOM].ZoneResult[0].Distance[0];
          timer = HAL_GetTick();
          
          printf("dis 0: %5ld \t dis 1: %5ld \t dis 2: %5ld \t dis 3: %5ld \t dis 4: %5ld \t totalTime: %5d\r\n", dis0, dis1,dis2,dis3,dis4, prevTotalTime);
          prevTotalTime = 0;
        }
        totalTime = HAL_GetTick() - timerTotal;
        if(prevTotalTime < totalTime)
          prevTotalTime = totalTime;
        
        HAL_GPIO_TogglePin(L_Y_GPIO_Port, L_Y_Pin);
      }
```

Voor onze applicatie is snelheid van metingen belangrijk zodat de user hierdoor geen hinder door ondervind.

## Vijf sensoren

Omdat ons systeem met 5 sensoren werkt zullen we dit ook even onderzoeken of dat we wel degelijk met interrupts de snelheid verhogen of niet. Idem als hierboven laten we eerst de terminal screenshots zien in modus *BLOCKING_CONTINUOUS* en nadien de modus *ASYNC_CONTINUOUS* die met interrupts werkt.

### BLOCKING_CONTINUOUS

|                       |min|typ|max|eenheid|
|-----------------------|---|---|---|-------|
|TimingBudget           |500|35 |16 |ms     |
|gemeten waarde software|508|86 |86 |ms     |

**minimaal**

![terminal beeld minimaal](foto's/terminal_min_speed_5.jpg)

**standaard**

![terminal beeld standaard](foto's/terminal_typ_speed_5.jpg)

**maximaal**

![terminal beeld maximaal](foto's/terminal_max_speed_5.jpg)

code 

``` C
while (1)
      {
        timerTotal = HAL_GetTick();

        getResults(VL53L3A2_DEV_LEFT, Result);
        getResults(VL53L3A2_DEV_CENTER, Result);
        getResults(VL53L3A2_DEV_RIGHT, Result);
        getResults(VL53L3A2_DEV_TOP, Result);
        getResults(VL53L3A2_DEV_BOTTOM, Result);

        if ((HAL_GetTick() - timer) >= 2000)
        {
          int dis0 = Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Distance[0];
          int dis1 = Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Distance[0];
          int dis2 = Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Distance[0];
          int dis3 = Result[VL53L3A2_DEV_TOP].ZoneResult[0].Distance[0];
          int dis4 = Result[VL53L3A2_DEV_BOTTOM].ZoneResult[0].Distance[0];
          timer = HAL_GetTick();

          printf("dis 0: %5ld \t dis 1: %5ld \t dis 2: %5ld \t dis 3: %5ld \t dis 4: %5ld \t totalTime: %5d\r\n", dis0, dis1, dis2, dis3, dis4, prevTotalTime);
          prevTotalTime = 0;
        }
        totalTime = HAL_GetTick() - timerTotal;
        if (prevTotalTime < totalTime)
          prevTotalTime = totalTime;

        HAL_GPIO_TogglePin(L_Y_GPIO_Port, L_Y_Pin);
      }
```

### ASYNC_CONTINUOUS

|                       |min|typ|max|eenheid|
|-----------------------|---|---|---|-------|
|TimingBudget           |500|35 |16 |ms     |
|gemeten waarde software|33 |86 |86 |ms     |

**minimaal**

![terminal beeld minimaal](foto's/terminal_min_speed_5_interrupt.jpg)

**standaard**

![terminal beeld standaard](foto's/terminal_typ_speed_5_interrupt.jpg)

**maximaal**

![terminal beeld maximaal](foto's/terminal_max_speed_5_interrupt.jpg)


code 

``` C
while (1)
      {
        timerTotal = HAL_GetTick();

        checkSensorReady(isStarted0, isReady0, VL53L3A2_DEV_LEFT, Result);
        checkSensorReady(isStarted1, isReady1, VL53L3A2_DEV_CENTER, Result);
        checkSensorReady(isStarted2, isReady2, VL53L3A2_DEV_RIGHT, Result);
        checkSensorReady(isStarted3, isReady3, VL53L3A2_DEV_TOP, Result);
        checkSensorReady(isStarted4, isReady4, VL53L3A2_DEV_BOTTOM, Result);

        if ((HAL_GetTick() - timer) >= 2000)
        {
          int dis0 = Result[VL53L3A2_DEV_LEFT].ZoneResult[0].Distance[0];
          int dis1 = Result[VL53L3A2_DEV_CENTER].ZoneResult[0].Distance[0];
          int dis2 = Result[VL53L3A2_DEV_RIGHT].ZoneResult[0].Distance[0];
          int dis3 = Result[VL53L3A2_DEV_TOP].ZoneResult[0].Distance[0];
          int dis4 = Result[VL53L3A2_DEV_BOTTOM].ZoneResult[0].Distance[0];
          timer = HAL_GetTick();

          printf("dis 0: %5ld \t dis 1: %5ld \t dis 2: %5ld \t dis 3: %5ld \t dis 4: %5ld \t totalTime: %5d\r\n", dis0, dis1, dis2, dis3, dis4, prevTotalTime);
          prevTotalTime = 0;
        }
        totalTime = HAL_GetTick() - timerTotal;
        if (prevTotalTime < totalTime)
          prevTotalTime = totalTime;

        HAL_GPIO_TogglePin(L_Y_GPIO_Port, L_Y_Pin);
      }
```

We kunnen concluderen dat snelheid niet het beste is wanneer we met meerdere sensoren werken. We gaan een balans moeten zoeken tussen de snelheid van het meten en de snelheid van verwerken.

We nemen hier 100 als waarde voor *TimingBudget* wat ons een software delay geeft van +-60ms.

# Plaats Sensoren PCBV0.3

## Kruislings

<img src="./foto's/stand_5_sensoren_1.jpg" width="33%">

Zoals besproken in [Plaats Sensoren Development Kit](#plaats-sensoren-development-kit) zijn er enkele mogelijkheden om de sensoren op te stellen. We hebben daarom een plexi glas plaat ontworpen die genoeg mogelijkheden voorziet om de sensoren op verschillende plaatsen te bevestigen.

<iframe src="https://myhub.autodesk360.com/ue2fad720/shares/public/SH9285eQTcf875d3c5393429cd8315483a19?mode=embed" width="800" height="600" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true"  frameborder="0"></iframe>

Als eerste opstelling gaan we opteren om de sensoren kruislings te plaatsen. Dit omdat we met de development kit goede resultaten hebben bekomen. Later in dit hoofdstuk gaan we nog enkele opstellingen uitvoeren op werking.

<img src="./foto's/PCBV0.3_opstelling_1.jpg" alt="foto opstelling 1" width="50%">

We verplaatsen telkens de sensoren dichter en dichter totdat de metingen elkaar overlappen (het gaat vooral over de Up-Down & Down-Up gestures die door de handgrootte de links en rechtse sensor kunnen triggeren en omgekeerd).

<img src="./foto's/PCBV0.3_opstelling_2.jpg" alt="foto opstelling 2" width="50%">

De foto hierboven is de maximale afstand die de sensoren kunnen verdragen om geen foutieve metingen te triggeren. Dit is uiteraard enkel met mijn hand getest. mensen met een groter hand, kunnen hier nog wel last van hebben. Vandaar dat we de sensoren finaal met 1 plaats opschuiven naar de buitenkant zodat we hopelijk deze hand grootte kunnen inperken. De flat cables zijn nu wat aan de lange kant en gaan we in de toekomst wat kleiner maken.

De afstanden zijn nu:

* S1 = 6cm
* S2 = 6cm
* S3 = 10.5cm
* S4 = 6.5cm

Nu we weten dat de opstelling kruislings werkt, kunnen we eens verder zien naar mogelijke opstellingen die eventueel kunnen werken met minder sensoren in gebruik. Dit zal wel voor complexere code zorgen maar de snelheid, kost en grootte van de opstelling wordt wel optimaler.

## Piramide

<img src="./foto's/stand_3_sensoren_4.jpg" alt="stand_3_sensoren_4" width="50%">

Met bovenstaande opstelling is het theoretisch mogelijk om links, rechts, boven en onder te detecteren.

We lijsten even op hoe we zullen detecteren:

?> **LEGENDE** SR = sensor rechts, SC = sensor center, SL = sensor links

* **RECHTS-LINKS** --> SR -> SC -> SL
* **LINKS-RECHTS** --> SL -> SC -> SR
* **BOVEN-ONDER**  --> SC -> SR & SL
* **ONDER-BOVEN**  --> SR & SL -> SC

Het is belangrijk dat we bij de gestures boven-onder & onder-boven kijken of dat de 2 sensoren tezamen getriggerd zijn. Als we dit niet doen kan een iets schuinere onder boven een rechts-links (of links-rechts) gesture triggeren.

In de praktijk ziet de opstelling er zo uit:

<img src="./foto's/PCBV0.3_opstelling_piramide_1.jpg" alt="foto opstelling piramide 1" width="50%">

Na het aanpassen van de code was het mogelijk om met de sensoren al de 4 gestures te verkrijgen. 

![piramide command terminal](foto's/terminal_piramide_commando.jpg)

?> zie de [blueprint](https://github.com/RobbeElsermans/GestureControl/blob/main/docs/Documenten/Blueprint_V1.1_Robbe_Elsermans.pdf) (<a href="./Documenten/Blueprint_V1.1_Robbe_Elsermans.pdf" download>download</a>) voor meer informatie over de commando waardes.

De snelheid is ook aanzienlijk verbeterd en het RAM geheugen zit minder vol. Met deze opstelling kunnen we gebruik maken van de STM32F302RCT6 i.p.v. de STM32F302RET6. In de repo is hiervoor een aparte branch opgezet genaamd *piramide*.

Een nadeel met deze opstelling is dat wanneer we ons hand te schuin van boven naar onder (of onder naar boven) verplaatsen, we de links-rechts en rechts-links triggeren. Dit is een beetje gefilterd in de code door een gemiddelde te nemen over 5 metingen en nog wat extra flags om ervoor te zorgen dat wanneer de gesture controller denkt een bepaalde gesture binnen te krijgen, de andere gestures wat te negeren. uiteraard mag deze hold van andere gestures niet te lang duren. Vandaar dat er ook een reset timer is geplaatst die al de flags op 0 zet om de 0.5 seconden.

De afstanden zijn nu:

* S1 = 5cm
* S2 = 5cm
* S3 = 6cm
* S4 = 6cm

## Trap

Omdat ik nu toch bezig was met allerlei opstellingen dacht ik er ook aan om deze eens te proberen:

<img src="./foto's/stand_3_sensoren_5.jpg" alt="stand_3_sensoren_5" width="50%">

en in praktijk ziet dit er zo uit:

<img src="./foto's/PCBV0.3_opstelling_trap_1.jpg" alt="PCBV0.3_opstelling_trap_1" width="50%">

We lijsten even op hoe we zullen detecteren:

?> **LEGENDE** SR = sensor rechts, SC = sensor center, SL = sensor links

* **RECHTS-LINKS** --> SR -> SC -> SL
* **LINKS-RECHTS** --> SL -> SC -> SR
* **BOVEN-ONDER**  --> SC -> SR -> SL
* **ONDER-BOVEN**  --> SL -> SR -> SC

Als we opstelling [Piramide](#piramide) vergelijken met de trap opstelling, is te zien dat we in deze opstelling SR en SL apart kunnen monitoren voor de 4 toestanden. Dit is niet het geval bij de piramide (hier gebruiken we SR & SL bij 2 gestures tezamen).

Tijdens het testen van deze opstelling met gebruik makend van de sensor die op het main bordje zit, merkte ik op dat wanneer ik de boven-onder gesture uitoefende, dit niet altijd even vlot ging dan bij de andere 3 gestures. Ik heb daarom een sensor bordje in de plaats gezet i.p.v. het main bordje. We zullen nu dus ook de XSHUT van het main bord op "0" moeten zetten zodat de sensor niet gebruikt wordt.

<img src="./foto's/PCBV0.3_opstelling_trap_2.jpg" alt="PCBV0.3_opstelling_trap_2" width="50%">

Na het testen van de opstelling en geprobeerd een zo ideaal mogelijke schikking te vinden, is er ook weer een stuk plexi glas voor uitgefreesd. Nu kan er weer gewerkt worden met een cover glas.

<img src="./foto's/PCBV0.3_opstelling_trap_3.jpg" alt="PCBV0.3_opstelling_trap_3" width="50%">

Wanneer deze opstelling uitvoerig werd getest, merkte ik op dat het niet altijd even correct werkten. Dit komt omdat wanneer we ervoor staan en we bewegen ons hand van links naar rechts (met je rechter hand), dan komt de arm in sommige gevallen al voor en sensor waarop dan de gesture geblokkeerd wordt. Als we dezelfde gesture (links -> rechts) met onze linker hand uitvoeren, is dit dan weer geen probleem. Dit is omgedraaid ook wanneer we de rechts -> links gesture uitoefenen met onze linker hand.

# Snelheid Metingen PCBV0.3

# Coverglas

Zoals beschreven in de [blueprint](https://github.com/RobbeElsermans/GestureControl/blob/main/docs/Documenten/Blueprint_V1.1_Robbe_Elsermans.pdf) (<a href="./Documenten/Blueprint_V1.1_Robbe_Elsermans.pdf" download>download</a>) zal de opstelling zich achter en cover glas bevinden. De sensor zal, zonder calibratie en cross-talk corrections, het coverglas aanschouwen als object. Dit moeten we uiteraard voorkomen. Omdat de afstand tussen ToF-sensor en coverglas niet oneindig variabel zal zijn, is het goed dat we dit eens onderzoeken hoe ver we zo'n coverglas kunnen plaatsen en hoe goed de metingen blijve


# Smudge Detection

Wanneer de sensor in gebruik zou zijn bij een eindgebruiker. Kan het altijd voorkomen dat het coverglas, dat zich over de sensor bevindt, vuil kan worden met vingerafdrukken en stof. ST heeft hier zelf een oplossing voor bedacht die geïntegreerd is in de API die men uitbracht. We moeten hier dus zelf niet ons hoofd over breken hoe we vuil kunnen weg filteren.

Wat we wel kunnen doen is de gebruiker waarschuwen wanneer er te veel vuil aanwezig zou zijn. Ook kunnen we testen wat nu de verschillende effecten zijn van vuil en de twee soorten standen die ST voorziet:

* **VL53LX_SMUDGE_CORRECTION_SINGLE**     --> Bij elk start commando de correctie toepassen
* **VL53LX_SMUDGE_CORRECTION_CONTINUOUS** --> Bij elke range de correctie toepassen

Om de data visueel te representeren heb ik een python script gemaakt dat te vinden is onder **python** genaamd **storeDataCSV_1Measurement.py** en **showDataCSV_1Measurement.py**. We sturen hiervoor een string van de afstand met de status van 1 sensor uit die we in het python script binnenhalen en opslaan als integers in een CSV bestand. Het andere python script zal de data (afkomstig van het CSV bestand) visualiseren met matplotlib.

**foutcodes** 
* 4: Raised when range result is out of bounds, 
* 6: No wraparound check has been done (this is the very first range), 
* 12: Indicate that there is a target, but signal is too low to report ranging,
* 14: Ranging data is negative and has to be ignored.

## Normale werking

hieronder is een screenshot te zien van een normale werking met een proper coverglas over x aantal meetingen. De sensor werd op een blauwe muur gefixeerd op een afstand van +- 1200mm. De meetingen zijn een gemiddelde van 4 meetingen achtereenvolgens.

![normal graph 1](foto's/normal_graph.png)

Zoals te zien zijn de metingen nog te fluxuerend. Dit komt omdat we hier werken met ene cover glas. De afstand wordt beduidend minder wanneer we met een cover glas werken. We verplaatsen het object eens naar +- 700mm. Deze keer is de muur wit van kleur.

![normal graph 2](foto's/normal_graph_2.png)

De meetingen zijn nog steeds zeer instabiel. We gaan een afstand van 500mm nemen.

![normal graph 3](foto's/normal_graph_3.png)

Dit lijkt al een betere afstand oms ons onderzoek op uit te voeren.

## VL53LX_SMUDGE_CORRECTION_SINGLE

Allereerst gaan we de mode **VL53LX_SMUDGE_CORRECTION_SINGLE** eens nader bekijken. Deze mode zal wanneer er een start commando wordt gegeven de correctie toepassen als deze eventueel nodig is. Zo'n correctie wordt enkel toegepast bij bepaalde omstandigheden. Het nadeel van deze mode is dat het maar één malig bij de start van de sensor wordt bekeken. Het kan altijd (meestal zal dit het geval zijn) dat de gebruiker het coverglas zal vuil maken tijdens het gebruik.

We voegen, voordat we de sensor aanzetten, wat vingerafdrukken toe op het coverglas. Daarna zetten we de voeding aan en zullen we de resultaten zien in de grafiek. 

![single mode graph](foto's/single_graph.png)

Op de grafiek zien we geen grote verschillen met voorgaande grafieken. In volgende grafiek hebben we met een keukenrol papier wat stof op het coverglas gebracht.

![single mode graph 2](foto's/single_graph_2.png)

Er is duidelijk een verschil te zien met de voorige grafiek. Met het stof op het coverglas, zijn er meer foutmeldingen. De afstand is over het algemeen wel constant.

## VL53LX_SMUDGE_CORRECTION_CONTINUOUS

Deze modus zal bij elke binnenkomende meeting, de correctie erop uitvoeren. Het is dus veel maal dynamischer dan bij de VL53LX_SMUDGE_CORRECTION_SINGLE modus.

We voegen, voordat we de sensor aanzetten, wat vingerafdrukken toe op het coverglas. Daarna zetten we de voeding aan en zullen we de resultaten zien in de grafiek. 

![continuous mode graph](foto's/continuous_graph.png)

Op de grafiek zien we geen grote verschillen met voorgaande grafieken. In volgende grafiek hebben we met een keukenrol papier wat stof op het coverglas gebracht.

![continuous mode graph 2](foto's/continuous_graph_2.png)

Zoals bij Single mode is hier ook goed op te merken dat het glas vuil is. We nemen eens een meeting nadat het toestel al even op staat.

![continuous mode graph 3](foto's/continuous_graph_3.png)

Dit geeft geen verschil.