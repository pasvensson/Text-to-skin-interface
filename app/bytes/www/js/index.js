var app = {
  initialize: function() {
    this.bindEvents();
  },
  bindEvents: function() {
    document.addEventListener('deviceready', this.onDeviceReady, false);
  },
  onDeviceReady: function() {
    log("Device Ready");

    var onError = function(reason) {
      log("Discovery failed " + reason);
    };

    log("Looking for RFduinos");
    rfduino.discover(1000, app.onDiscover, onError);

  },
  onDiscover: function(device) {
    log("Discovered " + device.name);

    var onConnect = function() {
      log("Connected to " + device.name);
      setTimeout(app.sendData, 2000);
    };

    var onDisconnect = function(reason) {
      log("Disconnected from " + device.name + " " + reason);
    };

    if (device.name === 'RFduinoBytes') {
      log("Connecting to " + device.name);
      rfduino.connect(device.uuid, onConnect, onDisconnect);
    }
  },
  sendData: function() {
    log("Sending Data"); // TODO print it out
    // send an Array of bytes
    var data = new Uint8Array(4);
    data[0] = 0xFF;
    data[1] = 0x00;
    data[2] = 128;
    data[3] = 80;

    table(data);

    rfduino.write(
      data.buffer,
      function() {
        log("OK");
      },
      function(reason) {
        log("Error sending data " + reason);
      }
    );
  }
};

var log = function(message) {
  messageDiv.innerHTML = messageDiv.innerHTML + message + "<br/>";
};

var table = function(array) {

  var markup = "<table border='1' margin='2'>"; // oldschool
  markup += "<tr><th>DEC</th><th>HEX</th><th>OCT</th><th>BIN</th></tr>";
  for (var i = 0; i < array.length; i++) {
    markup += "<tr><td>" +
      array[i].toString(10) + "</td><td>" +
      array[i].toString(16) + "</td><td>" +
      array[i].toString(8) + "</td><td>" +
      array[i].toString(2) + "</td></tr>";
  }
  markup += "</table>";
  console.log(markup);
  log(markup);
};

app.initialize();
