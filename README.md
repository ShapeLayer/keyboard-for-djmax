# Keyboard for DJMAX RESPECT V

_A project task for &lt;IoT Computing&gt; lecture in computer engineering undergraduate course program._

A keyboard for a PC rhythm game, like DJMAX RESPECT V, EZ2ON, etc that supports key input of up to 10 keys, a knob module(usual rotary encoder), and an I2C OLED display module.

## Getting Started

The controller sketch is designed to have compatibility with any Arduino board that supports the `Keyboard` library like Arduino Leonardo.

However, only Arduino Leonardo has been implemented and tested in reality. So it is recommended to use Arduino Leonardo for this project.

### Hardware Requirements
- Arduino board supports `Keyboard` library  
- 10x switches  
    _(If there aren't enough keyboard key switches, you can use push buttons)_
- 1x rotary encoder (with push button)
- 1x I2C OLED display module  
    _(I used a 128x32 pixels OLED display. If you use a different size, you may need to adjust the display code.)_

A controller processes the key input designed as a 5x2 key matrix. You have to implement the key matrix circuit. The circuit diagram I used is available in the [`circuits`](./circuits/) directory.

### Printing the Case

If you want to print the case, you can find the 3D model files in the [`models`](./models/) directory.

### Software Requirements

- [u8g2 library](https://github.com/olikraus/u8g2) for OLED display  
    Install it through Arduino Library Manager in Arduino IDE. or refer [`INSTALL.ps1`](./INSTALL.ps1)  
- Configuration
    - [`controller/config.h`](./controller/config.h)  
        Configure the pin numbers of the switches, key output mapping, and others.
