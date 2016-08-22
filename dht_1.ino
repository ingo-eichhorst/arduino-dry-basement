#include <dht.h>

#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
#define RELAY1 13
 
void setup(){
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1,HIGH);
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
}

void loop(){
    DHT.read11(dht_apin);
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    if (DHT.humidity > 65.00) {
      digitalWrite(RELAY1,LOW);
    } else {
      digitalWrite(RELAY1,HIGH);
    }
    delay(5000);
}
