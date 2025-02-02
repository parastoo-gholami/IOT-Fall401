#include <ESP8266WiFi.h>
const char* ssid = "PARPAR";
const char* password = "123456789";
int ledPin = D4;
int value = LOW;
WiFiServer server(80);
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
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(1000);
 Serial.print(".");
 digitalWrite(ledPin, !digitalRead(ledPin));
 }
 Serial.println("");
 Serial.println("WiFi connected");
 // Start the server
 server.begin();
 Serial.println("Server started");
 // Print the IP address
 Serial.print("Use this URL : ");
 Serial.print("http://");
 Serial.print(WiFi.localIP());
 Serial.println("/");
}
void loop() {
 // Check if a client has connected
 WiFiClient client = server.available();
 if (!client) {
 return;
 }
 // Wait until the client sends some data
 Serial.println("new client");
 while(!client.available()){
 delay(1);
 }
 // Read the first line of the request
 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();
 // Match the request
 
 if (request.indexOf("/LED=ON") != -1) {
 digitalWrite(ledPin, HIGH);
 value = HIGH; } 
 if (request.indexOf("/LED=OFF") != -1){
 digitalWrite(ledPin, LOW);
 value = LOW;
 }
 // Return the response
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println(""); // do not forget this one
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
 client.print("Led pin is now: ");
 if(value == HIGH) {
 client.print("On"); 
 digitalWrite(ledPin, LOW);
 } else {
 client.print("Off");
 digitalWrite(ledPin, HIGH);
 }
 client.println("<br><br>");
 client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 5 ON<br>");
 client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 5 OFF<br>");
 client.println("</html>");
 delay(1);
 Serial.println("Client disconnected");
 Serial.println("");
}
