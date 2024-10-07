

#include "CTBot.h"
//#include <ESP8266WiFi.h>
CTBot myBot;

String ssid = "Wokwi-GUEST";     
String pass = ""; 
String token = "5777617746:AAECsvxuYC4aO4KyjsNU139VfaTx0GEu--w";   
int ledPin = 2;
void setup() {

 Serial.begin(115200);
 delay(10);
 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW);
 // Connect to WiFi network
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 myBot.wifiConnect(ssid, pass);

Serial.println("Starting TelegramBot...");

  // connect the ESP8266 to the desired access point
  

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
  digitalWrite(ledPin, HIGH);
}
  

void loop() {
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (CTBotMessageText == myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("OFF")) {              
      digitalWrite(ledPin, LOW);                               
      myBot.sendMessage(msg.sender.id, "Light is now OFF");  
    }
    else if (msg.text.equalsIgnoreCase("ON")) {        
      digitalWrite(ledPin, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Light is now ON"); 
    }
    else {                                                    
      // generate the message for the sender
      String reply;
      reply = (String)"Try Only ON or  OFF.";
      myBot.sendMessage(msg.sender.id, reply);             
    }
  }
  // wait 500 milliseconds
  delay(500);
}
