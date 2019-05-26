#include <WebSockets.h>
#include <WebSocketsClient.h>
#include <WebSocketsServer.h>

#include <ESP8266WiFi.h>

const char *ssid = "RopyAP";
const char *password = "Ropy1234";

WebSocketsServer webSocket = WebSocketsServer(81);

// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(2, OUTPUT);
    digitalWrite(2, 1);
    delay(1000);
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configuring access point...");
    WiFi.disconnect();
    delay(100);
    WiFi.mode(WIFI_STA);
    // You can remove the password parameter if you want the AP to be open. 
    WiFi.softAP(ssid, password);
    
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // Start the server
   
    Serial.println("Server started");

    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop(){
    webSocket.loop();
  
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        
        // send message to client
        webSocket.sendTXT(num, "Connected");
            }
            break;
        case WStype_TEXT:
            Serial.printf("[%u] get Text: %s\n", num, payload);

            // send message to client
            // webSocket.sendTXT(num, "message here");

            // send data to all connected clients
            // webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
           Serial.printf("[%u] get binary length: %u\n", num, length);
            hexdump(payload, length);

            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
    }

}
