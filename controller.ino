#include <ETH.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* test_host = "https://authentic-policy-alarm.vercel.app/beacon";
const uint16_t test_port = 80;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize Ethernet
  ETH.begin();

  // Wait for the Ethernet link to come up
  Serial.print("Waiting for Ethernet...");
  while (!ETH.linkUp()) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Ethernet connected!");

  // Set pins as outputs
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  HTTPClient http;

  http.begin(test_host); // Specify the URL
  int httpCode = http.GET(); // Make the request

  if (httpCode > 0) { // Check for the returning code
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);

    // If the payload is "yes", perform the sequence
    if (payload == "yes") {
      // Turn on pin 14
      digitalWrite(14, HIGH);

      // Beep pin 12 on and off thrice in 1 second
      for (int i = 0; i < 3; i++) {
        digitalWrite(12, HIGH);
        delay(150); // On for 150ms
        digitalWrite(12, LOW);
        delay(200); // Off for 200ms (total 350ms for one cycle)
      }

      // Keep pin 14 on for 3950 more ms
      delay(3950);

      // Turn off pin 14 after the total 5 seconds
      digitalWrite(14, LOW);
    }

  } else {
    Serial.println("Error on HTTP request");
  }
  http.end(); // Free the resources

  delay(5000); // 5s delay so we are not reading same state twice
}
