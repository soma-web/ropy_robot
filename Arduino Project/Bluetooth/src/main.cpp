#include <Arduino.h>
#include <ArduinoJson.h>
#include "motor.h"
#include "BluetoothSerial.h"
#include <algorithm>
#include <string>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define BLUETTOTHNAME "RopyBT"
#define LED 2

BluetoothSerial SerialBT;
boolean isConnected;
Motor motor;

//string buffer for the bluetooth serial connection
String lineBuffer;

//Json
StaticJsonBuffer<200> jsonBuffer;

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


String ReadLine(){
  boolean hasEndOfLine = false;   
  while(SerialBT.available() > 0 && !hasEndOfLine){
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

void handleBTInput(String json){
  int last = json.length() - 1;
  char lastChar = json[last];
  if(lastChar == '\n') Serial.println("last is linebreak");
  //str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
  JsonObject& command = jsonBuffer.parseObject(json);
  if(command.success()){
    Serial.println("read command");
    float motorSpeed = command["motor"]["speed"];
    Serial.println(motorSpeed);
    motor.setPercentage(motorSpeed);
  }else{    
    Serial.print("unable to parse"); Serial.println(json);    
  }
  jsonBuffer.clear();
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
  motor.stop();
}

void loop() {

  motor.loop();

  String btCommand = ReadLine();
  if(btCommand != ""){
    Serial.print("BTCommand received "); Serial.println(btCommand);     
    handleBTInput(btCommand);
  }
  

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



