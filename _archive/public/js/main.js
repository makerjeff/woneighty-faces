/** MAIN.JS
 * Created by jefferson.wu on 1/7/16.
 */

// SOCKET.IO FUNCTIONALITY
//var socket = io.connect();   //Lynda.com tutorial erroneous, asks for "io('localhost:3000');
var socket = io('localhost:3000');

//built-in disconnect event
socket.on('disconnect', function(){
    setTitle("Disconnected");
});

//built-in connection event
socket.on('connect', function(socket){
    setTitle("Connected to CyberChat!");
});

//custom message event
socket.on('message', function(message){
    printMessage(message);
});


// BASIC FORM MANIPULATION
document.forms[0].onsubmit = function() {
    var input = document.getElementById('message');

    //after user submits form, emit that message.
    socket.emit('chat', input.value);

    //print to local message area (doesn't go through server)
    printMessage('you: ' + input.value);
    input.value = '';
};

// FORM HELPER FUNCTIONS
function setTitle(title){
    document.querySelector('h1').innerHTML = title;
}

/**
 * Print Message
 * Append messages to a certain div without having to store into an array.
 * @param message String: Message to Print
 */
function printMessage(message){
    var p = document.createElement('p');
    p.innerText = message;
    document.querySelector('div.messages').appendChild(p);
}
