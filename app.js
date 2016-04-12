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

// serve static pages
app.use(express.static(__dirname + '/public'));



