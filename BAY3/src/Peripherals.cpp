#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"


DHT   dht(DHT_PIN , DHT_TYPE);
float mapFloat(long x, long inMin, long inMax, float outMin, float outMax){
return (x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}

void sample_sensor(void)
{
    int raw_current = analogRead(CURRENT_PIN); 
    int raw_voltage = analogRead(VOLTAGE_PIN); 
    voltage=mapFloat(raw_voltage,0,4095,0,250);
    if(bayStatus = "CHARGING")
    {

       current=mapFloat(raw_current,0,4095,0,32);

    }
    else{
      current = 0;
   }
   
    power=voltage *current;
    float t = dht.readTemperature(DHT_PIN);
    if(!(isnan(t)))temperature = t;



    //to read temperature 
    temperature = dht.readTemperature(DHT_PIN );
    
    

}
float recentAvgCurrent()
   {
   float sum= 0;
   for(int i = 0;i<5; i++)
   {
    sum = sum+current;
   }
   return sum/5;

   }
bool plugin_flag_once= 1;
bool plugout_flag_once = 1;

void plug_status(void)

{

bool pluginReading = digitalRead(BTN_PLUGIN);

// detect the sw is pressed

if( pluginReading == LOW && plugin_flag_once)

{
 sessionStartMs = millis();

// plug in switch is pressed

plugin_flag_once = 0;

// change bay_status FREE to charging

if(bayStatus == "FREE")

{

bayStatus = "CHARGING";

Serial.println("Bay1 plugin detected, Bay is Charging");
digitalWrite(RELAY_PIN,HIGH);
}

//update leds

}
if (pluginReading == HIGH)
{
   plugin_flag_once= 1;
}


bool plugoutReading = digitalRead(BTN_PLUGOUT);

// detect the sw is pressed

if (plugoutReading == LOW && plugout_flag_once)

{

// plug in switch is pressed

plugout_flag_once = 0;



if(bayStatus == "CHARGING")

{

bayStatus = "FREE";

Serial.println("Bay1 plugout detected, Bay is FREE");

}

//update leds

}
if (plugoutReading == HIGH)
{
   plugout_flag_once= 1;
}

}
/*void update_led_status(void)
{
   //if(bayStatus == "FREE"){
      digitalWrite(LED_GREEN,HIGH);
      digitalWrite(LED_YELLOW,LOW);
   }
   //else{
      digitalWrite(LED_GREEN,LOW);
      digitalWrite(LED_YELLOW,HIGH);

   }
 
} */



