#include <avr/interrupt.h>
#include <avr/sleep.h>

int buttonPin = 1;  //push button at PB1, Physical PIN 6 of ATtiny13
int high_bright_enable_pin = 0;     //LED driver at PB0, Physical PIN 5 of ATtiny13
int indicator_LED_Pin = 3;     //LED driver at PB3, Physical PIN 2 of ATtiny13
int master_power_Pin = 2;     //LED driver at PB2, Physical PIN 7 of ATtiny13
//int built_in_LED = 2; // Physical PIN 7 // which is connected to PIN 13 of Arduino UNO while using shield

volatile bool sleep = 0;
int button_press_count = 0;
int i;


//modified from http://playground.arduino.cc/Learning/arduinoSleepCode


void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(high_bright_enable_pin, OUTPUT);
  pinMode(indicator_LED_Pin, OUTPUT);
  pinMode(master_power_Pin, OUTPUT);
  //pinMode(built_in_LED, OUTPUT);

  for (i = 0; i < 3; i++)
  {
    digitalWrite(indicator_LED_Pin, HIGH);
    //digitalWrite(high_bright_enable_pin, HIGH);
    delay(200);
    digitalWrite(indicator_LED_Pin, LOW);
    //digitalWrite(high_bright_enable_pin, LOW);
    delay(100);
  }
  sleepNow();
}


void sleepNow()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
  sleep_enable();                          // enables the sleep bit in the mcucr register so sleep is possible
  attachInterrupt(0, wakeUpNow, LOW);     // use interrupt 0 (pin 2) and run function wakeUpNow when pin 2 gets LOW
  
  digitalWrite(master_power_Pin, LOW);
  digitalWrite(high_bright_enable_pin, LOW);
  
  delay(300);
  digitalWrite(indicator_LED_Pin, LOW);
  delay(100);
  

  sleep_mode();                          // here the device is actually put to sleep!!

  sleep_disable();                       // first thing after waking from sleep: disable sleep...
  detachInterrupt(0);                    // disables interrupton pin 3 so the wakeUpNow code will not be executed during normal running time.

  digitalWrite(indicator_LED_Pin, HIGH);
  delay(300);
  digitalWrite(master_power_Pin, HIGH);
}



void wakeUpNow() {       // here the interrupt is handled after wakeup

  //execute code here after wake-up before returning to the loop() function
  // timers and code using timers (serial.print and more...) will not work here.
  sleep = 0;
}


void loop()
{

  read_switch();

}

void read_switch()
{
  if (digitalRead(buttonPin) == LOW) // if Switch is ON
  {

    delay(50); // debouncing delay

    if (digitalRead(buttonPin) == LOW)
    {
      button_press_count++;

      switch (button_press_count)
      {
        case 1:
          digitalWrite(high_bright_enable_pin, HIGH);
          delay(500);
          break;
        case 2:
          button_press_count = 0;
          sleepNow();
          break;
      }

    }

  }
}

