/**
 * DATA SENDER HELPERS
 * Created by jefferson.wu on 4/13/16.
 */

/**
 * Sends object to the backend via socket messages.
 * @param head Head of the object; Identifier.
 * @param body Body of the object; Data value or values to send.
 */
var dataSender = function(head, body){
    this.dataObject = {head: head, body:body};
    this.dataString = JSON.stringify(this.dataObject);
};

/**
 * Fire the LAYSERS!
 */
dataSender.prototype.send = function(){
    console.log(this.dataObject);
    socket.emit('data', this.dataString);
};