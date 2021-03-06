// NODE.JS > servo test
//opening the serial serverPort, send basic data

var serialport = require('serialport');
var colors = require('colors');
var SerialPort = serialport.SerialPort;

//get serverPort from command line
var portName = process.argv[2];
var value = process.argv[3];

//read from serverPort until a '\n' newline character
var myPort = new SerialPort(portName, {
    baudRate: 9600,
    //look for return and newline at the end of each 'data packet'
    parser: serialport.parsers.readline('\n')
});
console.log(colors.green('serial listener started on ' + portName));

// == Event Listeners ==

myPort.on('open', showPortOpen);
myPort.on('data', sendSerialData);
myPort.on('close', showPortClose);
myPort.on('error', showError);

// == Custom Functions ==
function showPortOpen() {
    console.log('serverPort open. Data rate: ' + myPort.options.baudRate);
}

function sendSerialData(data) {
    console.log('data: '.blue + data);

    myPort.write(33, function(error, bytesWritten){
        if(error){
            return console.log('error: ' + error.message);
        } else {
            console.log('sending: ' + bytesWritten);
        }
    });
}

function showPortClose() {
    console.log('serverPort closed.');
}

function showError(error) {
    console.log('Serial serverPort error: ' + error);
}

//run this

