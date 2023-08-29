#include "../Readers.h"


#define LED_PIN 2

AnalogReader<uint8_t> light_detector(A2);
DigitalReader ir_detector(3);


void setup()
{
  ir_detector.init(); // INPUT_PULLUP default
  pinMode(LED_PIN, OUTPUT); // simple LED.
}

void loop()
{
  ir_detector.read();
  light_detector.read(255, 0); // map 0, 1023 to 255, 0

  if (ir_detector.onActivate()) {
    analogWrite(LED_PIN, light_detector.getConvertedValue());
  }

  if (ir_detector.onDeactivate()) {
    digitalWrite(LED_PIN, 0);
  }
  delay(1000);
}