
/*Testing LCD via IIC bus and MAX31865 - PT100 temerature probe */

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here:
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.

#include <LiquidCrystal_I2C.h>

/*************************************************** 
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_MAX31865.h>

/*-----( Declare Constants )-----*/
//none
/*-----( Declare objects )-----*/
// set the LCD address to 0x20 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address 0x20, 0x3f or something else
                                                                // in order to find the right address run IICaddress.ino


// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 max = Adafruit_MAX31865(10, 11, 12, 13);
Adafruit_MAX31865 max2 = Adafruit_MAX31865(9, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 max = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      427.0
#define RREF2      427.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0
#define RNOMINAL2  100.0


/*-----( Declare Variables )-----*/
//none

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  //initialize the hardware UART for speed 9600

  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines
  
  
  

  max.begin(MAX31865_2WIRE);  // set to 2WIRE or 4WIRE as necessary
  max2.begin(MAX31865_2WIRE); 
// ------- Quick 5 blinks of backlight  -------------
  for(int i = 0; i< 5; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on 
 
//-------- Write characters on the display ----------------
  // NOTE: Cursor Position: CHAR, LINE) start at 0 
  lcd.setCursor(3,0); //Start at character 4 on line 0
  lcd.print("Hello, world!");
  delay(5000);
  lcd.clear();
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
    uint16_t rtd = max.readRTD();
 


  /*----------Print some values to terminal-----------*/
  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  
  ratio /= 32768;
  
 
  Serial.print("Ratio = "); Serial.println(ratio,8);
  Serial.print("Resistance = "); Serial.println(RREF*ratio,8);
  Serial.print("Temperature = "); Serial.println(max.temperature(RNOMINAL, RREF));
  
  /*----------Print to LCD-----------*/
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hanna testing!");
  lcd.setCursor(0, 1);
  lcd.print("Sek=");
  lcd.print(millis()/1000);
  lcd.setCursor(10, 1);
  lcd.print("Min=");
  //lcd.setCursor(12, 2);
  lcd.print(millis()/60000);
  lcd.setCursor(0, 2);
  lcd.print("Res="); lcd.print(RREF*ratio,8);
  lcd.setCursor(0, 3);
  lcd.print("Temp= "); lcd.print(max.temperature(RNOMINAL, RREF));
  lcd.print(" = "); lcd.print(max2.temperature(RNOMINAL2, RREF2));
  delay(1000);
  
  

}/* --(end main loop )-- */


/* ( THE END ) */
