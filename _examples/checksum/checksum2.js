/**
 * Created by jeffersonwu on 4/18/16.
 */

var checksum = require('checksum');

var message = process.argv[2];
var md5message = checksum(message);

// console.log(message);
// console.log(md5message);

checksum.file(message, function(error, sum){
    if(error){
        console.log(Error('horrible error occurred.'));
    }

    else if (sum === "c63e33d61c85d406e7f3560ef6dcf1fca267afd7") {
        console.log('File matches!');
    }

    else {
        console.log('file does not match!');
    }
});