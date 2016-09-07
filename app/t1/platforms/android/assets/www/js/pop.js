function sayHi() {
	console.log('HI');
}

function startDiscover() {
    rfduino.discover(30, onDiscover,
                     console.log('Something went wrong!'));
}

function clickHandler(e) {
  setTimeout(startDiscover, 1000);
}

function onDiscover(device) {
    var deviceListText = JSON.stringify(device);
    console.log(deviceListText);
    document.getElementById("p1").innerHTML = device.uuid;
    rfduino.connect(device.uuid, onConnectBand,
                    function() {
                        console.log('ERROR CONNECTING!');
                    });
}

function onConnectBand(device) {
    console.log('connectedBand ' + device);
    setTimeout(sendMoreData,1000);
}

// 20 bytes seems to be the maximum number of bytes that can be sent with one write
// Limitations in the plugin?
function sendMoreData() {
    var arrayLength = 4;
    var buffer = new ArrayBuffer(arrayLength);
    var view = new DataView(buffer);

    for (i=0; i<arrayLength; i++) {
        view.setInt8(i,i+1);
    }
    
    rfduino.write(buffer, success, failure);
}

function success() {
    console.log('Success!');
    setTimeout(sendMoreData,50);
}

function failure() {
    console.log('FAILURE!');
}

document.addEventListener('DOMContentLoaded', function () {
  document.querySelector('button').addEventListener('click', clickHandler);
});
