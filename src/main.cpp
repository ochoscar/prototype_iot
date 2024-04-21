#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC "esp32/esp32-to-aws"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/aws-to-esp32"

#define PUBLISH_INTERVAL 4000  // 4 seconds

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
void connect_aws();
void publishMessage(String);
void messageHandler(char*, byte*, unsigned int);

unsigned long lastPublishTime = 0;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("ESP32 connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");

  connect_aws();
}

void loop() {
  client.loop();

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    publishMessage("Hola mundo");
    lastPublishTime = millis();
  }
}



void connect_aws() 
{
  Serial.println("Connecting AWS");

  // Broker MQTT AWS
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(messageHandler);
   
  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS connected");
  delay(1500);
}

void publishMessage(String msg)
{
  StaticJsonDocument<200> doc;
  doc["payload"] = msg;
  char jsonBuffer[1024];
  serializeJson(doc, jsonBuffer);
  Serial.println("Sending data:");
  Serial.println(jsonBuffer);
  bool response = client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.println("Message from AWS:");
  Serial.println(topic);
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  String strMessage = String(message);
  Serial.println(message);
}
