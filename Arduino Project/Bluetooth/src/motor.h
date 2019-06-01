#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
    private:
         // Motor A
        int motor1Pin1 = 27; 
        int motor1Pin2 = 26; 
        int enable1Pin = 14; 

        // Setting PWM properties
        const int freq = 30000;
        const int pwmChannel = 0;
        const int resolution = 8;
        int dutyCycle = 200;

        float percentage;

    public:
        void setup();
        void loop();
        void setPercentage(float percentage);
        void stop();
        void foreward();
        void backward();
};

#endif