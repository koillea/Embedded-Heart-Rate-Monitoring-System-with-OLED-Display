#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

int sensorPin = A0;   // Simulated MAX30102
int ledPin = 13;      // LED for heartbeat
int heartRate;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Simulate reading from sensor
  int sensorValue = analogRead(sensorPin);
  heartRate = map(sensorValue, 0, 1023, 60, 120); // map to 60-120 BPM
  Serial.println(heartRate);

  // Display heart rate on OLED
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Heart Rate:");
  display.setCursor(0,30);
  display.print(heartRate);
  display.print(" BPM");
  display.display();

  // LED blinking in sync with heartbeat
  int beatInterval = 60000 / heartRate; // ms between beats
  digitalWrite(ledPin, HIGH);
  delay(100); // LED on duration
  digitalWrite(ledPin, LOW);
  delay(beatInterval - 100); // wait rest of the beat interval
}
