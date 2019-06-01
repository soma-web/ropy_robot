#include <Arduino.h>
#include "motor.h"


void Motor::setup(){
        pinMode(Motor::motor1Pin1, OUTPUT);
        pinMode(Motor::motor1Pin2, OUTPUT);
        pinMode(Motor::enable1Pin, OUTPUT);
        ledcSetup(Motor::pwmChannel, Motor::freq, Motor::resolution);
        ledcAttachPin(Motor::enable1Pin, Motor::pwmChannel);
        Serial.println("setup motor done");
    }

void Motor::loop(){
    /*
    if(abs(Motor::percentage) < 0.01) 
    {
        Motor::stop();
        return;
    }
    */
    int a = (Motor::percentage > 0.0f) ? HIGH:LOW;
    int b = (Motor::percentage > 0.0f) ? LOW:HIGH;
    digitalWrite(Motor::motor1Pin1, a);
    digitalWrite(Motor::motor1Pin2, b);

    ledcWrite(Motor::pwmChannel, Motor::percentage * 255);
}

void Motor::foreward(){
    ledcWrite(Motor::pwmChannel, 255); 
     Serial.println("Motor foreward");
    digitalWrite(Motor::motor1Pin1, HIGH);
    digitalWrite(Motor::motor1Pin2, LOW);
}

void Motor::backward(){
    ledcWrite(Motor::pwmChannel, 255);   
     Serial.println("Motor backward");
    digitalWrite(Motor::motor1Pin1, LOW);
    digitalWrite(Motor::motor1Pin2, HIGH);
}

void Motor::setPercentage(float percentage){
    Motor::percentage = constrain(percentage, -1.0f, 1.0f);
    Serial.print("Setting percentage to:"); Serial.println(Motor::percentage);
}

void Motor::stop(){
    Serial.println("Motor stopped");
    digitalWrite(Motor::motor1Pin1, LOW);
    digitalWrite(Motor::motor1Pin2, LOW);
}

