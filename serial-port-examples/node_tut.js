// NODE.JS > node tutorial
//opening the serial port, send basic data
//TODO: implement into servo controller

//serial port initializations
var serialport = require('serialport');
var colors = require('colors');
var SerialPort = serialport.SerialPort;
var portName = process.argv[2];
var portConfig = {
    baudRate: 9600,
    //calls myPort.on('data') when a newline is received
    parser: serialport.parsers.readline('\n')
};

//open the serial port
var myPort = new SerialPort(portName, portConfig);

myPort.on('open', openPort);

// function definitions
function openPort(){
    var servoVal = 10;

    var keys = ['q', 'w', 'e','r','t','r','e','w']; //THIS WORKS!!! in conjunction with 'nodeTut()' on arduino side.
    var keysIndex = 0;

    console.log('port open');
    console.log('baud rate: ' + myPort.options.baudRate);

    //local function for sending data, since you only send data when port is open
    function sendData(){
        //convert value to ascii string before sending
        myPort.write(keys[keysIndex].toString());

        console.log('Sending ' + keys[keysIndex] + ' out the serial port');

        //increment index
        if(keysIndex < keys.length-1){
            keysIndex = keysIndex + 1;
        }
        else {
            keysIndex = 0;
        }



    }
    //set interval to update servo val 2x per second
    setInterval(sendData, 500);
}