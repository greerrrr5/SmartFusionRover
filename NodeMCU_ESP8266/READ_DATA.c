#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <String.h>
#include "sound.h"
#define DEVICE_ID "1055107638"
#define API_Key "ba1N42BvFylMutHjcMVZmJYKUsg="

const char* ssid = "wsy";
const char* password = "13880124858";

const int D5_PIN = 5;   // 温度
const int D6_PIN = 6;   // 湿度
const int D7_PIN = 7;   // co2
const int D0_PIN = 4;   // tvoc
const int D1_PIN = 20;  // sun

String GET_URL_temp = "http://api.heclouds.com/devices/" + String(DEVICE_ID) + "/datastreams/temp";
String GET_URL_hum = "http://api.heclouds.com/devices/" + String(DEVICE_ID) + "/datastreams/hum";
String GET_URL_co2 = "http://api.heclouds.com/devices/" + String(DEVICE_ID) + "/datastreams/co2";
String GET_URL_tvoc = "http://api.heclouds.com/devices/" + String(DEVICE_ID) + "/datastreams/tvoc";
String GET_URL_sun = "http://api.heclouds.com/devices/" + String(DEVICE_ID) + "/datastreams/sun";
void setup() {
  Serial.begin(9600);
//  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

void loop() {
//  for(int i=0;i<2;i++){
//  Serial.print(sound);
//  delay(3000);
//  delay(3000);
//  }
  if (WiFi.status() == WL_CONNECTED) {
    ESP8266_GET_hum();
    ESP8266_GET_temp();
    ESP8266_GET_sun();  
    ESP8266_GET_co2(); 
    ESP8266_GET_tvoc();
  } else {
    Serial.println("[ERROR] WiFi Disconnected!");
//    delay(10000);
  }
}






void Json_Analysis_GET_hum(String input) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, input);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

//  int err_num_temp = doc["errno"]; // 0

  JsonObject data = doc["data"];
  const char *data_update_at_hum = data["update_at"]; // "2021-03-04 10:40:32"
  const char *data_id_hum = data["id"]; // "Light"
  int data_current_value = data["current_value"]; // 1

  
  Serial.println("[GET]     data_id: " + String(data_id_hum));
  Serial.println("[GET]  data_value: " + String(data_current_value));
  Serial.println("[GET] update_time: " + String(data_update_at_hum));
 
  if (data_current_value >= 60) {
 //   digitalWrite(D6_PIN, LOW);   // LED on
    for(int i=0;i<2;i++){
        Serial.print(soundhum);
        delay(3000);
        delay(3000);
    }
  } 
//  else {
  //  digitalWrite(D6_PIN, HIGH);  // LED off
        
//  }
} 



void Json_Analysis_GET_co2(String input) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, input);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

//  int err_num_temp = doc["errno"]; // 0

  JsonObject data = doc["data"];
  const char* data_update_at_co2 = data["update_at"]; // 
  const char* data_id_co2 = data["id"]; // "Light"
  int data_current_value = data["current_value"]; // 1

  
  Serial.println("[GET]     data_id: " + String(data_id_co2));
  Serial.println("[GET]  data_value: " + String(data_current_value));
  Serial.println("[GET] update_time: " + String(data_update_at_co2));
 
  if (data_current_value >=400 ) {
//    digitalWrite(D7_PIN, LOW);   // LED on
    for(int i=0;i<2;i++){
        Serial.print(soundco2);
        delay(3000);
        delay(3000);
    }
  } 
//  else {
//    digitalWrite(D7_PIN, HIGH);  // LED off
        
//  }
} 




void Json_Analysis_GET_tvoc(String input) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, input);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

//  int err_num_temp = doc["errno"]; // 0

  JsonObject data = doc["data"];
  const char *data_update_at_tvoc = data["update_at"]; // "2021-03-04 10:40:32"
  const char *data_id_tvoc = data["id"]; // "Light"
  int data_current_value = data["current_value"]; // 1

  
  Serial.println("[GET]     data_id: " + String(data_id_tvoc));
  Serial.println("[GET]  data_value: " + String(data_current_value));
  Serial.println("[GET] update_time: " + String(data_update_at_tvoc));
 
  if (data_current_value >= 140) {
//    digitalWrite(D0_PIN, LOW);   // LED on
    for(int i=0;i<2;i++){
        Serial.print(soundtvoc);
        delay(3000);
        delay(3000);
    }
  } 
//  else {
//    digitalWrite(D0_PIN, HIGH);  // LED off
        
//  }
} 

void Json_Analysis_GET_sun(String input) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, input);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

