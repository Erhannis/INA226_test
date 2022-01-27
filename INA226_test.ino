#include <Wire.h>
#include "INA226.h"

INA226 INA(0x40);

void setup() {
  Wire.begin();
  Serial.begin(115200);

  //String s = null;

  Serial.println("Scanning...");

  byte error, address;
  
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address ");
      Serial.print(address);
      Serial.println(" !");
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address ");
      Serial.print(address);
      Serial.println(" !");
    }
  }
  Serial.println("...done");



  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  INA.setMaxCurrentShunt(1, 0.002);
}

void loop() {
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER");
  for (int i = 0; i < 20; i++)
  {
    float bv = 0;
    float sv = 0;
    float c = 0;
    float p = 0;
    const int N = 800;
    for (int j = 0; j < N; j++) {
      bv += INA.getBusVoltage();
      sv += INA.getShuntVoltage_mV();
      c += abs(INA.getCurrent_mA());
      p += INA.getPower_mW();
      delay(1);
    }
    Serial.print(bv/N, 3);
    Serial.print("\t");
    Serial.print(sv/N, 3);
    Serial.print("\t");
    Serial.print(c/N, 3);
    Serial.print("\t");
    Serial.print(p/N, 3);
    Serial.print("\t");
    Serial.print(millis());
    Serial.println();
  }
}
