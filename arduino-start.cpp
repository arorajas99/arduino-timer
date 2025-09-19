#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

const int ldrPin = A0;
int threshold = 500;
bool raceStarted = false;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  
  if (!raceStarted && ldrValue < threshold) { 
    const char text[] = "START";
    radio.write(&text, sizeof(text));
    raceStarted = true;
  }
}
`
