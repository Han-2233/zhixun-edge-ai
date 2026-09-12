// 智巡开源：ESP32-C3 RISC-V 传感节点参考固件
// 依赖：ArduinoJson、PubSubClient、DHT sensor library、Adafruit INA219
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

#define DHT_PIN 4
#define DHT_TYPE DHT22
#define SMOKE_PIN 0
#define BUZZER_PIN 10
#define I2C_SDA 8
#define I2C_SCL 9

const char* WIFI_SSID = "YOUR_WIFI";
const char* WIFI_PASSWORD = "YOUR_PASSWORD";
const char* MQTT_HOST = "192.168.1.10";
const char* NODE_ID = "SEN-02";

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);
DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_INA219 ina219;

void connectNetwork() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(MQTT_HOST, 1883);
  while (!mqtt.connected()) mqtt.connect(NODE_ID);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  Wire.begin(I2C_SDA, I2C_SCL);
  dht.begin();
  ina219.begin();
  connectNetwork();
}

void loop() {
  if (!mqtt.connected()) connectNetwork();
  mqtt.loop();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float powerW = ina219.getPower_mW() / 1000.0;
  int smokeRaw = analogRead(SMOKE_PIN);
  bool danger = smokeRaw > 1800 || temperature > 45 || powerW > 30;
  digitalWrite(BUZZER_PIN, danger ? HIGH : LOW); // 断网时同样执行本地告警

  StaticJsonDocument<256> data;
  data["nodeId"] = NODE_ID;
  data["temperature"] = temperature;
  data["humidity"] = humidity;
  data["smokeRaw"] = smokeRaw;
  data["power"] = powerW;
  data["danger"] = danger;
  data["uptime"] = millis();
  char payload[256];
  serializeJson(data, payload);
  mqtt.publish("zhixun/nodes/SEN-02/telemetry", payload, true);
  delay(2000);
}
