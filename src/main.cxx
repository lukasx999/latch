#include <Arduino.h>

#include "latch.hxx"

#define LED_ON()       (PORTD |=  (1 << PORTD2))
#define LED_OFF()      (PORTD &= ~(1 << PORTD2))
#define LED_SETUP()    (DDRD  |=  (1 << DDD2  ))
#define CHECK_INPUT() !(PINC  &   (1 << PINC1 ))

#define BLINK_SETUP()  (DDRD  |=  (1 << DDD7  ))
#define BLINK() {          \
  PORTD |=  (1 << PORTD7); \
  delay(500);              \
  PORTD &= ~(1 << PORTD7); \
  delay(500);              \
} static_assert(true)



Latch g_latch(3);

void setup()
{
  LED_SETUP();
  BLINK_SETUP();
  Serial.begin(9600);
}

void loop()
{

  // do something else...
  BLINK();


  // Latch
  g_latch.trigger(CHECK_INPUT());

  if (CHECK_INPUT())
    Serial.println("button was pressed");

  if (g_latch.is_latched()) {
    LED_ON();
    Serial.println("LED ON");

  } else {
    LED_OFF();

  }

}