/**
 * Created by jeffersonwu on 4/18/16.
 */

var checksum = require('checksum');

var message = process.argv[2];
var md5message = checksum(message);

console.log(message);
console.log(md5message);

checksum.file('checksum.js', function(error, sum){
    if(error){
        console.log(Error('something horrible happened!'));
    } else {
        console.log(sum)
    }
});