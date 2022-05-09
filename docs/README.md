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
- [Gebruikte Hardware](#gebruikte-hardware)
- [Opbouw Project](#opbouw-project)
  - [PinOut](#pinout)
    - [Pin description](#pin-description)
  - [genereer code](#genereer-code)
  - [Importeer API VL53LXC](#importeer-api-vl53lxc)
  - [importeren include & src bestanden](#importeren-include--src-bestanden)
  - [Importeer Andere Bestanden](#importeer-andere-bestanden)
  - [Installeer Platform & Board](#installeer-platform--board)
  - [configureer platformio.ini file](#configureer-platformioini-file)
  - [main.h & .c](#mainh--c)
  - [Overzicht geïmporteerde bestanden](#overzicht-geïmporteerde-bestanden)
  - [Build & Upload](#build--upload)
- [Hardware Opbouw](#hardware-opbouw)
- [LED Controller](#led-controller)
- [Bevindingen & Upgrades](#bevindingen--upgrades)
- [Onderzoek](#onderzoek)

----

# Inleiding

Dit markdown document zal de geschreven code wat verduidelijken in beste maten mogelijk. Het is de bedoeling dat dit document gebruikt kan worden om van scratch heel de software omgeving op te zetten en te kunnen gebruiken.
Ook wordt er ook een sectie voorzien over de hardware specificaties opgelijst van de gemaakte PCB.
Als laatste wordt er een sectie voorzien hoe dit systeem met een ander systeem kan communiceren met voorbeeld code.

Helemaal onderaan is een link naar de onderzoekspagina waar ik sommige zaken dieper heb bekeken en onderzocht.

Bij het begin van dit project had ik geen kennis over het programmeren van 32-bit microcontrollers. 
STM32CUBEIDE was me destijds ook onbekend. Gaandeweg dit project zijn beide items duidelijk geworden.

Tijdens het middelbaar en hoger onderwijs heb ik de basis mee gekregen om een ordelijke PCB op te stellen. in dit project is de zelfzekerheid en het kritisch denken over hoe en wat we waar leggen/ tekenen, verhoogt.

De API geschreven door ST-Elektronics ([hier](https://www.st.com/content/st_com/en/products/embedded-software/imaging-software/stsw-img015.html) te vinden) zal in dit document niet volledig beschreven worden. Enkel de gebruikte calls worden in dit document aangehaald. De handleiding om met de gegeven API te werken is [hier](https://www.st.com/resource/en/data_brief/stsw-img015.pdf) te vinden.

De gebruikte bibliotheek wordt in dit document opgesteld zodat deze stap voor stap na gebouwd kan worden. Er is ook een werkende bibliotheek aanwezig in de repo onder [GestureControl/Code PlatformIO/GestureControl/lib](https://github.com/RobbeElsermans/GestureControl/tree/main/Code%20PlatformIO/Gesture%20Control/lib).

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
|ST STM32 Platform| V15.2.0 | PlatformIO ST STM32 platform | [link](https://github.com/platformio/platform-ststm32?utm_source=platformio&utm_medium=piohome)|
</div>

----

# Gebruikte Hardware

We lijsten in volgende tabel op wat we precies gebruikt hebben om onze hardware te vervaardigen (aka BOM). Ook staat hierbij de plaats op de PCB.

<div style="color:black; background-color:white">

<iframe src="./Hardware/ibom.html" title="BOM PCB0.3" height="1000"></iframe>
</div>

<a href="./Hardware/ibom.html" target="_blank">Hier</a>  de link om het op een aparte pagina te bekijken.

----

# Opbouw Project

Initieel ben ik gestart met STM32CubeIDE omdat hierbij examples geleverd waren om de desbetreffende ToF-sensoren te gebruiken. Hierdoor kon ik me eerst focussen op het leren werken met de ToF-sensoren en met STM32CubeIDE.

Nadien zag ik de mogelijkheid om met PlatformIO IDE (plugin van Visual Code) verder te werken. Het is een vertrouwde omgeving en de basis functionaliteiten zijn hetzelfde als bij STM32CubeIDE.

Omdat de gegenereerde code in STM32CubeIDE wel heel handig is, heb ik het project eerst in STM32CubeIDE opgezet (configuratie I²C, GPIO, ...) en nadien de bestanden overgeplaatst naar het PlatformIO project. uiteraard heeft PLatformIO ook de nodige HAL(Hardware Abstraction Layer) bibliotheken nodig om de gegenereerde code te compileren. Later bespreken we hoe we deze installeren.

Om met de ToF-sensoren aan de slag te gaan, heb ik gebruik gemaakt van het development kit [P-NUCLEO-53L3A2](https://www.st.com/en/evaluation-tools/p-nucleo-53l3a2.html) die een voor-gecompileerde bibliotheek meegeleverd kreeg. Hier heb ik eerst met leren werken. Nadien ben ik overgestapt naar de *"Bare API"* en hier al de nodige extra bestanden die we moeten toevoegen om het compatibel te maken met het gebruikte platform.

----

## PinOut

In onderstaande Miro sheets worden de pinouts weergegeven van zowel de (mogelijke) MCU(s) als de ST Morpho Extention pin header.


PCB Pinout F401RxT
<iframe width="768" height="600" src="https://miro.com/app/live-embed/uXjVOF_Iavc=/?moveToViewport=-1493,-812,2822,1560" frameBorder="0" scrolling="no" allowFullScreen></iframe>

PCB Pinout F151Lx
<iframe width="768" height="600" src="https://miro.com/app/live-embed/uXjVOC73SG8=/?moveToViewport=-794,-502,1535,853" frameBorder="0" scrolling="no" allowFullScreen></iframe>

PCB Pinout F302Rx
<iframe width="768" height="600" src="https://miro.com/app/live-embed/uXjVO7LxdQU=/?moveToViewport=-355,-347,595,605" frameBorder="0" scrolling="no" allowFullScreen></iframe>

!> Merk op dat we **EXTERN1** & **EXTERN2** hebben moeten vervangen door **I2C2_SDA** & **I2C2_SCL**. 

ST Morpho Extention pin header
<iframe width="768" height="600" src="https://miro.com/app/live-embed/uXjVOF_cksw=/?moveToViewport=-1651,-1262,3867,2149" frameBorder="0" scrolling="no" allowFullScreen></iframe>


### Pin description 

<div style="display:inline-block; background-color:white">
<table style="background-color: white; color: black; display:inline;">
  <tr>
    <th>naam</th>
    <th>type</th>
    <th>default state</th>
  </tr>
  <tr>
    <td>XSHUT_0</td>
    <td>GPIO_Output</td>
    <td>HIGH</td>
  </tr>
  <tr>
    <td>XSHUT_1</td>
    <td>GPIO_Output</td>
    <td>HIGH</td>
  </tr>
    <tr>
    <td>XSHUT_2</td>
    <td>GPIO_Output</td>
    <td>HIGH</td>
  </tr>
    <tr>
    <td>XSHUT_3</td>
    <td>GPIO_Output</td>
    <td>HIGH</td>
  </tr>
    <tr>
    <td>XSHUT_4</td>
    <td>GPIO_Output</td>
    <td>HIGH</td>
  </tr>
    <tr>
    <td>GPIOI_0</td>
    <td>GPIO_EXTIx</td>
    <td>HIGH</td>
  </tr>
    <tr>
    <td>GPIOI_1</td>
    <td>GPIO_EXTIx</td>
    <td>HIGH</td>
  </tr>
    <tr>
    <td>GPIOI_2</td>
    <td>GPIO_EXTIx</td>
    <td>HIGH</td>
  </tr>
    <tr>
    <td>GPIOI_3</td>
    <td>GPIO_EXTIx</td>
    <td>HIGH</td>
  </tr>
    <tr>
    <td>GPIOI_4</td>
    <td>GPIO_EXTIx</td>
    <td>HIGH</td>
  </tr>  
  <tr>
    <td>LED_0</td>
    <td>GPIO_Output</td>
    <td>LOW</td>
  </tr>
  <tr>
    <td>LED_1</td>
    <td>GPIO_Output</td>
    <td>LOW</td>
  </tr>  
  <tr>
    <td>LED_2</td>
    <td>GPIO_Output</td>
    <td>LOW</td>
  </tr>  
  <tr>
    <td>LED_3</td>
    <td>GPIO_Output</td>
    <td>LOW</td>
  </tr>
  <tr>
    <td>LED_4</td>
    <td>GPIO_Output</td>
    <td>LOW</td>
  </tr>
  <tr>
    <td>SW_1</td>
    <td>GPIO_Input</td>
    <td>LOW</td>
  </tr>
  <tr>
    <td>SW_2</td>
    <td>GPIO_Input</td>
    <td>LOW</td>
  </tr>
  <tr>
    <td>EN_5V</td>
    <td>GPIO_Output</td>
    <td>HIGH</td>
  </tr>
</table>
</div>

----

## genereer code

Om het onszelf makkelijk te maken gaan we gebruik maken van de STM32CubeIDE tools die voor ons de code genereren.

1. Installeer [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) en open dit in een directory naar keuzen.

![foto opstart popup 0](foto's/tutorial_Importeer_bestanden_0.jpg)

2. Start een nieuw project op. Dit kan even duren vooraleer een nieuwe window verschijnt.

![foto opstart project 1](foto's/tutorial_Importeer_bestanden_1.jpg)

1. Type in **Part Number** het volgende: *stm32f302rc*. Nadien selecteer je in de tabel de 1ste rij om nadien op **Next** te drukken.

![foto opstart project 2](foto's/tutorial_Importeer_bestanden_2.jpg)

4. Een nieuw venster verschijnt waarin we de naam, de locatie en de programmeer taal dat we willen gebruiken instellen. De naam is vrij te kiezen net zoals de locatie van het project. Ik neem hier *GestureController* als naam en de locatie laat ik op default staan. Als programmeer taal gaan we C nemen. Nu drukken we op **Finish** zodat ons project wordt aangemaakt. Men zal vragen of dat men het **Device Configuration Tool perspective** mag openen. Druk hierbij op **Yes**.

![foto opstart project 3](foto's/tutorial_Importeer_bestanden_3.jpg)
![foto opstart project 4](foto's/tutorial_Importeer_bestanden_4.jpg)

?> Nu bevinden we ons in ST's hun (mijn mening) handigste tool ooit. Hier kunnen we op grafischer wijze heel ons project opbouwen zonder 1 lijn code te schrijven.

5. Nu gaan we de ToF-sensor extensie installeren zodat we de nodige code kunnen laten genereren. Hiervoor gaan we naar de dropdown **Software Packs** vervolgens **Manage Software Packs** (of ALT+U)

![foto opstart project 5](foto's/tutorial_Importeer_bestanden_5.jpg)

1. In het popup-venster **Embedded Software packages Manager** gaan we bovenaan naar de 2de tab **STMicroelektronics** en zoeken we in de lijst naar **X-CUBE-TOF1** waar we vervolgens in de dropdown versie 1.0.0 aanvinken & versie 3.0.0 aanvinken. We installeren deze.

![foto opstart project 6](foto's/tutorial_Importeer_bestanden_6.jpg)

!> men vraagt voor akkoord (of niet akkoord) te gaan met de licentie van de software. Als we niet akkoord gaan kunnen we uiteraard de software niet gebruiken. Ik ga dus akkoord.

Wanneer de installatie voltooid is, zou het vinkje volledig groen moeten zijn. We sluiten het **Embedded Software packages Manager** venster.

![foto opstart project 7](foto's/tutorial_Importeer_bestanden_7.jpg)

7. Vervolgens plaatsen we de pin gegevens (die te vinden zijn in hoofdstuk [PinOut](#pinout) meer bepaald in foto **PCB Pinout F302Rx** en in hoofdstuk [Pin description](#pin-description)) in de grafische editor. Zoals de opmerking zegt, is I2C2 op een andere pin dan de MCU's die we in gedachten hadden om te gebruiken. Dit wordt in hoofdstuk [Hardware Opbouw](#hardware-opbouw) beschreven hoe we dit aanpassen met PCBV0.3.

Om een pin de definiëren gaan we met de cursor van de muis op de desbetreffende pin staan. Met de linker muisknop komt er een dropdown waarin alle opties staan die de geselecteerde pin kan hebben. Hieronder een voorbeeld hoe we XSHUT_0 - dat een GPIO_Output is en zich op PC0 bevindt - definiëren. We geven de pin ook een naam zodat dit later in de code leesbaar is.

![foto declareren pinnen 8](foto's/tutorial_Importeer_bestanden_8.jpg)

Om een naam te geven klikken we met de rechter muisknop op de aangemaakte GPIO pin en selecteren we **Enter User label** om dan een naam in te kunnen geven.

![foto declareren pinnen 9](foto's/tutorial_Importeer_bestanden_9.jpg)

Dit herhalen we totdat we al de XSHUT, GPIOI, LED en SW pinnen hebben gedeclareerd. Dit resulteert in onderstaande foto:

![foto declareren pinnen 10](foto's/tutorial_Importeer_bestanden_10.jpg)

Nu rest ons nog om voor de interrupts (GPIOI_0->4) code te laten genereren. Dit vinden we in de zijbalk onder **System Core** -> **NVIC** die ons een ander zijbalk 
toont waarin we **EXTI line [9:5] interrupts** en **EXTI line [15:10] interrupts** aanvinken. Dit zal later voor ons de code activeren.

![foto declareren peripheral pinnen 11](foto's/tutorial_Importeer_bestanden_11.jpg)

8. Na het plaatsen van de input, output en interrupt pinnen, moeten de peripheral pinnen nog gedeclareerd worden (zoals I2C1, I2C2, Externe clock, UART, ...). Dit vergt iets meer werk dan voorgaande stap.
   1. Als eerste gaan we de programming peripheral activeren genaamd **Async Serial Wire**. Dit doen we door in de zijbalk onder **System Core** -> **SYS** bij de dropdown **Debug** de laatste optie **Trace Asynchronous Sw** te selecteren. Na de selectie zullen er enkele pinnen groen worden en een naam krijgen.
   
   ![foto declareren peripheral pinnen 12](foto's/tutorial_Importeer_bestanden_12.jpg)
   ![foto declareren peripheral pinnen 13](foto's/tutorial_Importeer_bestanden_13.jpg)
   
   2. Het volgende dat we gaan instellen zijn de externe klok kristallen. Hiervoor gaan we ook onder **System Core** naar **RCC** waar we dan de HSE (High Speed Clock) en de LSE (Low Speed Clock) kunnen instellen. Beiden worden geplaatst op **Crystal/Ceramic Resonator**. Wederom worden er enkele pinnen groen met een naam.
    
    ![foto declareren peripheral pinnen 14](foto's/tutorial_Importeer_bestanden_14.jpg)
    ![foto declareren peripheral pinnen 15](foto's/tutorial_Importeer_bestanden_15.jpg)
    
    Nu dat de pinnen gedefinieerd zijn, kunnen we de klok zelf definiëren. Dit doen we in een andere tab (die bovenaan te vinden is) genaamd **Clock Configuration**. Hierin gaan we 2 bolletjes van plaats veranderen. Bij **PLL Source Mux** veranderen we het bolletje van **HSI** naar **HSE**. Bij **System Clock Mux** veranderen we het bolletje van **HSI** naar **PLLCLK**. Later komen we hier nog enkele zaken aanpassen.

    ![foto declareren peripheral pinnen 16](foto's/tutorial_Importeer_bestanden_16.jpg)

   3. We keren terug naar de **Pinout & Configuration** tab bovenaan. Nu gaan we de FTDI peripheral aanmaken op **USART1**. Hiervoor gaan we onder **Connectivity** -> **USART1** de volgende zaken wijzigen:
      - Mode: Asynchronous
      - Hardware Flow Control (RS232): CTS/RTS
      - Baud Rate: 115200
      - TX and RX Pins Swapping: Enable
    
    ![foto declareren peripheral pinnen 17](foto's/tutorial_Importeer_bestanden_17.jpg)
    ![foto declareren peripheral pinnen 18](foto's/tutorial_Importeer_bestanden_18.jpg)

    Zoals te zien op de foto zijn er weer enkele pinnen groen geworden met hun bijhorende naam. Merk op dat USART1_RX en USART1_TX niet op de juiste plaatst staat. Om de pin op de juiste plaats te zetten, gaan we met de muis over de pin staan en we drukken Ctrl+linker muisknop. nu zal je pinnen zien pinken. Deze pinnen kunnen de functie (USART1_RX) eveneens aansturen.

    ![foto declareren peripheral pinnen 19](foto's/tutorial_Importeer_bestanden_19.jpg)

    We slepen dus de vastgenomen pin naar PB7. Dit doen we ook voor USART1_TX maar dan naar PB6. Nu staat de pin juist.
      
    ![foto declareren peripheral pinnen 20](foto's/tutorial_Importeer_bestanden_20.jpg)

   4. Een van de belangrijkste peripheral is toch I2C1 die in communicatie gaat met de ToF-sensoren. Deze stellen we in via **Connectivity** -> **I2C1** waar we de dropdown op **I2C** plaatsen. De snelheid van de klok stellen we in op **Fast Mode Plus** (1MHz frequentie).
   
   ![foto declareren peripheral pinnen 21](foto's/tutorial_Importeer_bestanden_21.jpg)

   Net zoals bij de USART1 peripheral staan de pinnen niet zoals we het willen. Hier wordt hetzelfde gedaan als met USART1_RX & USART1_TX maar dit dan met I2C1_SCL. We verplaatsen I2C1_SCL van PA15 naar PB8.

   ![foto declareren peripheral pinnen 22](foto's/tutorial_Importeer_bestanden_22.jpg)

   1. De 2de belangrijkste peripheral is I2C2 die in slave mode zal staan zodat andere toestellen hiermee verbinding kunnen aangaan. Net zoals hierboven gaan we in de zijbalk bij **Connectivity** naar **I2C2** waar we in de dropdown **I2C** selecteren en we stellen zijn adres in op **32** (HEX: 0x20).

    ![foto declareren peripheral pinnen 23](foto's/tutorial_Importeer_bestanden_23.jpg)

    Omdat we met de gesture controller niet willen wachten totdat wanneer er een master iets stuurt, zal dit over een interrupt verlopen. Hiervoor gaan we naar de tab **NVIC Settings** waar we **I2C2 event global interrupt / I2C2 wake-up interrupt trhough EXTI line 24** aanvinken.

    ![foto declareren peripheral pinnen 24](foto's/tutorial_Importeer_bestanden_24.jpg)

    De pinnen worden nu wel juist geplaatst. We moeten wel later de pinnen doorverbinden op de PCBV0.3 (zie [Hardware Opbouw](#hardware-opbouw)).

    ![foto declareren peripheral pinnen 25](foto's/tutorial_Importeer_bestanden_25.jpg)

9. De MCU heeft al de aansluitingen gekregen die deze nodig heeft voor de GestureController. De ToF-sensor bibliotheek gaan we nu importeren om dan automatisch te laten integreren met de genomen MCU. Hiervoor gaan we naar **Software Packs** -> **Select Components** (of Alt+O). Er komt een tabel tevoorschijn. 

![foto declareren peripheral pinnen 26](foto's/tutorial_Importeer_bestanden_26.jpg)

De rij **STMicroelektronics.X-CUBE-TOF1** vouwen we open om dan door te gaan naar **Board Part Ranging** waar we **VL53L3CX** selecteren. We vouwen ook **Device ToF1_Applications** open om daar in de dropdown **VL53L3CX_SimpleRanging** te selecteren. Dit zal een oranje driehoek tevoorschijn laten komen. Wanneer we op deze driehoek klikken met de linker muisknop, zal er onderaan in de kader **Component dependencies** informatie tevoorschijn komen. Hier klikken we met de linker muisknop op **Resolve** wat automatisch voor ons de dependencies zal oplossen.

![foto declareren peripheral pinnen 27](foto's/tutorial_Importeer_bestanden_27.jpg)

De ToF-sensor bibliotheek is te configureren in de tab **Software Packs**->**STMicroelectronics.X-CUBE-TOF1.3.0.0**. Hier Gaan we het eerste vinkjes selecteren in de kader **Mode**. In de kader **Configuration** stellen we in welke pin voor wat in staat. Omdat we onze pinnen al gedefinieerd hebben is het enkel maar de dropdown open doen en een correcte pin selecteren. We nemen in dit geval voor XSHUT pin PC0 en voor I2C nemen we I2C1 met adres 82 (HEX: 0x52) dat het default adres is van de ToF-sensoren. Later in de code wordt er bijna geen gebruik gemaakt van deze instellingen. Dit moet gewoon ingevuld zijn zodat ST de code voor ons kan genereren.

![foto declareren peripheral pinnen 28](foto's/tutorial_Importeer_bestanden_28.jpg)

10. Een laatste wijziging voeren we door zodat al de peripherals in apare c en h bestanden geplaatst worden. Dit is overzichtelijker maar niet noodzakelijk. Hiervoor ga je naar **Project manager**->**Code Generation** waar we de regel **Generate peripheral initialization as a pair of '.c/.h' files per peripheral** aanvinken.

![foto declareren peripheral files 29](foto's/tutorial_Importeer_bestanden_29.jpg)

Nu is het tijd om de code te genereren. Als we op ctrl+S (opslaan) drukken, dan zal er een popup verschijnen om de code te genereren. Nadien volgt een andere popup om het perspecitief om te zetten naar C/C++ perspecief. bijde druk je op **Yes**. De code wordt gegenereerd. 

Omdat ik mijn project in PlatformIO heb gemaakt, zal ik hier nog verder beschrijven hoe we dit daarin importeren. Men kan vanaf hieruit ook alles in STM32CubeIDE uitvoeren net zoals in PlatformIO.

----


## Importeer API VL53LXC

Zoals gezegt in de [inleiding](#inleiding) hebben we voor de ToF-sensoren een API ter beschikking geschreven door ST zelf. Hier hebben we de **modules** en **porting** folder onder **BSP/Components/vl53l3cx** waarin de .h en .c  bestanden staan. Deze bestanden gaan we overbrengen naar de **lib** folder waar we al de bestanden kopiëren in de map **BSP_vl53l3cx** onder de folder **src**. 

Wanneer we het gegenereerde project opendoen met de VL53L3CX sensoren, staan er nog enkele andere bestanden onder **BSP/Components/vl53l3cx.h & .c** en **TOF/Target** in die van belang zijn:

* vl53l3cx.h
* vl53l3cx.c
* custom_tof_conf.h

Deze bestanden moeten eveneens in de folder **BSP_vl53l3cx** geplaatst worden.

!> Het is belangrijk dat we de bestanden rechtstreeks hierin plaatsen. We verkrijgen dus een map waarin zowel .h als .c bestanden staan. PlatformIO's [Library Dependency Finder (LDF)](https://docs.platformio.org/en/stable/librarymanager/ldf.html) werkt namelijk niet met een een *inc* folder. Voor simpliciteit gaan we dus alle .c en .h bestanden samen voegen in dezelfde folder genaamd **src**.

?> Al de bestanden die we nu overzetten, zijn gegenereerd in STM32CubeIDE (zie [genereer code](#genereer-code)).

In het bestand **custom_tof_conf.h** moeten we nog een lijn code toevoegen tussen **/\* USER CODE BEGIN 1 \*/** en **/\* USER CODE END 1 \*/** (lijn 34) om de gemaakte code te laten werken. 

´´´ C custom_tof_conf.h

/* USER CODE BEGIN 1 */
#define CUSTOM_VL53L3CX_I2C_GetTick   BSP_GetTick
/* USER CODE END 1 */

´´´

<!-- Omdat het example project gebruik maakt van het [X-NUCLEO-53L3A2](https://www.st.com/en/evaluation-tools/x-nucleo-53l3a2.html) development kit, moeten we in bepaalde bestanden nog wat wijzigingen doorvoeren. 

?> De development kit maakt gebruik van een [STMP1600](https://html.alldatasheet.com/html-pdf/942880/STMICROELECTRONICS/STMPE1600/1946/1/STMPE1600.html) GPIO Expander die d.m.v. I²C communiceert. Ze gaan namelijk de XSHUT pinnen van de ToF-sensoren hiermee aansturen (Zie [hier](https://www.st.com/resource/en/user_manual/um2757-getting-started-with-xnucleo53l3a2-multi-target-ranging-tof-sensor-expansion-board-based-on-vl53l3cx-for-stm32-nucleo-stmicroelectronics.pdf) op pagina 5). Ook gebruikt deze development kit maar 3 ToF-sensoren (LEFT, CENTER, RIGHT) waar we in dit project er 5 gaan gebruiken (LEFT, CENTER, RIGHT, TOP, BOTTOM).

De veranderingen die we dus moeten doorvoeren is de manier waarop we de XSHUT pinnen gaan aansturen. Dit zal i.p.v. via de GPIO Expanders (die I²C verbinding hebben met de MCU) via gewone GPIO pinnen verlopen op de MCU.

Het desbetreffende bestand is *53l3a2.c* waarin we de wijzigingen gaan doorvoeren. De methode genaamd *int32_t VL53L3A2_ResetId(uint8_t DevNo, uint8_t state)* gaan we vervangen door een switch case waarin we de HAL bibliotheek gebruiken om de GPIO's op *state* te plaatsen.

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

!> Zoals de [documentatie](https://www.st.com/resource/en/user_manual/um2778-vl53l3cx-timeofflight-ranging-module-with-multi-object-detection-stmicroelectronics.pdf) ons voorschrijft gebruiken we de XSHUT pin om de ToF-sensor in HW-Standby te plaatsen. We gebruiken deze methode later in ons programma om de ToF-sensoren van een uniek adres te voorzien. We moeten dit dus voor elke XSHUT pin doen!

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

---- -->

----

## importeren include & src bestanden

Als laatste gaan we de bestanden importeren die het eigenlijke project tot leven brengen. Dit zijn al de bestanden die te vinden zijn onder de folder **Core/Inc** en **Core/Src**. We plaatsen al de bestanden van **Core/Inc** in de **include** folder en de **Core/Src** in de **src** folder. Dit zijn de bestanden:

* main.h
* custom_bus.h
* custom_conf.h
* custom_errno.h
* gpio.h
* i2c.h
* stm32f3xx_hal_conf.h
* stm32f3xx_it.h
* uart.h
* uart.c
* stm32f3xx_hal_msp.c
* system_stm32f3xx.c
* main.c
* syscalls.c
* sysmem.c
* custom_bus.c
* gpio.c
* i2c.c
* stm32f3xx_it.c

?> deze bestanden zijn wederom gegenereerd door STM32CubeIDE. Later wijzigen we nog enkelen.

----

## Importeer Andere Bestanden

Naast de gekregen API van ST, zijn er nog andere bestanden gegenereerd onder **CMSIS** en **STM32F3xx_HAL_Driver**.
Deze 2 bibliotheken zetten we elks apart in een bestand met een src map waarin we alle .h en .c bestanden plaatsen van die bibliotheek. We maken dus een folder **CMSIS** en een folder **STM32F3xx_HAL_Driver** met beiden een map **src**. Nu plaatsen we elk .c of .h bestand in de src folder van die bibliotheek.

De bestanden die het project tot leven brengen zijn nog niet geïmporteerd. We hebben een map [**Gesture_Detect**](https://github.com/RobbeElsermans/GestureControl/tree/main/Code%20PlatformIO/gesture%20Control%20Final/lib/Gesture_Detect/src) die we in de folder **lib** moeten plaatsen.

----

## Installeer Platform & Board

Om PlatformIO goed te kunnen gebruiken moeten we het platform **ST STM32** installeren zodat we de software kunnen compileren.

<div style="display:inline">
<img src="../foto's/platformio_platforms.jpg" alt="picture of monitor"width="25%">
<img src="../foto's/platformio_platforms_2.jpg" alt="picture of monitor" width="70%">
</div>
<!-- <img src="../foto's/platformio_platforms.jpg" alt="picture of monitor"
style=" display: block;
        margin-left: auto;
        margin-right: auto;"> -->

In de figuur (die linksboven afgebeeld is) is de 1<sup>ste</sup> kader, de kader om de dropdown te openen waarin we de 2<sup>de</sup> kader vinden. We selecteren hier *platforms*.

Nadien komen we op de figuur rechtsboven uit. We selecteren *Embedded* bovenaan en we zoeken naar *ST*. We zien dan in de lijst *ST STM32* verschijnen. Wanneer we hier op drukken, kunnen we het platform installeren met de juiste versie gebruikt in dit project (V15.2.0).

----

## configureer platformio.ini file

Het platform.ini bestand is een belangrijk bestand. Hierin wordt de configuratie van het project geplaatst.

Hieronder is de content dat je in dit bestand moet plaatsen.

``` platformio.ini
[env:custom_f302rct6]
platform = ststm32
board = custom_f302rct6
framework = stm32cube
test_transport = custom
monitor_speed = 115200
```

Met deze tekst stellen we in dat de compileerder het framework van *stm32cube* moet gebruiken. Zo worden de HAL-bibliotheken aangesproken. Ook wordt er gedefinieerde welk board dat we gebruiken. Voor debug redenen zal de baudrate ingesteld worden op 115200. Het voorafgaande platform dat geïnstalleerd is, plaatsen we hier ook in.

De test_transponder parameter is toegevoegd zodat we optimaal gebruik kunnen maken van Unit testing. De nodige bestanden hiervoor zijn **unittest_transport.c** & **unittest_transport.h** die onder de folder **test** gezet moet worden. [Hier](https://docs.platformio.org/en/stable/plus/unit-testing.html) is wat extra uitleg over wat dit nu juist doet en hoe het gebruikt moet worden.

Omdat we werken met de STM32F302RCT6, die (nog) niet ondersteund is door PlatformIO, moeten we hier onze eigen spin aan geven. Er wordt een bestand genaamd **custom_f302rct6.json** aangemaakt en het wordt in de folder **boards** geplaatst met volgende content:

``` json custom_f302rct6
{
  "build": {
    "core": "stm32",
    "cpu": "cortex-m4",
    "extra_flags": "-DSTM32F302xC",
    "f_cpu": "32000000L",
    "mcu": "stm32f302rc",
    "product_line": "STM32F302xC",
    "variant": "STM32F3xx/F302R(B-C-D-E)T"
  },
  "debug": {
    "default_tools": [
      "stlink"
    ],
    "jlink_device": "STM32F302RE",
    "openocd_target": "stm32f3x",
    "svd_path": "STM32F302x.svd"
  },
  "frameworks": [
    "arduino",
    "cmsis",
    "mbed",
    "stm32cube",
    "libopencm3",
    "zephyr"
  ],
  "name": "ST Nucleo F302RE (40k RAM. 256k Flash)",
  "upload": {
    "maximum_ram_size": 32768,
    "maximum_size": 262144,
    "protocol": "stlink",
    "protocols": [
      "jlink",
      "cmsis-dap",
      "stlink",
      "blackmagic",
      "mbed"
    ]
  },
  "url": "https://www.st.com/en/microcontrollers-microprocessors/stm32f302.html",
  "vendor": "ST"
  }
```

Voor meer informatie zie de [documentatie](https://docs.platformio.org/en/stable/platforms/creating_board.html).

----

## main.h & .c

Het main bestand bevat de code die we gebruiken voor de gesture controller. hieronder is een link die leid naar de bestanden op GitHub.

[main.h](https://github.com/RobbeElsermans/GestureControl/blob/main/Code%20PlatformIO/gesture%20Control%20Final/include/main.h)
[main.c](https://github.com/RobbeElsermans/GestureControl/blob/main/Code%20PlatformIO/gesture%20Control%20Final/src/main.c)

## Overzicht geïmporteerde bestanden

Hier is een schematische voorstelling hoe de bestanden structuur er uit ziet in PlatformIO

``` file structure
┏╸GestureControllerPlatformIO
┣┓ boards
┃┗╸ custom_f302rct6.json
┣┓ include
┃┗╸ (.h bestanden)
┣┓ lib
┃┣┓ BSP
┃┃┗┓ src
┃┃ ┗╸ (.h & .c bestanden)
┃┣┓ CMSIS
┃┃┗┓ src
┃┃ ┗╸ (.h bestanden)
┃┣┓ STM32F3xx_HAL_Driver
┃┃┗┓ src
┃┃ ┗╸ (.h & .c bestanden)
┃┗┓ Gesture_Detect
┃ ┗┓ src
┃  ┗╸ (.h & .c bestanden)
┣┓ python
┃┗╸ (data scripts)
┣┓ src
┃┗╸ (.h & .c bestanden)
┣┓ test
┃┗╸ (.h & .c bestanden)
┣╸ platformio.ini

```

----

## Build & Upload

Het project is nu compleet om gebuild en nadien geupload te worden naar het bordje.

![foto build & upload knop](foto's/platformio_platforms_3.jpg)

Op bovestaande foto is te zien dat we enkele knoppen ter beschikking hebben om zaken uit te voeren. Zo staat er naast het **huisje** een **vinkje** dat de code zal compileren.
Daarnaast staat een **pijl naar rechts** die de code zal uploaden.

----

# Hardware Opbouw

De gemaakte PCB V0.3 wordt op een plexi plaat gemonteerd zodat dit kan fungeren als een coverglas. In het [onderzoek document](Onderzoek.md) is meer informatie terug te vinden hoe we uiteindelijk bij deze opstelling geraakt zijn.

![foto opstelling](foto's/PCBV0.3_opstelling_trap_3.jpg)

Zoals beschreven in [PinOut](#pinout) zijn de SDA & SCL van I2C2 een plaats opgeschoven. Dit is makkelijk verholpen door de pads door te lussen die we voorzien hebben tijdens het PCB ontwerpen. We gaan daarom J19 met TP1 verbinden en J18 met TP2 verbinden. Ook halen we R38 en R37 van de PCB af.

![I2C verhelpen kicad](foto's/I2C_verhelping_Kicad.jpg)
<img src="foto's/I2C2%20verhelping.png" width="50%">

</div>

# LED Controller

<img src="foto's/Smart%20Object.jpg" width="70%">

In bovenstaande foto is te zien hoe we de Gesture Controller (Systeem B) aansluiten met de LED Controller. De communicatie verloopt over I²C waarbij de LED Controller de master is en de Gesture Controller de slave. 

Zoals beschreven in de [blueprint](https://github.com/RobbeElsermans/GestureControl/blob/main/docs/Documenten/Blueprint_V1.1_Robbe_Elsermans.pdf) (<a href="./Documenten/Blueprint_V1.1_Robbe_Elsermans.pdf" download>download</a>) zal de master een commando versturen *(0x01)* waarop de slave een aantal commando's kan terug sturen.

* **0x10** -> Geen object aanwezig
* **0x20** -> Een object aanwezig
* **0x21** -> Er is in de afgelopen 3 seconden een gesture geweest die van links naar rechts ging.
* **0x22** -> Er is in de afgelopen 3 seconden een gesture geweest die van recht naar links ging.
* **0x23** -> Er is in de afgelopen 3 seconden een gesture geweest die van boven naar onder ging.
* **0x24** -> Er is in de afgelopen 3 seconden een gesture geweest die van onder naar boven ging.
* **0x25** -> Er is een hand op en neer aan het bewegen. Dit wordt gevolgd door een waarde van 10-bits groot. (0->1024)
* **0x26** -> ... 

De LED Controller heeft uiteraard een LED Matrix waarop hij de uitgeoefende commando's kan uitbeelden d.m.v. een dot op de matrix die beweegt te gevolgen van het commando. We gebruiken hiervoor [deze](https://docs.rs-online.com/9319/0900766b814a9f89.pdf) led matrix die we connecteren met een NUCLEO_F401RE die zich gedraagt als LED-Controller.

# Bevindingen & Upgrades 

Het project is gestart met een idee waar een mogelijke toekomst in zit. Omdat dit project vanaf 0 is opgestart, is het op dit moment ook niet marktwaardig. De genomen beslissingen kunnen nog in twijfel genomen worden net zoals de geschreven software. Dit project is ontwikkeld om aan te tonen dat er toekomst in zit mits het verdere onderzoeken.

Zo zijn er enkele zaken die ik tijdens het maken van het project heb ondervonden.

De genomen sensor VL53L3CX is een mogelijke kandidaat om gesture te detecteren. Enkel bestaat er een ToF-sensor die misschien nog beter geschikt is namelijk de [VL53L1X](https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html). 

Deze sensor zijn kijkveld kunnen we opdelen in 2 aparte kijkvelden. Dit is ideaal om gesture detectie uit te voeren. De sensor heeft ook een ingebouwde MCU die al de data verwerkt (in tegenstelling tot de VL53L3CX die dit niet heeft) zodat de host hier minder rekenkracht moet uitvoeren. ST heeft voor deze sensor ook een ULD (Ultra-Low Driver) API gemaakt.

Dit project ging enkel over ToF-sensoren. uiteraard zijn dit niet de enige sensoren waarmee we dit kunnen doen. Zo bestaat er een druksensor genaamd ILPS22QS die een waardige tegenhanger kan zijn om de gestures te detecteren. Omdat deze een nauwkeurigheid heeft van 0.5hPa, is het mogelijk om voorbijgaande zaken te detecteren. Dit zou, in combinatie met de ToF-sensor, de gestures kunnen herkennen.

Op gebied van software kan er ook geëxperimenteerd worden met Machine Learning. We werken tenslotte met data. Op deze manier kunnen we met genoeg data, een model creëren die nog beter de verschillende gestures kan onderscheiden van elkaar. 

De genomen eindpositie waarin de sensoren staan, zijn niet perfect. Het geef een weergaven van hoe we met 3 sensoren de x & y as kunnen monitororen. In een latere fase kan hier een aparte studie over gedaan worden om de ideale opstelling te bedenken.

# Onderzoek
[link](Onderzoek.md)