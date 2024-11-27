#include <U8g2lib.h>

// Rotary Encoder Pins
#define CLK 2
#define DT 3
#define SW 4

// Initialize U8g2 for I2C OLED (replace U8G2_R0 with the correct constructor for your display)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Menu variables
int currentMenu = 0; // Track the current menu option
int numMenus = 5;    // Total number of menu options

void setup() {
  // Rotary Encoder setup
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  // Initialize U8g2
  u8g2.begin();

  // Show loading animation
  loadingScreen();
}

void loop() {
  static int lastStateCLK = digitalRead(CLK); // Store the last state of CLK
  int currentStateCLK = digitalRead(CLK);    // Read the current state of CLK

  // Detect rotation
  if (currentStateCLK != lastStateCLK && currentStateCLK == LOW) {
    if (digitalRead(DT) != currentStateCLK) {
      currentMenu = (currentMenu + 1) % numMenus; // Increment menu
    } else {
      currentMenu = (currentMenu - 1 + numMenus) % numMenus; // Decrement menu
    }
    updateMenu(); // Update the menu display
  }
  lastStateCLK = currentStateCLK;

  // Detect button press
  if (digitalRead(SW) == LOW) {
    selectOption();
    delay(200); // Debounce delay
  }
}

void loadingScreen() {
  for (int i = 0; i < 10; i++) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr); // Select a font
    u8g2.drawStr(10, 30, "Loading");
    for (int j = 0; j <= i; j++) {
      u8g2.drawStr(70 + (j * 5), 30, ".");
    }
    u8g2.sendBuffer();
    delay(200); // Delay for animation
  }
}

void updateMenu() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB12_tr); // Select a bold font for the menu
  u8g2.drawStr(10, 15, "Main Menu:");
  for (int i = 0; i < numMenus; i++) {
    if (i == currentMenu) {
      u8g2.setFont(u8g2_font_helvB08_tr); // Highlight selected option
      u8g2.drawStr(20, 30 + (i * 12), ("> Option " + String(i + 1)).c_str());
    } else {
      u8g2.setFont(u8g2_font_helvR08_tr); // Regular font for other options
      u8g2.drawStr(20, 30 + (i * 12), ("  Option " + String(i + 1)).c_str());
    }
  }
  u8g2.sendBuffer();
}

void selectOption() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr); // Use a different font for selection
  u8g2.drawStr(10, 30, ("Selected: Option " + String(currentMenu + 1)).c_str());
  u8g2.sendBuffer();
  delay(1000); // Display the selection for 1 second
  updateMenu(); // Return to the menu
}
