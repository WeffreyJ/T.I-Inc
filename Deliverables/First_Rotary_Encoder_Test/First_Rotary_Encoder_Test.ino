#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDRESS 0x3C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Rotary Encoder pins
#define CLK 2
#define DT 3
#define SW 4

int currentMenu = 0; // Track the current menu option
int numMenus = 5;    // Total number of menu options

void setup() {
  Serial.begin(9600);

  // OLED initialization
  if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // Stop if OLED initialization fails
  }

  delay(2000);         // Allow time for the display to initialize
  oled.clearDisplay(); // Clear the display
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.println("OLED Initialized!");
  oled.display();
  delay(1000);

  // Rotary encoder setup
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);

  // Display the initial menu
  updateDisplay();
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
    updateDisplay(); // Update the OLED display
  }
  lastStateCLK = currentStateCLK;

  // Detect button press
  if (digitalRead(SW) == LOW) {
    selectOption();
    delay(200); // Debounce delay
  }
}

void updateDisplay() {
  oled.clearDisplay(); // Clear the screen
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.println("Menu:");

  // Display the menu options
  for (int i = 0; i < numMenus; i++) {
    if (i == currentMenu) {
      oled.print("> "); // Highlight the current menu option
    } else {
      oled.print("  ");
    }
    oled.println("Option " + String(i + 1));
  }
  oled.display(); // Send the buffer to the display
}

void selectOption() {
  oled.clearDisplay(); // Clear the screen
  oled.setCursor(0, 0);
  oled.println("Selected Option:");
  oled.println("Option " + String(currentMenu + 1)); // Display the selected option
  oled.display();
  delay(1000); // Show the selection message for 1 second
  updateDisplay(); // Return to the menu
}
