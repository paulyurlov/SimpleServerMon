#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define WIFI_SSID "peeper"
#define WIFI_PASSWORD "&Qu,i:rZOcO1E2MiMu"

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Подключаемся
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();

  // показать текст
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(24, 26);
  display.println("Starting up =)");
  display.display();
  delay(2000);
  display.clearDisplay();
}
void loop()
{
  WiFiClient wifiClient;
  HTTPClient http;

  http.begin(wifiClient, "http://95.84.200.10:89/p0sS7OmXDH");
  int httpCode = http.GET();         // Send the request
  String payload = http.getString(); // Get the response payload
  Serial.println("Kek lol");
  Serial.println(httpCode); // Print HTTP return code
  Serial.println(payload);  // Print request response payload
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  Serial.println(doc["cpu_temp"].as<float>());

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  // Welcome
  display.setCursor(0, 4);
  display.println("MyServer Stats:");

  const int x_1 = 24;
  const int x_2 = 48;
  // CPU Temp

  display.setCursor(0, x_1);
  display.printf("CPU_t:%d", doc["cpu_temp"].as<int>());
  // display.setCursor(40, 18);
  // display.println(doc["cpu_temp"].as<int>());

  // GPU Temp

  display.setCursor(0, x_2);
  display.printf("GPU_t:%d", doc["gpu_temp"].as<int>());
  // display.setCursor(40, 32);
  // display.println(doc["gpu_temp"].as<int>());

  // CPU Load

  display.setCursor(58, x_1);
  display.printf("CPU_l:%0.1f%%", doc["cpu_load"].as<float>());
  // display.setCursor(84, 18);
  // display.println(doc["cpu_load"].as<float>());

  // MEM Load

  display.setCursor(58, x_2);
  display.printf("MEM_l:%0.1f%%", doc["mem_load"].as<float>());

  display.display();
  display.clearDisplay();
  http.end(); // Close connection
  delay(2000);
}
