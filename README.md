# Anti-Derivative-Digital-Distortion

# Author

Nezar Saba

# About

Digital implementation of a distortion pedal.
There are three modes controlled by the toggle switch.
All signal processing code is written by me, the only dependency is LibDaisy for the Diasy Seed dev board slotted into the PCB.

Left position: Ibanez Tube Screamer
Middle Position: Electro-Harmonix Big Muff
Right position: Boss HM-2

I based my filter designs on the frequency response and schematic of these pedals and made a few changes to my liking, and to make it a bit unique and a bit my own.

# Random info abut the pedal in no particular order

96k sample rate
supports latching as well as momentary footswitches
has input voltage protection
Implments audio bypass using a relay
power does not need to be plugged in for the guitar signal to pass through the pedal
4 layer PCB signal-pwr / GND / GND / signal-pwr
All through hole coomponents supports repairability
anti-alising input and output filters.
->in case someone puts another distorion pedal before this pedal
->if input voltage is too large it will clip and this filter will stop aliasing from the protection
->since sample rate is 96k it could cause alisaing if later sampled by a system with a 44.1k/48k sample rate
->both filters are second order sallen-key filters