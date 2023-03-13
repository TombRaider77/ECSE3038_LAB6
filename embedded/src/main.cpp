#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"
#define light 23
#define sensor 21
#define fan 22 


float sunset;

void setup() {
  pinMode (fan ,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(sensor,INPUT);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS); 


  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
if (WiFi.status() != WL_CONNECTED ){
  HTTPClient http;
  http.begin(endpoint);


  String http_response;
  http.addHeader("Content-Type", "application/json"); 
  StaticJsonDocument<100> doc; 
  char * httpRequestData;


  http.addHeader("Content-length","100");

  serializeJson(doc, httpRequestData); 
  

  int httpResponseCode = http.PUT(httpRequestData); 
  if (httpResponseCode>0){
    
    Serial.print("HTTP Response code: ");
    Serial.print(httpResponseCode);
    Serial.print("Response from server:");
    http_response = http.getString();
    Serial.print(http_response);
  }
  else{
    Serial.print("Error code:");
    Serial.print(httpResponseCode);
  }
  http.end();
 
  DeserializationError error = deserializeJson(doc,http_response);

  if (error){
    Serial.print("Deserialize failed: ");
    Serial.print(error.c_str());
    return;
  }
  
    const bool Fan= doc["Fan"];
    const bool Light= doc["Light"];
    //either on or off


 
    float reading =random(21,33);
    //creates a random value for temp

  
    if (reading >=28){
      //of temp above 28 turn on fan else opponsite
      doc["Fan"]=true ;
      const bool Fan= doc["Fan"];
      digitalWrite (fan,Fan);
    }
    else{
      doc["Fan"]=false ;
      const bool Fan= doc["Fan"];
      digitalWrite(fan,Fan);
    } 
    if (float time= sunset){  
      //if it begins to get dark, aka sunset, turn on light, else opposite

      doc["Light"]= true;  
      const bool Light= doc["Light"];
      digitalWrite(light,Light);
    } 
    else{
      doc["Light"]= false;
      const bool Light= doc["Light"];
      digitalWrite(light,Light);
    }
    delay(2000);
}
else
  return;


}