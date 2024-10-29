#include <DHT11.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Matter.h>
#include <MatterTemperature.h>
#include <MatterIlluminance.h>
#include <MatterAirQuality.h>
#include <MatterPressure.h>
#include <MatterHumidity.h>

// Define LED pins
const int RED_LED_PIN = 7;
const int GREEN_LED_PIN = 8;
const int BLUE_LED_PIN = 9;

// Define LDR pin
const int LDR_PIN = A0;

// Define MICS-6814 sensor pins
const int CO_PIN = A1;
const int NO2_PIN = A2;
const int NH3_PIN = A3;

// Define BMP280 sensor
Adafruit_BMP280 bmp; // I2C

// // Define DHT11 Pin
// const int H_PIN = 3;
// DHT dht(H_PIN, DHT11);
DHT11 dht11(3);



MatterTemperature matter_temp_sensor;
MatterIlluminance matter_illuminance_sensor;
MatterAirQuality matter_air_quality_sensor;
MatterPressure matter_pressure_sensor;
MatterHumidity matter_humidity_sensor;

void decommission_handler()
{
  if (digitalRead(BTN_BUILTIN) == LOW) {  // Push button pressed
    int startTime = millis();
    while (digitalRead(BTN_BUILTIN) == LOW) {
      int elapsedTime = (millis() - startTime) / 1000.0;
      if (elapsedTime > 10) {
        Serial.printf("Decommissioning!\n");
        for (int i = 0; i < 10; i++) {
          digitalWrite(LEDR, !(digitalRead(LEDR)));
          delay(100);
        }
        if (!Matter.isDeviceCommissioned()) {
          Serial.println("Decommission done!");
          digitalWrite(LEDR, LOW);
        } else {
          Serial.println("Matter device is commissioned-> Starting Decommission process");
          nvm3_eraseAll(nvm3_defaultHandle);  // Decommission command
          digitalWrite(LED_BUILTIN, LOW);
          Serial.println("Decommission done!");
        }
        break;
      }
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Matter.begin();
  matter_temp_sensor.begin();
  matter_illuminance_sensor.begin();
  matter_air_quality_sensor.begin();
  matter_pressure_sensor.begin();
  matter_humidity_sensor.begin();

  Serial.println("Plant Monitoring System");

  decommission_handler();

  if (!Matter.isDeviceCommissioned()) {
    Serial.println("Matter device is not commissioned");
    Serial.println("Commission it to your Matter hub with the manual pairing code or QR code");
    Serial.printf("Manual pairing code: %s\n", Matter.getManualPairingCode().c_str());
    Serial.printf("QR code URL: %s\n", Matter.getOnboardingQRCodeUrl().c_str());
  }
  while (!Matter.isDeviceCommissioned()) {
    delay(200);
  }

  Serial.println("Waiting for Thread network...");
  while (!Matter.isDeviceThreadConnected()) {
    delay(200);
  }
  Serial.println("Connected to Thread network");

  Serial.println("Waiting for Matter device discovery...");
  while (!matter_temp_sensor.is_online() || !matter_illuminance_sensor.is_online() || !matter_air_quality_sensor.is_online() || !matter_pressure_sensor.is_online() || !matter_humidity_sensor.is_online()) {
    delay(200);
  }
  Serial.println("Matter device is now online");

  // Initialize LED pins
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // Initialize BMP280 sensor
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  // Initialize DHT11 sensor
  // dht.begin();
}

void loop()
{
  // Read BMP280 sensor values
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // Convert to hPa
  float humidity = dht11.readHumidity();
  // Print BMP280 sensor values
  Serial.printf("Temperature: %.02f C\n", temperature);
  Serial.printf("Pressure: %.02f hPa\n", pressure);
  Serial.printf("Humidity: %.02f %\n", humidity);
  // Control LEDs based on BMP280 temperature


  // Read LDR value and calculate illuminance
  int ldr_value = analogRead(LDR_PIN);
  Serial.printf("Raw LDR Value: %d\n", ldr_value);  // Debug statement to print raw LDR value
  float voltage = ldr_value * (5.0 / 1023.0);
  Serial.printf("LDR Voltage: %.02f V\n", voltage);

  // Convert LDR value to illuminance (lux)
  // Note: This conversion depends on your specific LDR and circuit. Adjust the formula as needed.
  float illuminance = (ldr_value / 1023.0) * 1000; // Example conversion

  // Print illuminance value
  Serial.printf("Illuminance: %.02f lux\n", illuminance);

  // Update Matter temperature sensor with BMP280 temperature
  matter_temp_sensor.set_measured_value_celsius(temperature);

  // Update Matter illuminance sensor with LDR illuminance
  matter_illuminance_sensor.set_measured_value_lux(illuminance);

  // Read DHT11 sensor value
  
  //float humidity_value = DHT.read(DHT11PIN);

  // Print DHT11 sensor value
  //Serial.printf("Humidity: %.02f %%\n", DHT11.humidity);

  // Update Matter humidity sensor with DHT11 humidity
  matter_humidity_sensor.set_measured_value(humidity);

  // Control Red LED based on illuminance
  

  if (temperature < 23) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
  } else if (humidity < 20){
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
  }
  else{
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
  }

  // Read MICS-6814 sensor values
  int co_value = analogRead(CO_PIN);
  int no2_value = analogRead(NO2_PIN);
  int nh3_value = analogRead(NH3_PIN);

  // Print MICS-6814 sensor values
  Serial.printf("CO Value: %d\n", co_value);
  Serial.printf("NO2 Value: %d\n", no2_value);
  Serial.printf("NH3 Value: %d\n", nh3_value);

  // Calculate air quality index (example calculation, adjust as needed)
  int air_quality_value = (co_value + no2_value + nh3_value) / 3;

  // Handle air quality value
  if ((air_quality_value > 0) && (air_quality_value < 50)) {
    matter_air_quality_sensor.set_air_quality(MatterAirQuality::AirQuality_t::GOOD);
    Serial.println("Current air quality: good");
  } else if (air_quality_value < 100) {
    matter_air_quality_sensor.set_air_quality(MatterAirQuality::AirQuality_t::FAIR);
    Serial.println("Current air quality: fair");
  } else if (air_quality_value < 200) {
    matter_air_quality_sensor.set_air_quality(MatterAirQuality::AirQuality_t::MODERATE);
    Serial.println("Current air quality: moderate");
  } else if (air_quality_value < 300) {
    matter_air_quality_sensor.set_air_quality(MatterAirQuality::AirQuality_t::POOR);
    Serial.println("Current air quality: poor");
  } else if (air_quality_value < 400) {
    matter_air_quality_sensor.set_air_quality(MatterAirQuality::AirQuality_t::VERY_POOR);
    Serial.println("Current air quality: very poor");
  } else if (air_quality_value < 500) {
    matter_air_quality_sensor.set_air_quality(MatterAirQuality::AirQuality_t::EXTREMELY_POOR);
    Serial.println("Current air quality: extremely poor");
  } else if (air_quality_value > 500) {
    matter_air_quality_sensor.set_air_quality(MatterAirQuality::AirQuality_t::UNKNOWN);
    Serial.println("Current air quality: unknown");
  } else {
    matter_air_quality_sensor.set_air_quality(MatterAirQuality::AirQuality_t::UNDEFINED_VALUE);
    Serial.println("Current air quality: undefined value");
  }

  // Update Matter pressure sensor with BMP280 pressure
  matter_pressure_sensor.set_measured_value(pressure);

  delay(2000);
}