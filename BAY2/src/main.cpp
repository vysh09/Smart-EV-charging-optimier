#include <Arduino.h>
#include <WiFi.h>
#include "State.h"
#include "config.h"
#include "Peripherals.h"
#include "Network.h"
#include "telemetry.h"
#include "model.h"
#include "edge_ai.h"
#include "optimization.h"



void setup()
{ 
    
    Serial.begin(115200);
    dht.begin();  // initialise sesnor
    configTime(0,0,"pool.ntp.org","time.nist.gov");
    pinMode(BTN_PLUGIN, INPUT_PULLUP );
    pinMode(BTN_PLUGOUT, INPUT_PULLUP );
    pinMode(RELAY_PIN,OUTPUT);
    pinMode(LED_GREEN,OUTPUT);
    pinMode(LED_RED,OUTPUT);
   pinMode(LED_YELLOW,OUTPUT);
    connectWiFi();
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    connectMQTT();

}

unsigned long now;
unsigned long last_print;

void loop()
{
    //print vals every 2 sec
    now = millis();
    if((now - last_print) > 2000)
    {
        last_print = now;
        sample_sensor();
        runEdgeAIInference();
        runOptimization();
        publishTelemetry();
        

    }
    plug_status();
    updateLeds() ;
    
}

