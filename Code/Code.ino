#include <avr/interrupt.h>
#include <avr/sleep.h>

int buttonPin = 1;  //push button at PB1, Physical PIN 6 of ATtiny13
int LED_load_Pin = 0;     //LED driver at PB0, Physical PIN 5 of ATtiny13
int indicator_LED_Pin = 3;     //LED driver at PB0, Physical PIN 5 of ATtiny13
int master_power_Pin = 2;     //LED driver at PB0, Physical PIN 5 of ATtiny13
//int built_in_LED = 2; // Physical PIN 7 // which is connected to PIN 13 of Arduino UNO while using shield

volatile bool sleep = 0;
int button_press_count = 0;
int i;


//modified from http://playground.arduino.cc/Learning/arduinoSleepCode


void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(LED_load_Pin, OUTPUT);
  pinMode(indicator_LED_Pin, OUTPUT);
  pinMode(master_power_Pin, OUTPUT);
  //pinMode(built_in_LED, OUTPUT);

  for (i = 0; i < 3; i++)
  {
    digitalWrite(indicator_LED_Pin, HIGH);
    digitalWrite(LED_load_Pin, HIGH);
    delay(200);
    digitalWrite(indicator_LED_Pin, LOW);
    digitalWrite(LED_load_Pin, LOW);
    delay(100);
  }
}


void sleepNow()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
  sleep_enable();                          // enables the sleep bit in the mcucr register so sleep is possible
  attachInterrupt(0, wakeUpNow, LOW);     // use interrupt 0 (pin 2) and run function wakeUpNow when pin 2 gets LOW
  digitalWrite(LED_load_Pin, LOW);


  delay(1000);
  digitalWrite(indicator_LED_Pin, LOW);
  delay(100);
  digitalWrite(master_power_Pin, LOW);

  sleep_mode();                          // here the device is actually put to sleep!!

  sleep_disable();                       // first thing after waking from sleep: disable sleep...
  detachInterrupt(0);                    // disables interrupton pin 3 so the wakeUpNow code will not be executed during normal running time.

  digitalWrite(master_power_Pin, HIGH);
  digitalWrite(indicator_LED_Pin, HIGH);
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
          analogWrite(LED_load_Pin, 180);
          delay(500);
          break;

        case 2:
          analogWrite(LED_load_Pin, 255);
          delay(500);
          break;
        case 3:
          analogWrite(LED_load_Pin, 0);
          button_press_count = 0;
          sleepNow();
          break;

          //        default:
          //
          //          delay(2000);


          //          for (i = 0; i < 5; i++)
          //          {
          //            digitalWrite(LED_load_Pin, HIGH);
          //            delay(100);
          //            digitalWrite(LED_load_Pin, LOW);
          //            delay(80);
          //          }
      }

    }

  }
}

