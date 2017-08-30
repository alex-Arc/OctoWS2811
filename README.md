OctoWS2811 (or ??HexaWS2811??)
==========
## !!warning WIP!!
this code has only been tested on a Teensy 3.6 and to a very small degree

outputs 16 LED channels to the first 8 pins on port C and D

### in uses:
- FTM1 (don't use pin 3 and 4 as PWM)
- FTM2 (don't use pin 29 and 30 as PWM)
- PTB0 (PIN 16) (maybe it's okay to use this pin)
- 6 DMA channels

Control thousands of WS2811/2812 LEDs at video refresh speeds

http://www.pjrc.com/teensy/td_libs_OctoWS2811.html

https://www.youtube.com/watch?v=M5XQLvFPcBM
