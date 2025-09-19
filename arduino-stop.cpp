#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

const int ldrPin = A0;
int threshold = 500;

bool raceActive = false;
unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
}

void loop() {
  if (radio.available() && !raceActive) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    if (String(text) == "START") {
      raceActive = true;
      startTime = millis();
    }
  }

  if (raceActive) {
    int ldrValue = analogRead(ldrPin);
    if (ldrValue < threshold) { 
      unsigned long finishTime = millis();
      unsigned long raceTime = finishTime - startTime;
      Serial.print("Race Time: ");
      Serial.print(raceTime);
      Serial.println(" ms");
      raceActive = false;
    }
  }
}
