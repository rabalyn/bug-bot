# Bug-Bot

## Setup

install libraries via arduino ide:
  - v1.1.4 Servo library by Michael Margolis, Arduino (https://www.arduino.cc/en/Reference/Servo)
  - v2.0.0 Bifrost library for HC-SR04 by Jeremy Lindsay (https://github.com/jeremylindsayni/Bifrost.Arduino.Sensors.HCSR04)
    - In the `$arduino_libraries/Bifrost_library_for_HC-SR04/src/hcsr04.cpp` file I had to edit the 2nd line from 
    ```
    #include "HCSR04.h"
    ```

    to

    ```
    #include "hcsr04.h"
    ```
