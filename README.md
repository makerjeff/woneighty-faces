#180 Faces Hardware

Based off of Node Serial experiments <br>

###Instructions
1. Run server with 'nodemon app.js (server port number) (serial port)' 

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