//Define and include Libraries
#define USE_ARDUINO_INTERRUPTS true    
#define dht_apin A0 // Analog Pin Temperature sensor is connected to
#include "dht.h" // Temperature sensor library, this needs to be downloaded
#include <PulseSensorPlayground.h> // heartbeat sensor library, in the official repos

// Define Variables
int time_in_millis = 0;
float time_in_seconds = 0;
float MyTemp = 0;
int MyBPM = 0;
int buzzer = 11;//the pin of the active buzzer
// Variables for the heart monitor
const int PulseWire = 5; // Analog Pin
int Threashold = 550; // analog threshhold for a beat

PulseSensorPlayground heartbeat; //Create heartbeat object
dht DHT; //Create temperature object

void setup()
// init function, all the things that happen once
{
    //Initialize Serial for diagnostics
    Serial.begin(9600);
    delay(500);//Delay to let system boot
    heartbeat.analogInput(PulseWire);//Initialize pins as output
    heartbeat.setThreshold(Threashold); // Define heartbeat threashold
    pinMode(buzzer, OUTPUT); //initialize the buzzer pin as an output
    heartbeat.begin(); // function to begin heart monitor, im wondering if I need to pause it, wait a second, and get temperature
    Serial.println("Time , Temperature, BPM"); // print to serial in csv format.
    }

void loop()
//think of this as the main function, continues to execute
{
    int MyBPM = heartbeat.getBeatsPerMinute(); // get the BPM
    heartbeat.pause();
    delay(100);
    DHT.read11(dht_apin); // Initialize reading of temperature
    float MyTemp = DHT.temperature; // Set temperature value.
    heartbeat.resume();
    time_in_millis = millis();
    time_in_seconds = millis() / 1000;
    // Print data in CSV format
    Serial.print(time_in_seconds); //time
    Serial.print(",\t");
    Serial.print(MyTemp); //prints temperature
    Serial.print(",\t");
    Serial.println(MyBPM); // prints BPM
    //conditional to check if it meets requirements for stress. If so, output buzzer tone
    if (MyTemp >= 38 and MyBPM >= 100)
    {
        tone(buzzer, 100, 500);
    }
    // DHT 11 tutorials say to give it at least 2 seconds of delay before reading again.
    //Giving time also allows the heartbeat sensor to gather data.
    delay(3000);
}