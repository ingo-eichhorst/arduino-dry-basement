// Dry Basement Project
// inspired by http://forum.arduino.cc/index.php?topic=175778.15

#include <dht.h>

#define dht1_apin A0 // Analog pin sensor 1
#define dht2_apin A1 // Analog pin sensor 2

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

    // read input of sensor 1
    DHT.read11(dht1_apin);
    float hum1 = DHT.humidity;
    float temp1 = DHT.temperature;
    Serial.print("S1 = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print(" ");
    Serial.print(DHT.temperature); 
    Serial.print("C  ");

    // read input of sensor 2
    DHT.read11(dht2_apin);
    float hum2 = DHT.humidity;
    float temp2 = DHT.temperature;
    Serial.print(" - S2 = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print(" ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");

    // calculate relative and abs humidity 1
    float abs_hum = 0;
    float temp_k = temp1 + 273.15;
    float gas_const = 8314.3;
    float mol_steam = 18.016;
    float a,b;
    
    if (temp1 >= 0 ) {
      a = 7.5;
      b = 237.3;
    }
    else {
      a = 7.6; 
      b = 240.7;
    }

    float sdd_1 = ((a * temp1)/(b + temp1));
    float sdd = 6.1078 * pow(10,sdd_1);
    float dd = hum1/100 * sdd;
    float dd1 = (dd / 6.1078);
    float dew_point = log10(dd1);
    abs_hum = 100000 * mol_steam/gas_const * dd / temp_k;
    abs_hum = (round(abs_hum * 10)) / 10;
    
    Serial.print("Abs Hum 1: ");
    Serial.println(abs_hum);

    // calculate relative and abs humidity 2
    temp_k = temp2 + 273.15;

    if (temp2 >= 0 ) {
      a = 7.5;
      b = 237.3;
    }
    else {
      a = 7.6; 
      b = 240.7;
    }

    sdd_1 = ((a * temp2)/(b + temp2));
    sdd = 6.1078 * pow(10,sdd_1);
    dd = hum1/100 * sdd;
    dd1 = (dd / 6.1078);
    dew_point = log10(dd1);
    abs_hum = 100000 * mol_steam/gas_const * dd / temp_k;
    abs_hum = (round(abs_hum * 10)) / 10;
    
    Serial.print("Abs Hum 2: ");
    Serial.println(abs_hum);

    if (hum1 > hum2) {
      digitalWrite(RELAY1,LOW);
    } else {
      digitalWrite(RELAY1,HIGH);
    }
    
    delay(5000);
}
