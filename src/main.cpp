#include <ESP8266WiFi.h>
#include <SimpleDHT.h>

constexpr char SSID[] = "YOUR_SSID";
constexpr char PASS[] = "PASSWORD";
const IPAddress HOST(192,168,1,13); // IP python server is listening on
constexpr int PORT = 8000; // Port server is active on
constexpr int DHT11_PIN = 2;
SimpleDHT11 dht11;
WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  if(client.connect(HOST, PORT))
  {
    byte temperature = 0;
    byte humidity = 0;
    if (dht11.read(DHT11_PIN, &temperature, &humidity, nullptr)) {
        Serial.println("Read DHT11 failed.");
    }

    String payload = "t=";
    payload += temperature;
    payload += "&h=";
    payload += humidity;

    client.flush();
    client.printf("POST / HTTP/1.1\nHost: %s\nContent-Type: application/x-www-form-urlencoded\nContent-Length: %d\n\n%s",
                   HOST.toString().c_str(),
                   payload.length(),
                   payload.c_str());
    delay(1);
  }
  delay(30000);
}