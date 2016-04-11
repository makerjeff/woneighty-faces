/** Socket.IO Server (Lynda tutorial)
 * A properly documented Socket.IO project.
 * Created by jefferson.wu on 1/7/16.
 *
 */

// SOCKET.IO BOILERPLATE
var express = require('express');
var http = require('http');
var app = express();
var server = http.createServer(app);
var io = require('socket.io')(server);
// SOCKET.IO BOILERPLATE - END

// static serving middleware
app.use(express.static(__dirname + '/public'));


//hold the total number of clients
var allClients = [];

//
io.on('connection', function(socket){


    allClients.push(socket);

    console.log(socket.client.id + ' connected');
    //console.log(allClients);

    //on receiving chat message
    socket.on('chat', function(message){

        //broadcast to all
        socket.broadcast.emit('message', socket.client.id + ': ' + message);
        console.log(socket.client.id + ': ' + message);
    });

    //greeting message, fired at the beginning (and when server is reset)
    socket.emit('message', 'welcome to CyberChat!');

    socket.on('disconnect', function(){
        console.log(socket.client.id + ' got disconnected');


    });
});

server.listen(3000);
console.log('Starting Socket App = http://localhost:3000');