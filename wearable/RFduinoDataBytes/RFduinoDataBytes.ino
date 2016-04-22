// RFduino test receiving bytes from PhoneGap app
#include <RFduinoBLE.h>

void setup() {
  // Rename Peripheral
  RFduinoBLE.deviceName = "RFduinoBytes";
  RFduinoBLE.advertisementData = "BrB";
  RFduinoBLE.advertisementInterval = 1000;
  
  Serial.begin(9600);
  Serial.println("Hello");
  delay(4000);
  Serial.println("Init-1");

  // start the BLE stack
  RFduinoBLE.begin();

//  delay(100); 
//  Serial.println("Init-2");

}

void RFduinoBLE_onAdvertisement(bool start)
{
  Serial.println("X");  
}

void loop() {
  // go into low power mode
  //RFduino_ULPDelay(INFINITE);
  Serial.print(".");
  RFduino_ULPDelay(5000);  
}

void RFduinoBLE_onConnect()
{
  Serial.println("");
  Serial.println("onConnect");
  //digitalWrite(led_out, HIGH);
}

void RFduinoBLE_onReceive(char *data, int len) {
  Serial.println("");
  Serial.println("onReceive");
  Serial.print("data len= ");
  Serial.println(len,DEC);
  
  // print each byte in multiple formats
  Serial.println("DEC\tHEX\tBIN");
  for (int i = 0; i < len; i++) {
    Serial.print(data[i], DEC);
    Serial.print("\t");
    Serial.print(data[i], HEX);
    Serial.print("\t");
    Serial.println(data[i], BIN);
    //Values may not be printable chars
    //Serial.print(" ");
    //Serial.println(data[i]);
  }
}
