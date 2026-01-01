// Libraries to get time from NTP Server
#include <WiFi.h>
#include <time.h>
// Display library
#include <U8g2lib.h>

// Replace with your network credentials
const char* ssid = "SSID";
const char* password = "PASSWORD";

#define OLED_RESET U8X8_PIN_NONE
#define OLED_SDA 5
#define OLED_SCL 6

// Display Initialization
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);

/*
Display is 72 (length) x 40 (width) pixels large
*/
// Display Settings
int flipDisplaySetting = 1;     // Set if the display should be flipped
int yOffset = 0;                // Set to 0 if flipDisplaySetting == 1, otherwise 24
int xOffset = 28;               // Seems to be good at 28 regardless of the display orientation
int counter = 0;                // Used to display runtime in seconds


void display_content(int counter) {
  u8g2.clearBuffer();

  // Display text
  u8g2.setFont(u8g2_font_10x20_tr);
  char buffer[21];
  snprintf(buffer, sizeof(buffer), " %d", counter);
  u8g2.drawStr(xOffset + 0, yOffset + 24, buffer);
  
  // Send it
  u8g2.sendBuffer();
}


void setup(void) {
  u8g2.begin();
  u8g2.setContrast(255);                // Set contrast to maximum because it's an OLED with only on/off
  u8g2.setBusClock(400000);             // 400kHz I2C
  u8g2.setFlipMode(flipDisplaySetting); // Set which orientation is up

  // Connect to WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Print the status
  char buffer[30];
  snprintf(buffer, sizeof(buffer), " %s", "Connecting to WiFi ..");
  u8g2.drawStr(xOffset + 0, yOffset + 10, buffer);

  // Check for non-connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Print the status
  snprintf(buffer, sizeof(buffer), " %s", "Connecting to WiFi ..");
  u8g2.drawStr(xOffset + 0, yOffset + 24, buffer);
}

void loop(void) {

}