//  int err_num_temp = doc["errno"]; // 0

  JsonObject data = doc["data"];
  const char *data_update_at_sun = data["update_at"]; // "2021-03-04 10:40:32"
  const char *data_id_sun = data["id"]; // "Light"
  int data_current_value = data["current_value"]; // 1

  
  Serial.println("[GET]     data_id: " + String(data_id_sun));
  Serial.println("[GET]  data_value: " + String(data_current_value));
  Serial.println("[GET] update_time: " + String(data_update_at_sun));
 
  if (data_current_value >= 54) {
//    digitalWrite(D1_PIN, LOW);   // LED on 
    for(int i=0;i<2;i++){
        Serial.print(soundsun);
        delay(3000);
        delay(3000);
    }
    
  } 
//  else {
//    digitalWrite(D1_PIN, HIGH);  // LED off
        
//  }
} 


void Json_Analysis_GET_temp(String input) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, input);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

//  int err_num_temp = doc["errno"]; // 0

  JsonObject data = doc["data"];
  const char *data_update_at_temp = data["update_at"]; // "2021-03-04 10:40:32"
  const char *data_id_temp = data["id"]; // "Light"
  int data_current_value = data["current_value"]; // 1

  
  Serial.println("[GET]     data_id: " + String(data_id_temp));
  Serial.println("[GET]  data_value: " + String(data_current_value));
  Serial.println("[GET] update_time: " + String(data_update_at_temp));
 
  if (data_current_value >= 28) {
//    digitalWrite(D5_PIN, LOW);   // LED on
    for(int i=0;i<2;i++){
        Serial.print(soundtemp);
        delay(3000);
        delay(000);
    }
  } 
//  else {
//    digitalWrite(D5_PIN, HIGH);  // LED off
        
//  }
} 
void ESP8266_GET_hum() {
  HTTPClient httpClient;
  WiFiClient client;
  httpClient.begin(client, GET_URL_hum);
  httpClient.addHeader("api-key", API_Key);
  int httpCode = httpClient.GET();
  Serial.println("[GET] Send request to: " + GET_URL_hum);

  if (httpCode == HTTP_CODE_OK) {
    String responsePayload = httpClient.getString();
    Json_Analysis_GET_hum(responsePayload);
    Serial.println("[GET] Server Response: " + responsePayload);
    Serial.println("-------------------------------------------\n");
  } else {
    Serial.println("Server Response Code: " + String(httpCode));
  }
  httpClient.end();
}


void ESP8266_GET_temp(){
  HTTPClient httpClient;
  WiFiClient client;
  httpClient.begin(client, GET_URL_temp);
  httpClient.addHeader("api-key", API_Key);
  int  httpCode = httpClient.GET();
  Serial.println("[GET] Send request to: " + GET_URL_temp);

  if (httpCode == HTTP_CODE_OK) {
    String responsePayload = httpClient.getString();
    Json_Analysis_GET_temp(responsePayload);
    Serial.println("[GET] Server Response: " + responsePayload);
    Serial.println("-------------------------------------------\n");
  } else {
    Serial.println("Server Response Code: " + String(httpCode));
  }

  httpClient.end();
}


void ESP8266_GET_co2() {
  HTTPClient httpClient;
  WiFiClient client;
  httpClient.begin(client, GET_URL_co2);
  httpClient.addHeader("api-key", API_Key);
  int httpCode = httpClient.GET();
  Serial.println("[GET] Send request to: " + GET_URL_co2);

  if (httpCode == HTTP_CODE_OK) {
    String responsePayload = httpClient.getString();
    Json_Analysis_GET_co2(responsePayload);
    Serial.println("[GET] Server Response: " + responsePayload);
    Serial.println("-------------------------------------------\n");
  } else {
    Serial.println("Server Response Code: " + String(httpCode));
  }
  httpClient.end();
}


void ESP8266_GET_tvoc() {
  HTTPClient httpClient;
  WiFiClient client;
  httpClient.begin(client, GET_URL_tvoc);
  httpClient.addHeader("api-key", API_Key);
  int httpCode = httpClient.GET();
  Serial.println("[GET] Send request to: " + GET_URL_tvoc);

  if (httpCode == HTTP_CODE_OK) {
    String responsePayload = httpClient.getString();
    Json_Analysis_GET_tvoc(responsePayload);
    Serial.println("[GET] Server Response: " + responsePayload);
    Serial.println("-------------------------------------------\n");
  } else {
    Serial.println("Server Response Code: " + String(httpCode));
  }
  httpClient.end();
}


void ESP8266_GET_sun() {
  HTTPClient httpClient;
  WiFiClient client;
  httpClient.begin(client, GET_URL_sun);
  httpClient.addHeader("api-key", API_Key);
  int httpCode = httpClient.GET();
  Serial.println("[GET] Send request to: " + GET_URL_sun);

  if (httpCode == HTTP_CODE_OK) {
    String responsePayload = httpClient.getString();
    Json_Analysis_GET_sun(responsePayload);
    Serial.println("[GET] Server Response: " + responsePayload);
    Serial.println("-------------------------------------------\n");
  } else {
    Serial.println("Server Response Code: " + String(httpCode));
  }
  httpClient.end();
}