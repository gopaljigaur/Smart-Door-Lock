# Smart Door Lock

This is a protoype for door lock system which logs the door lock and unlock events for increased surveillance and security. The circuit diagram is included in `.\Circuit` folder. We have used microcontroller 8051 for the door lock system and a NodeMCU for sending the data to database. We referred to [http://www.firmcodes.com](http://www.firmcodes.com/microcontrollers/8051-3/password-based-door-locking-system-8051/) for the circuit and 8051 codes.

The modifications include:
* We used a servo motor instead of a motor driver for the door locking and unocking system
* We interfaced a NodeMCU (ESP8266) board for the WiFi capabilities
* We added the functionality to change the passkey form the keypad itself after entering the secret password changing passphrase.

Whenever the door is locked, unlocked or the password for the lock is changed, the NodeMCU is triggered and it logs the current date and time to the Firebase Realtime Database. This databse is monitored by and Android application for the door lock system. The event times of latest lock, unlock and password reset can be viwed by the user on the application.

To implement this project for your own personal use follow these steps:
1. Create your [Firebase account](https://firebase.google.com/docs/database).
2. Create a new project and navigate to realtime database.
3. Obtain the Firebase Database Secret key and your realtime database links.
4. Add the Secret key and database links in the `doorlock.ino` file. Also add your WiFi SSID and password to which the doorlock will connect to.
5. Now open the `main.c` file in `.\8051 Codes` and edit line `unsigned char cc[5]={"ABCCD"};` to set your own secret passphrase. Enter this passphrase whenever you need to change the password. Default password is **00000**
