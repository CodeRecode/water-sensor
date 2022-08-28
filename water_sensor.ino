#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <WifiPass.h>

extern char ssid[];
extern char pass[];
extern char broker[];

int port = 1883;
const char topic[] = "abc";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {  }
  
  WiFi.begin(ssid, pass);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  
  Serial.println("MQTT connection succes!");
  mqttClient.beginMessage(topic);
  mqttClient.print("Hello from water_sensor");
  mqttClient.endMessage();
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
