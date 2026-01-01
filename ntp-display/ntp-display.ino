// Libraries to get time from NTP Server
#include <WiFi.h>
#include <time.h>
// Display library
#include <U8g2lib.h>

// Replace with your network credentials
const char* ssid = "SSID";
const char* password = "PASSWORD";

// NTP server setup
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -28790;    // Adjust this for your timezone, up (or less negative) = set time later, down (or more negative) = set time earlier, -28850 seems good for Pacific
const int daylightOffset_sec = 0;  // Adjust if DST is in effect, 0 = no, 3600 = yes?

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

// Function that prints formatted date and time
void printDateTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  char formattedTime[80];  // Buffer to store the formatted string
  // strftime(formattedTime, sizeof(formattedTime), "%A, %B %d %Y %H:%M:%S", &timeinfo); // OG version
  strftime(formattedTime, sizeof(formattedTime), "%H:%M:%S", &timeinfo);
  Serial.println(formattedTime);

  // Time
  char time_buffer[20];
  snprintf(time_buffer, sizeof(time_buffer), formattedTime, formattedTime);
  u8g2.drawStr(xOffset + 0, yOffset + 25, time_buffer);
  // u8g2.sendBuffer(); // No longer needed, we do this later

  // Date
  strftime(formattedTime, sizeof(formattedTime), "%m / %d / %Y", &timeinfo);
  snprintf(time_buffer, sizeof(time_buffer), formattedTime, formattedTime);
  u8g2.drawStr(xOffset + 0, yOffset + 35, time_buffer);
  u8g2.sendBuffer();
}

void setup(void) {
  u8g2.begin();
  u8g2.setContrast(255);                // Set contrast to maximum because it's an OLED with only on/off
  u8g2.setBusClock(400000);             // 400kHz I2C
  u8g2.setFlipMode(flipDisplaySetting); // Set which orientation is up

  // Breakpoint Test
  // u8g2.setFont(u8g2_font_10x20_tr);
  // char buffer[10];
  // snprintf(buffer, sizeof(buffer), "test", "test");
  // u8g2.drawStr(xOffset + 0, yOffset + 10, buffer);
  // snprintf(buffer, sizeof(buffer), "test", "test");
  // u8g2.drawStr(xOffset + 0, yOffset + 25, buffer);
  // u8g2.sendBuffer();

  // Connect to WiFi
  // u8g2.setFont(u8g2_font_10x20_tr);

  // u8g2.setFont(u8g2_font_3x3basic_tr); // Too small
  u8g2.setFont(u8g2_font_4x6_tr);
  char buffer[15];
  snprintf(buffer, sizeof(buffer), "wifi connect", "wifi connect");
  u8g2.drawStr(xOffset + 0, yOffset + 5, buffer);
  u8g2.sendBuffer();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Check for non-connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Print the status
  snprintf(buffer, sizeof(buffer), "success", "success");
  u8g2.drawStr(xOffset + 0, yOffset + 15, buffer);
  u8g2.sendBuffer();

  // Configure NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("NTP time configured.");
}

void loop(void) {
  printDateTime();
  delay(1000);
}