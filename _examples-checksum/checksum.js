/**
 * Created by jeffersonwu on 4/18/16.
 */

var checksum = require('checksum');

var message = process.argv[2];
var md5message = checksum(message);

console.log(message);
console.log(md5message);

// checksum.file('checksum.js', function(error, sum){
//     if(error){
//         console.log(Error('something horrible happened!'));
//     } else {
//         console.log(sum)
//     }
// });

var checker = new JeffChecker();

for(var i = 0; i < 10; i++){
    checker.moreFun();
}



/* FUNCTIONS / OBJECTS */


//type 1 object
function JeffChecker(str){
    this.funFactor = 0;
    this.debugMessage = str;
}
JeffChecker.prototype.moreFun = function(val){
    this.funFactor += val;
    console.log(this.funFactor);
};
JeffChecker.prototype.lessFun = function(val){
    this.funFactor -= val;
    console.log(this.funFactor);
};

//type 2 object
function JeffChecker2(str){
    this.funFactor = 0;

    //encapsulated moreFun
    this.moreFun = function(val){
        this.funFactor += val;
    };

    //encapsulated lessFun
    this.lessFun = function(val){
        this.funFactor -= val;
    };
}