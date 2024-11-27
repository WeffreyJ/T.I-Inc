#include <U8g2lib.h>

// OLED setup (replace U8G2_R0 with your display constructor)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Rotary Encoder Pins
#define CLK 2
#define DT 3
#define SW 4

// Variables
int currentMenu = 0;       // Tracks the current menu
int numMenus = 3;          // Number of menu items in the Main Menu
float var1 = 1000;         // Default value for Variable 1
float var2 = 0.5;          // Default value for Variable 2
float calFactor = 0.0;     // Default calibration factor

void calibrate(); // Declare the calibrate function

void setup() {
  // Initialize rotary encoder pins
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  // Initialize OLED display
  u8g2.begin();

  // Splash Screen
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 20, "Menu Demo");
  u8g2.drawStr(10, 40, "v1.0");
  u8g2.sendBuffer();
  delay(5000); // Show splash screen for 5 seconds
}
void displayCurrentValues() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB08_tr);
  u8g2.drawStr(10, 10, "Var 1     Var 2");
  
  char buf[16];
  snprintf(buf, sizeof(buf), "%d      %.1f", (int)var1, var2);
  u8g2.drawStr(10, 30, buf);

  u8g2.sendBuffer();
}
void countdownTimer() {
  float duration = (var1 * var2) / 100.0; // Calculate duration
  int steps = 50;                         // Number of steps for the progress bar
  float stepTime = duration / steps;      // Time for each step

  for (int i = 0; i <= steps; i++) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB08_tr);
    u8g2.drawStr(10, 10, "Countdown...");
    
    // Draw progress bar
    u8g2.drawFrame(10, 30, 100, 10); // Outline
    u8g2.drawBox(10, 30, (i * 100) / steps, 10); // Progress

    u8g2.sendBuffer();
    delay(stepTime * 1000); // Wait for stepTime seconds
  }
}
void mainMenu() {
  static int lastStateCLK = digitalRead(CLK); // Store the last state of CLK

  // Detect rotary encoder movement
  int currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK && currentStateCLK == LOW) {
    if (digitalRead(DT) != currentStateCLK) {
      currentMenu = (currentMenu + 1) % numMenus; // Increment menu
    } else {
      currentMenu = (currentMenu - 1 + numMenus) % numMenus; // Decrement menu
    }
  }
  lastStateCLK = currentStateCLK;

  // Display Main Menu
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvB08_tr);
  u8g2.drawStr(10, 10, "Main Menu:");

  for (int i = 0; i < numMenus; i++) {
    if (i == currentMenu) {
      u8g2.drawStr(10, 20 + (i * 12), ("> Option " + String(i + 1)).c_str());
    } else {
      u8g2.drawStr(10, 20 + (i * 12), ("  Option " + String(i + 1)).c_str());
    }
  }
  u8g2.sendBuffer();

  // Detect pushbutton press
  if (digitalRead(SW) == LOW) {
    delay(200); // Debounce delay
    executeOption(currentMenu);
  }
}
void calibrate() {
  static int lastStateCLK = digitalRead(CLK); // Store the last state of CLK

  while (true) {
    int currentStateCLK = digitalRead(CLK);
    if (currentStateCLK != lastStateCLK && currentStateCLK == LOW) {
      if (digitalRead(DT) != currentStateCLK) {
        calFactor += 0.1; // Increment calibration factor
      } else {
        calFactor -= 0.1; // Decrement calibration factor
      }
    }
    lastStateCLK = currentStateCLK;

    // Display calibration factor
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB08_tr);
    u8g2.drawStr(10, 10, "Calibration:");

    char buf[16];
    snprintf(buf, sizeof(buf), "%.1f", calFactor);
    u8g2.drawStr(10, 30, buf);
    u8g2.sendBuffer();

    // Exit on button press
    if (digitalRead(SW) == LOW) {
      delay(200); // Debounce
      break;
    }
  }
}

void executeOption(int option) {
  switch (option) {
    case 0:
      displayCurrentValues();
      delay(2000); // Pause to view
      break;
    case 1:
      countdownTimer();
      break;
    case 2:
      calibrate(); // Ensure this matches the declared function name
      break;
    default:
      break;
  }
}

void loop() {
  mainMenu();
}
