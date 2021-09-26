/**************************************************************************************
 
Bud humidity
 
***************************************************************************************/
 
 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>                         // Include DHT library code
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_ADDR 0x3C   // Address may be different for your module, also try with 0x3D if this doesn't work

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dhtJar1(14,DHT11);             // Configure DHT library
DHT dhtJar2(12,DHT11);
DHT dhtJar3(13,DHT11);
DHT dhtJar4(15,DHT11);

char temperature[] = "00.0 C";
char humidity[]    = "00.0 %";
float humidityJar1;
float humidityJar2;
float humidityJar3;
float humidityJar4;
char auth[] = "lgBVO8wqAMe4pAoMuH_6SZoPGc3LR5PU";
char ssid[] = "The Abbotts"; //Voyager,
char pass[] = "th3BlueP1t"; //Sp0ckIsNotDead

BlynkTimer timer;

void setup(void)
{
 
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();           // Required to clear display
  display.display();
 
  dhtJar1.begin();                // Initialize the DHT library
  dhtJar2.begin();
  dhtJar3.begin();
  dhtJar4.begin();
  
  display.setTextColor(WHITE);
  display.setTextSize(1);           // Set text size
  display.setCursor(35, 0);
  display.print("Humidity");

  display.setCursor(0, 16);
  display.print("Jar One: ");
  display.setCursor(80, 16);
  display.print(" %");
  
  display.setCursor(0, 27);
  display.print("Jar Two: ");
  display.setCursor(80, 27);
  display.print(" %");

  display.setCursor(0, 38);
  display.print("Jar Three: ");
  display.setCursor(90, 38);
  display.print(" %");

  display.setCursor(0, 49);
  display.print("Jar Four: ");
  display.setCursor(85, 49);
  display.print(" %");

  
  display.display(); 
  delay(2000);
  
  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, pushData);
}

void pushData()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    // Read humidity
  humidityJar1 = dhtJar1.readHumidity();
  humidityJar2 = dhtJar2.readHumidity();
  humidityJar3 = dhtJar3.readHumidity();
  humidityJar4 = dhtJar4.readHumidity();
  Blynk.virtualWrite(V1, humidityJar1);
  Blynk.virtualWrite(V2, humidityJar2);
  Blynk.virtualWrite(V3, humidityJar3);
  Blynk.virtualWrite(V4, humidityJar4);
 
  Serial.print("Humidity Jar One: ");
  Serial.println(humidityJar1);
  
  // print data on the SSD1306 display
  display.setTextColor(WHITE,BLACK);
  display.setTextSize(1); 
  
  display.setCursor(50, 16);
  display.print(humidityJar1);

  display.setCursor(50, 27);
  display.print(humidityJar2);

  display.setCursor(62, 38);
  display.print(humidityJar3);

  display.setCursor(57, 49);
  display.print(humidityJar4);

  display.display();
}

void loop()
{
  Blynk.run();
 
}
