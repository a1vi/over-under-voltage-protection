
/*
  Over and Under Voltage Protection System
  Arduino Uno + EmonLib + 20x4 LCD

  Normal Voltage: 192V to 242V
  Above 242V: Over Voltage
  Below 192V: Under Voltage

  LCD: RS=13, E=12, D4=11, D5=10, D6=9, D7=8
  Relay: D7
  LED: D6
*/

#include "EmonLib.h"
#include <LiquidCrystal.h>
#include <string.h>

// Create voltage measurement object
EnergyMonitor emon1;

// LCD connections
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Pin connections
const int RELAY_PIN = 7;
const int LED_PIN = 6;

// Voltage limits
const float V_LOW_TRIP = 192.0;
const float V_HIGH_TRIP = 242.0;

// Safety margin
const float V_HYST = 5.0;

// System variable
bool relayOn = false;


// Control relay and LED
void setRelay(bool on)
{
  relayOn = on;

  digitalWrite(RELAY_PIN, on ? HIGH : LOW);

  // LED ON means load is disconnected
  digitalWrite(LED_PIN, on ? LOW : HIGH);
}


// Display text on one LCD row
void showLine(byte row, const char *text)
{
  lcd.setCursor(0, row);
  lcd.print(text);

  // Clear remaining characters
  for (int i = strlen(text); i < 20; i++)
  {
    lcd.print(' ');
  }
}


void setup()
{
  // Set pin modes
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Keep load disconnected at startup
  setRelay(false);

  // Voltage sensor calibration
  emon1.voltage(A0, 187, 1.7);

  // Start LCD
  lcd.begin(20, 4);

  showLine(0, "VOLTAGE PROTECTION");
  showLine(1, "System Starting...");
  showLine(2, "Range: 192-242V");
  showLine(3, "Please Wait");

  delay(1000);
  lcd.clear();
}


void loop()
{
  // Measure RMS voltage
  emon1.calcVI(20, 500);

  float v = emon1.Vrms;

  const char *status;

  // Check for over-voltage
  if (v > V_HIGH_TRIP)
  {
    setRelay(false);
    status = "OVER VOLTAGE";
  }

  // Check for under-voltage
  else if (v < V_LOW_TRIP)
  {
    setRelay(false);
    status = "UNDER VOLTAGE";
  }

  // Voltage is safe enough to reconnect
  else if (v >= V_LOW_TRIP + V_HYST &&
           v <= V_HIGH_TRIP - V_HYST)
  {
    setRelay(true);
    status = "NORMAL VOLTAGE";
  }

  // Voltage is inside the trip limits but too close to a limit
  else
  {
    setRelay(false);
    status = "WAITING TO RECONNECT";
  }


  // Display voltage on LCD
  char buf[21];
  char num[10];

  dtostrf(v, 1, 1, num);
  snprintf(buf, sizeof(buf), "VOLTAGE = %s V", num);

  showLine(0, "VOLTAGE PROTECTION");
  showLine(1, buf);

  if (relayOn)
  {
    showLine(2, "RELAY: ON");
  }
  else
  {
    showLine(2, "RELAY: OFF");
  }

  showLine(3, status);

  delay(200);
}
