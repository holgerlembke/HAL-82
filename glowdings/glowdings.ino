// Board settings
// Board: "ATtiny45/85 (Optiboot)"
// Chip: "ATtiny85"
// Clock: "8 MHz (internal)"
// B.O.D. Level (Only set on ISP bootload): "B.O.D. Disabled (saves power)"
// Timer 1 Clock: "CPU (CPU frequency)"
// LTO (1.6.11+ only): "Enabled"
// millis()/micros(): "Enabled"


/*
   Glow-Coprozessor

   2020-10-21
     ++ start

   Hardware: Attiny25/45/85 https://github.com/SpenceKonde/ATTinyCore
  Reset 5[--]Vcc
     A3 3[  ]2 A1
Ctrl A2 4[  ]1      blink
      Gnd[--]0      pwm

      Ctrl LOW/HIGH-Zyklus
*/

const int sinus[] = {  0, 20, 45, 89, 134, 178, 221, 265, 308, 350, 391, 432,
                       472, 512, 550, 587, 623, 658, 691, 723, 754, 784,
                       812, 838, 863, 886, 907, 927, 945, 961, 976, 988,
                       999, 1007, 1014, 1019, 1022, 1023, 1023, 1023
                    };
const int sinuslen = sizeof(sinus) / sizeof(sinus[0]);
const int sinusschrittzeit = 60;
const long sinusdauer = sinusschrittzeit * sinuslen;

const byte PinPWM = 0;              // PWM auf Pin 0, 1, 4
const byte PinBlink = 1;            // HB-Blinker
const byte PinAnalogCtrl = A2;

//*****************************************************************************************************
//*****************************************************************************************************
void setup()
{
  pinMode(PinPWM, OUTPUT);
  pinMode(PinBlink, OUTPUT);

  analogWrite(PinPWM, 255);
  analogWrite(PinPWM, 0);
}

//*****************************************************************************************************
//*****************************************************************************************************
int analogValue(void) {
  int summe = 0;
  for (byte i = 0; i < 10; i++) {
    summe += analogRead(PinAnalogCtrl);
  }

  return summe / 10;
}

//*****************************************************************************************************
//*****************************************************************************************************
void loop() {
  static int step = 0;
  static int direction = 1;
  static byte state = 0;
  static unsigned long ticker = 0;
  static unsigned long blinker = 0;

  //-------------------------------------------------------------------
  // blinkerdings als funktionskontrolle
  if ( (state != 2) && (millis() - blinker > 1000) ) {
    digitalWrite(PinBlink, ! digitalRead(PinBlink));
    blinker = millis();
  }

  //-------------------------------------------------------------------
  // endlicher Automat, um weiter zu blinken
  const byte analogLimit = 50;
  switch (state) {
    case 0 :
      if (analogValue() < analogLimit) {
        state = 1;
      }
      break;
    case 1 :
      if (analogValue() > analogLimit) {
        state = 2;
      }
      break;
    case 2 :
      if  (millis() - ticker > sinusschrittzeit) {
        ticker = millis();
        analogWrite(PinPWM, sinus[step] >> 2); // sinus ist 10 bit, pwm ist 8 bit
        step += direction;
        if (step < 0) {
          step = 0;
          direction = 1;
          state = 0;
        }
        if (step > sinuslen - 1) {
          step = sinuslen - 1;
          direction = -1;
        }
      }
      break;
  }
}
