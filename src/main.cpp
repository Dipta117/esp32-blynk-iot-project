/*************************************************************
  ESP32 Smart Monitoring System with Blynk
  Simple Button Control - LED ON/OFF Only
*************************************************************/

#define BLYNK_TEMPLATE_ID "TMPL3HHqv9_dZ"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "9MR5YEkNZzbCfDTk-7dMXeP_2chTxvg8"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi credentials - FOR WOKWI SIMULATION
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// DHT Sensor
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LED Pin
#define LED_PIN 23

BlynkTimer timer;

// Connection status
bool blynkConnected = false;
bool ledState = false;

// Sensor data
float temperature = 25.0;
float humidity = 50.0;
unsigned long dataCounter = 0;

// =============================================
// BLYNK READ OPERATIONS (Mobile App → ESP32)
// =============================================

// READ from Blynk Button - Virtual Pin V0
BLYNK_WRITE(V0)
{
  if (!blynkConnected) return;
  
  int buttonState = param.asInt();  // READING from app
  
  if (buttonState == HIGH) {
    digitalWrite(LED_PIN, HIGH);  // Turn LED ON
    ledState = true;
    Serial.println("📱 READ from App: Button V0 - ON | LED: 🔴 ON");
    Blynk.virtualWrite(V1, "LED Status: ON");  // WRITE status back
  } 
  else {
    digitalWrite(LED_PIN, LOW);   // Turn LED OFF
    ledState = false;
    Serial.println("📱 READ from App: Button V0 - OFF | LED: ⚪ OFF");
    Blynk.virtualWrite(V1, "LED Status: OFF"); // WRITE status back
  }
}

// =============================================
// BLYNK WRITE OPERATIONS (ESP32 → Mobile App)
// =============================================

void sendSensorData()
{
  if (!blynkConnected) return;
  
  dataCounter++;
  
  // Generate realistic sensor data for simulation
  temperature = 22.0 + (sin(dataCounter * 0.1) * 8.0) + (random(0, 30) / 10.0);
  if (temperature < 20.0) temperature = 20.0;
  if (temperature > 35.0) temperature = 35.0;
  
  humidity = 50.0 + (cos(dataCounter * 0.08) * 20.0) + (random(0, 20) / 10.0);
  if (humidity < 30.0) humidity = 30.0;
  if (humidity > 80.0) humidity = 80.0;

  // WRITE to Blynk app
  Blynk.virtualWrite(V2, temperature);  // WRITE Temperature to V2
  Blynk.virtualWrite(V3, humidity);     // WRITE Humidity to V3
  
  Serial.print("📤 WRITE to App: ");
  Serial.print("Temp: ");
  Serial.print(temperature, 1);
  Serial.print("°C | Hum: ");
  Serial.print(humidity, 1);
  Serial.println("%");
}

// =============================================
// BLYNK EVENT HANDLERS
// =============================================

BLYNK_CONNECTED()
{
  blynkConnected = true;
  Serial.println();
  Serial.println("🎉 SUCCESS: Connected to Blynk Server!");
  Serial.println("🔄 Syncing data from Blynk app...");
  
  // Sync button state from app
  Blynk.syncVirtual(V0);
  
  Serial.println("✅ Data synced successfully!");
  Blynk.virtualWrite(V1, "System Online - Ready!");
}

BLYNK_DISCONNECTED()
{
  blynkConnected = false;
  Serial.println("❌ WARNING: Disconnected from Blynk!");
}

// =============================================
// SETUP & LOOP
// =============================================

void setup()
{
  Serial.begin(115200);
  delay(1000);
  
  // Initialize components
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Start with LED OFF
  
  Serial.println();
  Serial.println("==========================================");
  Serial.println("   ESP32 Smart Monitoring System");
  Serial.println("   Simple Button Control - LED ON/OFF");
  Serial.println("==========================================");
  Serial.println();

  // Connect to WiFi
  Serial.print("📶 Connecting to WiFi...");
  WiFi.begin(ssid, pass);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 15) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" ✅ CONNECTED");
    Serial.print("📡 IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(" ❌ FAILED");
  }

  // Connect to Blynk
  Serial.println("☁️  Connecting to Blynk Server...");
  Blynk.config(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);
  Blynk.connect(5000);

  // Setup timer for sensor data
  timer.setInterval(2000L, sendSensorData);

  Serial.println();
  Serial.println("✅ System Ready!");
  Serial.println("👉 Press button in Blynk app to control LED");
  Serial.println("==========================================");
  Serial.println();
}

void loop()
{
  Blynk.run();
  timer.run();
}