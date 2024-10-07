#include <ESP8266WiFi.h>
const char* ssid = "PARPAR";
const char* password = "123456789";
int ledPin = D4;
int onTIME=100;
int offTIME=100;
bool flag=true;
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
 digitalWrite(ledPin, LOW);
}

void loop() {

 // Check if a client has connected
 WiFiClient client = server.available();
 if (!client) {
  digitalWrite(ledPin,HIGH);
  delay(onTIME);
  digitalWrite(ledPin,LOW);
  delay(offTIME);
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
 Serial.println(request);
 client.flush();
 // Match the request

if (request.indexOf("GET /?On=") != -1) {
  int index1= request.indexOf("On=")+3;
  int index2=request.indexOf("&");
  onTIME =request.substring(index1,index2).toInt();
  int index3= request.indexOf("off=")+4;
  int index4=request.length();
  offTIME =request.substring(index3,index4).toInt();
  Serial.println(onTIME);
  Serial.println(offTIME);
}
 // Return the response
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println(""); // do not forget this one
 client.println("<!DOCTYPE HTML>");
 client.println("<html>");
 client.println(" <form action=\"\" method=\"get\" class=\"form-example\">");
 client.println("<label for=\"ON\">Time(ms) on: </label>");
 client.println("<input type=\"text\" name=\"On\" id=\"On\" required><br><br>");
 client.println("<label for=\"OFF\">Time(ms) off: </label>");
 client.println("<input type=\"text\" name=\"off\" id=\"off\" required><br><br>");
 client.println("<input type=\"submit\" value=\"Send\">");
 client.println("</form>");
 client.println("</html>");
 
 delay(1);

 Serial.println("Client disconnected");
 Serial.println("");
 }
