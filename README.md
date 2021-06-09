Tutorial Link: https://create.arduino.cc/projecthub/taunoerik/programming-attiny13-with-arduino-uno-07beba

-Turn the Arduino into a AVRISP:  Open Arduino IDE -> File -> Examples -> 11.ArduinoISP ->ArduinoISP and upload to Arduino

-Link for adding ATtiny board in boards manager of arduino:  https://mcudude.github.io/MicroCore/package_MCUdude_MicroCore_index.json

-install Micro Core board

-Connect the hardware

    ATtiny13A leg 1 -> Arduino 10
    ATtiny13A leg 5 -> Arduino 11
    ATtiny13A leg 6 -> Arduino 12
    ATtiny13A leg 7 -> Arduino 13
    ATtiny13A leg 8 -> 5v
    ATtiny13A leg 4 -> Ground (GND) 

-Arduino IDE settings

-Go to Arduino IDE -> Tools and select:

    Board: ATtiny 13
    BOD: 4.3v
    Clock: 1.2 MHz internal osc.
    Compiler LTO: Enable
    Port: (Your Arduino port)
    Programmer: Arduino as ISP

- Burn Bootloader

- Finally upload the required sketch: Go to: Arduino IDE -> Sketch -> Upload Using Programmer