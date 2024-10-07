#include "CTBot.h"
//#include <ESP8266WiFi.h>
CTBot myBot;
int ONTIME;
int OFFTIME;
String ssid = "Wokwi-GUEST";     
String pass = ""; 
String token = "5777617746:AAECsvxuYC4aO4KyjsNU139VfaTx0GEu--w";   
int ledPin = 2;
bool timer=false;
bool flagon = true;
int count = 0;
void LedTimer()
{
  if(timer == true)//on or off with time
  {
    
    if(flagon==true)
    {
      Serial.print("led is on ");
      Serial.println(count);
      if(count == ONTIME)
      {
        Serial.println("light off");
        count = 0;
        digitalWrite(ledPin, LOW);
        flagon=false;
      }
    }
    if(flagon==false)
    {
      Serial.print("led is off ");
      Serial.println(count);
      if(count == OFFTIME)
      {
        Serial.println("light on");
        count = 0;
        digitalWrite(ledPin, HIGH);
        flagon=true;
      }
    }
  }
}
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
    Serial.println("\ntestConnection Not OK");
  digitalWrite(ledPin, HIGH);
}
  

void loop() {
  // a variable to store telegram message data
  TBMessage msg;
  LedTimer();
  // if there is an incoming message...
  if (CTBotMessageText == myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("OFF")) {  
      Serial.println(msg.text);            
      digitalWrite(ledPin, LOW);                               
      myBot.sendMessage(msg.sender.id, "Light is now OFF"); 
      timer=false; 
      flagon = false;
    }
    else if (msg.text.equalsIgnoreCase("ON")) { 
      Serial.println(msg.text);       
      digitalWrite(ledPin, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Light is now ON"); 
      timer=false;
      flagon=true;
    }
    else if (msg.text.equalsIgnoreCase("TIME")) {
      Serial.println(msg.text);        
      timer=true;                              
      myBot.sendMessage(msg.sender.id, "ON time=");
      while(CTBotMessageText != myBot.getNewMessage(msg))
      {
        delay(1);
        count++;
        LedTimer();
      }
      ONTIME = msg.text.toInt();
      Serial.println(ONTIME);
      myBot.sendMessage(msg.sender.id, "OFF time=");
      while(CTBotMessageText != myBot.getNewMessage(msg))
      {
        delay(1);
        count++;
        LedTimer();
      }
      myBot.getNewMessage(msg);
      OFFTIME = msg.text.toInt();
      Serial.println(OFFTIME);
      count = 0; //timer avaz shod
    }
    else {                                                    
      // generate the message for the sender

      Serial.println(msg.text);
      String reply;
      reply = (String)"Try Only ON or  OFF or TIME.";
      myBot.sendMessage(msg.sender.id, reply);             
    }
  }
  count++;
  delay(1);
}
