#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


Adafruit_SSD1306 display(-1);

void setup(){
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);



  display.display();

}

void loop(){
  delay(250);
  float readData = dht.computeHeatIndex();
  float hu = dht.readHumidity();
  float temp = dht.readTemperature();

  display.clearDisplay();
  display.setCursor(0,20);

  display.print(F("Humidade: "));
  display.print(hu);
  display.print("\nTemperatura: ");
  display.print(temp);
  display.print("°C ");
  delay(500);
  display.display();

}