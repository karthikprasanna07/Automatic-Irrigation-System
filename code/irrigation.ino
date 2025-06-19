#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Replace with your WiFi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// ThingSpeak channel details
const char* server = "api.thingspeak.com";  // ThingSpeak server
const String apiKey = "your_API_KEY";  // Your ThingSpeak Write API Key

// Soil moisture sensor and relay pin
const int moisturePin = A0;  // Soil moisture sensor connected to A0
const int relayPin = D1;     // Relay to control water pump or solenoid valve

// Moisture threshold
int moistureThreshold = 400; // Below this value, water the plants

// Initialize the Wi-Fi connection
void setup() {
  Serial.begin(115200);
  
  // Initialize soil moisture sensor and relay pin
  pinMode(moisturePin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Ensure the pump/valve is off initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}

// Main loop to handle sending data to ThingSpeak and controlling irrigation
void loop() {
  int moistureValue = analogRead(moisturePin);
  Serial.print("Soil Moisture: ");
  Serial.println(moistureValue);

  // Check if soil moisture is below the threshold, activate irrigation
  int irrigationStatus = 0;  // Default irrigation status (OFF)
  if (moistureValue < moistureThreshold) {
    Serial.println("Soil is dry. Watering the plants.");
    digitalWrite(relayPin, HIGH);  // Turn on pump/valve
    irrigationStatus = 1;          // Set irrigation status to ON
  } else {
    Serial.println("Soil moisture is sufficient.");
    digitalWrite(relayPin, LOW);  // Turn off pump/valve
  }

  // Send the soil moisture and irrigation status to ThingSpeak
  sendToThingSpeak(moistureValue, irrigationStatus);
  
  delay(60000);  // Wait for 1 minute before the next reading (adjust as needed)
}

// Function to send data to ThingSpeak
void sendToThingSpeak(int moisture, int irrigation) {
  if (WiFi.status() == WL_CONNECTED) {  // Check WiFi connection
    HTTPClient http;
    WiFiClient client;  // Create a WiFiClient object

    // Construct the URL with parameters to send to ThingSpeak
    String url = "http://api.thingspeak.com/update?api_key=" + apiKey;
    url += "&field1=" + String(moisture);
    url += "&field2=" + String(irrigation);

    // Use the correct method to start the HTTP request with WiFiClient and the URL
    http.begin(client, url);  // Initialize HTTP request with WiFiClient

    int httpCode = http.GET();  // Send GET request

    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak successfully.");
    } else {
      Serial.println("Failed to send data to ThingSpeak.");
    }

    http.end();  // Free resources
  } else {
    Serial.println("WiFi not connected.");
  }
}
