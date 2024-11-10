/*

1. Wiring the Components
MQ3 Sensor

VCC: Connect to VIN on the NodeMCU.
GND: Connect to GND on the NodeMCU.
AO (Analog Output): Connect to A0 on the NodeMCU.
Buzzer

Positive Lead: Connect to D2 (GPIO 4) on the NodeMCU.
Negative Lead: Connect to GND on the NodeMCU.
Relay Module

VCC: Connect to 3.3V on the NodeMCU.
GND: Connect to GND on the NodeMCU.
IN: Connect to D1 (GPIO 5) on the NodeMCU.
*/


#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

#define MQ3_PIN A0      // Analog pin connected to MQ3 sensor
#define BUZZER_PIN D2   // Digital pin connected to buzzer
#define RELAY_PIN D1    // Digital pin connected to relay

// Define threshold for alcohol detection
#define ALCOHOL_THRESHOLD 700

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize buzzer and relay pins as outputs
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Turn off buzzer and relay initially
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  // Read the analog value from the MQ3 sensor
  int sensorValue = analogRead(MQ3_PIN);

  // Print the sensor value to the Serial Monitor
  Serial.print("Alcohol Sensor Value: ");
  Serial.println(sensorValue);
  Blynk.virtualWrite(V0, sensorValue);
  // Check if the sensor value exceeds the threshold
  if (sensorValue > ALCOHOL_THRESHOLD) {
    // Alcohol level is high
    Serial.println("Alcohol detected. Buzzer ON, Relay OFF.");
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
    digitalWrite(RELAY_PIN, LOW);   // Turn off relay
    Blynk.virtualWrite(V1, 1);
  } else {
    // Alcohol level is low
    Serial.println("No alcohol detected. Buzzer OFF, Relay ON.");
    digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
    digitalWrite(RELAY_PIN, HIGH);  // Turn on relay
    Blynk.virtualWrite(V1, 0);
  }

  // Add a delay between readings
  delay(1000); // 1 second
}

