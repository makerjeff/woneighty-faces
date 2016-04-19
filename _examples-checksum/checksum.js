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

var checker = new JeffChecker2();

for(var i = 0; i < 100; i++){
    checker.moreFun(1);
}

for(i = 0; i < 100; i++){
    checker.lessFun(1);
}



/* FUNCTIONS / OBJECTS */
//type 1 object constructor prototype
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

//type 2 object constructor prototype
function JeffChecker2(str){
    this.funFactor = 0;
    this.debugMessage = str;

    //encapsulated moreFun
    this.moreFun = function(val){
        this.funFactor += val;
        console.log(this.funFactor);
    };

    //encapsulated lessFun
    this.lessFun = function(val){
        this.funFactor -= val;
        console.log(this.funFactor);
    };
}