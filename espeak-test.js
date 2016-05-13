/**
 * Created by jefferson.wu on 5/12/16.
 */

var espeak = require('espeak');

espeak.speak('hello world', function(error, wav){
    if(error){
        return console.error(err);
    }

    //raw binary wav data
    var buffer = wav.buffer;

    //grab base 64 data URI
    var dataUri = wav.toDataUri();
});

//espeak.speak('hello world, slower', ['-p 100', '-s 120', '-v+f4', '-w out.wav'], function(error, wav){});
