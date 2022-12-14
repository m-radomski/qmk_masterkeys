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

To compile the default keymap simply do:

```
make mkeysproswhite:default
```

## Flashing

To install the firmware it's recommended to use [pok3rtool](https://github.com/pok3r-custom/pok3rtool).
More information will follow...

To easily reflash the keyboard press both shifts (left and right) and b at the same time.
This puts the keyboard into it's bootloader which allows for reprogramming with the pok3rtool.
