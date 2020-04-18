#include "FirebaseESP8266.h"
#include <FirebaseJson.h>
#include <ESP8266WiFi.h>
#define FIREBASE_HOST //FIREBASE PROJECT DATABASE URL
#define FIREBASE_AUTH //DATABSE SECRET
FirebaseData firebaseData;
const char* ssid = //SSID;
const char* password = //PASSWORD;   
void printJsonObjectContent(FirebaseData &data);
String path = //PATH OF YOUR FIREBASE BUCKET;

void setup() {
    Serial.begin(9600);
    pinMode(D0,INPUT);
    pinMode(D1,INPUT);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid); Serial.println(" ...");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(' ');
  }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    Firebase.setReadTimeout(firebaseData, 1000 * 60);
    Firebase.setwriteSizeLimit(firebaseData, "tiny");
    delay(500);
  }


void loop() {
  d_status();
  pass_change();
  delay(1000);
}


void d_status(){
  if(digitalRead(D0) == 0){
    FirebaseJson json;
    json.clear().addDouble("status" + String(1), 0.0);
    Firebase.updateNode(firebaseData, path, json);
  }
  else{
    FirebaseJson json;
    json.clear().addDouble("status" + String(1), 1.0);
    Firebase.updateNode(firebaseData, path, json);
  }
}

void pass_change(){
  if(digitalRead(D1) == 0){
    FirebaseJson json;
    json.clear().addDouble("wrong" + String(1), 1.0);
    Firebase.updateNode(firebaseData, path, json);
  }
  else{
    FirebaseJson json;
    json.clear().addDouble("wrong" + String(1), 0.0);
    Firebase.updateNode(firebaseData, path, json);
  }
}
