# arduino-cool
This repository is for my personal learning journey with learning how to use Arduino and a little bit of C++<br>
I don't have much prior experience, especially when it comes to programming, so right now a lot of the concepts I am learning are very new to me. However, so far, it has been really interesting, and I'm having a lot of fun. I definitely want to learn more about coding
# Building - Software
To build and run the files as is, you will need to use the Arduino IDE.<br>
I am using Arduino IDE 2.1.2. The download and documentation can be found on their website [here.](https://docs.arduino.cc/software/ide-v2)<br>
If you want to use it with a different IDE, you'll probably have to figure out how to get it to compile yourself.<br>
I haven't tried it myself (because I don't know how to do so), but to my knowledge you'd need to adjust things in the original code. If you know what you're doing it's fine, but for the most case, it's probably just best to run it through the Arduino IDE (just in case).
# Hardware details
This code has *only* been tested with the circuit components that I currently have, meaning that it has **not** been tested with other boards or modules.<br>
While it should theoretically work if you're using components that are similar enough, I can't assure anything, so please be careful. <br>
Board: [Arduino Nano](https://docs.arduino.cc/hardware/nano)<br>
Joystick Module: [keyestudio Joystick Module](https://wiki.keyestudio.com/Ks0008_keyestudio_Joystick_Module) (but it's basically just 2 potentiometers + a push button)
# Wiring Instructions
- Wire Joycon Z or momentary push button between a Digital I/O pin.<br>
- Wire Joycon X and Y pins into seperate Analog pins.<br>
- Wire the joycon positive and ground pins into the Nano's 5V and Ground pins<br>
- You can use the internal pullup resistor or use your ow pullup resistor between the digital pin if you want, but you might have to adjust either the pinMode input or the digitalRead<br>
- So far I've just been using the Arduino's power via the computer, I haven't tested with external power sources yet
# Disclaimedr
Be safe and smart , I highly reccomend to **not** follow what I am doing especially when it comes to the hardware Because I am definitely not qualified xoxo
