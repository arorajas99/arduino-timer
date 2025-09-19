#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "00001";

const int startSensor = 2;  // IR sensor or LDR setup
bool raceStarted = false;

void setup() {
  Serial.begin(9600);
  pinMode(startSensor, INPUT_PULLUP);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  if (!raceStarted && digitalRead(startSensor) == LOW) { // beam broken
    const char text[] = "START";
    radio.write(&text, sizeof(text));
    Serial.println("Sent START");
    raceStarted = true;
  }
}
