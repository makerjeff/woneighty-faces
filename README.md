#180 Faces Hardware

Based off of Node Serial experiments <br>

###Instructions
1. Run server with 'nodemon app.js (server port number) (serial port) (network IP)' 

	- example: 'nodemon app.js 3000 /dev/ttyUSB0 XX.XX.XX.XXX'

###Technologies
- Express
- Jade **(new)** (for socket.io namespace exploration)
- Colors
- [Socket.io](http://socket.io/)
- [Serialport](https://www.npmjs.com/package/serialport)
- [Node Checksum](https://www.npmjs.com/package/checksum)


###Tutorials Base

1. [NYU: ITP](https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-communication-with-node-js/)<br>
2. [Tigoe: Serial to Browser using NODE.JS](http://www.tigoe.com/pcomp/code/arduinowiring/1096/) (doesn't work out of the box)
3. [ITP: NYU: Node-Arduino tutorial](https://itp.nyu.edu/physcomp/labs/labs-serial-communication/lab-serial-control-of-an-arduino/)
4. [Node 4: Buffer Objects](https://nodejs.org/dist/latest-v4.x/docs/api/buffer.html#buffer_new_buffer_str_encoding) **(NEW)**

###NOTES
- the SIO-SERVER.JS writes messages to other users, while dropping your message in locally.
- switching data packet to be an object vs. string.
- Latest version of Jade is now Pug! Rolling back to version ^1.1.0 **(NEW)**
- The Arduino is on port **/dev/ttyUSB0** and not **/dev/ttyAMA0** !


###Arduino Notes
- 9G Microservo draws 0.250a 0.600a of current at 5v.
- Serial.write() artificially slows down servo position updating.
- Writing to serial:
    - Serial.write(48); ASCII 48 = SYMBOL 0.
    - Serial.write("write my string"); Sends the proper symbols for included characters.
    - Serial.write(myCharString); requires declaring a char array with terminal null char:
        - char myCharString[] = {'m','e','s','s','a','g','e', '\r', '\n', '\0'};
- SerialMonitor's 'new line' drop down controls the SENDING of values, not display.
- Serial.write(inByte) writes out the actual character.
- Serial.print(inByte) writes ou the ASCII character ## (char code)
- **Serial.SetTimeout() DO NOT USE for direct connection through terminal!  Times out before you can finish inputting the values.**