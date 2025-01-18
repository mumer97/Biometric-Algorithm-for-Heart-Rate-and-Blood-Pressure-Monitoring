#include <Wire.h>
#include <Adafruit_SSD1306.h> // OLED display library
#include <Adafruit_MAX30102.h> // MAX30102 library for PPG
#include <Filters.h> // Simple filter library

// OLED display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

// MAX30102 sensor
Adafruit_MAX30102 max30102;

// Variables for signal processing
float ppgValue, ecgValue; 
float heartRate = 0;
float ptt = 0; // Pulse Transit Time
unsigned long lastPPGTime = 0, lastECGTime = 0;

// Filter for smoothing data
FilterOnePole lowPassFilter(LOWPASS, 0.1); 

// Constants for BP estimation (example coefficients from ML model)
const float bpIntercept = 120.0; // Replace with trained model value
const float bpCoeffPTT = -0.5;  // Replace with trained model value

void setup() {
  Serial.begin(115200);

  // Initialize OLED display
  if (!display.begin(SSD1306_I2C_ADDRESS, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Initialize MAX30102
  if (!max30102.begin()) {
    Serial.println("MAX30102 initialization failed!");
    for (;;);
  }
  Serial.println("MAX30102 initialized.");

  // Initial message
  displayMessage("Initializing...");
}

void loop() {
  // Read PPG sensor data
  ppgValue = lowPassFilter.input(max30102.getRed());

  // Simulate ECG signal reading (replace with actual AD8232 implementation)
  ecgValue = analogRead(A0); // ECG connected to A0 pin
  ecgValue = lowPassFilter.input(ecgValue);

  // Detect peaks in PPG to calculate Heart Rate
  if (detectPPGPeak(ppgValue)) {
    unsigned long currentTime = millis();
    heartRate = 60000.0 / (currentTime - lastPPGTime); // Heart rate in bpm
    lastPPGTime = currentTime;
  }

  // Calculate PTT when both PPG and ECG peaks are detected
  if (detectECGPeak(ecgValue)) {
    unsigned long currentTime = millis();
    ptt = (currentTime - lastECGTime) / 1000.0; // PTT in seconds
    lastECGTime = currentTime;
  }

  // Estimate Blood Pressure
  float bloodPressure = bpIntercept + bpCoeffPTT * ptt;

  // Display results
  displayResults(heartRate, bloodPressure);
}

bool detectPPGPeak(float value) {
  // Simple threshold-based peak detection (fine-tune as needed)
  static float prevValue = 0;
  if (value > 2000 && prevValue < value) { // Threshold of 2000 (adjust based on sensor)
    prevValue = value;
    return true;
  }
  prevValue = value;
  return false;
}

bool detectECGPeak(float value) {
  // Simple threshold-based peak detection for ECG
  static float prevValue = 0;
  if (value > 500 && prevValue < value) { // Threshold of 500 (adjust based on sensor)
    prevValue = value;
    return true;
  }
  prevValue = value;
  return false;
}

void displayResults(float hr, float bp) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Heart Rate: ");
  display.print(hr, 1);
  display.println(" bpm");
  display.print("Blood Pressure: ");
  display.print(bp, 1);
  display.println(" mmHg");
  display.display();
}

void displayMessage(const char *message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}
