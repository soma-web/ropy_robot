#include <Arduino.h>
#include "motor.h"
#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define BLUETTOTHNAME "RopyBT"
#define LED 2

BluetoothSerial SerialBT;
boolean isConnected;
Motor motor;

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  //Serial.println("event" + event);
  if(event == ESP_SPP_SRV_OPEN_EVT){
    digitalWrite(LED,HIGH);
    isConnected = true;
    Serial.println("Client is Connected callback");
  }

  if(event == ESP_SPP_CLOSE_EVT ){
    isConnected = false;
    digitalWrite(LED,LOW);
    Serial.println("Client disconnected");
  }
}

String lineBuffer;
String ReadLine(){
  boolean hasEndOfLine = false;   
  while(SerialBT.available() > 0){
    char receivedChar = SerialBT.read();
    Serial.println("reading");
    Serial.print("received a char: "); Serial.println(receivedChar);
    switch(receivedChar){
      case '\n':
        hasEndOfLine = true;
        break;
      default:
        lineBuffer += receivedChar;  
    }
    delay(2);
  }  

  if(hasEndOfLine){
    String returnValue = lineBuffer;
    lineBuffer = "";
    return returnValue;
  }
  return "";
}

/// SETUP
void setup() {
  
  Serial.begin(115200);
  SerialBT.register_callback(callback);
  if(!SerialBT.begin(BLUETTOTHNAME)){
     Serial.println("Unable to start bluetooth");    
  }
  Serial.println("The device started, now you can pair it with bluetooth! DO it!");

  pinMode(LED,OUTPUT);

  motor.setup();
  motor.setPercentage(0.75f);
}



void loop() {

  String btCommand = ReadLine();
  if(btCommand != ""){
     Serial.print("BTCommand received "); Serial.println(btCommand);       
  }
  
  motor.loop();

  /*
  motor.foreward();
  delay(3000);
  motor.stop();
  delay(1000);
  motor.backward();
  delay(3000);
  motor.stop();
  delay(1000);
*/

  /*
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  */
  //
}

void motorTest() {
    delay(3000);
    motor.setPercentage(0.1f);
    motor.loop();
    
    delay(3000);
    motor.setPercentage(-0.25f);
    motor.loop();
    
    delay(3000);
    motor.setPercentage(0.5f);
    motor.loop();

    delay(3000);
    motor.setPercentage(-0.75f);
    motor.loop();

    delay(3000);
    motor.setPercentage(1.75f);
    motor.loop();
}



