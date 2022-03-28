#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "MidjoSkyen";
const char* password = "1234abcd";

IPAddress local_ip(192, 168, 200, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(420);

void handle_root();

void setup() {
  Serial.begin(9600);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  Serial.print("Connect to my access point: ");
  Serial.println(ssid);

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);

}

void loop() {
  server.handleClient();
}

String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - AP Mode &#128522;</h1>\
</body>\
</html>";

void handle_root(){
  server.send(200, "text/html", HTML);
}

/*  Forandre nettverknavnet (SSID) ditt til «MidjoSkyen», behold passordet du hadde. 
 *  Klarer PC-en din å koble til nettverket automatisk etter navnebytte?
 *    -Brukte telefonen, og denne klarte ikke dette, men vet at PC kan klare dette, og har sett dette skje før!
 *  
 *  Forandre IP-adressen (IPV4, local_ip i eksempelkode) til ESP32-en din. Hvordan kobler
 *  du nå til nettsiden som ESP32-en setter opp? HUSK: en IPV4 adresse må starte med
 *  «192.168» og slutte med to tall som ikke er over 254 i verdi (innenfor 8-bit rekkevidden)
 *    -Kan fortsatt koble til nettsiden, må bare passe på at det jeg skriver inn i nettleseren matcher local_ip
 *  
 *  Forandre port-nummeret du har satt opp nettsiden din på (tallet i WebServer server()
 *  objektet) fra «80» til et vilkårlig nummer (gjerne 3-sifferet for enkelhet). Her får du ikke
 *  noe hint, klarer du nå å koble til nettsiden din? Det er mulig med et tillegg i nettadressen.
 *    -Jeg satte port til 420, så ved å legge til :420 på enden av IP så kunne jeg koble til
 */