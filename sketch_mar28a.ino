#include "DHT.h"

#define RELAY_FAN_PIN 5 // Arduino pin connected to relay which connected to fan
#define DHTPIN 2           // Arduino pin connected to relay which connected to DHT sensor
#define DHTTYPE DHT11

const int TEMP_THRESHOLD_UPPER = 33; // upper threshold of temperature, change to your desire value

DHT dht(DHTPIN, DHTTYPE);

float temperature;    // temperature in Celsius
float humidity;
String status;

void setup()
{
  Serial.begin(9600); // initialize serial
  dht.begin();        // initialize the sensor
  pinMode(RELAY_FAN_PIN, OUTPUT); // initialize digital pin as an output
}

void loop()
{
  // wait a few seconds between measurements.
  delay(2000);

  temperature = dht.readTemperature();  // read temperature in Celsius
  humidity = dht.readHumidity();
  
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    if(temperature > TEMP_THRESHOLD_UPPER){
      digitalWrite(RELAY_FAN_PIN, HIGH); // turn on
      status = "ON";
    } else {
      digitalWrite(RELAY_FAN_PIN, LOW); // turn off
      status = "OFF";
    }
  }
  
  String dhtData = String(temperature) + "," + status + "," + String(humidity);
  Serial.println(dhtData);

}
