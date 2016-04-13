/**
 * 180 Faces - Hardware Interface
 * Created by jefferson.wu on 4/11/16.
 */

// SOCKET.IO BOILERPLATE
var express = require('express');
var http = require('http');
var app = express();
var server = http.createServer(app);
var io = require('socket.io')(server);
// SOCKET.IO BOILERPLATE - END

var colors = require('colors');

// MIDDLEWARE
app.use(express.static(__dirname + '/public'));

// GLOBALS
var allClients = [];
var port = process.argv[2];

// ROUTES
app.get('/debug', function(request, response){
    response.type('text/html');
    response.sendFile(__dirname + '/public/debug.html');
});

// SOCKET.IO
io.on('connection', function(socket){
    allClients.push(socket);
    console.log(socket.client.id.toString().blue + ' connected');

    numberOfClients(allClients);

    //greeting message, fired at the beginning
    socket.emit('message', 'welcome message!');

    // ==== SOCKET EVENTS ====

    //on receiving of data
    socket.on('data', function(message){
        var stringObject = message;
        var dataObject = JSON.parse(stringObject);
        console.log(socket.client.id.toString().green + ': ' + dataObject.head + ', ' + dataObject.body);
    });

    //on disconnect
    socket.on('disconnect', function(){
        console.log(socket.client.id.toString().red + ' disconnected');
        allClients.splice(allClients.indexOf(socket.client.id), 1);
        //console.log(allClients);
        numberOfClients(allClients);
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

/**
 * Return and log to console the number of connected clients.
 * @param allClientsArr The 'allClients' array
 */
function numberOfClients(allClientsArr){
    console.log('Total clients: ' + allClientsArr.length);
    return allClientsArr.length;
}

