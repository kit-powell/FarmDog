
/* FarmDog firmware notes and attribs go here 
Kit Powell
July 15 2014

/***************************************************************************
  This is a library for the BME680 gas, humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME680 Breakout
  ----> http://www.adafruit.com/products/3660

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <bsec.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme;  // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1)
      ;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);  // 320*C for 150 ms
}

void loop() {
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  Serial.println("{"); //add { to the Json}

 
  Serial.print("  \"id\"");
  Serial.print(" : ");
  Serial.println("109");
  
  Serial.print("  \"temp\"");
  Serial.print(" : ");
  Serial.println(bme.temperature);

  Serial.print("  \"humidity\"");
  Serial.print(" : ");
  Serial.println(bme.humidity);

  Serial.print("  \"pressure\"");
  Serial.print(" : ");
  Serial.println(bme.pressure/100);

  Serial.print("  \"Gas_R\"");
  Serial.print(" : ");
  Serial.print(bme.gas_resistance);




  Serial.println("");
  Serial.println("}"); //add } to Json
  delay(1000);
}