# chprothrottle
Arduino code to run a gameport edition CH Products Pro Throttle under Windows via USB

CH Products Pro Throttle v1.0

 NOTE: This sketch file is for use with Arduino Leonardo and
       Arduino Micro only. To USE the four buttons (non-hat) you
       must bypass the internal diodes inside the throttle.
       Before uploading, you must install the Joystick library from
       https://github.com/MHeironimus/ArduinoJoystickLibrary

To implememnt hardware, just unplug the cable coming from the stick and plug directly into the Arduino micro on pins 2-10.
For Analog throttle support, run the Arduino 5v and Ground pins to the 2 outter lugs of the potentimer, and Analog 3 pin to center lug.
