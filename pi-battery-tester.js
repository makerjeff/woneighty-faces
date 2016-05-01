/**
 * Created by jeffersonwu on 4/30/16.
 */

var fs = require('fs');
var colors = require('colors');


// FUNCTIONS

var BatteryTester = {
    logData: function(){
        fs.appendFile(__dirname + '/log/survive.txt', new Date() + '\r\n', 'utf8', function(error){
            if(error){
                throw error;
            } else {
                console.log('still alive...' + new Date());
            }
        });
    }
};

var timer = setInterval(BatteryTester.logData, 1000);


