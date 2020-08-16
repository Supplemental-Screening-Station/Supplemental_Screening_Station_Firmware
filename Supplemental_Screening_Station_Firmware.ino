#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_ST7789.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//The setup function is called once at startup of the sketch
#define TFT_CS  5
#define TFT_DC  16
#define TFT_RST 17

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

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
	//mlx.writeEmissivity(1.0);
}

// The loop function is called in an endless loop
void loop()
{
	  float objtemp = mlx.readObjectTempC()*1.06;
	  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
	  Serial.print("*C\tObject = "); Serial.print(objtemp); Serial.println("*C");
	  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
	  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()*1.06); Serial.println("*F");
	  tft.fillScreen(ST77XX_WHITE);
	  tft.setCursor(0, 0);
	  tft.setTextColor(ST77XX_BLACK);
	  tft.setTextSize(8);
	  tft.setTextWrap(false);
	  tft.print(String(objtemp));
	  Serial.println();
	  delay(500);
//Add your repeated code here
}
