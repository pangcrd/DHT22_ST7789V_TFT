#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <Adafruit_Sensor.h>
#include <ST7789v_arduino.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>
#include <DHT.h> 
//#include <SimpleKalmanFilter.h>
#include "iconBitmap.h"

#define TFT_CS   PA4
#define TFT_RST  PB12// Or set to -1 and connect to Arduino RESET pin
#define TFT_DC   PA3
#define TFT_MOSI PA7  // Data out
#define TFT_SCLK PA5  // Clock out
#define POT_PIN   PB0
#define LED PA8


int lastValue = 0;
unsigned long prevMillis = 0;
const long myTimer = 5000;
float last_temp, last_hum;  


/*My STM32F103C6T6 not enough FLASH memmory for KalmanFilter analog signal*/
/*Uncomment SimpleKalmanFilter if you use other chip*/

 ST7789v_arduino tft = ST7789v_arduino(TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_CS); //for display with CS pin
 //SimpleKalmanFilter valuefillter(2, 2, 0.01);

 /**************************DTH DEFINE************************/
#define DHTPIN PB15
#define DHTTYPE    DHT22   
DHT dht(DHTPIN, DHTTYPE);

/**************************DTH END************************/


void DrawSlider(){
  tft.drawRoundRect(3, 262, 233, 39, 2, 0xFABF);
  tft.setTextColor(0x57EA);
  tft.setTextWrap(false);
  //tft.setFont(&FreeMono12pt7b);
  tft.setTextSize(2);
  tft.setCursor(62, 202);
  tft.println("Brightness");
  int potValue = analogRead(POT_PIN);
  //float Valfillter = valuefillter.updateEstimate(potValue);
  // Serial.println(Valfillter);
  tft.setTextSize(2);
  tft.fillRect(62, 231, 123, 22, 0xFFFF);
  tft.setCursor(80, 235); //value pos
  tft.setTextColor(0xFAAA);
  tft.println(potValue);
  tft.drawBitmap(13, 229, bright, 25, 27, 0xF7EA);


  int filldWidth = map(potValue, 0, 3999, 0, 231); 
  if (potValue > lastValue) {
    tft.fillRect(4 + map(lastValue, 0, 3999, 0, 231), 263, filldWidth - map(lastValue, 0, 3999, 0, 231), 37, 0x57FF); 
  } else if (potValue < lastValue) {
    tft.fillRect(4 + filldWidth, 263, map(lastValue, 0, 3999, 0, 231) - filldWidth, 37,BLACK); 
  }
  lastValue = potValue;
  int ledBrightness = map(lastValue, 0, 3999, 0, 255);
  analogWrite(LED, ledBrightness);
}

void tempHumi(){

   float temperature = dht.readTemperature();
   float humidity = dht.readHumidity();


   if (temperature != last_temp)
  {
  tft.fillRect(82, 70, 90, 30, 0xF49B);
  tft.setTextColor(0xFAAA);
  tft.setTextSize(2.5);
  tft.setCursor(88, 75);
  tft.print(temperature,1);         
  tft.print((char)247);     // Symbol '°' 
  tft.print("C"); 
  }
     if ( humidity != last_hum)
  {
  tft.fillRect(80, 150, 70, 30, 0xBFBF);
  tft.setTextColor(0xFABE);
  tft.setTextSize(2.5);
  tft.setCursor(90, 160);
  tft.print(humidity,1);
  tft.print("%"); 
  }
  last_temp = temperature;
  last_hum = humidity;
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  SPI.beginTransaction(SPISettings(55000000, MSBFIRST, SPI_MODE1)); 
  tft.init(320,240);  
  tft.setRotation(0);  
  tft.invertDisplay(false);  // Đảo ngược màu nếu cần
  tft.fillScreen(BLACK);
  pinMode(POT_PIN, INPUT);
  analogReadResolution(12);

    //tft.drawBitmap(169, 35, temperature_ico, 16, 16, 0xFABF);
  tft.fillRoundRect(65, 59, 110, 45, 3, 0xF49B);
  tft.setTextSize(3);
  tft.setTextColor(0xFFE7);
  tft.setCursor(25, 30);
  tft.print("TEMPERATURE");
 
  //tft.drawBitmap(169, 117, humidity_ico, 11, 16, 0x57FF);
  tft.fillRoundRect(65, 144, 110, 45, 3, 0xBFBF);
  tft.setTextSize(3);
  tft.setTextColor(0x553F);
  tft.setCursor(50, 115);
  tft.print("HUMIDITY");

}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis >= myTimer) {// Update sensor value after 5 seconds
    prevMillis = currentMillis;
    tempHumi();
  }
  DrawSlider(); //Update slide
  delay(50);
}

