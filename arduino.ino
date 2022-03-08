#include <dht.h>
#include <PulseSensorPlayground.h>
#define dhtTemp A0 // Analog Pin sensor is connected to
PulseSensorPlayground pulseSensor; //Give the module a bertter name
dht temp; //Defines dht as DHT. Think import dht as DHT

int buzzer = 11;//the pin of the active buzzer
const int PulseWire = 0;
int Threashold = 550;


void setup()
// init function, all the things that happen once
{
    //Initialize Serial for diagnostics
    Serial.begin(9600);
    delay(500);//Delay to let system boot

    pulseSensor.setThreshold(Threashold); // Define heartbeat threashold
    //Initialize pins as output
    pulseSensor.analogInput(PulseWire);
    pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
}

void loop()
//think of this as the main function, continues to execute
{
    temp.read11(dhtTemp);
    Serial.println()
    if (temp.temperature > 100 ) 
    {
        tone(buzzer, 100, 500);
    }

}