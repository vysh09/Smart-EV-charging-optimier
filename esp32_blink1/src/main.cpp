#include <Arduino.h>
#include "WiFi.h"

#include <WiFi.h>
#include <PubSubClient.h>

// ---------------- WiFi Details ----------------
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

// ---------------- ThingsBoard Details ----------------
const char* MQTT_SERVER = "mqtt.thingsboard.cloud";
const int MQTT_PORT = 1883;

// ThingsBoard Device Access Token
const char* ACCESS_TOKEN = "WGU9z6J1n4DCnSqeXpz5";

// ---------------- MQTT ----------------
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// ---------------- Variables ----------------
unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 5000;


// Connect ESP32 to WiFi
void connectWiFi()
{
    Serial.print("Connecting to WiFi");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected!");
    
}


// Connect ESP32 to ThingsBoard
void connectMQTT()
{
    while (!mqttClient.connected())
    {
        Serial.print("Connecting to ThingsBoard...");

        // ThingsBoard uses the device access token as MQTT username
        if (mqttClient.connect("ESP32_WOKWI", ACCESS_TOKEN, NULL))
        {
            Serial.println("connected!");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.println(mqttClient.state());

            delay(2000);
        }
    }
}


// Send telemetry to ThingsBoard
void sendTelemetry()
{
    float temperature = 25.5;
    float humidity = 60.0;

    String payload = "{";
    payload += "\"temperature\":" + String(temperature);
    payload += ",";
    payload += "\"humidity\":" + String(humidity);
    payload += "}";

    Serial.print("Sending telemetry: ");
    Serial.println(payload);

    mqttClient.publish("v1/devices/me/telemetry", payload.c_str());
}


void setup()
{
    Serial.begin(115200);

    // Connect WiFi
    connectWiFi();

    // Configure MQTT server
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);

    // Connect to ThingsBoard
    connectMQTT();
}


void loop()
{
    // Reconnect if MQTT connection is lost
    if (!mqttClient.connected())
    {
        connectMQTT();
    }

    mqttClient.loop();

    // Send telemetry every 5 seconds
    if (millis() - lastPublishTime >= publishInterval)
    {
        lastPublishTime = millis();

        sendTelemetry();
    }
}