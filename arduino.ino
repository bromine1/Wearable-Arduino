#include <dht.h>
#define dhtTemp A0 // Analog Pin sensor is connected to

dht temp; //Defines dht as DHT. Think import dht as DHT
int buzzer = 12;//the pin of the active buzzer

void setup()
// init function, all the things that happen once
{
  //Initialize Serial for diagnostics
    Serial.begin(9600);
    delay(500);//Delay to let system boot

    pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
}

void loop()
//think of this as the main function, continues to execute
{
    temp.read11(dhtTemp);
    if (temp.temperature > 100) 
    {
        Serial.print(temp.temperature);
        Serial.print("Activating Buzzer \n");
        digitalWrite(buzzer, LOW);
        delay(500);
        noTone(buzzer);
    }

}