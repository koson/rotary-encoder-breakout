/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 4);
//   avoid using pins with LEDs attached

unsigned long then = millis();

unsigned int limit = 63;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = 128;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition < 0) {
    newPosition = 0;
    myEnc.write(0);
  }
  if (newPosition > limit) {
    newPosition = limit;
    myEnc.write(limit);
  }
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
  unsigned long now = millis() - then;
  if (now < newPosition) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  if (now > limit) {
    then = millis();
  }
}
