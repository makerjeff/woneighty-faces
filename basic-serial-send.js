/**
 * Created by jeffersonwu on 5/4/16.
 */

var colors = require('colors');
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;

var portName = process.argv[2]; //port ####
var value = process.argv[3];    //wait 5 seconds

var myPort = new SerialPort(portName, {
    baudRate: 9600,
    parser: serialport.parsers.readline('\n')
});

console.log(colors.green('serial listener started on ' + portName));

// == event listeners ==
myPort.on('open', showPortOpen);
//myPort.on('data', sendSerialData);    //creates an endless loop, because arduino pings.
myPort.on('close', showPortClose);
myPort.on('error', showError);

// == functions ==
function showPortOpen() {
    console.log('serverPort open. Data rate: ' + myPort.options.baudRate);
}

function sendSerialData(data){
    console.log('data: '.blue + data);

    myPort.write('100;', function(error, bytesWritten){
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

// serialSendTest function
function serialSendTest() {

    var value = Math.floor(Math.random() * 255) + ';';

    myPort.write(value, function(error, bytesWritten){
        if(error) {
            return console.log('error: '.red + error.message);
        } else {
            console.log('sending: ' + bytesWritten + ' bytes, value: ' + value);
        }
    });
}

var timer = setInterval(serialSendTest, 100);