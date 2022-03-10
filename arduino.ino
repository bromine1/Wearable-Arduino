#include "dht.h"
#include <PulseSensorPlayground.h>
#define dht_apin A0 // Analog Pin sensor is connected to
#define USE_ARDUINO_INTERRUPTS true

float MyTemp = 0;
int MyBPM = 0;
int buzzer = 11;//the pin of the active buzzer
const int PulseWire = 5;
int Threashold = 550;

PulseSensorPlayground heartbeat; //Give the module a bertter name
dht DHT; //Defines dht as DHT. Think import dht as DHT

void setup()
// init function, all the things that happen once
{
    //Initialize Serial for diagnostics
    Serial.begin(9600);
    delay(500);//Delay to let system boot
    heartbeat.analogInput(PulseWire);//Initialize pins as output
    heartbeat.setThreshold(Threashold); // Define heartbeat threashold
    pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
    Serial.print(heartbeat.begin());
if (1 == 1) {
        Serial.println("Time , Temperature, BPM");
    }
}
void loop()
//think of this as the main function, continues to execute
{
    DHT.read11(dht_apin); // Initialize reading of temperature
    float MyTemp = DHT.temperature;
    int MyBPM = heartbeat.getBeatsPerMinute();
    // Print data in CSV format
    Serial.print(millis());
    Serial.print(",\t");
    Serial.print(MyTemp); //prints temperature
    Serial.print(",\t");
    Serial.println(MyBPM);
    if (MyTemp > 100 and MyBPM > 100)
    {
        tone(buzzer, 100, 500);
    }
    delay(3000);
    }