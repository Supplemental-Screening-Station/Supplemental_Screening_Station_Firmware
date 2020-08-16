#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_ST7789.h>
#include <RBE1001Lib.h>
#include "Rangefinder.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//The setup function is called once at startup of the sketch
#define TFT_CS  5
#define TFT_DC  16
#define TFT_RST 17
#define ULTRASONIC_TRIG 4
#define ULTRASONIC_ECHO 27

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Rangefinder rangefinder1;

void setup()
{
// Add your initialization code here
	Serial.begin(115200);
	Serial.println("Adafruit MLX90614 test");
	mlx.begin();
	Wire.begin(22,21,100000);
	SPI.begin(18,19,23,5);

	tft.init(135, 240);
	tft.setRotation(1);
	tft.fillScreen(ST77XX_WHITE);
	rangefinder1.attach(ULTRASONIC_TRIG, ULTRASONIC_ECHO);

	//mlx.writeEmissivity(1.0);
}

// The loop function is called in an endless loop
void loop()
{
	  float objtemp = mlx.readObjectTempC()*1.06;
	  float distance = rangefinder1.getDistanceCM();
	  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
	  Serial.print("*C\tObject = "); Serial.print(objtemp); Serial.println("*C");
	  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
	  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()*1.06); Serial.println("*F");
	  //tft.fillScreen(ST77XX_WHITE);

	  tft.setTextSize(4);
	  tft.setCursor(0, 0);
	  tft.setTextColor(ST77XX_BLACK);
	  tft.setTextWrap(false);
	  tft.print(String(distance));
	  tft.setCursor(180, 0);
	  tft.print("cm");
	  tft.setCursor(0, 135/2);
	  tft.print(String(objtemp));
	  tft.setCursor(180, 135/2);
	  tft.print("c");
	  delay(250);
	  tft.setTextSize(4);
	  tft.setCursor(0, 0);
	  tft.setTextColor(ST77XX_WHITE);
	  tft.setTextWrap(false);
	  tft.print(String(distance));
	  tft.setCursor(0, 135/2);
	  tft.print(String(objtemp));

	  Serial.println();

//Add your repeated code here
}
