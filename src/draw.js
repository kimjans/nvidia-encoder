//Create context
var width   = 1280
var height  = 720
var gl = require('gl')(width, height, { preserveDrawingBuffer: true })
 
//Clear screen to red
gl.clearColor(0, 0, 1, 1)
gl.clear(gl.COLOR_BUFFER_BIT)


const addon = require('bindings')('AppEncGL');

console.info( addon )

const startTime = new Date().getTime();
const enc = new addon.EncoderProxy(1280, 760, "./output/output.h264", "-preset HP -fps 24 -profile baseline -bitrate 2M");
enc.create();

for(var i = 0 ; i < 2000 ; ++i){
	enc.encodeCurrentFrame(i==1999);
}
enc.finish();
//enc.add(1.2);


//
// 애드온 함수를 실행합니다.
// "Hi!" 라는 문자열을 가져오게 됩니다.

// const oEncoder = addon.CreateEncoder(1280, 760, "./output/output.h264");
// oEncoder.create();

console.info( new Date().getTime() - startTime)


