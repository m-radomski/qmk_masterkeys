# Cooler Master Masterkeys Pro S White QMK firmware

A simple ANSI TKL with per-key white LED lighting.

* Keyboard Maintainer: [mateuszradomski](https://github.com/mateuszradomski)
* Hardware Supported: Pro S White

## Status

What works:

- Basic keyboard functions
- Layers
- 6KRO
- Lighting

Small inconvinences:

- Lighting configuration not saved in SPI, reset at each power on

## Compilation

This step if very important, failing to do it might **brick your keyboard**!
Apply the ChibiOS and ChibiOS-contrib patch (make sure you are in the root of the project!):

```
cd lib/chibios
git apply < ../../keyboards/mkeysproswhite/patches/chibios.patch
cd ../../lib/chibios-contrib
git apply < ../../keyboards/mkeysproswhite/patches/chibios_contrib.patch
cd ../..
```

Now to compile the default keymap simply do:

```
make mkeysproswhite:default
```

## Flashing

To install the firmware it's recommended to use [pok3rtool](https://github.com/pok3r-custom/pok3rtool).
For more information checkout [re-masterkey](https://github.com/mateuszradomski/re-masterkeys).

To easily reflash the keyboard press both shifts (left and right) and b at the same time.
This puts the keyboard into it's bootloader which allows for reprogramming with the pok3rtool.

## Why is the patch needed?

ChibiOS startup files will align ARM reset vectors to a 1024 byte boundary.
Masterkeys keyboards have their firmware starting at the address 0x3200 - not a multiple of 0x400.
If this patch is not applied everything will be shifted over and keyboard won't boot which might require manual JTAG reflashing.

The second patch fixes a coding mistake in the contribution repo of ChibiOS for Holtek chips.
This error is already fixed in the master branch of chibios-contrib, although the main qmk-firmware repo did not rebase that submodule for some time now.
