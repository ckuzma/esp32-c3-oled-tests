// Libraries to get time from NTP Server
// #include <WiFi.h>
// #include <time.h>
// Display library
#include <U8g2lib.h>

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

void setup(void) {
  u8g2.begin();
  u8g2.setContrast(255);                // Set contrast to maximum because it's an OLED with only on/off
  u8g2.setBusClock(400000);             // 400kHz I2C
  u8g2.setFlipMode(flipDisplaySetting); // Set which orientation is up

  // Breakpoint
  u8g2.setFont(u8g2_font_10x20_tr);
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "Test", "Test");
  u8g2.drawStr(xOffset + 0, yOffset + 10, buffer);
  u8g2.sendBuffer();
}

void loop(void) {

}