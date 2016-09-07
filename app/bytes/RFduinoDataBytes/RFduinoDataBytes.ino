// RFduino test receiving bytes from PhoneGap app
#include <RFduinoBLE.h>

// Project specific constants
#define NUMBER_OF_MOTORS 6
#define BUZZ_LENGTH_MS 2000
#define BREAK_LENGTH_MS 1000

// Project specific global variables
uint8_t motorPins[] = {1,2,3,4,5,6};
uint8_t motorValues[] = {0,0,0,0,0,0};


void setup() {
  // Rename Peripheral
  RFduinoBLE.deviceName = "RFduinoBytes";
  RFduinoBLE.advertisementData = "BrB";
  RFduinoBLE.advertisementInterval = 1000;
  
  Serial.begin(9600);
  delay(4000);

  // start the BLE stack
  RFduinoBLE.begin();

  // setup pin mode for motor pins
  for (int i=0;i<NUMBER_OF_MOTORS;i++) {
    pinMode(motorPins[i], OUTPUT);
  }
}

void RFduinoBLE_onAdvertisement(bool start)
{
  Serial.println("");
  Serial.println("onAdvertisement");
}

void loop() {
  // go into low power mode
  RFduino_ULPDelay(INFINITE);
  //Serial.print(".");
  //RFduino_ULPDelay(5000);  
}

void RFduinoBLE_onConnect()
{
  Serial.println("");
  Serial.println("onConnect");
}

void RFduinoBLE_onReceive(char *data, int len) {
  Serial.println("");
  Serial.println("onReceive");
  
  // Use only first byte for now
  uint8_t dc = data[0];
  SetMotorOutputs(dc);
  delay(BUZZ_LENGTH_MS);
  SetAllMotorOutputs(LOW);
  delay(BREAK_LENGTH_MS);
}

void SetMotorOutputs(uint8_t value) {
  for (int i=0; i<NUMBER_OF_MOTORS; i++) {
    motorValues[i] = 0 != value & 0x1<<i;
  }
  for (int i=0; i<NUMBER_OF_MOTORS; i++) {
    digitalWrite(motorPins[i], motorValues[i]);
  }
}

// HIGH == true 
// LOW == false
void SetAllMotorOutputs(bool value) {
  for (int i=0; i<NUMBER_OF_MOTORS; i++) {
    motorValues[i] = value;
    digitalWrite(motorPins[i],value);
  }
}


// ##################### Debug print functions #############################
void Debug_onReceive(char *data, int len) {
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



