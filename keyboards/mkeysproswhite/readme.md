# Cooler Master Masterkeys Pro S White QMK firmware

A simple ANSI TKL with per-key white LED lighting.

* Keyboard Maintainer: [m-radomski](https://github.com/m-radomski)
* Hardware Supported: Pro S White

## Status

What works:

- Basic keyboard functions
- Layers
- 6KRO

What does not yet still work:

- Lighting

## Compilation

This step if very important, failing to do it might **brick your keyboard**!
Apply the ChibiOS patch (make sure you are in the root of the project!):

```
cd lib/chibios
git apply < ../../keyboards/mkeysproswhite/patches/chibios.patch
cd ../..
```

Now to compile the default keymap simply do:

```
make mkeysproswhite:default
```

## Flashing

To install the firmware it's recommended to use [pok3rtool](https://github.com/pok3r-custom/pok3rtool).
More information will follow...

To easily reflash the keyboard press both shifts (left and right) and b at the same time.
This puts the keyboard into it's bootloader which allows for reprogramming with the pok3rtool.

## Why is the patch needed?

ChibiOS startup files will align ARM reset vectors to a 1024 byte boundry.
Masterkeys keyboards have their firmware starting at the address 0x3200 - not a multiple of 0x400.
If this patch is not applied everything will be shifted over and keyboard won't boot which might require manual JTAG reflashing.
