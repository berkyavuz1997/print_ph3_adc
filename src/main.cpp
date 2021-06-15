#include <LMP91000.h>
#include <Arduino.h>

const int average = 100;
const int sampling_interval = 10;

LMP91000 pstat = LMP91000();

void setupPH3()
{
  Wire.begin();
  delay(100);

  pstat.setThreeLead();
  delay(2000); //warm-up time for the gas sensor

  pstat.setGain(5);
  delay(100);

  pstat.setRLoad(0);
  delay(100);

  pstat.setBias(0);
  delay(100);

  pstat.setIntRefSource();
  delay(100);

  pstat.setIntZ(0);
  delay(100);

  pstat.lock();
  delay(100);
}

void setup()
{
  setupPH3();
  Serial.begin(115200);
}

void loop()
{
  uint32_t ph3_cumulative = 0;

  for (int i = 0; i < average; i++)
  {
    delay(sampling_interval);
    ph3_cumulative += analogRead(A0);
  }
  delay(sampling_interval);

  uint16_t ph3_single = analogRead(A0);
  uint16_t ph3_avg = ph3_cumulative / average;

  Serial.println("Single ADC read: " + String(ph3_single) + "     |      Average of " + String(average) + " samples: " + String(ph3_avg));
}
