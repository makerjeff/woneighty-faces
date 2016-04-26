/**
 * 180 Faces - Hardware Interface
 * Created by jefferson.wu on 4/11/16.
 * Namespaced + Jade
 *
 * TODO: Jade template
 * TODO: Fix Arduino connection on Pi.
 */

// SOCKET.IO BOILERPLATE
var express = require('express');
var http = require('http');
var app = express();
var server = http.createServer(app);
var io = require('socket.io')(server);
// SOCKET.IO BOILERPLATE - END

var jade = require('jade');
var colors = require('colors');

//serialport related
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;
var portName = process.argv[3];
var portConfig = {
    baudRate: 9600,
    //calls myPort.on('data') when a newline is received
    parser: serialport.parsers.readline('\n')
};

//open the serial port
var myPort = new SerialPort(portName, portConfig);

myPort.on('open', function(){
    console.log('serial port opened, please wait 3 seconds');
});

// MIDDLEWARE
app.use(express.static(__dirname + '/public'));
app.set('view engine', 'jade');

// GLOBALS
var allClients = [];
var port = process.argv[2];
var rgbHolder = {red: 0, green: 0, blue: 0};


// ROUTES
app.get('/', function(request, response){
    response.type('text/html');
    response.sendFile(__dirname + '/public/ns-servo-tester.html');
});

/*SOCKET.IO NAMESPACE*/
var namespaceString = 'servo';
var nsp = io.of('/' + namespaceString);

nsp.on('connection', function(socket){
    console.log(socket.client.id.toString().blue + ' has connected to namespace: ' + namespaceString);

    //work that servo (has to be under the namespace)
    socket.on('servoData', function(data){
        console.log('Message received: ' + data);
        myPort.write(data);
    });
});
/*SOCKET.IO NAMESPACE - END */

/*SOCKET.IO*/
io.on('connection', function(socket){
    allClients.push(socket);
    console.log(socket.client.id.toString().blue + ' connected');

    numberOfClients(allClients);

    //greeting message, fired at the beginning
    socket.emit('message', 'welcome message!');

    // ==== SOCKET EVENTS ====

    //on receiving of data
    socket.on('data', function(data){
        var stringObject = data;
        var dataObject = JSON.parse(stringObject);
        console.log(socket.client.id.toString().green + ': ' + dataObject.head + ', ' + dataObject.body);

        //set the color
        if(dataObject.head.toString() == 'slider1'){
            rgbHolder.red = dataObject.body;
        }
        else if(dataObject.head.toString() == 'slider2'){
            rgbHolder.green = dataObject.body;
        }
        else if(dataObject.head.toString() == 'slider3'){
            rgbHolder.blue = dataObject.body;
        }

        console.log(rgbHolder);
        //console.log(socket.client.id.toString().green + ': ' + dataObject.head + ', ' + dataObject.body);

        //send to view
        socket.broadcast.emit('viewUpdate', JSON.stringify(rgbHolder));
    });

    //on disconnect
    socket.on('disconnect', function(){
        console.log(socket.client.id.toString().red + ' disconnected');
        allClients.splice(allClients.indexOf(socket.client.id), 1);
        //console.log(allClients);
        numberOfClients(allClients);

        //reset the color on exit
        rgbHolder.red = 0;
        rgbHolder.green = 0;
        rgbHolder.blue = 0;

        console.log(rgbHolder);
    });

    // ==== SOCKET EVENTS - END ====
});

initServer(port);

// ==== HELPER FUNCTIONS ====
//TODO: move these to /helpers

function initServer(port){
    var serverPort = port || 3000;  //if no port, default to 3000
    server.listen(serverPort);
    console.log('Starting server on port ' + serverPort.rainbow);
}

function initSerialPort(){
    console.log('port open');
    console.log('baud rate: ' + myPort.options.baudRate);
}

/**
 * Return and log to console the number of connected clients.
 * @param allClientsArr The 'allClients' array
 */
function numberOfClients(allClientsArr){
    console.log('Total clients: ' + allClientsArr.length);
    return allClientsArr.length;
}

function updateViewer(dataObject){
}

