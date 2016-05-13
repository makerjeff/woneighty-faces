/**
 * Created by jefferson.wu on 5/12/16.
 */

var message = process.argv[2];

var exec = require('child_process').exec;

var cmd = 'espeak ';
cmd += '-v+f3 ';
cmd += '-s 120 ';
cmd += '-p 100 ';
cmd += message;

exec(cmd, function(error, stdout, stderr){
    if(error){
        return console.log(Error(error));
    }
});