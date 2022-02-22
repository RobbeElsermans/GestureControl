---
pagetitle: Release Notes for 53L3A2 BSP 
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for <mark>53L3A2</mark> BSP
Copyright &copy; 2021 STMicroelectronics\
    
[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>

# License

This software component is licensed by ST under BSD 3-Clause, the "License"; You may not use this component except in compliance with the License. You may obtain a copy of the License at:

[BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause)

# Purpose

The **53L3A2 BSP** is a software component intenteded to be used within the **STM32Cube** ecosystem. This software implements the BSP v2.0 specifications for the X-NUCLEO-53L3A2 Expansion Board on STM32. It is built on top of STM32Cube software technology that ease portability across different STM32 micro-controllers. 

Here is the list of references:

- [X-NUCLEO-53L3A2: Multi-targets ranging sensor expansion board based on VL53L3CX for STM32 Nucleo](https://www.st.com/content/st_com/en/products/ecosystems/stm32-open-development-environment/stm32-nucleo-expansion-boards/stm32-ode-sense-hw/x-nucleo-53l3a2.html)
- [VL53L3CX: Time-of-Flight ranging sensor with multi target detection](https://www.st.com/content/st_com/en/products/imaging-and-photonics-solutions/proximity-sensors/vl53l3cx.html)
- [VL53L3CX-SATEL: Breakout board with VL53L3CX multi-target detection](https://www.st.com/content/st_com/en/products/evaluation-tools/product-evaluation-tools/proximity-sensors-and-imaging-ics-eval-boards/vl53l3cx-satel.html)

:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section2" checked aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">__v2.0.1 / January 12th 2022__</label>
<div>			

## Main Changes

### Maintenance release and product update

- Update component used by the BSP ranging sensor class

## Contents
<small>The components flagged by "[]{.icon-st-update}" have changed since the
previous release. "[]{.icon-st-add}" are new.</small>

Components

  Name                                                        Version                                           License                                                                                                       Release note
  ----------------------------------------------------------- ------------------------------------------------- ------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------------------------
  **X-NUCLEO-53L3A2 BSP Driver**                                                     V2.0.1[]{.icon-st-update}                                            [BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause)                                                [release note](.\Release_Notes.html)

Note: in the table above, components **highlighted** have changed since previous release.

## Known Limitations


  Headline
  ----------------------------------------------------------
  No known limitations

## Development Toolchains and Compilers

- IAR System Workbench V8.50.9
- ARM Keil V5.32
- STM32CubeIDE v1.7.0

## Supported Devices and Boards

- X-NUCLEO-53L3A2
- VL53L3CX-SATEL

## Backward Compatibility

N/A

## Dependencies

This software release is compatible with:

- VL53L3CX Component Driver v2.0.1
- STM32CubeHAL F4 V1.7.13
- STM32CubeHAL L4 V1.13.0

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section2" checked aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">__v2.0.0 / July 1st 2021__</label>
<div>			

## Main Changes

### Maintenance release and product update

- Update data structures accordingly to the new BSP ranging sensor class
  - It is now possible to enable and disable ambient and signal output in RANGING_SENSOR_ConfigProfile_t
  - The sensor's measurement data are now stored in a different way which will ease portability of your application from one Time-of-Flight device to another
- Fix typos and other minor changes

## Contents
<small>The components flagged by "[]{.icon-st-update}" have changed since the
previous release. "[]{.icon-st-add}" are new.</small>

Components

  Name                                                        Version                                           License                                                                                                       Release note
  ----------------------------------------------------------- ------------------------------------------------- ------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------------------------
  **X-NUCLEO-53L3A2 BSP Driver**                                                     V2.0.0[]{.icon-st-add}                                            [BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause)                                                [release note](.\Release_Notes.html)

Note: in the table above, components **highlighted** have changed since previous release.

## Known Limitations


  Headline
  ----------------------------------------------------------
  No known limitations

## Development Toolchains and Compilers

- IAR System Workbench V8.50.9
- ARM Keil V5.32
- STM32CubeIDE v1.6.1

## Supported Devices and Boards

- X-NUCLEO-53L3A2
- VL53L3CX-SATEL

## Backward Compatibility

N/A

## Dependencies

This software release is compatible with:

- VL53L3CX Component Driver v2.0.0
- STM32CubeHAL F4 V1.7.12
- STM32CubeHAL L4 V1.13.0

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__v1.0.0 / March 15th 2021__</label>
<div>			

## Main Changes

### First release

This is the first release of the **53L3A2 BSP** Driver.

## Contents
<small>The components flagged by "[]{.icon-st-update}" have changed since the
previous release. "[]{.icon-st-add}" are new.</small>

Components

  Name                                                        Version                                           License                                                                                                       Release note
  ----------------------------------------------------------- ------------------------------------------------- ------------------------------------------------------------------------------------------------------------- ------------------------------------------------------------------------------------------------------------------------------------------------
  **X-NUCLEO-53L3A2 BSP Driver**                                                     V1.0.0[]{.icon-st-add}                                            [BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause)                                                [release note](.\Release_Notes.html)

Note: in the table above, components **highlighted** have changed since previous release.

## Known Limitations


  Headline
  ----------------------------------------------------------
  No known limitations

## Development Toolchains and Compilers

- IAR System Workbench V8.50.5
- ARM Keil V5.31
- STM32CubeIDE v1.6.0

## Supported Devices and Boards

- X-NUCLEO-53L3A2
- VL53L3CX-SATEL

## Backward Compatibility

N/A

## Dependencies

This software release is compatible with:

- VL53L3CX Component Driver v1.0.0

</div>
:::

:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
For complete documentation on **STM32Cube Expansion Packages** ,
visit: [STM32Cube Expansion Packages](https://www.st.com/en/embedded-software/stm32cube-expansion-packages.html)
:::
::: {.column width="5%"}
<abbr title="Based on template cx566953 version 2.0">Info</abbr>
:::
:::
</footer>
